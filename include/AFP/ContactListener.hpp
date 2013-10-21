/// Contact Listener
///
/// Listens and handles collisions.
#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <AFP/Entity/Entity.hpp>
#include <AFP/Entity/Character.hpp>

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

    };

}