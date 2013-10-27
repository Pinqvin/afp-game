/// Implementation for Tile class

#include <AFP/Entity/Tile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Return texture based on the type
const std::string toTextureId(AFP::Tile::Type type)
{
    /// TODO: Change when actual textures added
    switch (type)
    {
    case AFP::Tile::Grass:
        return "AFP::Textures::GrassTile";

    case AFP::Tile::Metal:
        return "AFP::Textures::Enemy";

    default:
        return "AFP::Textures::Player";

    }

}

AFP::Tile::Tile(Type type, const TextureHolder& textures):
    mType(type), mSprite(textures.get(toTextureId(type)))
{
    centerOrigin(mSprite);

}

void AFP::Tile::drawCurrent(sf::RenderTarget& target,
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Creates a tile
void AFP::Tile::createTile(b2World* world, float posX, float posY, Type type)
{
    switch (type)
    {
    case AFP::Tile::Grass:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f, true);
        break;
    case AFP::Tile::Metal:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.3f, 0.5f, true);
        break;
    case AFP::Tile::Dicks:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.2f, 0.8f, true);
        break;
    default:
        break;
    }

}

