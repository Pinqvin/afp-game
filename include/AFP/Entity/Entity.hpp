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
        Entity();

        /// Set velocity
        ///
        /// Sets the velocity of the entity
        void setVelocity(b2Vec2 velocity);

        /// Set velocity
        ///
        /// Applies an impulse to the entity
        void applyImpulse(b2Vec2 impulse);

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
            float friction, bool staticBody = false, bool isProjectile = false );

        /// Return position of body
        ///
        /// Converts position from meters to pixels and returns it.
        sf::Vector2f getPosition();

        /// Return position of body
        ///
        /// Return body position in meters.
        b2Vec2 getBodyPosition();

        /// Set position of body
        ///
        /// Set body position in meters.
        void setBodyPosition(b2Vec2 target);

        /// Return world pointer
        ///
        ///
        b2World* getWorld();

        /// Start Contact
        ///
        /// Logic applied when entity is in contact with something
        virtual void startContact() = 0;

        /// Get entity type
        ///
        /// Return type of entity
        virtual AFP::BodyType getEntityType() = 0;


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

    };

}

