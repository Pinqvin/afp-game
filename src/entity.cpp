/// Implementation for entity

#include "entity.hpp"

AFP::Entity::Entity(void):
    mVelocity(), mBodyDef(), mBody(), mDynamicBox(), mFixtureDef()
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
    if (mBody != nullptr) {
        b2Vec2 position = mBody->GetPosition(); 
        float32 angle = mBody->GetAngle(); 
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
}

/// Accelerate entity
void AFP::Entity::accelerate(sf::Vector2f vector)
{
    mVelocity += vector;

}

/// Accelerate entity
void AFP::Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;

}

/// Create body
void AFP::Entity::createBody(b2World* world)
{
    mBodyDef.type = b2_dynamicBody; 
    mBodyDef.position.Set(20.0f, 20.0f);
    mBody = world->CreateBody(&mBodyDef);

    mDynamicBox.SetAsBox(1.0f, 2.0f);
 
    mFixtureDef.shape = &mDynamicBox; 
    mFixtureDef.density = 1.0f;    mFixtureDef.friction = 0.3f;    mBody->CreateFixture(&mFixtureDef);
}

/// Convert position to pixels
sf::Vector2f AFP::Entity::getBodyPosition()
{
    sf::Vector2f getPos;
    b2Vec2 position = mBody->GetPosition();

    /// Calculate positions and invert y axis.
    /// 1 meter = 16 pixels
    getPos.x = position.x * 16;
    getPos.y = 2000 - (position.y * 16);

    return getPos;
}

