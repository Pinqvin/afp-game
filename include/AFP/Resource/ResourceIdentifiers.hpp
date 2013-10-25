/// All the resource identifiers are defined here
///
/// All the enumerative types to identify different resources
/// are described here

#pragma once

/// Forward declare sf::Texture
namespace sf
{
    class Texture;
    class Font;

}

namespace AFP
{
    namespace Textures
    {
        enum ID
        {
            Player,
            Enemy,
            Desert,
            TitleScreen,
            GrassTile,
            Bullet,
            Coin
        };

    }

    namespace Fonts
    {
        enum ID
        {
            Debug

        };

    }



    /// Forward declaration and a few type definitions
    template <typename Resource, typename Identifier>
    class ResourceHolder;

    typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
    typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

}
