/// Implementation for Tile class

#include <AFP/Entity/Tile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/DataTables.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Tile data table
namespace
{
    const std::vector<AFP::TileData> Table = AFP::initializeTileData();
}

/// Constructor
AFP::Tile::Tile(Type type, const TextureHolder& textures):
    Entity(Table[type].hitpoints), mType(type), mSprite(textures.get(Table[type].texture))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

/// Draw tile
void AFP::Tile::drawCurrent(sf::RenderTarget& target,
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Return category
unsigned int AFP::Tile::getCategory() const
{

    return Category::Tile;

}

/// Creates a tile
void AFP::Tile::createTile(b2World* world, float posX, float posY)
{
    switch (mType)
    {
    case AFP::Tile::Grass:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f);
        break;
    case AFP::Tile::Metal:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.3f, 0.5f);
        break;
    case AFP::Tile::Crate:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.2f, 0.8f);
        break;
    default:
        break;
    }

}
