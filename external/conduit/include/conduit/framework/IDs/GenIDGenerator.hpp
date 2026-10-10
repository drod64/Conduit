#ifndef CONDUIT_GEN_ID_GENERATOR_HPP
#define CONDUIT_GEN_ID_GENERATOR_HPP
#include <conduit/framework/IDs/GenID.hpp>
#include <conduit/core/containers/vector.hpp>

namespace conduit {
template <typename Category, typename IDType = uint32, uint32 IndexBits = 20>
class GenIDGenerator {
private:
    using packed_type       = IDType;
    using index_type        = packed_type;
    using generation_type   = packed_type;
    using size_type         = sizet;

    static constexpr uint32 TOTAL_BITS =
        std::numeric_limits<packed_type>::digits;
    static_assert(std::is_unsigned_v<packed_type>,
        "IDType must be an unsigned integer");
    static_assert(IndexBits > 0 && IndexBits < TOTAL_BITS,
        "IndexBits must leave room for generation bits");
    static_assert(IndexBits < std::numeric_limits<size_type>::digits,
        "IndexBits must be smaller than the number of bits in sizet");
    static_assert(IndexBits <= std::numeric_limits<index_type>::digits,
        "IndexBits exceeds index_type capacity");
        
    static constexpr uint32 GENERATION_BITS =
        TOTAL_BITS - IndexBits;
    static_assert(GENERATION_BITS <= std::numeric_limits<generation_type>::digits,
        "GenerationBits exceeds generation_type capacity");

    static constexpr packed_type INDEX_MASK =
        (packed_type{1} << IndexBits) - packed_type{1};
    static constexpr size_type MAX_CAPACITY =
        (size_type{1} << IndexBits) - size_type{1};

    static constexpr packed_type GENERATION_MASK =
        (packed_type{1} << GENERATION_BITS) - packed_type{1};
    static constexpr packed_type RETIRED_GENERATION =
        GENERATION_MASK + packed_type{1};

    vector<generation_type> m_generations{};
    vector<index_type>      m_free_indices{};

    static constexpr GenID<Category, IDType> pack(index_type index, generation_type generation);

    static constexpr index_type getIndex(packed_type id);
    
    static constexpr generation_type getGeneration(packed_type id);

public:
    GenIDGenerator();
    ~GenIDGenerator() = default;
    
    GenIDGenerator(const GenIDGenerator &other) = delete;
    GenIDGenerator operator= (const GenIDGenerator &other) = delete;

    GenIDGenerator(GenIDGenerator &&other) noexcept;
    GenIDGenerator& operator= (GenIDGenerator &&other) noexcept;

    GenID<Category, IDType> createID();

    void destroyID(GenID<Category, IDType> id);

    bool isValid(GenID<Category, IDType> id) const;
    
    void setGeneration(sizet index, generation_type generation);
}; // class GenIDGenerator
} // namespace conduit

// Implementation

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline constexpr conduit::GenID<Category, IDType> conduit::GenIDGenerator<Category, IDType, IndexBits>::pack(index_type index, generation_type generation)
{
    assert(index <= INDEX_MASK);
    assert(generation <= GENERATION_MASK);

    return {(generation << IndexBits) | index};
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline constexpr conduit::GenIDGenerator<Category, IDType, IndexBits>::index_type conduit::GenIDGenerator<Category, IDType, IndexBits>::getIndex(packed_type id)
{
    return (id & INDEX_MASK);
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline constexpr conduit::GenIDGenerator<Category, IDType, IndexBits>::generation_type conduit::GenIDGenerator<Category, IDType, IndexBits>::getGeneration(packed_type id)
{
    return (id >> IndexBits) & GENERATION_MASK; 
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline conduit::GenIDGenerator<Category, IDType, IndexBits>::GenIDGenerator()
{
    m_generations.push_back(0);
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline conduit::GenIDGenerator<Category, IDType, IndexBits>::GenIDGenerator(GenIDGenerator &&other) noexcept
{
    m_generations = std::move(other.m_generations);
    m_free_indices = std::move(other.m_free_indices);
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline conduit::GenIDGenerator<Category, IDType, IndexBits>& conduit::GenIDGenerator<Category, IDType, IndexBits>::GenIDGenerator::operator=(GenIDGenerator &&other) noexcept
{
    if (this != &other)
    {
        m_generations = std::move(other.m_generations);
        m_free_indices = std::move(other.m_free_indices);
    }

    return *this;
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline conduit::GenID<Category, IDType> conduit::GenIDGenerator<Category, IDType, IndexBits>::createID()
{
    index_type index{};

    if (!m_free_indices.empty())
    {
        index = m_free_indices.back();
        m_free_indices.pop_back();
    }
    else
    {
        if (m_generations.size() - 1 >= MAX_CAPACITY)
            return GenID<Category, IDType>::INVALID;

        index = static_cast<index_type>(m_generations.size());
        m_generations.push_back(0);
    }

    return pack(index, m_generations[index]);
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline void conduit::GenIDGenerator<Category, IDType, IndexBits>::destroyID(GenID<Category, IDType> id)
{
    if (!isValid(id))
        return;

    index_type index = getIndex(id.value);

    if (m_generations[index] == GENERATION_MASK)
    {
        m_generations[index] = RETIRED_GENERATION;
        return;
    }

    ++m_generations[index];
    m_free_indices.push_back(index);
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
inline bool conduit::GenIDGenerator<Category, IDType, IndexBits>::isValid(GenID<Category, IDType> id) const
{
    // Invalid IDs have index == 0 and generation == 0.
    if (id == GenID<Category, IDType>::INVALID) return false;

    // Calculate index and generation.
    index_type index = getIndex(id.value);
    generation_type generation = getGeneration(id.value);

    // Check if index is in bounds. (index 0 is reserved and thus treated inaccesible).
    if (index == 0 || index >= m_generations.size()) return false;

    // Check if stored generation equals calculated generation.
    return m_generations[index] == generation;
}

template <typename Category, typename IDType, conduit::uint32 IndexBits>
void conduit::GenIDGenerator<Category, IDType, IndexBits>::setGeneration(sizet index, generation_type generation)
{
    assert(index < m_generations.size());
    m_generations[index] = generation;
}

#endif // CONDUIT_GEN_ID_GENERATOR_HPP