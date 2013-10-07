/// This is the main class for the game
///
/// Game class handles all the main loops (main game loop, update loop
/// event loop and rendering).

#include <SFML/Graphics.hpp>
#include "resourceholder.hpp"

#ifndef GAME_HPP
#define GAME_HPP

namespace AFP
{
    namespace Textures
    {
        enum ID
        {
            RagNorris
        };

    }

    namespace Fonts
    {
        enum ID
        {
            Debug
        };

    }

    class Game
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
            void processEvents();

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

            /// Resource holder for textures
            ///
            /// Handles resource loading for fonts
            ResourceHolder<sf::Texture, Textures::ID> mTextureHolder;

            /// Resource holder for fonts
            ///
            /// Handles resource loading for fonts
            ResourceHolder<sf::Font, Fonts::ID> mFontHolder;

            /// Player
            ///
            /// Player texture (image data) and the sprite
            /// (player position, orientation and frame to display)
            sf::Texture mTexture;
            sf::Sprite mPlayer;

            /// Game update logic uses fixed time-steps. Game logic is
            /// fixed to 60 frames per second
            static const sf::Time TIME_PER_FRAME;

            /// Player speed
            static const float PLAYER_SPEED;

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

            /// Booleans related to playermovement.
            ///
            /// Really basic and shitty way to accomplish this
            /// TODO: Fix this ugly ass shit
            bool mIsMovingUp;
            bool mIsMovingDown;
            bool mIsMovingLeft;
            bool mIsMovingRight;

    };

}

#endif // GAME_HPP

