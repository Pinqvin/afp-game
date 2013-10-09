/// Implementation for Character class

#include "character.hpp"
#include "resourceholder.hpp"
#include "resourceidentifiers.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Return texture based on the type
AFP::Textures::ID toTextureId(AFP::Character::Type type)
{
    switch (type)
    {
        case AFP::Character::Player:
            return AFP::Textures::Player;
            
        case AFP::Character::Enemy:
            return AFP::Textures::Enemy;

        default:
            return AFP::Textures::Player;

    }

}

AFP::Character::Character(Type type, const TextureHolder& textures): 
    mType(type), mSprite(textures.get(toTextureId(type)))
{
    /// Align the origin to the center of the texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void AFP::Character::drawCurrent(sf::RenderTarget& target, 
						   sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/// Return category based on Type
unsigned int AFP::Character::getCategory() const
{
    switch (mType)
    {
        case Player:
            return Category::PlayerCharacter;

        default:
            return Category::EnemyCharacter;

    }

}

