/// This is the base class for entities in the game
///
/// Contains the data and functionality that all 
/// different kinds of entities have in common.

#pragma once

#include "scenenode.hpp"
#include <Box2D/Box2D.h>

namespace AFP
{
	class Entity : public SceneNode
	{
	public:
		/// Constructor
		///
		///
		Entity();

		/// Set velocity
		///
		/// Sets the velocity of the entity
		void setVelocity(sf::Vector2f velocity);

		/// Set velocity
		///
		/// Sets the velocity of the entity
		void setVelocity(float vx, float vy);

        /// Update the movement
        ///
        /// Update the movement done in deltaTime
        virtual void updateCurrent(sf::Time dt);

		/// Get velocity
		///
		/// Returns the velocity of the entity
		sf::Vector2f getVelocity() const;

        /// Accelerate entity
        ///
        /// Add the provided velocity to the current velocity
        void accelerate(sf::Vector2f velocity);

        /// Accelerate entity
        ///
        /// From a velocity vector from the provided floats and
        /// add it to the current velocity
        void accelerate(float vx, float vy);

        /// Create body for entity
        ///
        ///
        void createBody(b2World* world);

        /// Return position of body
        ///
        /// Converts position from meters to pixels and returns it.
        sf::Vector2f getBodyPosition();

	private:
		/// Velocity
		///
		/// Velocity of the entity in a 2D vector
		sf::Vector2f mVelocity;

        /// Body definition
        ///
        ///
        b2BodyDef mBodyDef;

        /// Body
        ///
        ///
        b2Body* mBody;

        /// Body boundaries
        ///
        ///
        b2PolygonShape mDynamicBox;

        /// Body fixture
        ///
        ///
        b2FixtureDef mFixtureDef;
		
	};

}

