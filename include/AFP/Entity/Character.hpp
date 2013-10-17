/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Projectile.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
    class Character : public Entity
    {
    public:
        /// Character type
        ///
        ///
        enum Type
        {
            Player,
            Enemy

        };

        /// Constructor
        ///
        ///
        Character(Type type, const TextureHolder& textures);

        /// Return character category
        ///
        /// Returns the character category based on the type
        virtual unsigned int getCategory() const;

        /// Create character in Box2D world
        ///
        /// Create character body based on type
        void createCharacter(b2World* world, float posX, float posY);

        /// Move character
        ///
        /// Move character along horizontal axis
        void moveHorizontal(float vx);

        /// Jump
        ///
        /// Make character jump
        void jump();

        /// Fire
        ///
        /// Sets mIsFiring true so shooting
        /// will happen
        void fire(sf::Vector2f target);

        /// Teleport
        ///
        /// Setis mIsTeleporting true
        void teleport(sf::Vector2f target);

        /// Set mouse translation
        ///
        /// Mouse translation is used in converting
        /// view coordinates to world coordinates
        void setMouseTranslation(sf::Vector2f translation);

    private:
        /// Draw character sprite
        ///
        ///
        virtual void drawCurrent(sf::RenderTarget& target,
            sf::RenderStates states) const;

        /// Update character
        ///
        ///
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

        /// Check projectile launch
        ///
        /// Contains cooldown calculation for firing.
        void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

        /// Create bullets
        ///
        /// Creates many projectiles
        void createBullets(SceneNode& node, const TextureHolder& textures);

        /// Create projectile
        ///
        /// Creates a projectile and links it to this node
        void createProjectile(SceneNode& node, 
            Projectile::Type type, float xOffset, 
            float yOffset, const TextureHolder& textures);

        /// Teleport character
        ///
        /// Moves character to target position
        void teleportCharacter(SceneNode& node,
            const TextureHolder& textures);

    private:
        /// Character type
        ///
        ///
        Type mType;

        /// Character sprite
        ///
        ///
        sf::Sprite mSprite;

        /// Jump Strength
        ///
        /// Increasing will make character
        /// jump higher
        float mJumpStrength;

        /// Command for firing
        ///
        ///
        Command mFireCommand;

        /// Command for teleporting
        ///
        ///
        Command mTeleportCommand;

        /// Is character firing
        ///
        /// Marked true if firing
        bool mIsFiring;

        /// Is character teleporting
        ///
        ///
        bool mIsTeleporting;

        /// Teleporting target
        ///
        /// Target position to teleport
        b2Vec2 mTeleportTarget;

        /// Firing angle
        /// 
        /// Bullets are shot in this direction.
        /// Updated everytime fire command is called.
        sf::Vector2f mFireTarget;

        /// Mouse translation
        ///
        /// Used to correct the position from view
        /// to world
        sf::Vector2f mMouseTranslation;

        ///  
        ///
        /// Firing cooldown
        sf::Time mFireCountdown;

        ///
        ///
        /// Firing rate
        int mFireRateLevel;

    };

}

