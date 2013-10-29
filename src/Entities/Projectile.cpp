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
    Entity(1), mType(type), mSprite(textures.get(Table[type].texture))
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

    float length = sqrt(pow(target.x,2) + pow(target.y,2));
    float spread = Table[mType].spread;

    // Calculate spread
    target.x += (float)rand()/((float)RAND_MAX/(length/(spread/2))) - length/spread;
    target.y += (float)rand()/((float)RAND_MAX/(length/(spread/2))) - length/spread;

    // Make target into a direction vector
    target /= length;

    mTarget = b2Vec2(target.x, target.y);

    // Apply speed
    mTarget *= Table[mType].speed;

    // Create body for bullet and apply velocity
    createBody(world, posX, posY, 0.1f, 0.1f, 1.0f, 0.0f);
    setVelocity(mTarget);

}

int AFP::Projectile::getDamage()
{
    return Table[mType].damage;

}