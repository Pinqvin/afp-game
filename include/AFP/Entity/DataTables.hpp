/// Data tables handle all data initializion for the game
///
///
#pragma once

#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <vector>

namespace AFP
{
    struct CharacterData
    {
        int hitpoints;
        int telecharge;
        float speed;
        float jumpStrength;
        Textures::ID texture;
    };

    struct ProjectileData
    {
        int damage;
        float speed;
        Textures::ID texture;
    };

    struct TileData
    {
        int hitpoints;
        bool destroyable;
        Textures::ID texture;
    };

    struct CollectableData
    {
        // Add collectible action
        Textures::ID texture;
    };

    // Functions to initialize different data types
    std::vector<CharacterData> initializeCharacterData();
    std::vector<ProjectileData> initializeProjectileData();
    std::vector<TileData> initializeTileData();
    std::vector<CollectableData> initializeCollectableData();

}