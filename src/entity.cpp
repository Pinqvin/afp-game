/// Implementation for entity

#include "entity.hpp"

AFP::Entity::Entity(void)
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

}

