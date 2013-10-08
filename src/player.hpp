/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#include <SFML\Graphics.hpp>
#include "entity.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace AFP
{
	class Player : public Entity
	{
	public:
		Player(void);

		/// Draw player sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target, 
			sf::RenderStates states) const;

	private:
		/// Player sprite
		///
		///
		sf::Sprite mSprite;

	};
}

#endif