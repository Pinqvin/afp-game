/// Title state comes before the main menu
///
///

#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.hpp"

// Forward declaration

namespace AFP
{
    class StateStack;

}

namespace AFP
{
    class TitleState : public State
    {
        public:
            /// Constructor
            ///
            ///
            TitleState(StateStack& stack, Context context);

            /// Destructor
            ~TitleState();

            /// Draw the title state/screen
            ///
            /// Draws the content of the title state
            virtual void draw();

            /// Updates the title state
            ///
            /// Returns true if we can continue on updating
            /// the states further down the stack, false
            /// otherwise.
            virtual bool update(sf::Time dt);

            /// Handle an event in this state
            ///
            /// Returns true if we can continue on propagating
            /// the event to states further down the stack,
            /// false otherwise.
            virtual bool handleEvent(const sf::Event& event);

        private:
            /// Text rendered in the title state
            ///
            ///
            sf::Text mText;

            /// Describes whether we draw the title text or not
            bool mShowText;

            /// The time it takes for the text to appear and disappear
            sf::Time mTextEffectTime;

    };

}

