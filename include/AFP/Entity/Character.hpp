/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Projectile.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Sound/SoundPlayer.hpp>
#include <AFP/Animation/Animation.hpp>

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
            Telepolice,
            Droid,
            TypeCount

        };

        enum WeaponType
        {
            Pistol,
            Shotgun,
            Machinegun,
            WeaponTypeCount
        };

        enum CharacterState
        {
            Stopped,
            Running,
            Jumping,
            Falling,
            Dying,
            StateCount
        };

        /// Constructor
        ///
        ///
        Character(Type type, const TextureHolder& textures);

        /// Return character category
        ///
        /// Returns the character category based on the type
        virtual unsigned int getCategory() const;

        /// Is character ready to be removed
        ///
        /// Returns true when character is destroyed and
        /// death animation has finished.
        virtual bool isMarkedForRemoval() const;

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

        /// Play a sound
        ///
        ///
        void playLocalSound(CommandQueue& commands, SoundEffect::ID effect);

        /// Teleport
        ///
        /// Setis mIsTeleporting true
        void teleport(sf::Vector2f target);

        /// Set mouse translation
        ///
        /// Mouse translation is used in converting
        /// view coordinates to world coordinates
        void setMouseTranslation(sf::Vector2f translation);

        /// Mouse position
        ///
        /// Mouse position is used when rotating character
        void setMousePosition(sf::Vector2f position);

        /// Character can jump
        ///
        /// set mCanJump to true
        void startFootContact();

        /// Character can't jump
        ///
        /// set mCanJump to false
        void endFootContact();

        /// Enemy must jump
        ///
        ///
        void startJumpContact();

        /// Enemy doesn't have to jump
        ///
        ///
        void endJumpContact();

        /// Recharge teleport
        ///
        /// Return false if already full
        bool recharge(int points);

        /// Set new target
        ///
        ///
        void newTarget(Character& target);

        ///
        ///
        /// sets boolean mTargetInVision to false
        void targetOutOfVision();

        /// Remove target
        ///
        ///
        void noTarget();

        /// Get teleport charge amount
        ///
        ///
        int getTeleCharge();

        /// Damage entity
        ///
        /// Decreases hitpoints
        virtual void damage(int points);

        /// Change weapon
        ///
        /// Change currently equipped weapon
        void changeWeapon(WeaponType weapon);

        ///
        ///
        /// Return weapon type
        WeaponType getWeapon() const;

        ///
        ///
        /// Return mouse position
        sf::Vector2f getMousePosition() const;

        /// Ray cast
        ///
        /// Do a ray cast between points from and to
        /// Returns false if there is a Category::Scene
        /// object in the way.
        bool isInLineOfSight(sf::Vector2f from, sf::Vector2f to);

        ///
        ///
        /// Add 1 coin
        void addCoin();

        ///
        ///
        /// Get coins
        int getCoins() const;

        ///
        ///
        /// Winning condition
        bool hasWon();

        ///
        ///
        /// Set win flag true
        void win();

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

        /// Is character friendly
        ///
        /// Returns true if character is friendly
        bool isFriendly() const;

    private:
        /// Character type
        ///
        ///
        Type mType;

        /// Weapon type
        ///
        ///
        WeaponType mWeaponType;

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

        /// Mouse position
        ///
        ///
        sf::Vector2f mMousePosition;

        ///
        ///
        /// Firing cooldown
        sf::Time mFireCountdown;

        ///
        ///
        /// Teleport cooldown
        sf::Time mTeleportCountdown;

        ///
        ///
        /// Is the character on the ground?
        int mFootContacts;

        ///
        ///
        /// Does the enemy have to jump?
        int mJumpContacts;

        /// Teleport charge
        ///
        /// Teleport charge decreases when teleporting
        /// and increases over time and when picking up
        /// charges
        /// Only entities with charge over zero can teleport
        int mTeleCharge;

        /// Weapon recoil
        ///
        /// Used to calculate recoil
        float mRecoil;

        /// Target
        ///
        /// Target to shoot at
        Character* mTarget;

        /// Target in vision
        ///
        /// Returns true if mTarget is in the vision sensor
        bool mTargetInVision;

        /// Character animations
        ///
        ///
        std::vector<Animation> mAnimations;

        /// Character state
        ///
        ///
        CharacterState mState;

        ///
        ///
        /// Amount of coins
        int mCoins;

        ///
        ///
        /// Winning condition
        bool mHasWon;

    };

}

