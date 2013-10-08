/// Implementation for the SpriteNode class

#include "spritenode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

/// Constructor
AFP::SpriteNode::SpriteNode(const sf::Texture& texture): 
    mSprite(texture)
{


}

/// Constructor
AFP::SpriteNode::SpriteNode(const sf::Texture& texture,
        const sf::IntRect& rect): mSprite(texture, rect)
{


}

/// Draw the current SpriteNode
void AFP::SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);

}

