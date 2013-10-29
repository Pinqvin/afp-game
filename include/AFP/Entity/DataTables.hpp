/// Data tables handle all data initializion for the game
///
///
#pragma once

#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Entity/Projectile.hpp>
#include <AFP/Entity/Collectable.hpp>
#include <AFP/Entity/Tile.hpp>
#include <vector>

namespace AFP
{
    struct CharacterData
    {
        int hitpoints;
        int telecharge;
        float speed;
        float jumpStrength;
        Character::WeaponType weapon;
        Textures::ID texture;
    };

    struct ProjectileData
    {
        int damage;
        float speed;
        float spread;
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
        // TODO: Add collectible action
        Textures::ID texture;
    };

    struct WeaponData
    {
        int firerate;
        float recoil;
        Projectile::Type bullets;
    };

    // Functions to initialize different data types
    std::vector<CharacterData> initializeCharacterData();
    std::vector<ProjectileData> initializeProjectileData();
    std::vector<TileData> initializeTileData();
    std::vector<CollectableData> initializeCollectableData();
    std::vector<WeaponData> initializeWeaponData();

}