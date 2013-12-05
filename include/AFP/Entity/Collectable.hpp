/// This is the class for collectable objects in the game
///
/// Collectables are static box2d sensor objects

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Animation/Animation.hpp>

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
            Orb,
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

    private:
        /// Draw collectable sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

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

    };
}
