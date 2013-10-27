/// Music Player
///
/// Plays music
#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>

namespace AFP
{
    namespace Music
    {
        enum ID
        {
            MenuTheme,
        };
    }


    class MusicPlayer : private sf::NonCopyable
    {
    public:
        /// Constructor
        ///
        ///
        MusicPlayer(void);

        /// Start playing
        ///
        ///
        void play(Music::ID theme);

        /// Stop playing
        ///
        ///
        void stop();

        /// Set Paused
        /// 
        /// Set paused state depending on parameter
        void setPaused(bool paused);

        /// Set Volume
        ///
        /// Set volume depending on parameter
        void setVolume(float volume);

    private:
        /// Music object
        ///
        /// SFML music object
        sf::Music mMusic;

        /// Filenames
        ///
        /// Filenames mapped with ID
        std::map<Music::ID, std::string> mFilenames;

        /// Volume
        ///
        ///
        float mVolume;

    };
}