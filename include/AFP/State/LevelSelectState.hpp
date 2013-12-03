/// Level selection state
///
/// In this state, player can select different levels.
#pragma once
#include <AFP/State/State.hpp>
#include <AFP/State/StateStack.hpp>
#include <AFP/GUI/Container.hpp>
#include <AFP/GUI/Button.hpp>
#include <AFP/GUI/Label.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace AFP
{
    class LevelSelectState: public State
    {
    public:
        /// Constructor
        ///
        ///
        LevelSelectState(StateStack& stack, Context context);

        /// Draw
        ///
        /// Draw current state
        virtual void draw();

        /// Update
        ///
        /// Update state
        virtual bool update(sf::Time dt);

        /// Handle events
        ///
        /// Handles events in current state
        virtual bool handleEvent(const sf::Event& event);

    private:
        /// Background sprite
        ///
        ///
        sf::Sprite mBackgroundSprite;

        /// GUI Object container
        ///
        ///
        GUI::Container mGUIContainer;

    };
}

