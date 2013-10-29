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
            Bullet,
            Shot,
            Laser,
            TypeCount
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

        /// Get category
        ///
        /// Return Projectile
        virtual unsigned int getCategory() const;

        /// Creates a projectile
        ///
        /// Create a projectile based on projectile type.
        void createProjectile(b2World* world, float posX, float posY, sf::Vector2f target, bool friendly);

        /// Get damage
        ///
        /// Return projectile damage
        int getDamage();

    private:
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

        /// Is projectile friendly
        ///
        /// Set to true if projectile is friendly.
        bool mFriendly;

    };
}
