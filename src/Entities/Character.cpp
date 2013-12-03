/// Implementation for Character class

#include <AFP/Entity/Character.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Entity/DataTables.hpp>
#include <AFP/Sound/SoundNode.hpp>
#include <AFP/Entity/Sensor.hpp>
#include <AFP/Particles/EmitterNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Character data table
namespace
{
    const std::vector<AFP::CharacterData> Table = AFP::initializeCharacterData();
    const std::vector<AFP::WeaponData> WeaponTable = AFP::initializeWeaponData();
}

/// Constructor
AFP::Character::Character(Type type, const TextureHolder& textures):
    Entity(Table[type].hitpoints)
    , mType(type), mWeaponType(Table[type].weapon), mJumpStrength(Table[type].jumpStrength)
    , mFireCommand(), mTeleportCommand(), mIsFiring(false), mIsTeleporting(false)
    , mTeleportTarget(), mFireTarget(), mMouseTranslation(), mFireCountdown(sf::Time::Zero), mTeleportCountdown(sf::Time::Zero)
    , mFootContacts(0), mJumpContacts(0), mIsMarkedForRemoval(false), mTeleCharge(Table[type].telecharge), mRecoil(WeaponTable[mWeaponType].recoil), mTarget(nullptr)
    , mAnimations(), mState(Stopped), mTargetInVision(false)
{
    /// Initialize animations
    mAnimations.resize(StateCount);

    /// Create new Animation object for every character state and assing values from data table to them
    for (size_t i = 0;i < mAnimations.size();++i)
    {
        mAnimations[i] = Animation(textures.get(Table[type].animation[i].texture));
        mAnimations[i].setFrameSize(Table[type].animation[i].frameSize);
        mAnimations[i].setNumFrames(Table[type].animation[i].frameCount);
        mAnimations[i].setDuration(Table[type].animation[i].duration);
        mAnimations[i].setRepeating(true);

        centerOrigin(mAnimations[i]);
    }

    // Add blood emitter
    std::unique_ptr<EmitterNode> blood(new EmitterNode(Particle::Blood));
    blood->setPosition(0.f, 0.f);
    attachChild(std::move(blood));

    // Set command category as scene so the command is called only once.
    mFireCommand.category = Category::Scene;
    mTeleportCommand.category = Category::Scene;

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

    createBody(world, posX, posY, 1.0f, 2.0f, 20.0f, 0.7f);

    if (mType == Player)
    {
        // Create footsensor
        std::unique_ptr<Sensor> sensor(new Sensor(this, Sensor::Foot));
        sensor->createFootSensor(1.0f, 2.0f);
        this->attachChild(std::move(sensor));
    }

    if (getCategory() == Category::EnemyCharacter)
    {
        createHead(world);

        // Create vision sensor
        std::unique_ptr<Sensor> sensor(new Sensor(this, Sensor::Vision));
        sensor->createVisionSensor(15.f, 90.f);
        this->attachChild(std::move(sensor));

        // Create surround sensor
        std::unique_ptr<Sensor> sensor2(new Sensor(this, Sensor::Surround));
        sensor2->createSurroundSensor(15.f);
        this->attachChild(std::move(sensor2));

        // Create footsensor
        std::unique_ptr<Sensor> sensor3(new Sensor(this, Sensor::Foot));
        sensor3->createFootSensor(1.0f, 2.0f);
        this->attachChild(std::move(sensor3));

        // Create jump sensor
        std::unique_ptr<Sensor> sensor4(new Sensor(this, Sensor::Jump));
        sensor4->createJumpSensor(1.f, 2.f);
        this->attachChild(std::move(sensor4));
    }

}

/// Move character along horizontal axis
/// Move-command
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
/// Jump-command
void AFP::Character::jump()
{
    if (mFootContacts > 0)
    {
        float force = mJumpStrength * getMass();
        applyImpulse(b2Vec2(0, force));
    }
}

/// Set firing flag true
/// Fire-command
void AFP::Character::fire(sf::Vector2f target)
{
    mIsFiring = true;

    // Apply mouse translation
    target += mMouseTranslation;

    // Calculate target position relative to
    // character
    target -= getPosition();

    mFireTarget = target;

}

/// Play sound
void AFP::Character::playLocalSound(CommandQueue& commands, SoundEffect::ID effect)
{
    sf::Vector2f worldPosition = getPosition();

    Command command;
    command.category = Category::SoundEffect;
    command.action = derivedAction<SoundNode>(
        [effect, worldPosition] (SoundNode& node, sf::Time)
    {
        node.playSound(effect, worldPosition);
    });

    commands.push(command);
}

/// Set teleporting flag true
/// Teleport-command
void AFP::Character::teleport(sf::Vector2f target)
{
    mIsTeleporting = true;

    // Apply mouse translation
    target += mMouseTranslation;

    mTeleportTarget.x = target.x;
    mTeleportTarget.y = target.y;

}

/// Set mouse translation
void AFP::Character::setMouseTranslation(sf::Vector2f translation)
{
    mMouseTranslation = translation;
}

void AFP::Character::setMousePosition(sf::Vector2f position)
{
    mMousePosition = position;
}

/// Start foot contact
void AFP::Character::startFootContact()
{
    mFootContacts++;

}

/// End foot contact
void AFP::Character::endFootContact()
{
    mFootContacts--;

}

/// Start foot contact
void AFP::Character::startJumpContact()
{
    mJumpContacts++;

}

/// End foot contact
void AFP::Character::endJumpContact()
{
    mJumpContacts--;

}


/// Recharge telecharge
void AFP::Character::recharge(int points)
{
    mTeleCharge += points;

}

/// Draw character
void AFP::Character::drawCurrent(sf::RenderTarget& target,
                                 sf::RenderStates states) const
{
    /// Draw this state
    target.draw(mAnimations[mState], states);

}

/// Update character
void AFP::Character::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    checkProjectileLaunch(dt, commands);

    /// Stop movement in x-axis
    b2Vec2 velocity = getVelocity();
    velocity.x *= 0.90f;
    setVelocity(velocity);

    /// Change character state
    if ((getVelocity().x > 0.5f || getVelocity().x < -0.5f) && getVelocity().y == 0.f)
    {
        mState = Running;
    } else if  (getVelocity().y < 0)
    {
        mState = Jumping;
    } else if (getVelocity().y > 0)
    {
        mState = Falling;
    } else 
    {
        mState = Stopped;
    }

    if(getCategory() == Category::PlayerCharacter){
        if (mMousePosition.x + mMouseTranslation.x < getWorldPosition().x)
        {
            mAnimations[mState].setScale(-1.0f,1.0f);
        } else
        {
            mAnimations[mState].setScale(1.0f,1.0f);
        }
    }

    /// Update state
    mAnimations[mState].update(dt);

    Entity::updateCurrent(dt, commands);

    ///Enemy AI update
    if(getCategory() == Category::EnemyCharacter){

        if(mTarget != nullptr){

            /// If you gotta jump
            if (mJumpContacts > 0)
            {
                /// You gotta jump
                jump();
            }

            if (mTarget->getPosition().x > getWorldPosition().x)
            {
                moveHorizontal(10.f);
                mAnimations[mState].setScale(-1.0f,1.0f);
                flip(b2_pi);
            } else
            {
                moveHorizontal(-10.f);
                mAnimations[mState].setScale(1.0f,1.0f);
                flip(0);
            }

            if(mTargetInVision)
            {
                fire(mTarget->getPosition());
            }
        }
    }

}

/// Check if firing
void AFP::Character::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
    if (mIsFiring && mFireCountdown <= sf::Time::Zero)
    {
        commands.push(mFireCommand);
        playLocalSound(commands, SoundEffect::Pistol);
        mFireCountdown += sf::milliseconds(WeaponTable[mWeaponType].firerate);
        mIsFiring = false;

    }
    else if (mFireCountdown > sf::Time::Zero)
    {
        mFireCountdown -= dt;
        mIsFiring = false;
    }

    if (mIsTeleporting && mTeleportCountdown <= sf::Time::Zero && mTeleCharge > 0)
    {
        commands.push(mTeleportCommand);
        mTeleportCountdown += sf::milliseconds(500);
        mIsTeleporting = false;
        mTeleCharge -= 10;

    }
    else if (mTeleportCountdown > sf::Time::Zero)
    {
        mTeleportCountdown -= dt;
        mIsTeleporting = false;

    }

}

/// Create bullets
void AFP::Character::createBullets(SceneNode& node, const TextureHolder& textures)
{
    sf::Vector2f offset = mFireTarget;
    float length = sqrt(pow(offset.x,2) + pow(offset.y,2));
    offset /= length;

    offset.x *= 16.0f;
    offset.y *= 32.0f;

    // Different weapons create bullets differently
    switch (mWeaponType)
    {
    case WeaponType::Machinegun:
    case WeaponType::Pistol:
        createProjectile(node, WeaponTable[mWeaponType].bullets, offset.x, offset.y, textures);
        break;
    case WeaponType::Shotgun:
        for(int i = 0;i < 10;i++)
        {
            createProjectile(node, WeaponTable[mWeaponType].bullets, offset.x, offset.y, textures);
        }
        break;
    default:
        break;
    }



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

void AFP::Character::newTarget(Character& target)
{
    mTarget = &target;
    mTargetInVision = true;
}

void AFP::Character::targetOutOfVision()
{
    mTargetInVision = false;
}

void AFP::Character::noTarget()
{
    mTarget = nullptr;
}

int AFP::Character::getTeleCharge()
{
    return mTeleCharge;
}