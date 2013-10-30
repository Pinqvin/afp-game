/// GUI Component
///
/// Base class for various components of the GUI
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>

/// Forward declaration
namespace sf
{
    class Event;
}

namespace AFP
{

    namespace GUI
    {
        class Component : public sf::Drawable
                        , public sf::Transformable
                        , private sf::NonCopyable
        {
        public:
            typedef std::shared_ptr<Component> Ptr;

            /// Constructor
            ///
            ///
            Component(void);
            
            /// Destructor
            ///
            ///
            virtual ~Component();

            /// Is selectable
            ///
            ///
            virtual bool isSelectable() const = 0;

            /// Is selected
            ///
            /// Return mIsSelected
            bool isSelected() const;

            /// Select
            ///
            /// Set mIsSelected true
            virtual void select();

            /// Deselect
            ///
            /// Set mIsSelected false
            virtual void deselect();

            /// Is active
            ///
            /// Return mIsActive
            virtual bool isActive() const;

            /// Activate
            ///
            /// Set mIsActive true
            virtual void activate();

            /// Deactivate
            ///
            /// Set mIsActive false
            virtual void deactivate();

            /// Handle event
            ///
            ///
            virtual void handleEvent(const sf::Event& event) = 0;

        private:
            /// Is selected
            ///
            /// Set to true if component is selected
            /// Set to false if component is not selected
            bool mIsSelected;

            /// Is active
            ///
            /// Set to true if component is active
            /// Set to false if component is not active
            bool mIsActive;

        };

    }
}