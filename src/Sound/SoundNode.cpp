/// Implementation for SoundNode class
#include <AFP/Sound/SoundNode.hpp>

/// Constructor
AFP::SoundNode::SoundNode(SoundPlayer& player):
    mSounds(player)
{
}

/// Play a sound
void AFP::SoundNode::playSound(SoundEffect::ID sound, sf::Vector2f position)
{
    mSounds.play(sound, position);

}

/// Return SoundEffect category
unsigned int AFP::SoundNode::getCategory() const
{
    return Category::SoundEffect;
}