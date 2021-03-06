/// Implementation for music player class
#include <AFP/Sound/MusicPlayer.hpp>
#include <stdexcept>

/// Constructor
AFP::MusicPlayer::MusicPlayer(void):
    mMusic(), mFilenames(), mVolume(50.0f)
{
    /// Set filenames
    mFilenames[Music::MenuTheme] = "Media/Music/MenuTheme.ogg";
    mFilenames[Music::MainTheme] = "Media/Music/TeleportHeroActionMusic.ogg";
}

/// Start playing
void AFP::MusicPlayer::play(Music::ID theme)
{
    std::string filename = mFilenames[theme];

    if (!mMusic.openFromFile(filename))
    {
        throw std::runtime_error("Music " + filename + " could not be loaded.");
    }

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();

}

/// Stop playing
void AFP::MusicPlayer::stop()
{
    mMusic.stop();
}

/// Pause or resume playing
void AFP::MusicPlayer::setPaused(bool paused)
{
    if(paused)
    {
        mMusic.pause();
    }
    else
    {
        mMusic.play();
    }
}

/// Set volume level
void AFP::MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
}
