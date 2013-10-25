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
    Entity(1), mType(type), mSprite(textures.get(Table[type].texture))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void AFP::Collectable::drawCurrent(sf::RenderTarget& target,
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Return category
unsigned int AFP::Collectable::getCategory() const
{
    return Category::Collectable;

}

/// Creates a collectable item
void AFP::Collectable::createCollectable(b2World* world, float posX, float posY)
{
    switch (mType)
    {
    case AFP::Collectable::Coin:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f);
        break;
    default:
        break;
    }

}