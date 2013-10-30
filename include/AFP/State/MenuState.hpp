/// Menu state shows a simplistic menu
/// where the game can either be started or
/// stopped

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

#include <AFP/State/State.hpp>
#include <AFP/GUI/Container.hpp>

// Forward declaration
namespace AFP
{
    class StateStack;

}

namespace AFP
{
    class MenuState : public State
    {
        public:
            /// Constructor
            MenuState(StateStack& stack, State::Context context);

            /// Destructor
            ~MenuState();

            /// Draw the menu state
            virtual void draw();

            /// Updates the menu
            virtual bool update(sf::Time dt);

            /// Handle event
            ///
            /// Used to handle the player selecting different menu options
            virtual bool handleEvent(const sf::Event& event);

        private:
            /// Describes all the different options available in the menu
            enum OptionNames
            {
                Play,
                Exit

            };

            /// Background drawn for the menu
            sf::Sprite mBackgroundSprite;

            /// Contains all GUI components
            GUI::Container mGUIContainer;

    };

}

