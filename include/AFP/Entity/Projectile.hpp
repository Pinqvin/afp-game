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

        /// Get body type
        ///
        /// Return ProjectileBody
        AFP::BodyType getEntityType();

        /// Creates a projectile
        ///
        /// Create a projectile based on projectile type.
        void createProjectile(b2World* world, float posX, float posY, sf::Vector2f target, Type type);

    private:

        /// Projectile contact
        ///
        /// Called when projectile comes in contact with
        /// something.
        void startContact();

        /// Tile type
        ///
        ///
        Type mType;

        /// Tile sprite
        ///
        ///
        sf::Sprite mSprite;

        /// Projectile target
        ///
        /// Projectile moves towards this.
        b2Vec2 mTarget;

    };
}
