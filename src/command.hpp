/// Command is a message sent to various game objects
///
/// Commands can alter objects and issue orders (moving, firing a weapon
/// etc).

#pragma once

#include <SFML/System/Time.hpp>
#include "category.hpp"
#include <functional>
#include <cassert>

/// Forward declaration
namespace AFP
{
    class SceneNode;

}

namespace AFP
{
    struct Command
    {
        /// Constructor
        Command();

        /// Action to send
        std::function<void(SceneNode&, sf::Time)> action;

        /// Categories to send the action to
        unsigned int category;

    };

    /// derivedAction takes a function from a derived class and
    /// converts it in to a function on the base class
    template <typename GameObject, typename Function>
    std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
    {
        return [=] (SceneNode& node, sf::Time dt)
        {
            /// Check cast safety
            assert(dynamic_cast<GameObject*> (&node) != nullptr);

            /// Downcast node and invoke function on it
            fn(static_cast<GameObject&> (node), dt);

        };

    }

}

