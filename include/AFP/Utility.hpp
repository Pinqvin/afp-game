/// Utility functions

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <string>
#include <sstream>

// Forward declaration
namespace sf
{
    class Sprite;
    class Text;

}

namespace AFP
{
    class Animation;

    /// Centers a sprite to its origin
    void centerOrigin(sf::Sprite& sprite);

    /// Centers an animation to its origin
    void centerOrigin(Animation& animation);

    /// Centers a text to its origin
    void centerOrigin(sf::Text& text);

    // Since std::to_string doesn't work on MinGW we have to implement
    // our own to support all platforms.
    template <typename T>
    std::string	toString(const T& value);

    /// Changes sf::Keyboard::Key to string
    std::string toString(sf::Keyboard::Key key);

    /// Changes sf::Mouse::Button to string
    std::string toString(sf::Mouse::Button button);

    /// Pixel to meter ratio
    const float PTM_RATIO = 16.f;

    /// Time per frame. Fixed to 60fps
    const float UPDATE_PER_FRAME = 1.f / 60.f;

    /// Camera speed
    const float CAMERA_SPEED = 20.f;

    /// Gravity
    const float GRAVITY = 90.8f;

}

