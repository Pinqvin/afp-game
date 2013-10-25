/// Implementation for Projectile class

#include <AFP/Entity/Projectile.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/DataTables.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

/// Projectile data table
namespace
{
    const std::vector<AFP::ProjectileData> Table = AFP::initializeProjectileData();
}

/// Constructor
AFP::Projectile::Projectile(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mSprite(textures.get(Table[type].texture)),
    mSpeed(Table[type].speed), mDamage(Table[type].damage)
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

/// Return category
unsigned int AFP::Projectile::getCategory() const
{
    if (mFriendly)
    {
        return Category::AlliedProjectile;
    }
    else
    {
        return Category::EnemyProjectile;
    }

}

/// Creates a projectile
void AFP::Projectile::createProjectile(b2World* world, float posX, float posY, sf::Vector2f target, bool friendly)
{
    mFriendly = friendly;
    
    // Make target into a direction vector
    float length = sqrt(pow(target.x,2) + pow(target.y,2));
    target /= length;

    mTarget = b2Vec2(target.x, target.y);

    // Apply speed
    mTarget *= mSpeed;

    switch(mType)
    {
    case AFP::Projectile::Bullet:
        // Create body for bullet and apply velocity
        createBody(world, posX, posY, 0.2f, 0.2f, 1.0f, 0.0f);
        setVelocity(mTarget);
        break;
    default:
        break;
    }

}

int AFP::Projectile::getDamage()
{
    return mDamage;

}