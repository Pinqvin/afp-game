/// Contact Listener
///
/// Listens and handles collisions.
#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Entity/Collectable.hpp>
#include <AFP/Entity/Tile.hpp>
#include <AFP/Entity/Sensor.hpp>

namespace AFP
{

    class ContactListener : public b2ContactListener
    {
    public:

        /// Contact handler
        ///
        /// Called when two fixtures contact
        void BeginContact(b2Contact* contact);

        /// Contact handler
        ///
        /// Called when contact ends
        void EndContact(b2Contact* contact);

        /// Begin contact
        ///
        /// Handles contacts
        void beginContact(SceneNode::Pair& collisionPair);

        /// End contact
        ///
        /// Handles contacts
        void endContact(SceneNode::Pair& collisionPair);

        /// Create pair
        ///
        /// Creates a pair from collisionPair if possible
        bool createPair(b2Contact* contact, SceneNode::Pair& collisionPair);

        /// Check if categories match
        ///
        /// If categories match, return true. If categories are in wrong order
        /// swap them and return true.
        bool matchesCategories(SceneNode::Pair& colliders, 
            Category::Type type1, Category::Type type2);

    };

}
