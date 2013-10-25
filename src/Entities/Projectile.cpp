/// Implementation for Projectile class

#include <AFP/Entity/Projectile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

/// Return texture based on the type
AFP::Textures::ID toTextureId(AFP::Projectile::Type type)
{
    /// TODO: Change when actual textures added
    switch (type)
    {
    case AFP::Projectile::Bullet:
        return AFP::Textures::Bullet;

    default:
        return AFP::Textures::Bullet;

    }

}

/// Constructor
AFP::Projectile::Projectile(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mSprite(textures.get(toTextureId(type)))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

/// Draw projectile
void AFP::Projectile::drawCurrent(sf::RenderTarget& target,
                                  sf::RenderStates states) const
{
    target.draw(mSprite, states);

}

/// Update projectile
void AFP::Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // Projectile moves at constant speed
    setVelocity(mTarget);
    Entity::updateCurrent(dt, commands);
}

/// Return body type
AFP::BodyType AFP::Projectile::getEntityType()
{
    return AFP::ProjectileBody;

}

/// Creates a projectile
void AFP::Projectile::createProjectile(b2World* world, float posX, float posY, sf::Vector2f target, Type type)
{
    
    // Make target into a direction vector
    float length = sqrt(pow(target.x,2) + pow(target.y,2));
    target /= length;

    mTarget = b2Vec2(target.x, target.y);

    // Speed
    mTarget *= 40.0f;

    switch(type)
    {
    case AFP::Projectile::Bullet:
        // Create body for bullet and apply velocity
        createBody(world, posX, posY, 0.2f, 0.2f, 1.0f, 0.0f, false, false, true);
        setVelocity(mTarget);
        break;
    default:
        break;
    }

    // Save target to maintain constant speed
    // or maintain target in case of a homing missile


}

/// Handle contact
void AFP::Projectile::startContact()
{
    // Projectiles are destroyed on collision
    destroy();
}