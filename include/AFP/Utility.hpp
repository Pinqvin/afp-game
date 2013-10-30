/// Utility functions

#pragma once

// Forward declaration
namespace sf
{
    class Sprite;
    class Text;

}

namespace AFP
{
    /// Centers a sprite to its origin
    void centerOrigin(sf::Sprite& sprite);

    /// Centers a text to its origin
    void centerOrigin(sf::Text& text);

    /// Pixel to meter ratio
    const float PTM_RATIO = 16.f;

    /// Time per frame. Fixed to 60fps
    const float UPDATE_PER_FRAME = 1.f / 60.f;

    /// Camera speed
    const float CAMERA_SPEED = 20.f;

    /// Gravity
    const float GRAVITY = 90.8f;

}

