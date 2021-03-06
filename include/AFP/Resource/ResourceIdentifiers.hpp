/// All the resource identifiers are defined here
///
/// All the enumerative types to identify different resources
/// are described here

#pragma once

#include <string>

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
            TelepoliceStopped,
            TelepoliceRunning,
            TelepoliceDying,
            Droid,
            TitleScreen,
            Box16,
            Box16Destroy,
            Box16Coin,
            Box16CoinDestroy,
            Box16Orb,
            Box16OrbDestroy,
            Box32,
            Box32Destroy,
            Bullet,
            Coin,
            Orb,
            ButtonNormal,
            ButtonSelected,
            ButtonPressed,
            Particle,
            PlayerStopped,
            PlayerRunning,
            PlayerJumping,
            PlayerFalling,
            PlayerDying,
            HpBar,
            TeleBar,
            GunIcons,
            Arrow,
            Crosshair,
            Barrel,
            Explosion,
            Medkit,
            CoinIcon,
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

    typedef ResourceHolder<sf::Texture, std::string> TextureHolder;
    typedef ResourceHolder<sf::Font, std::string> FontHolder;

}

