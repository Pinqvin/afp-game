/// Implementation for entity

#include <AFP/Entity/Entity.hpp>
#include <AFP/Utility.hpp>
#include <iostream>

AFP::Entity::Entity(void):
    mVelocity(), mBody()
{

}

void AFP::Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;

}

void AFP::Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;

}

sf::Vector2f AFP::Entity::getVelocity() const
{
	return mVelocity;
}

void AFP::Entity::updateCurrent(sf::Time dt)
{
    move(mVelocity * dt.asSeconds());

    /// Print Box2D info
    if (mBody != nullptr)
    {
        b2Vec2 position = mBody->GetPosition();
        float32 angle = mBody->GetAngle();
        std::cout << position.x << " " << position.y
            << " " << angle << std::endl;

    }

}

/// Accelerate entity
void AFP::Entity::accelerate(sf::Vector2f vector)
{
    mVelocity = vector;

    mBody->ApplyLinearImpulse(b2Vec2(vector.x, vector.y), mBody->GetWorldCenter());

}

/// Accelerate entity
void AFP::Entity::accelerate(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;

    mBody->ApplyLinearImpulse(b2Vec2(vx, vy), mBody->GetWorldCenter());

}

/// Create body
void AFP::Entity::createBody(b2World* world, float posX, float posY,
                             float sizeX, float sizeY, float density,
                             float friction, bool staticBody)
{

    b2BodyDef mBodyDef;
    b2PolygonShape mDynamicBox;
    b2FixtureDef mFixtureDef;

    if ( staticBody ) {
        mBodyDef.type = b2_staticBody;
    } else {
        mBodyDef.type = b2_dynamicBody;
        mBodyDef.fixedRotation = true;
    }

    /// Convert to meters
    posX /= AFP::PTM_RATIO;
    posY /= AFP::PTM_RATIO;

    mBodyDef.position.Set(posX, posY);
    mBody = world->CreateBody(&mBodyDef);

    mDynamicBox.SetAsBox(sizeX / 2.f, sizeY / 2.f);

    mFixtureDef.shape = &mDynamicBox;
    mFixtureDef.density = density;
    mFixtureDef.friction = friction;
    mBody->CreateFixture(&mFixtureDef);

}

/// Convert position to pixels
sf::Vector2f AFP::Entity::getBodyPosition(float worldSizeX, float worldSizeY)
{
    if ( mBody == NULL ) {
        return sf::Vector2f(0.f, 0.f);
    }

    sf::Vector2f getPos;
    b2Vec2 position = mBody->GetPosition();

    /// Calculate positions and invert y axis.
    /// 1 meter = 16 pixels
    getPos.x = position.x * AFP::PTM_RATIO;
    getPos.y = (position.y * AFP::PTM_RATIO);

    return getPos;
}

float AFP::Entity::getBodyAngle()
{
    return -mBody->GetAngle();
}
