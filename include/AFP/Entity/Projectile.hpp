/// This is the class for the projectile entity
///
/// Projectiles are fast moving dynamic objects

#pragma once

#include "AFP/Entity/Entity.hpp"
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
    class Projectile : public Entity
    {
    public:

        /// Projectile type
        ///
        ///
        enum Type
        {
            Bullet
        };

        /// Constructor
        ///
        ///
        Projectile(Type type, const TextureHolder& textures);

        /// Draw projectile sprite
        ///
        ///
        virtual void drawCurrent(sf::RenderTarget& target,
            sf::RenderStates states) const;

        /// Update projectile
        ///
        ///
        virtual void updateCurrent(sf::Time dt, 
            CommandQueue& commands);

        /// Creates a projectile
        ///
        /// Create a projectile based on projectile type.
        void createProjectile(b2World* world, float posX, float posY, Type type);

    private:

        /// Tile type
        ///
        ///
        Type mType;

        /// Tile sprite
        ///
        ///
        sf::Sprite mSprite;

    };
}
