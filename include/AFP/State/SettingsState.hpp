/// SettingsState class
///
///
#pragma once

#include <AFP/State/State.hpp>
#include <AFP/Input/Player.hpp>
#include <AFP/GUI/Container.hpp>
#include <AFP/GUI/Button.hpp>
#include <AFP/GUI/Label.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

namespace AFP
{
    class SettingsState: public State
    {
    public:
        /// Constructor
        ///
        ///
        SettingsState(StateStack& stack, Context context);

        /// Draw
        ///
        ///
        virtual void draw();
        
        /// Update
        ///
        ///
        virtual bool update(sf::Time dt);
        
        /// Handle event
        ///
        ///
        virtual bool handleEvent(const sf::Event& event);

    private:
        /// Update labels
        ///
        ///
        void updateLabels();
        
        /// Add button label
        ///
        ///
        void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

    private:
        /// Background sprite
        ///
        ///
        sf::Sprite mBackgroundSprite;
        
        /// GUI Object container
        ///
        ///
        GUI::Container mGUIContainer;
        
        /// Binding buttons
        ///
        ///
        std::array<GUI::Button::Ptr, Player::ActionCount> mBindingButtons;
        
        /// Binding labels
        ///
        ///
        std::array<GUI::Label::Ptr, Player::ActionCount> mBindingLabels;

    };
}
