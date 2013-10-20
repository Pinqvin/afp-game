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
    mType(type), mSprite(textures.get(toTextureId(type)))
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
    Entity::updateCurrent(dt, commands);
}

/// Creates a projectile
void AFP::Projectile::createProjectile(b2World* world, float posX, float posY, sf::Vector2f target, Type type)
{
    switch(type)
    {
    case AFP::Projectile::Bullet:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 10.0f, false, false);
        // Amount of force
        target *= 100.0f;
        // Apply impulse to bullet
        applyImpulse(b2Vec2(target.x, target.y));
        break;
    default:
        break;
    }
}

