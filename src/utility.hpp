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

    const float PTM_RATIO = 16;

}

