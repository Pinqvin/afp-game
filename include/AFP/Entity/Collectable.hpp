/// This is the class for collectable objects in the game
///
/// Collectables are static box2d sensor objects

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

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
            TypeCount
        };

        /// Constructor
        ///
        ///
        Collectable(Type type, const TextureHolder& textures);

        /// Draw collectable sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

        /// Get category
        ///
        /// Return Collectable
        virtual unsigned int getCategory() const;

        /// Creates a collectable item
        ///
        /// Create an item based on collectable type.
        void createCollectable(b2World* world, float posX, float posY);

    private:
        /// Collectable type
        ///
        ///
        Type mType;

        /// Collectable sprite
		///
		///
		sf::Sprite mSprite;

    };
}
