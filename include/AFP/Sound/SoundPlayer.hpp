/// Sound Player
///
/// Sound player plays sounds
#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <AFP/Resource/ResourceHolder.hpp>

#include <list>

namespace AFP
{
    namespace SoundEffect
    {
        enum ID
        {
            Pistol,
        };
    }

    typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;

    class SoundPlayer : private sf::NonCopyable
    {
    public:
        /// Constructor
        ///
        ///
        SoundPlayer(void);

        /// Play sound
        ///
        /// Push sound to buffer and play it
        void play(SoundEffect::ID effect);

        /// Play sound
        ///
        /// Play sound in a position
        void play(SoundEffect::ID effect, sf::Vector2f position);

        /// Remove stopped sounds
        ///
        /// Remove sounds from buffer
        void removeStoppedSounds();

        /// Set listener
        ///
        /// Player is the listener
        void setListenerPosition(sf::Vector2f position);

        /// Get listener
        ///
        ///
        sf::Vector2f getListenerPosition() const;

    private:
        /// Sound Buffers
        ///
        /// Holds all sounds
        SoundBufferHolder mSoundBuffers;

        /// Sounds
        ///
        /// Currently playing sounds
        std::list<sf::Sound> mSounds;

    };
}

