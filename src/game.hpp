/// This is the main class for the game
///
/// Game class handles all the main loops (main game loop, update loop
/// event loop and rendering).

#ifndef GAME_HPP
#define GAME_HPP

#include "world.hpp"
#include "player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace AFP
{
    class Game : sf::NonCopyable
    {
        public:
            /// Game constructor
            /// 
            /// Sets the window size for the game and
            /// constructs all the required entities to
            /// run the game
            Game();

            /// Game loop
            ///
            /// Main game loop, calls the eventhandler, game-logic update
            /// and rendering as long as the window is open.
            void run();

        private:
            /// Process player input
            ///
            /// This functon handles all the input made by the player
            void processInput();

            /// Update game logic
            ///
            /// Updates the game logic
            void update(sf::Time deltaTime);

            /// Render to window
            ///
            /// Used to render all the game objects etc. to the window
            void render();

            /// Handles the player input
            ///
            /// Handles the player input based on the type of events
            /// received in the eventhandler.
            void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
            
            /// Used to show debug statistics/info
            ///
            /// Updates different debug statistics
            void updateStatistics(sf::Time elapsedTime);

            /// The game window
            ///
            /// Main game window
            sf::RenderWindow mWindow;

            /// Game update logic uses fixed time-steps. Game logic is
            /// fixed to 60 frames per second
            static const sf::Time TIME_PER_FRAME;

            /// Fonts and text displayed by the debug window
            sf::Font mFont;
            sf::Text mStatisticsText;
            sf::Time mStatisticsUpdateTime;

            /// Frame count used for FPS counter in the debug/statistics
            /// window
            std::size_t mStatisticsNumFrames;

            /// Boolean used to determine if we want to show debug info
            /// or not
            bool mShowDebug;

            /// The game world
            ///
            /// Depicts what is shown to the user and updates all the
            /// game logic inside the depicted world
            World mWorld;

            /// The player
            ///
            /// Used to handle events and input from the player
            Player mPlayer;

    };

}

#endif // GAME_HPP

