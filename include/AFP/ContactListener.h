#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <AFP/Entity/Entity.hpp>

class ContactListener :
    public b2ContactListener
{
    void BeginContact(b2Contact* contact);

};

