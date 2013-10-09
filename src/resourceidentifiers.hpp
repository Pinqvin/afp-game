/// All the resource identifiers are defined here
///
/// All the enumerative types to identify different resources
/// are described here

#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

/// Forward declare sf::Texture
namespace sf
{
    class Texture;

}

namespace AFP
{
    namespace Textures
    {
        enum ID
        {
            Player,
            Enemy,
            Desert

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

}

#endif // RESOURCEIDENTIFIERS_HPP

