/// Player class processes events
///
/// Events (movement etc) are then forwarded to the world
/// and from there to the scene graph (and game objects).

#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include "command.hpp"
#include "commandqueue.hpp"

namespace AFP
{
    class Player
    {
        public:
            /// Constructor
            ///
            /// Instantiates the default keybindings
            Player();

            /// All the different actions a player can take
            ///
            ///
            enum Action
            {
                MoveLeft,
                MoveRight,
                MoveUp,
                MoveDown,
                ActionCount

            };

            /// Handle a received event
            ///
            /// 
            void handleEvent(const sf::Event& event,
                    CommandQueue& commands);

            /// Handle real-time input
            ///
            ///
            void handleRealtimeInput(CommandQueue& commands);

            /// Assign a key to a specific action
            ///
            ///
            void assignKey(Action action, sf::Keyboard::Key key);

            /// Get the key an action is assigned to
            ///
            ///
            sf::Keyboard::Key getAssignedKey(Action action) const;

        private:
            /// Initialize actions for movement
            ///
            ///
            void initializeActions();

            /// Check if an action is a real-time action or not
            ///
            ///
            static bool isRealtimeAction(Action action);

            /// Keys are bound to specific actions
            ///
            ///
            std::map<sf::Keyboard::Key, Action> mKeyBinding;

            /// Actions are bound to specific commands
            ///
            ///
            std::map<Action, Command> mActionBinding;

    };

}

