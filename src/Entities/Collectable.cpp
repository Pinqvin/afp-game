/// Implementation for Collectable class

#include <AFP/Entity/Collectable.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Return texture based on the type
AFP::Textures::ID toTextureId(AFP::Collectable::Type type)
{
    /// TODO: Change when actual textures added
    switch (type)
    {
    case AFP::Collectable::Coin:
        return AFP::Textures::Coin;
    default:
        return AFP::Textures::Player;

    }

}

AFP::Collectable::Collectable(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mSprite(textures.get(toTextureId(type)))
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

/// Return body type
AFP::BodyType AFP::Collectable::getEntityType()
{
    return AFP::CollectableBody;

}

/// Creates a collectable item
void AFP::Collectable::createCollectable(b2World* world, float posX, float posY, Type type)
{
    switch (type)
    {
    case AFP::Collectable::Coin:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f, false, true, false, true);
        break;
    default:
        break;
    }

}

/// Handle contact
void AFP::Collectable::startContact()
{
    
    ///Todo:
    ///delete the collectable when in collision with player
}