/// Game state is the main state for the program
///
///

#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <AFP/State/State.hpp>
#include <AFP/World.hpp>

// Forward declaration
namespace AFP
{
    class StateStack;
    class Player;

}

namespace AFP
{
    class GameState : public State
    {
        public:
            /// Constructor
            ///
            ///
            GameState (StateStack& stack, Context context);

            /// Destructor
            ~GameState();

            /// Draw the state
            ///
            /// Draws the state (eg. the world)
            virtual void draw();

            /// Update the state
            ///
            /// Updates the state by updating the game world.
            /// Returns true if we can continue relaying the updates
            /// further down the state stack, false otherwise
            virtual bool update(sf::Time dt);

            /// Handle events
            ///
            /// Handles events by passing them over to the
            /// game world. Returns true if we can continue relaying
            /// the updates further down the state stack, false
            /// otherwise
            virtual bool handleEvent(const sf::Event& event);

        private:
            /// The game world
            ///
            /// Game state mainly relays the events the world
            World mWorld;

            /// Pointer to the player
            ///
            /// Most of our events/input comes from the player
            Player& mPlayer;

            /// @brief The name of the current level.
            ///
            /// If the player dies, we set the stack level to be the same level
            /// again
            std::string mCurrentLevel;

            /// @brief Pointer to state stack
            ///
            /// Used to set level to the current level if the player dies
            StateStack& mStack;

    };

}

