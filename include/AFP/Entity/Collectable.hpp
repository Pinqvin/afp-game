/// This is the class for collectable objects in the game
///
/// Collectables are static box2d sensor objects

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Animation/Animation.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
    class Collectable : public Entity
    {

    public:

        /// Item type
        ///
        ///
        enum Type {
            Coin,
            Medkit,
            Orb,
            GameEnd,
            TypeCount
        };

        /// Constructor
        ///
        ///
        Collectable(Type type, const TextureHolder& textures);

        /// Get category
        ///
        /// Return Collectable
        virtual unsigned int getCategory() const;

        /// Creates a collectable item
        ///
        /// Create an item based on collectable type.
        void createCollectable(b2World* world, float posX, float posY);

        /// Apply collectable
        ///
        /// Applies collectable to player
        bool apply(Character& player);

        ///
        ///
        /// Collectables are removed after sound has played
        virtual bool isMarkedForRemoval() const;

    private:
        /// Draw collectable sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

        /// Play a sound
        ///
        ///
        void playLocalSound(CommandQueue& commands, SoundEffect::ID effect);

        /// Update collectable
        ///
        ///
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        /// Collectable type
        ///
        ///
        Type mType;

        /// Collectable sprite
		///
		///
		Animation mAnimation;

        ///
        ///
        /// Has been picked up
        bool mPickedUp;

        ///
        ///
        /// Pickup sound played
        bool mSoundPlayed;

    };
}
