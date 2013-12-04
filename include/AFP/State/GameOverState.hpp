/// Game over state is triggered when player dies or completes a level. 
///
///

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <AFP/State/State.hpp>

namespace AFP
{
    class GameOverState : public State
    {
        public:
            /// Constructor
            ///
            ///
            GameOverState(StateStack& stack, State::Context context);

            /// Destructor
            ///
            ///
            ~GameOverState();

            /// Draw the state
            ///
            ///
            virtual void draw();

            /// Update the state
            ///
            ///
            virtual bool update(sf::Time dt);

            /// Handle events in the state
            ///
            /// Handles key presses in this state.
            virtual bool handleEvent(const sf::Event& event);

        private:
            /// Background sprite for the pause state
            sf::Sprite mBackgroundSprite;

            /// Game over text
            sf::Text mGameOverText;

            /// Instruction text
            sf::Text mInstructionText;

    };

}

