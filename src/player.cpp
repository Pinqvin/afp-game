#include "player.hpp"

AFP::Player::Player(void)
{
}

void AFP::Player::drawCurrent(sf::RenderTarget& target, 
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);
}