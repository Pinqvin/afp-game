/// Implementation of Sensor class
#include <AFP/Entity/Sensor.hpp>
#include <AFP/Entity/Character.hpp>

#include <iostream>

/// Constructor
AFP::Sensor::Sensor(Entity* parent, Type type):
    mFixture(), mParent(parent), mType(type)
{
}

/// Return sensor category
unsigned int AFP::Sensor::getCategory() const
{
    return Category::Sensor;
}

/// Update sensor
void AFP::Sensor::updateCurrent(sf::Time, CommandQueue&)
{
}

/// Create foot sensor
void AFP::Sensor::createFootSensor(float sizeX, float sizeY)
{
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;

    /// Add foot sensor fixture
    dynamicBox.SetAsBox(sizeX / 2.f - 0.1f, 0.3f, b2Vec2(0, sizeY / 2.f), 0);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.isSensor = true;
    mFixture = mParent->attachSensorToBody(&fixtureDef);

    /// Set pointer to this sensor
    mFixture->SetUserData(this);
}

/// Create surround sensor
void AFP::Sensor::createSurroundSensor(float radius)
{
    b2CircleShape circleShape;
    b2FixtureDef fixtureDef;

    /// Add sensor fixture
    circleShape.m_radius = radius;
    fixtureDef.shape = &circleShape;
    fixtureDef.isSensor = true;
    mFixture = mParent->attachSensorToHead(&fixtureDef);

    /// Set pointer to this sensor
    mFixture->SetUserData(this);

}

/// Create jump sensor
void AFP::Sensor::createJumpSensor(float sizeX, float sizeY)
{
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;

    /// Add jump sensor fixture
    dynamicBox.SetAsBox(sizeX * 1.f, 0.3f, b2Vec2(-1.f, sizeY * 0.1f), b2_pi/7);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.isSensor = true;
    mFixture = mParent->attachSensorToHead(&fixtureDef);

    /// Set pointer to this sensor
    mFixture->SetUserData(this);
}

/// Create vision sensor
void AFP::Sensor::createVisionSensor(float radius, float angle)
{
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2Vec2 vertices[8];

    float mAngle = 2.0f * b2_pi / 3.0f;
    float step = (angle * (b2_pi/180.0f)) / 6.0f;

    vertices[0].Set(0, 0);
    for (int i = 0; i < 7; i++) {
        vertices[i+1].Set( radius * cosf(mAngle), radius * sinf(mAngle) );
        mAngle += step;
    }


    /// Add sensor fixture
    polygonShape.Set(vertices, 8);
    fixtureDef.shape = &polygonShape;
    fixtureDef.isSensor = true;
    mFixture = mParent->attachSensorToHead(&fixtureDef);

    /// Set pointer to this sensor
    mFixture->SetUserData(this);

}

/// Begin sensor contact
void AFP::Sensor::beginContact()
{
    if (mType == Foot)
    {
        auto& character = static_cast<Character&>(*mParent);
        character.startFootContact();
    }
    else if (mType == Jump)
    {
        auto& enemy = static_cast<Character&>(*mParent);
        enemy.startJumpContact();
    }
}

/// Begin sensor contact
void AFP::Sensor::beginContact(Character& character)
{
    if (mType == Vision)
    {
        auto& enemy = static_cast<Character&>(*mParent);
        enemy.newTarget(character);
    }
}

/// End sensor contact
void AFP::Sensor::endContact()
{
    if (mType == Foot)
    {
        auto& character = static_cast<Character&>(*mParent);
        character.endFootContact();
    }
    else if (mType == Jump)
    {
        auto& character = static_cast<Character&>(*mParent);
        character.endJumpContact();
    }

}

/// End sensor contact
void AFP::Sensor::endContact(Character&)
{
    if(mType == Vision)
    {
        auto& enemy = static_cast<Character&>(*mParent);
        enemy.targetOutOfVision();
    }
    if (mType == Surround)
    {
        auto& enemy = static_cast<Character&>(*mParent);
        enemy.noTarget();
    }

}
