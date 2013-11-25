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
            Enemy,
            TypeCount

        };

        enum WeaponType
        {
            Pistol,
            Machinegun,
            Shotgun,
            WeaponTypeCount
        };

        enum CharacterState
        {
            Stopped,
            Running,
            Jumping,
            Falling,
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

        ///
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

        /// Character can jump
        ///
        /// set mCanJump to true
        void startFootContact();

        /// Character can't jump
        ///
        /// set mCanJump to false
        void endFootContact();

        /// Return true if marked for removal
        ///
        ///
        bool isMarkedForRemoval();

        /// Recharge teleport
        ///
        ///
        void recharge(int points);

        /// Set new target
        ///
        ///
        void newTarget(Character& target);

        /// Remove target
        ///
        ///
        void noTarget();

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

        /// Is marked for removal
        ///
        /// Set to true when character can be removed from the game.
        bool mIsMarkedForRemoval;

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
        
        /// Stopped animation
        ///
        /// Animation to be used when the character is stopped
        Animation mStopped;

        /// Running animation
        ///
        /// Animation to be used when the character is moving
        Animation mRunning;

        /// Jumping animation
        ///
        /// Animation to be used when the character is jumping
        Animation mJumping;

        /// Falling animation
        ///
        /// Animation to be used when the character is falling
        Animation mFalling;

        std::vector<Animation> mAnimations;

        /// Character state
        ///
        ///
        CharacterState mState;

    };

}

