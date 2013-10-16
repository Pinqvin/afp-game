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

/// Constructor
AFP::Character::Character(Type type, const TextureHolder& textures):
    mType(type), mSprite(textures.get(toTextureId(type))), mJumpStrength(-40.f),
    mIsFiring(false), mFireCountdown(sf::Time::Zero), mFireCommand(),
    mFireRateLevel(1)
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    mFireCommand.category = Category::PlayerCharacter;
    /// Create the fire command
    mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createBullets(node, textures);
    };

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
        createBody(world, posX, posY, 1.0f, 2.0f, 20.0f, 0.7f);
        break;
    case AFP::Character::Enemy:
        createBody(world, posX, posY, 1.0f, 2.0f, 1.0f, 0.3f);
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

/// Set firing flag true
void AFP::Character::fire()
{
    mIsFiring = true;
}

/// Draw character
void AFP::Character::drawCurrent(sf::RenderTarget& target,
                                 sf::RenderStates states) const
{
    target.draw(mSprite, states);

}

/// Update character
void AFP::Character::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    checkProjectileLaunch(dt, commands);

    /// Stop movement in x-axis
    b2Vec2 velocity = getVelocity();
    velocity.x *= 0.90f;
    setVelocity(velocity);

    Entity::updateCurrent(dt, commands);

}

/// Check if firing
void AFP::Character::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
    if (mIsFiring && mFireCountdown <= sf::Time::Zero)
    {
        commands.push(mFireCommand);
        mFireCountdown += sf::seconds(1.f / (mFireRateLevel+1));
        mIsFiring = false;
    }
    else if (mFireCountdown > sf::Time::Zero)
    {
        mFireCountdown -= dt;
    }

}

/// Create many bullets
void AFP::Character::createBullets(SceneNode& node, const TextureHolder& textures)
{
    createProjectile(node, Projectile::Bullet, 0.0f, 0.0f, textures);

}

/// Creates a projectile
void AFP::Character::createProjectile(SceneNode& node, Projectile::Type type, 
                                      float xOffset, float yOffset, 
                                      const TextureHolder& textures)
{
    /// Make new node for projectile
    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

    /// Get position of the shooter and apply offset to it
    sf::Vector2f position = getPosition();
    position.x += xOffset;
    position.y += yOffset;

    /// Create projectile in Box2D world
    projectile->createProjectile(getWorld(), position.x, position.y, type);

    /// Set position
    projectile->setPosition(projectile->getPosition());

    /// Attach node to this character
    node.attachChild(std::move(projectile));

}