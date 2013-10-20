#include <AFP/ContactListener.h>

void BeginContact(b2Contact* contact) {
  
      
      void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

      /// If the body has user data, call the startContact-function of the member
      if (bodyAUserData){
        static_cast<Entity*>(bodyAUserData)->startContact();
      }

      if (bodyBUserData){
        static_cast<Entity*>(bodyAUserData)->startContact();
      }

    }

