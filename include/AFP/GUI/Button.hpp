/// GUI Button object
///
/// Creates a button in the GUI
#pragma once

#include <AFP/GUI/Component.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace AFP
{
    namespace GUI
    {

        class Button : public Component
        {
        public:
            typedef std::shared_ptr<Button> Ptr;
            typedef std::function<void()> Callback;

            /// Constructor
            ///
            ///
            Button(const FontHolder& fonts, const TextureHolder& textures);
            
            /// Set callback
            ///
            /// Set a callback function to the button
            void setCallback(Callback callback);

            /// Set Text
            ///
            /// Set a label for the button
            void setText(const std::string& text);

            /// Set toggle
            ///
            /// Set the button to be toggleable
            void setToggle(bool flag);

            /// Is selectable
            ///
            /// Returns true
            virtual bool isSelectable() const;

            /// Select
            ///
            /// Selects the button
            virtual void select();

            /// Deselect
            ///
            /// Deselects the button
            virtual void deselect();

            /// Activate
            ///
            /// Activates the button. If button is toggleable
            /// sets texture to pressed.
            virtual void activate();

            /// Deactivate
            ///
            /// Deactivates the button. If button is toggleable
            /// sets texture back to normal.
            virtual void deactivate();

            /// Handle event
            ///
            ///
            virtual void handleEvent(const sf::Event& event);

        private:
            /// Draw
            ///
            /// Draws the button
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            /// Callback
            ///
            /// Callback function to be called when the button
            /// is activated.
            Callback mCallback;

            /// Normal texture
            ///
            /// Normal texture of the button.
            const sf::Texture& mNormalTexture;

            /// Selected texture
            ///
            /// Texture of the button when it is selected.
            const sf::Texture& mSelectedTexture;
            
            /// Pressed texture
            ///
            /// Texture of the button when it is pressed.
            const sf::Texture& mPressedTexture;
            
            /// Button sprite
            ///
            ///
            sf::Sprite mSprite;
            
            /// Button text
            ///
            ///
            sf::Text mText;
            
            /// Is toggle
            ///
            /// Set to true if button is toggleable
            bool mIsToggle;

        };

    }

}
