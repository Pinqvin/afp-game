/// Implementation for Player class

#include "player.hpp"
#include "resourceholder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

AFP::Player::Player(const TextureHolder& textures): 
    mSprite(textures.get(Textures::Player))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void AFP::Player::drawCurrent(sf::RenderTarget& target, 
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

