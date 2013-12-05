/// Implementation of ContactListener class
#include <AFP/ContactListener.hpp>
#include <iostream>

/// Begin contact
void AFP::ContactListener::BeginContact(b2Contact* contact)
{
    SceneNode::Pair collisionPair;
    // Try to create a pair and return if not a valid pair
    if (!createPair(contact, collisionPair))
    {
        return;
    }

    // Check collision pairs
    // Allied bullet collides with enemy or enemy bullet collides with allied character
    if(matchesCategories(collisionPair, Category::Character, Category::Projectile))
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

        if (collectable.apply(player))
        {
            collectable.destroy();
        }

    }
    // Projectile collides with tile
    else if (matchesCategories(collisionPair, Category::Projectile, Category::Tile))
    {
        auto& projectile = static_cast<Projectile&>(*collisionPair.first);
        auto& tile = static_cast<Tile&>(*collisionPair.second);

        tile.damage(projectile.getDamage());
        projectile.destroy();
    }
    // Projectile collides with walls
    else if (matchesCategories(collisionPair, Category::Projectile, Category::Scene))
    {
        auto& projectile = static_cast<Projectile&>(*collisionPair.first);
        projectile.destroy();
    }
    // Sensor collides with scene
    else if (matchesCategories(collisionPair, Category::Sensor, Category::Scene))
    {
        auto& sensor = static_cast<Sensor&>(*collisionPair.first);

        sensor.beginContact();
    }
    // Sensor collides with player
    else if (matchesCategories(collisionPair, Category::Sensor, Category::PlayerCharacter))
    {
        auto& sensor = static_cast<Sensor&>(*collisionPair.first);
        auto& player = static_cast<Character&>(*collisionPair.second);

        sensor.beginContact(player);

    }

}

/// End contact
void AFP::ContactListener::EndContact(b2Contact* contact)
{
    SceneNode::Pair collisionPair;
    if (!createPair(contact, collisionPair))
    {
        return;
    }

    // Sensor ends contact with scene
    if (matchesCategories(collisionPair, Category::Sensor, Category::Scene))
    {
        auto& sensor = static_cast<Sensor&>(*collisionPair.first);

        sensor.endContact();
    }

    // Sensor ends contact with player
    else if (matchesCategories(collisionPair, Category::Sensor, Category::PlayerCharacter))
    {
        auto& sensor = static_cast<Sensor&>(*collisionPair.first);
        auto& player = static_cast<Character&>(*collisionPair.second);

        sensor.endContact(player);

    }
}

/// Create a collision pair from given parameters
bool AFP::ContactListener::createPair(b2Contact* contact, SceneNode::Pair& collisionPair)
{
    // Get user datas
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

    // Check sensors
    bool sensorA = contact->GetFixtureA()->IsSensor();
    bool sensorB = contact->GetFixtureB()->IsSensor();

    // Both are sensors -> nothing happens
    if (sensorA && sensorB)
    {
        return false;
    }

    // A is entity and B is sensor
    if (bodyAUserData && fixtureBUserData && sensorB)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureBUserData);
    }
    // B is entity and A is sensor
    else if (bodyBUserData && fixtureAUserData && sensorA)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyBUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureAUserData);
    }

    // Both are entities
    else if (bodyAUserData && bodyBUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(bodyBUserData);
    }
    else
    {
        return false;
    }

    return true;
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
