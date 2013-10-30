/// GUI Container
///
/// Contains all GUI components and is used to select and
/// activate them
#pragma once

#include <AFP/GUI/Component.hpp>

#include <vector>

namespace AFP
{
    namespace GUI
    {

        class Container : public Component
        {
        public:
            typedef std::shared_ptr<Container> Ptr;

            /// Constructor
            ///
            ///
            Container(void);

            /// Pack container
            ///
            /// Adds a component to the container
            void pack(Component::Ptr component);

            /// Is selectable
            ///
            /// Container is not selectable so return false
            virtual bool isSelectable() const;

            /// Handle event
            ///
            /// Handles keyboard events
            virtual void handleEvent(const sf::Event& event);

        private:
            /// Draw
            ///
            /// Calls draw for all components
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            /// Has selection
            ///
            /// Return true if something is selected
            bool hasSelection();

            /// Select
            ///
            /// Select component based on index and deselects
            /// last selection
            void select(std::size_t index);

            /// Select next
            ///
            /// Selects next component that is selectable
            void selectNext();

            /// Select previous
            ///
            /// Selects previous component that is selectable
            void selectPrevious();

        private:
            /// Children
            ///
            /// Contains all components
            std::vector<Component::Ptr> mChildren;

            /// Selected child
            ///
            /// Only one child is selected at a time
            int mSelectedChild;

        };

    }
}
