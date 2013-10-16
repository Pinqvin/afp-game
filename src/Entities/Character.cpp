/// Implementation for Character class

#include <AFP/Entity/Character.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Return texture based on the type
AFP::Textures::ID toTextureId(AFP::Character::Type type)
{
    switch (type)
    {
        case AFP::Character::Player:
            return AFP::Textures::Player;

        case AFP::Character::Enemy:
            return AFP::Textures::Enemy;

        default:
            return AFP::Textures::Player;

    }

}

AFP::Character::Character(Type type, const TextureHolder& textures):
    mType(type), mSprite(textures.get(toTextureId(type))), mJumpStrength(-40.f)
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void AFP::Character::drawCurrent(sf::RenderTarget& target,
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Return category based on Type
unsigned int AFP::Character::getCategory() const
{
    switch (mType)
    {
        case Player:
            return Category::PlayerCharacter;

        default:
            return Category::EnemyCharacter;

    }

}

/// Create a body based on character type
void AFP::Character::createCharacter(b2World* world, float posX, float posY)
{
    switch (mType)
    {
    case AFP::Character::Player:
        createBody(world, posX, posY, 1.0f, 2.0f, 40.0f, 0.7f, false);
        break;
    case AFP::Character::Enemy:
        createBody(world, posX, posY, 1.0f, 2.0f, 1.0f, 0.3f, false);
        break;
    default:
        break;
    }

}

/// Move character along horizontal axis
void AFP::Character::moveHorizontal(float vx)
{
    b2Vec2 velocity = getVelocity();

    /// Acceleration
    if ( vx < 0 ) 
    {
        velocity.x = b2Max(velocity.x - 3.0f, vx);
    } else
    {
        velocity.x = b2Min(velocity.x + 3.0f, vx);
    }

    setVelocity(velocity);
}

/// Make character jump
void AFP::Character::jump()
{
    float force = mJumpStrength * getMass();
    applyImpulse(b2Vec2(0, force));
}
