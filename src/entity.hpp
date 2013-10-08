/// This is the base class for entities in the game
///
/// Contains the data and functionality that all 
/// different kinds of entities have in common.

#include <SFML\System.hpp>
#include "scenenode.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace AFP
{

	class Entity : public SceneNode
	{
	public:
		/// Constructor
		///
		///
		Entity(void);

		/// Set velocity
		///
		/// Sets the velocity of the entity
		void setVelocity(sf::Vector2f velocity);

		/// Set velocity
		///
		/// Sets the velocity of the entity
		void setVelocity(float vx, float vy);

		/// Get velocity
		///
		/// Returns the velocity of the entity
		sf::Vector2f getVelocity() const;

	private:
		/// Velocity
		///
		/// Velocity of the entity in a 2D vector
		sf::Vector2f mVelocity;
		
	};

}

#endif