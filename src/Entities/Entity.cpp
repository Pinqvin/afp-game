/// Implementation for entity

#include <AFP/Entity/Entity.hpp>
#include <iostream>

/// Constructor
AFP::Entity::Entity(int hitpoints):
    mBody(nullptr), mHead(nullptr), mJoint(nullptr), mHitpoints(hitpoints)
{
}

/// Set velocity of mBody
void AFP::Entity::setVelocity(b2Vec2 velocity)
{
    mBody->SetLinearVelocity(velocity);
}

/// Set position in world
void AFP::Entity::setBodyPosition(b2Vec2 target)
{
    target.x /= AFP::PTM_RATIO;
    target.y /= AFP::PTM_RATIO;
    mBody->SetTransform(target, 0);
    mBody->SetAwake(true);
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

/// Create body
void AFP::Entity::createBody(b2World* world, float posX, float posY,
                             float sizeX, float sizeY, float density,
                             float friction)
{

    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;

    // Create body based on category
    if (getCategory() & Category::Character)
    {
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
    }

    if (getCategory() & Category::Scene)
    {
        bodyDef.type = b2_staticBody;
    }

    if (getCategory() & Category::Projectile)
    {
        bodyDef.type = b2_dynamicBody;
        bodyDef.bullet = true;
    }

    if (getCategory() & Category::Collectable)
    {
        fixtureDef.isSensor = true;
    }

    /// Convert to meters
    posX /= AFP::PTM_RATIO;
    posY /= AFP::PTM_RATIO;

    bodyDef.position.Set(posX, posY);
    mBody = world->CreateBody(&bodyDef);

    /// Set this entity in the body's user data
    mBody->SetUserData(this); 

    dynamicBox.SetAsBox(sizeX / 2.f, sizeY / 2.f);

    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = density;
    fixtureDef.friction = friction;

    mBody->CreateFixture(&fixtureDef);


}

void AFP::Entity::createHead(b2World* world)
{
    b2BodyDef bodyDef;
    b2CircleShape circleShape;
    b2FixtureDef fixtureDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
    bodyDef.position.Set(mBody->GetPosition().x, mBody->GetPosition().y);
    mHead = world->CreateBody(&bodyDef);

    circleShape.m_radius = 0.5f;

    fixtureDef.shape = &circleShape;

    mHead->CreateFixture(&fixtureDef);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = mBody;
    jointDef.bodyB = mHead;

    jointDef.collideConnected = false;

    mJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Rotate head
    mHead->SetAngularVelocity(1.0f);
}

b2Fixture* AFP::Entity::attachSensorToBody(const b2FixtureDef* sensor)
{
    return mBody->CreateFixture(sensor);
}

b2Fixture* AFP::Entity::attachSensorToHead(const b2FixtureDef* sensor)
{
    return mHead->CreateFixture(sensor);
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
    mBody->SetUserData(nullptr);

    if(mHead != nullptr)
    {
        mHead->GetWorld()->DestroyJoint(mJoint);
        mHead->GetWorld()->DestroyBody(mHead);
    }

    mBody->GetWorld()->DestroyBody(mBody);
}

/// Update entity
void AFP::Entity::updateCurrent(sf::Time, CommandQueue&)
{
    /// Set position of entity
    sf::Vector2f position = getPosition();
    position -= getParentPosition();
    setPosition(position);

}
