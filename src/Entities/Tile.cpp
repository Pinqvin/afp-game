/// Implementation for Tile class

#include <AFP/Entity/Tile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Return texture based on the type
AFP::Textures::ID toTextureId(AFP::Tile::Type type)
{
    /// TODO: Change when actual textures added
    switch (type)
    {
    case AFP::Tile::Grass:
        return AFP::Textures::GrassTile;

    case AFP::Tile::Metal:
        return AFP::Textures::Enemy;

    default:
        return AFP::Textures::Player;

    }

}

AFP::Tile::Tile(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mSprite(textures.get(toTextureId(type)))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void AFP::Tile::drawCurrent(sf::RenderTarget& target,
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Return body type
AFP::BodyType AFP::Tile::getEntityType()
{
    return AFP::TileBody;

}

/// Creates a tile
void AFP::Tile::createTile(b2World* world, float posX, float posY, Type type)
{
    switch (type)
    {
    case AFP::Tile::Grass:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f, false, true);
        break;
    case AFP::Tile::Metal:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.3f, 0.5f, false, true);
        break;
    case AFP::Tile::Dicks:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.2f, 0.8f, false, true);
        break;
    default:
        break;
    }

}

// Handle contact
void AFP::Tile::startContact()
{
}
