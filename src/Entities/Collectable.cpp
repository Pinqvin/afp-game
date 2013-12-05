/// Implementation for Collectable class

#include <AFP/Entity/Collectable.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/DataTables.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Character data table
namespace
{
    const std::vector<AFP::CollectableData> Table = AFP::initializeCollectableData();
}

/// Constructor
AFP::Collectable::Collectable(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mAnimation(textures.get(Table[type].texture))
{
    switch (mType)
    {
    case AFP::Collectable::Coin:
        mAnimation.setFrameSize(sf::Vector2i(16,16));
        mAnimation.setNumFrames(14);
        mAnimation.setDuration(sf::seconds(1));
        mAnimation.setRepeating(true);
        break;
    case AFP::Collectable::Orb:
        mAnimation.setFrameSize(sf::Vector2i(16,16));
        mAnimation.setNumFrames(7);
        mAnimation.setDuration(sf::seconds(1));
        mAnimation.setRepeating(true);
    default:
        break;
    }

    centerOrigin(mAnimation);

}

/// Return category
unsigned int AFP::Collectable::getCategory() const
{
    return Category::Collectable;

}

/// Creates a collectable item
void AFP::Collectable::createCollectable(b2World* world, float posX, float posY)
{
    createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f);

}

/// Apply collectable
bool AFP::Collectable::apply(Character& player)
{
    switch (mType)
    {
    case Coin:
        return player.heal(25);
    case Orb:
        return player.recharge(25);
    default:
        break;
    }

    return false;
}

void AFP::Collectable::drawCurrent(sf::RenderTarget& target,
                                   sf::RenderStates states) const
{
    target.draw(mAnimation, states);

}

void AFP::Collectable::updateCurrent(sf::Time dt, CommandQueue&)
{
    mAnimation.update(dt);
}
