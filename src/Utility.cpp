/// Implementation for utility functions

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <AFP/Utility.hpp>
#include <AFP/Animation/Animation.hpp>

#include <cmath>

/// Centers sprite origin
void AFP::centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

/// Centers sprite origin
void AFP::centerOrigin(Animation& animation)
{
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));

}

/// Centers text origin
void AFP::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

