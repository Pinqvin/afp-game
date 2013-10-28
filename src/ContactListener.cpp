/// Implementation of ContactListener class
#include <AFP/ContactListener.hpp>
#include <iostream>

void AFP::ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    // Check that user data exists
    if (bodyAUserData && bodyBUserData)
    {
        // Make a pair of entities
        SceneNode::Pair collisionPair(static_cast<SceneNode*>(bodyAUserData), static_cast<SceneNode*>(bodyBUserData));

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
        // Player collides with a collectable
        else if (matchesCategories(collisionPair, Category::PlayerCharacter, Category::Collectable))
        {
            // Cast into correct classes
            auto& player = static_cast<Character&>(*collisionPair.first);
            auto& collectable = static_cast<Collectable&>(*collisionPair.second);

            collectable.apply(player);
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
        // Projectile collides with walls
        else if (matchesCategories(collisionPair, Category::Projectile, Category::Scene))
        {
            auto& projectile = static_cast<Projectile&>(*collisionPair.first);
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
bool AFP::ContactListener::matchesCategories(SceneNode::Pair& colliders,
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
