/// Implementation for data tables
#include <AFP/Entity/DataTables.hpp>

/// Initialize character data
std::vector<AFP::CharacterData> AFP::initializeCharacterData()
{
    std::vector<AFP::CharacterData> data(AFP::Character::TypeCount);

    data[AFP::Character::Player].hitpoints = 100;
    data[AFP::Character::Player].telecharge = 100;
    data[AFP::Character::Player].speed = 10.0f;
    data[AFP::Character::Player].jumpStrength = -40.0f;
    data[AFP::Character::Player].weapon = Character::Shotgun;
    data[AFP::Character::Player].texture = AFP::Textures::Player;

    data[AFP::Character::Enemy].hitpoints = 100;
    data[AFP::Character::Enemy].telecharge = 100;
    data[AFP::Character::Enemy].speed = 10.0f;
    data[AFP::Character::Enemy].jumpStrength = -10.0f;
    data[AFP::Character::Enemy].weapon = Character::Pistol;
    data[AFP::Character::Enemy].texture = AFP::Textures::Enemy;

    return data;
}

/// Initialize projectile data
std::vector<AFP::ProjectileData> AFP::initializeProjectileData()
{
    std::vector<AFP::ProjectileData> data(AFP::Projectile::TypeCount);

    data[AFP::Projectile::Bullet].damage = 10;
    data[AFP::Projectile::Bullet].speed = 40.0f;
    data[AFP::Projectile::Bullet].spread = 60.0f;
    data[AFP::Projectile::Bullet].texture = AFP::Textures::Bullet;

    data[AFP::Projectile::Shot].damage = 5;
    data[AFP::Projectile::Shot].speed = 40.0f;
    data[AFP::Projectile::Shot].spread = 10.0f;
    data[AFP::Projectile::Shot].texture = AFP::Textures::Bullet;

    return data;

}

/// Initialize tile data
std::vector<AFP::TileData> AFP::initializeTileData()
{
    std::vector<AFP::TileData> data(AFP::Tile::TypeCount);

    data[AFP::Tile::Grass].hitpoints = 1;
    data[AFP::Tile::Grass].destroyable = false;
    data[AFP::Tile::Grass].texture = AFP::Textures::GrassTile;

    return data;

}

/// Initialize collectable data
std::vector<AFP::CollectableData> AFP::initializeCollectableData()
{
    std::vector<AFP::CollectableData> data(AFP::Collectable::TypeCount);

    data[AFP::Collectable::Coin].texture = AFP::Textures::Coin;

    return data;
}

/// Initialize weapon data
std::vector<AFP::WeaponData> AFP::initializeWeaponData()
{
    std::vector<AFP::WeaponData> data(AFP::Character::WeaponTypeCount);

    data[AFP::Character::Pistol].firerate = 300.0f;
    data[AFP::Character::Pistol].recoil = 0.0f;
    data[AFP::Character::Pistol].bullets = AFP::Projectile::Bullet;

    data[AFP::Character::Machinegun].firerate = 50.0f;
    data[AFP::Character::Machinegun].recoil = 1.2f;
    data[AFP::Character::Machinegun].bullets = AFP::Projectile::Bullet;

    data[AFP::Character::Shotgun].firerate = 1000.0f;
    data[AFP::Character::Shotgun].recoil = 1.0f;
    data[AFP::Character::Shotgun].bullets = AFP::Projectile::Shot;

    return data;
}