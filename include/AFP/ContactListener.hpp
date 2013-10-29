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
        /// Handles Body to Body contacts
        void beginContactB2B(SceneNode::Pair& collisionPair);

        /// Begin contact
        ///
        /// Handles Body to Fixture contacts
        void beginContactB2F(SceneNode::Pair& collisionPair);

        /// Begin contact
        ///
        /// Handles Fixture to Fixture contacts
        void beginContactF2F(SceneNode::Pair& collisionPair);

        /// End contact
        ///
        /// Handles Body to Body contacts
        void endContactB2B(SceneNode::Pair& collisionPair);

        /// End contact
        ///
        /// Handles Body to Fixture contacts
        void endContactB2F(SceneNode::Pair& collisionPair);

        /// End contact
        ///
        /// Handles Fixture to Fixture contacts
        void endContactF2F(SceneNode::Pair& collisionPair);

        /// Check if categories match
        ///
        /// If categories match, return true. If categories are in wrong order
        /// swap them and return true.
        bool matchesCategories(SceneNode::Pair& colliders, 
            Category::Type type1, Category::Type type2);

    };

}