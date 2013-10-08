/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "resourceidentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
	class Player : public Entity
	{
	public:
		Player(const TextureHolder& textures);

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

#endif // PLAYER_HPP

