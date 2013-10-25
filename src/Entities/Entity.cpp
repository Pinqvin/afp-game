/// Implementation for entity

#include <AFP/Entity/Entity.hpp>
#include <iostream>

AFP::Entity::Entity(int hitpoints):
    mBody(), mHitpoints(hitpoints)
{
}

/// Set velocity of mBody
void AFP::Entity::setVelocity(b2Vec2 velocity)
{
    mBody->SetLinearVelocity(velocity);
}

/// Applies impulse to mBody
void AFP::Entity::applyImpulse(b2Vec2 impulse)
{
    mBody->ApplyLinearImpulse(impulse, mBody->GetWorldCenter() );
}

/// Applies force to mBody
void AFP::Entity::applyForce(b2Vec2 force)
{
    mBody->ApplyForce(force, mBody->GetWorldCenter());
}

/// Return velocty of mBody
b2Vec2 AFP::Entity::getVelocity() const
{
    return mBody->GetLinearVelocity();
}

/// Return mass of mBody
float AFP::Entity::getMass() const
{
    return mBody->GetMass();
}

void AFP::Entity::updateCurrent(sf::Time, CommandQueue&)
{

    /// Set position of entity
    sf::Vector2f position = getPosition();
    position.x -= getParentPosition().x;
    position.y -= getParentPosition().y;
    setPosition(position);

    /*
    /// Print Box2D info
    if (mBody != nullptr)
    {
    b2Vec2 position = mBody->GetPosition();
    float32 angle = mBody->GetAngle();
    std::cout << position.x << " " << position.y
    << " " << angle << std::endl;

    }
    */
}

/// Create body
void AFP::Entity::createBody(b2World* world, float posX, float posY,
                             float sizeX, float sizeY, float density,
                             float friction, bool isCharacter, bool staticBody, bool isProjectile, bool isCollectable)
{

    b2BodyDef mBodyDef;
    b2PolygonShape mDynamicBox;
    b2FixtureDef mFixtureDef;

    if ( staticBody )
    {
        mBodyDef.type = b2_staticBody;
    } else
    {
        mBodyDef.type = b2_dynamicBody;
        mBodyDef.fixedRotation = true;
    }

    /// Enable continuous collision detection
    if ( isProjectile )
    {
        mBodyDef.bullet = true;

    }

    ///make the fixture a sensor, so it won't collide with anything in the world
    if(isCollectable)
    {
        mFixtureDef.isSensor = true;
    }


    /// Convert to meters
    posX /= AFP::PTM_RATIO;
    posY /= AFP::PTM_RATIO;

    mBodyDef.position.Set(posX, posY);

    mBody = world->CreateBody(&mBodyDef);

    ///set this entity in the body's user data
    mBody->SetUserData( this ); 

    mDynamicBox.SetAsBox(sizeX / 2.f, sizeY / 2.f);


    mFixtureDef.shape = &mDynamicBox;
    mFixtureDef.density = density;
    mFixtureDef.friction = friction;
    mBody->CreateFixture(&mFixtureDef);

    if(isCharacter)
    {
        ///add foot sensor fixture
        mDynamicBox.SetAsBox(sizeX/2.f-0.2f, 0.3f, b2Vec2(0, sizeY/2.f), 0);
        mFixtureDef.isSensor = true;
        b2Fixture* footSensorFixture = mBody->CreateFixture(&mFixtureDef);
        ///set pointer to this entity in it's footsensor
        footSensorFixture->SetUserData( this );
    }

}

/// Convert position to pixels
sf::Vector2f AFP::Entity::getPosition() const
{
    if ( mBody == NULL ) {
        return sf::Vector2f(0.f, 0.f);
    }

    sf::Vector2f getPos;
    b2Vec2 position = mBody->GetPosition();

    /// Calculate positions and invert y axis.
    /// 1 meter = 16 pixels
    getPos.x = position.x * AFP::PTM_RATIO;
    getPos.y = position.y * AFP::PTM_RATIO;

    return getPos;
}

/// Return body position in meters
b2Vec2 AFP::Entity::getBodyPosition() const
{
    return mBody->GetPosition();

}

void AFP::Entity::setBodyPosition(b2Vec2 target)
{
    target.x /= AFP::PTM_RATIO;
    target.y /= AFP::PTM_RATIO;
    mBody->SetTransform(target, 0);
    mBody->SetAwake(true);
}

/// Return pointer to world
b2World* AFP::Entity::getWorld() const
{
    return mBody->GetWorld();

}

/// Return entity hitpoints
int AFP::Entity::getHitpoints() const
{
    return mHitpoints;

}

/// Decreases hitpoints
void AFP::Entity::damage(int points)
{
    assert(points > 0);

    mHitpoints -= points;

}

/// Increases hitpoints
void AFP::Entity::heal(int points)
{
    assert(points > 0);

    mHitpoints += points;
}

/// Destroy entity
void AFP::Entity::destroy()
{
    mHitpoints= 0;

}

/// Returns true if hitpoints are below or equal to zero
bool AFP::Entity::isDestroyed() const
{
    return mHitpoints <= 0;

}

/// Destroy body
void AFP::Entity::destroyBody()
{
    mBody->GetWorld()->DestroyBody(mBody);
}