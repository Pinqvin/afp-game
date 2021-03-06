/// Player class processes events
///
/// Events (movement etc) are then forwarded to the world
/// and from there to the scene graph (and game objects).

#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>

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
            /// Action count just describes the number of actions a player
            /// has (last enumerative type in the list == number of actions
            /// described before it)
            enum Action
            {
                MoveLeft,
                MoveRight,
                Jump,
                Fire,
                Teleport,
                Weapon1,
                Weapon2,
                Weapon3,
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
            /// Can be used by a GUI to assign the keys. Default values
            /// are assigned when the game is instantiated.
            void assignKey(Action action, sf::Keyboard::Key key);

            /// Assign a key to a specific action
            ///
            /// Can be used by a GUI to assign the keys. Default values
            /// are assigned when the game is instantiated.
            void assignMouseButton(Action action, sf::Mouse::Button button);

            /// Get the key an action is assigned to
            ///
            /// Returns the key the action is bound to
            sf::Keyboard::Key getAssignedKey(Action action) const;

            /// Get the mouse button an action is assigned to
            ///
            /// Returns the mouse button the action is bound to
            sf::Mouse::Button getAssignedButton(Action action) const;

            /// Set mouse position
            ///
            ///
            void setMousePosition(sf::Vector2f position);

        private:
            /// Initialize actions for movement
            ///
            /// Initialize the CharacterMover actions that move the player.
            void initializeActions();

            /// Check if an action is a real-time action or not
            ///
            /// Returns true if an action is real-time, false otherwise
            static bool isRealtimeAction(Action action);

            /// Keys are bound to specific actions
            ///
            ///
            std::map<sf::Keyboard::Key, Action> mKeyBinding;

            /// Mouse Buttons are bound to specific actions
            ///
            ///
            std::map<sf::Mouse::Button, Action> mMouseBinding;

            /// Actions are bound to specific commands
            ///
            ///
            std::map<Action, Command> mActionBinding;

            /// Mouse position
            ///
            /// Mouse position relative to window
            sf::Vector2f mMousePosition;

    };

}

