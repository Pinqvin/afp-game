/// Implementation for SoundPlayer class
#include <AFP/Sound/SoundPlayer.hpp>

#include <SFML/Audio/Listener.hpp>
#include <cmath>

namespace
{
    const float ListenerZ = 300.0f;
    const float Attenuation = 8.0f;
    const float MinDistance2D = 200.0f;
    const float MinDistance3D =
        std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

/// Constructor
AFP::SoundPlayer::SoundPlayer(void):
    mSoundBuffers(), mSounds()
{
    mSoundBuffers.load(SoundEffect::Pistol, "Media/Sound/pistol.wav");

    // Listener points towards the screen (default in SFML)
    sf::Listener::setDirection(0.f, 0.f, -1.f);
}

/// Play sound
void AFP::SoundPlayer::play(SoundEffect::ID effect)
{
    play(effect, getListenerPosition());

}

/// Play sound
void AFP::SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(effect));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.play();
}

/// Remove stopped sounds
void AFP::SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

/// Set listener position
void AFP::SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

/// Return listener position
sf::Vector2f AFP::SoundPlayer::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}
