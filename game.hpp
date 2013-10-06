/// This is the main class for the game
///
/// Game class handles all the main loops (main game loop, update loop
/// event loop and rendering).

#include <SFML/Graphics.hpp>

#ifndef GAME_HH
#define GAME_HH

namespace AFP
{
    
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
            void update();

            /// Render to window
            ///
            /// Used to render all the game objects etc. to the window
            void render();

            /// Handles the player input
            ///
            /// Handles the player input based on the type of events
            /// received in the eventhandler.
            void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
            
            /// The game window
            ///
            /// Main game window
            sf::RenderWindow mWindow;

            /// Player
            ///
            /// "Player"
            sf::CircleShape mPlayer;

            /// Booleans related to playermovement.
            ///
            /// Really basic and shitty way to accomplish this
            /// TODO: Fix this ugly ass shit
            bool mIsMovingUp;
            bool mIsMovingDown;
            bool mIsMovingLeft;
            bool mIsMovingRight;

    };

};

#endif

