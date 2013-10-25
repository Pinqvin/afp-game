/// Implementation of ContactListener class
#include <AFP/ContactListener.hpp>

void AFP::ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    /// If the body has user data, call the startContact-function of the member
    if (bodyAUserData){
        static_cast<Entity*>(bodyAUserData)->startContact();

    }

    if (bodyBUserData){
        static_cast<Entity*>(bodyBUserData)->startContact();
    }

    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    //if fixtureA is the character's foot sensor
    // Foot sensor is the only fixture with user data
    if (fixtureUserData)
    {
        static_cast<Character*>(fixtureUserData)->startFootContact();
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    //if fixtureB is the character's foot sensor
    if (fixtureUserData)
    {
        static_cast<Character*>(fixtureUserData)->startFootContact();
    }
}

void AFP::ContactListener::EndContact(b2Contact* contact)
{
    // Updates jump sensor when ending contact
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if (fixtureUserData)
    {
        static_cast<Character*>(fixtureUserData)->endFootContact();
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if (fixtureUserData)
    {
        static_cast<Character*>(fixtureUserData)->endFootContact();
    }
}

