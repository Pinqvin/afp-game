/// This is the class for tile objects in the game
///
/// Tiles are static box2d objects

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

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
            Grass,
            Metal,
            Dicks
        };

        /// Constructor
        ///
        ///
        Tile(Type type, const TextureHolder& textures);

        /// Draw tile sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

        /// Get body type
        ///
        /// Return TileBody
        AFP::BodyType getEntityType();

        /// Creates a tile
        ///
        /// Create a tile based on tile type.
        void createTile(b2World* world, float posX, float posY, Type type);

    private:

        /// Tile contact
        ///
        /// Called when tile comes in contact with
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

    };
}
