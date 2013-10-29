/// Implementation of ContactListener class
#include <AFP/ContactListener.hpp>
#include <iostream>

void AFP::ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

    SceneNode::Pair collisionPair;

    // Both are bodies
    if (bodyAUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(bodyBUserData);
        beginContactB2B(collisionPair);
    }

    // A is body and B is fixture
    if (bodyAUserData && fixtureBUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureBUserData);
        beginContactB2F(collisionPair);
    }

    // B is body and A is fixture
    if (bodyBUserData && fixtureAUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyBUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureAUserData);
        beginContactB2F(collisionPair);
    }

    // Both are fixtures
    if (fixtureAUserData && fixtureBUserData)
    {
        collisionPair.first =  static_cast<SceneNode*>(fixtureAUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureBUserData);
        beginContactF2F(collisionPair);
    }

}

void AFP::ContactListener::EndContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

    SceneNode::Pair collisionPair;

    // Both are bodies
    if (bodyAUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(bodyBUserData);
        endContactB2B(collisionPair);
    }

    // A is body and B is fixture
    if (bodyAUserData && fixtureBUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyAUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureBUserData);
        endContactB2F(collisionPair);
    }


    // B is body and A is fixture
    if (bodyBUserData && fixtureAUserData)
    {
        collisionPair.first = static_cast<SceneNode*>(bodyBUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureAUserData);
        endContactB2F(collisionPair);
    }

    // Both are fixtures
    if (fixtureAUserData && fixtureBUserData)
    {
        collisionPair.first =  static_cast<SceneNode*>(fixtureAUserData);
        collisionPair.second =  static_cast<SceneNode*>(fixtureBUserData);
        endContactF2F(collisionPair);
    }

}

/// Handle Body to Body contacts
void AFP::ContactListener::beginContactB2B(SceneNode::Pair& collisionPair)
{
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

/// Handle Body to Fixture contacts
void AFP::ContactListener::beginContactB2F(SceneNode::Pair& collisionPair)
{
    // Footsensor collides with scene
    if (matchesCategories(collisionPair, Category::Character, Category::Scene))
    {
        auto& player = static_cast<Character&>(*collisionPair.first);
        player.startFootContact();
    }
}

/// Handle Fixture to Fixture contacts
void AFP::ContactListener::beginContactF2F(SceneNode::Pair& collisionPair)
{
    // Nothing here yet
}

/// Handle ending Body to Body contacts
void AFP::ContactListener::endContactB2B(SceneNode::Pair& collisionPair)
{
    // Nothing here yet
}

/// Handle ending Body to Fixture contacts
void AFP::ContactListener::endContactB2F(SceneNode::Pair& collisionPair)
{
    // Footsensor collides with scene
    if (matchesCategories(collisionPair, Category::Character, Category::Scene))
    {
        auto& player = static_cast<Character&>(*collisionPair.first);
        player.endFootContact();
    }
}

/// Handle ending Fixture to Fixture contacts
void AFP::ContactListener::endContactF2F(SceneNode::Pair& collisionPair)
{
    // Nothing here yet
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
