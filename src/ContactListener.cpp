/// Implementation of ContactListener class
#include <AFP/ContactListener.hpp>

void AFP::ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    // Check that user data exists
    if (bodyAUserData && bodyBUserData)
    {
        // Make a pair of entities
        std::pair<Entity*, Entity*> collisionPair(static_cast<Entity*>(bodyAUserData), static_cast<Entity*>(bodyBUserData));

        // Check collision pairs
        // Allied bullet collides with enemy or enemy bullet collides with allied character
        if(matchesCategories(collisionPair, Category::AlliedCharacter, Category::EnemyProjectile)
            || matchesCategories(collisionPair, Category::EnemyCharacter, Category::AlliedProjectile))
        {
            // Cast to correct classes
            auto& character = static_cast<Character&>(*collisionPair.first);
            auto& projectile = static_cast<Projectile&>(*collisionPair.second);

            character.damage(projectile.getDamage());
            projectile.destroy();
        }
        // Player collides with a collectible
        else if (matchesCategories(collisionPair, Category::PlayerCharacter, Category::Collectable))
        {
            // Cast into correct classes
            auto& character = static_cast<Character&>(*collisionPair.first);
            auto& collectable = static_cast<Collectable&>(*collisionPair.second);

            collectable.destroy();
        }
        // Projectile collides with tile
        else if (matchesCategories(collisionPair, Category::Projectile, Category::Tile))
        {
            auto& projectile = static_cast<Projectile&>(*collisionPair.first);
            auto& tile = static_cast<Tile&>(*collisionPair.second);

            // Damage tile if it is destroyable
            if (tile.getCategory() & Category::DestroyableTile)
            {
                tile.damage(projectile.getDamage());
            }
            projectile.destroy();
        }

    }
    // Check projectile collisions with walls
    else if (bodyAUserData)
    {
        Entity* userData = static_cast<Entity*>(bodyAUserData);
        if (userData->getCategory() & Category::Projectile) 
        {
            auto& projectile = static_cast<Projectile&>(*userData);
            projectile.destroy();
        }
    }
    else if (bodyBUserData)
    {
        Entity* userData = static_cast<Entity*>(bodyBUserData);
        if (userData->getCategory() & Category::Projectile) 
        {
            auto& projectile = static_cast<Projectile&>(*userData);
            projectile.destroy();
        }
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

/// Match given categories
bool AFP::ContactListener::matchesCategories(std::pair<Entity*, Entity*>& colliders,
                                             Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}
