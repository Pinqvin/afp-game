/// This is the class for tile objects in the game
///
/// Tiles are static box2d objects

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Animation/Animation.hpp>
#include <AFP/Sound/SoundPlayer.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
    class Tile : public Entity
    {

    public:

        /// Tile type
        ///
        ///
        enum Type {
            Box16,
            Box16Coin,
            Box16Orb,
            Box32,
            Barrel,
            TypeCount
        };

        /// Constructor
        ///
        ///
        Tile(Type type, const TextureHolder& textures);

        /// Get body type
        ///
        /// Return TileBody
        virtual unsigned int getCategory() const;

        /// Creates a tile
        ///
        /// Create a tile based on tile type.
        void createTile(b2World* world, float posX, float posY);

        /// Is tile destroyed
        ///
        /// Tile can be removed when destroy animation has finished
        virtual bool isMarkedForRemoval() const;

    private:
        /// Draw tile sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

        /// Play a sound
        ///
        ///
        void playLocalSound(CommandQueue& commands, SoundEffect::ID effect);

        /// Update tile
        ///
        ///
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        /// Tile type
        ///
        ///
        Type mType;

        /// Tile sprite
		///
		///
		sf::Sprite mSprite;

        /// Destroy animation
        ///
        /// Played when tile is destroyed
        Animation mDestroyAnimation;

        /// Command executed when tile is destroyed
        ///
        /// Creates a new collectable on tile position
        Command mDropCollectable;

        /// Has tile dropped a collectable
        ///
        ///
        bool mCollectableDropped;

        ///
        ///
        /// Destroy sound played
        bool mSoundPlayed;

    };
}
