#ifndef CONDUIT_CONFIG_HPP
#define CONDUIT_CONFIG_HPP
#include <cstddef>

namespace conduit::config {
    #define CONDUIT_ALIGN_16 alignas(16)
    #define CONDUIT_ALIGN_64 alignas(64)

    using precision_type = float;

    constexpr precision_type TARGET_FRAME_RATE  = precision_type(60.0);
    constexpr precision_type FIXED_TIME_STEP    = precision_type(1.0) / TARGET_FRAME_RATE;
    
    constexpr size_t MAX_GAMEPADS = 4; 

    constexpr size_t KEYBOARD_KEY_COUNT     = 512;
    constexpr size_t MOUSE_BUTTON_COUNT     = 8;
    constexpr size_t GAMEPAD_BUTTON_COUNT   = 32;
    constexpr size_t GAMEPAD_AXIS_COUNT     = 16;

} // namespace conduit

#endif // CONDUIT_CONFIG_HPP