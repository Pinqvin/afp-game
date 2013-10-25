/// Implementation for Character class

#include <AFP/Entity/Character.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/DataTables.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

/// Character data table
namespace
{
    const std::vector<AFP::CharacterData> Table = AFP::initializeCharacterData();
}

/// Constructor
AFP::Character::Character(Type type, const TextureHolder& textures):
    Entity(Table[type].hitpoints)
    , mType(type), mSprite(textures.get(Table[type].texture)), mJumpStrength(Table[type].jumpStrength)
    , mFireCommand(), mTeleportCommand(), mIsFiring(false), mIsTeleporting(false)
    , mTeleportTarget(), mFireTarget(), mMouseTranslation(), mFireCountdown(sf::Time::Zero), mFireRateLevel(5)
    , mFootContacts(0), mIsMarkedForRemoval(false)
{
    // Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    mFireCommand.category = Category::PlayerCharacter;
    mTeleportCommand.category = Category::PlayerCharacter;
    // Create the fire command
    mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createBullets(node, textures);
    };

    // Create the teleport command
    mTeleportCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        teleportCharacter(node, textures);
    };

}

/// Return category based on Type
unsigned int AFP::Character::getCategory() const
{
    if (isFriendly())
    {
        return Category::PlayerCharacter;
    }
    else
    {
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
        createFootSensor(1.0f, 2.0f);
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
    if (mFootContacts > 0)
    {
        float force = mJumpStrength * getMass();
        applyImpulse(b2Vec2(0, force));
    }
}

/// Set firing flag true
void AFP::Character::fire(sf::Vector2f target)
{
    mIsFiring = true;

    // Apply mouse translation
    target.x += mMouseTranslation.x;
    target.y += mMouseTranslation.y;

    // Calculate target position relative to
    // character
    target.x -= getPosition().x;
    target.y -= getPosition().y;

    mFireTarget = target;

}

/// Set teleporting flag true
void AFP::Character::teleport(sf::Vector2f target)
{
    mIsTeleporting = true;

    // Apply mouse translation
    target.x += mMouseTranslation.x;
    target.y += mMouseTranslation.y;

    mTeleportTarget.x = target.x;
    mTeleportTarget.y = target.y;

}

/// Set mouse translation
void AFP::Character::setMouseTranslation(sf::Vector2f translation)
{
    mMouseTranslation = translation;
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

    if (mIsTeleporting)
    {
        commands.push(mTeleportCommand);
        mIsTeleporting = false;

    }

}

/// Create bullets
void AFP::Character::createBullets(SceneNode& node, const TextureHolder& textures)
{
    // TODO:
    // Calculate offset using target so projectile is created in correct
    // place. For example when shooting up the projectile is created
    // on top of the character.

    sf::Vector2f offset = mFireTarget;
    float length = sqrt(pow(offset.x,2) + pow(offset.y,2));
    offset /= length;

    offset.x *= 16.0f;
    offset.y *= 32.0f;

    createProjectile(node, Projectile::Bullet, offset.x, offset.y, textures);

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
    projectile->createProjectile(getWorld(), position.x, position.y, mFireTarget, isFriendly());

    /// Set position
    projectile->setPosition(projectile->getPosition());

    /// Attach node to this character
    node.attachChild(std::move(projectile));

}

/// Teleport character
void AFP::Character::teleportCharacter(SceneNode&,
                                       const TextureHolder&)
{
    /// Move the player body to target position
    setBodyPosition(mTeleportTarget);
}

// Returns true if character is friendly
bool AFP::Character::isFriendly() const
{
    return mType == Player;
}

void AFP::Character::startFootContact()
{
    mFootContacts++;
}

void AFP::Character::endFootContact()
{
    mFootContacts--;
}
