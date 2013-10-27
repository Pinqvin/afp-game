/// Application class handles events/input, rendering
/// and updates to the statestack

#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <AFP/State/StateStack.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Input/Player.hpp>
#include <AFP/Sound/MusicPlayer.hpp>
#include <AFP/Sound/SoundPlayer.hpp>

namespace AFP
{
    class Application
    {
        public:
            /// Constructor
            ///
            ///
            Application();

            /// Run method starts the game loop
            ///
            /// Called from main function
            void run();

        private:
            /// Handle input we get from events etc.
            ///
            ///
            void processInput();

            /// Update game logic in small timesteps
            ///
            ///
            void update(sf::Time dt);

            /// Render the world
            ///
            /// Renders the active states which render the
            /// world
            void render();

            /// Update debug statistics
            ///
            ///
            void updateStatistics(sf::Time dt);

            /// Register all the different states the game has
            ///
            ///
            void registerStates();

            /// Fixed time to handle the updates in
            static const sf::Time TIME_PER_FRAME;

            /// Window which we render the world through
            ///
            /// All events are polled from the window
            sf::RenderWindow mWindow;

            /// TextureHolder has all the textures we need to render
            ///
            ///
            TextureHolder mTextures;

            /// Font holder has all the required fonts
            ///
            ///
            FontHolder mFonts;

            /// Player class handles the events
            ///
            /// Events are propagated further to world and the scenegraph
            Player mPlayer;

            /// Music player
            ///
            /// Music player handles music
            MusicPlayer mMusicPlayer;

            /// Sound Player
            ///
            /// Sound player plays sounds
            SoundPlayer mSoundPlayer;

            /// State stack holds all the different states
            ///
            /// We register all the states in Application class
            StateStack mStateStack;

            /// Statistics text we render for debugging purposes
            sf::Text mStatisticsText;

            /// Time we use to calculate the length of an update with
            sf::Time mStatisticsUpdateTime;

            /// FPS counter for statistics
            std::size_t mStatisticsNumFrames;

    };

}

