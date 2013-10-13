/// Pause state can be activated from the game
/// and it is a special state in that it can
/// coexist with other states (mainly Game state)

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "state.hpp"

namespace AFP
{
    class PauseState : public State
    {
        public:
            /// Constructor
            PauseState(StateStack& stack, State::Context context);

            /// Destructor
            ~PauseState();

            /// Draw the pause state
            virtual void draw();

            /// Update the state
            virtual bool update(sf::Time dt);

            /// Handle events in the state
            ///
            /// In pause state this mainly means leaving
            /// the pause state or going back to the main
            /// menu.
            virtual bool handleEvent(const sf::Event& event);

        private:
            /// Background sprite for the pause state
            sf::Sprite mBackgroundSprite;

            /// Pause text
            sf::Text mPausedText;

            /// Instruction text for the pause state
            sf::Text mInstructionText;

    };

}

