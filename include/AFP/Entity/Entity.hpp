/// This is the base class for entities in the game
///
/// Contains the data and functionality that all
/// different kinds of entities have in common.

#pragma once

#include <AFP/Scene/SceneNode.hpp>

namespace AFP
{
    class Entity : public SceneNode
    {
    public:
        /// @brief Constructor
        Entity();

        /// Set velocity
        ///
        /// Sets the velocity of the entity
        void setVelocity(b2Vec2 velocity);

        /// Set velocity
        ///
        /// Applies an impulse to the entity
        void applyImpulse(b2Vec2 impulse);

        /// Update the movement
        ///
        /// Update the movement done in deltaTime
        virtual void updateCurrent(sf::Time dt);

        /// Get velocity
        ///
        /// Returns the linear velocity of the entity
        b2Vec2 getVelocity() const;

        /// Get velocity
        ///
        /// Returns the mass of the entity
        float getMass() const;

        /// Create body for entity
        ///
        ///
        void createBody(b2World* world, float posX, float posY,
            float sizeX, float sizeY, float density,
            float friction, bool staticBody);

        /// Return position of body
        ///
        /// Converts position from meters to pixels and returns it.
        sf::Vector2f getBodyPosition();

        /// Return the angle of the body
        ///
        ///
        float getBodyAngle();

    private:

        /// Body
        ///
        ///
        b2Body* mBody;

    };

}

