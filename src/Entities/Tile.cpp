/// Implementation for Tile class

#include <AFP/Entity/Tile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Utility.hpp>
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
    Entity(Table[type].hitpoints), mType(type), mSprite(textures.get(Table[type].texture)),
    mDestroyAnimation(textures.get(Table[type].destroyanim)), mDropCollectable(), mCollectableDropped(false)
{

    switch (mType)
    {
    case AFP::Tile::Box16:
    case AFP::Tile::Box16Coin:
    case AFP::Tile::Box16Orb:
        mDestroyAnimation.setFrameSize(sf::Vector2i(48, 48));
        break;
    case AFP::Tile::Box32:
        mDestroyAnimation.setFrameSize(sf::Vector2i(80, 80));
        break;
    default:
        break;
    }

    mDestroyAnimation.setNumFrames(5);
    mDestroyAnimation.setDuration(sf::seconds(0.5));
    mDestroyAnimation.setRepeating(false);

    centerOrigin(mSprite);
    centerOrigin(mDestroyAnimation);

    // If collectable type is TypeCount, nothing will be dropped
    if (Table[mType].collectable == Collectable::TypeCount)
    {
        mCollectableDropped = true;
    }

    /// Create command for dropping collectables
    mDropCollectable.category = Category::Scene;
    mDropCollectable.action = [this, &textures] (SceneNode& node, sf::Time)
    {
        std::unique_ptr<Collectable> dropCoin(new Collectable(Table[mType].collectable, textures));

        dropCoin->createCollectable(this->getWorld(), this->getPosition().x, this->getPosition().y);
        dropCoin->setPosition(getPosition());

        node.attachChild(std::move(dropCoin));
    };

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
    case AFP::Tile::Box16:
    case AFP::Tile::Box16Coin:
    case AFP::Tile::Box16Orb:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f);
        break;
    case AFP::Tile::Box32:
        createBody(world, posX, posY, 2.0f, 2.0f, 1.3f, 0.5f);
        break;
    default:
        break;
    }

}

bool AFP::Tile::isMarkedForRemoval() const
{
    return isDestroyed() && mDestroyAnimation.isFinished();
}

/// Draw tile
void AFP::Tile::drawCurrent(sf::RenderTarget& target,
                            sf::RenderStates states) const
{
    if (isDestroyed())
    {
        target.draw(mDestroyAnimation, states);
    }
    else
    {
        target.draw(mSprite, states);
    }

}

/// Draw tile
void AFP::Tile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (isDestroyed())
    {
        mDestroyAnimation.update(dt);
        if (!mCollectableDropped)
        {
            commands.push(mDropCollectable);
            mCollectableDropped = true;
        }

    }

}
