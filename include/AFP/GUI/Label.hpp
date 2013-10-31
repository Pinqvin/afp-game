/// GUI Text object
///
/// Used to display text
#pragma once

#include <AFP/GUI/Component.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Text.hpp>

namespace AFP
{
    namespace GUI
    {

        class Label : public Component
        {
        public:
            typedef std::shared_ptr<Label> Ptr;

            /// Constructor
            ///
            ///
            Label(const std::string& text, const FontHolder& fonts);
            
            /// Is selectable
            ///
            /// Returns false
            virtual bool isSelectable() const;

            /// Set Text
            ///
            /// Set label text to text
            void setText(const std::string& text);

            /// Handle event
            ///
            ///
            virtual void handleEvent(const sf::Event& event);

            /// Get bounding rectangle
            ///
            /// Returns a empty rectangle
            virtual sf::FloatRect getBoundingRect() const;

        private:
            /// Draw
            ///
            /// Draw label
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            /// Text
            ///
            ///
            sf::Text mText;
        };

    }
}
