/// This is the base class for entities in the game
///
/// Contains the data and functionality that all
/// different kinds of entities have in common.

#pragma once

#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Utility.hpp>

namespace AFP
{
    class Entity : public SceneNode
    {
    public:
        /// @brief Constructor
        explicit Entity(int hitpoints);

        /// Set velocity
        ///
        /// Sets the velocity of the entity
        void setVelocity(b2Vec2 velocity);

        /// Set position of body
        ///
        /// Set body position in meters.
        void setBodyPosition(b2Vec2 target);

        /// Set velocity
        ///
        /// Applies an impulse to the entity
        void applyImpulse(b2Vec2 impulse);

        /// Apply force
        ///
        /// Applies force to the entity
        void applyForce(b2Vec2 force);

        /// Get velocity
        ///
        /// Returns the linear velocity of the entity
        b2Vec2 getVelocity() const;

        /// Get velocity
        ///
        /// Returns the mass of the entity
        float getMass() const;

        /// Return position of body
        ///
        /// Converts position from meters to pixels and returns it.
        sf::Vector2f getPosition() const;

        /// Return position of body
        ///
        /// Return body position in meters.
        b2Vec2 getBodyPosition() const;

        /// Return world pointer
        ///
        ///
        b2World* getWorld() const;

        /// Get hitpoints
        ///
        /// Return entity hitpoints
        int getHitpoints() const;

        /// Create body for entity
        ///
        ///
        void createBody(b2World* world, float posX, float posY,
            float sizeX, float sizeY, float density,
            float friction);

        /// Create head for the entity
        ///
        ///
        void createHead(b2World* world);

        /// Attach sensor
        ///
        /// Attaches a sensor to body of this entity
        b2Fixture* attachSensorToBody(const b2FixtureDef* sensor);

        /// Attach sensor
        ///
        /// Attaches a sensor to head of this entity
        b2Fixture* attachSensorToHead(const b2FixtureDef* sensor);

        /// Damage entity
        ///
        /// Decreases hitpoints
        virtual void damage(int points);

        /// Heal entity
        ///
        /// Increases hitpoints, return false if already full
        bool heal(int points);

        /// Destroy
        ///
        /// Destroy entity
        void destroy();

        /// Is entity destroyed
        ///
        /// Returns true if hitpoints are below or equal to zero
        bool isDestroyed() const;

        /// Destroy body
        ///
        /// Destroy Box2D body.
        void destroyBody();

        /// flip
        ///
        /// flips the entity's head over
        void flip(float angle);

        /// Search for enemy
        ///
        /// Flip the look-sensor around to find enemy
        void search();

        /// End searching
        ///
        ///
        void endSearch();

    protected:
        /// Update the movement
        ///
        /// Update the movement done in deltaTime
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:

        /// Body
        ///
        ///
        b2Body* mBody;

        /// Head
        ///
        ///
        b2Body* mHead;

        /// Joint that connects head to the body
        ///
        ///
        b2RevoluteJoint* mJoint;
     
        /// Hitpoints
        ///
        /// Hitpoints of the entity. Entity is destroyed when
        /// hitpoints reach zero.
        int mHitpoints;

    };

}

