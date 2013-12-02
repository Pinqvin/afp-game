/// This is the sensor class
///
/// Sensor is a box2d fixture that is attached to a parent body
/// Sensors are used to detect entities in an area.
#pragma once
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Character.hpp>

namespace AFP
{
    class Sensor : public SceneNode
    {
    public:

        enum Type
        {
            Foot,
            Surround,
            Vision,
            Jump
        };

        /// Constructor
        ///
        ///
        Sensor(Entity* parent, Type type);

        /// Return sensor category
        ///
        /// Returns the sensor category based on the type
        virtual unsigned int getCategory() const;
       
        /// Create foot sensor
        ///
        /// Creates a foot sensor on feet
        void createFootSensor(float sizeX, float sizeY);
        
        /// Create vision sensor
        ///
        /// Creates a vision sensor for the entity. 
        ///Takes radius in meters and the angle in degrees as parameters
        void createVisionSensor(float radius, float angle);

        /// Create surround sensor
        ///
        /// Creates a foot sensor on feet
        void createSurroundSensor(float radius);

        /// Create foot sensor
        ///
        /// Creates a foot sensor on feet
        void createJumpSensor(float sizeX, float sizeY);

        /// Begin contact
        ///
        /// Begin contact with an entity
        void beginContact();

        /// Begin contact
        ///
        /// Begin contact with an character
        void beginContact(Character& character);

        /// End contact
        ///
        /// End contact with an entity
        void endContact();

        /// End contact
        ///
        /// End contact with a character
        void endContact(Character& character);

    private:
        /// Update
        ///
        /// Update sensor data.
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        /// Sensor fixture
        ///
        /// Sensors fixture is linked to the body of the parent.
        b2Fixture* mFixture;

        /// Parent entity
        ///
        /// Entity on which the sensor is attached to
        Entity* mParent;

        /// Type
        ///
        /// Type of the sensor
        Type mType;

    };
}

