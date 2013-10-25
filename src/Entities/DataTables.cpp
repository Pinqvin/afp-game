/// Implementation for data tables
#include <AFP/Entity/DataTables.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Entity/Projectile.hpp>
#include <AFP/Entity/Collectable.hpp>
#include <AFP/Entity/Tile.hpp>

/// Initialize character data
std::vector<AFP::CharacterData> AFP::initializeCharacterData()
{
    std::vector<AFP::CharacterData> data(AFP::Character::TypeCount);

    data[AFP::Character::Player].hitpoints = 100;
    data[AFP::Character::Player].speed = 10.0f;
    data[AFP::Character::Player].jumpStrength = -40.0f;
    data[AFP::Character::Player].texture = AFP::Textures::Player;

    data[AFP::Character::Enemy].hitpoints = 100;
    data[AFP::Character::Enemy].speed = 10.0f;
    data[AFP::Character::Enemy].jumpStrength = -10.0f;
    data[AFP::Character::Enemy].texture = AFP::Textures::Enemy;

    return data;
}

/// Initialize projectile data
std::vector<AFP::ProjectileData> AFP::initializeProjectileData()
{
    std::vector<AFP::ProjectileData> data(AFP::Projectile::TypeCount);

    data[AFP::Projectile::Bullet].damage = 10;
    data[AFP::Projectile::Bullet].speed = 40.0f;
    data[AFP::Projectile::Bullet].texture = AFP::Textures::Bullet;

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