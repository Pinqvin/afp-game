/// Implementation for data tables
#include <AFP/Entity/DataTables.hpp>

/// Initialize character data
std::vector<AFP::CharacterData> AFP::initializeCharacterData()
{
    std::vector<AFP::CharacterData> data(AFP::Character::TypeCount);

    /// Player data
    data[AFP::Character::Player].hitpoints = 100;
    data[AFP::Character::Player].telecharge = 100;
    data[AFP::Character::Player].speed = 10.0f;
    data[AFP::Character::Player].jumpStrength = -40.0f;
    data[AFP::Character::Player].weapon = Character::Pistol;

    /// Initialize animation data
    data[AFP::Character::Player].animation.resize(AFP::Character::StateCount);

    data[AFP::Character::Player].animation[AFP::Character::Stopped].texture = "AFP::Textures::PlayerStopped";
    data[AFP::Character::Player].animation[AFP::Character::Stopped].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Player].animation[AFP::Character::Stopped].frameCount = 6;
    data[AFP::Character::Player].animation[AFP::Character::Stopped].duration = sf::seconds(1);

    data[AFP::Character::Player].animation[AFP::Character::Running].texture = "AFP::Textures::PlayerRunning";
    data[AFP::Character::Player].animation[AFP::Character::Running].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Player].animation[AFP::Character::Running].frameCount = 8;
    data[AFP::Character::Player].animation[AFP::Character::Running].duration = sf::seconds(1);

    data[AFP::Character::Player].animation[AFP::Character::Jumping].texture = "AFP::Textures::PlayerJumping";
    data[AFP::Character::Player].animation[AFP::Character::Jumping].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Player].animation[AFP::Character::Jumping].frameCount = 1;
    data[AFP::Character::Player].animation[AFP::Character::Jumping].duration = sf::seconds(1);

    data[AFP::Character::Player].animation[AFP::Character::Falling].texture = "AFP::Textures::PlayerFalling";
    data[AFP::Character::Player].animation[AFP::Character::Falling].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Player].animation[AFP::Character::Falling].frameCount = 1;
    data[AFP::Character::Player].animation[AFP::Character::Falling].duration = sf::seconds(1);

    data[AFP::Character::Player].animation[AFP::Character::Dying].texture = "AFP::Textures::PlayerDying";
    data[AFP::Character::Player].animation[AFP::Character::Dying].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Player].animation[AFP::Character::Dying].frameCount = 6;
    data[AFP::Character::Player].animation[AFP::Character::Dying].duration = sf::seconds(0.5);

    /// Telepolice data
    data[AFP::Character::Telepolice].hitpoints = 100;
    data[AFP::Character::Telepolice].telecharge = 100;
    data[AFP::Character::Telepolice].speed = 10.0f;
    data[AFP::Character::Telepolice].jumpStrength = -10.0f;
    data[AFP::Character::Telepolice].weapon = Character::Pistol;

    /// Initialize animation data
    data[AFP::Character::Telepolice].animation.resize(AFP::Character::StateCount);

    data[AFP::Character::Telepolice].animation[AFP::Character::Stopped].texture = "AFP::Textures::Telepolice";
    data[AFP::Character::Telepolice].animation[AFP::Character::Stopped].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Telepolice].animation[AFP::Character::Stopped].frameCount = 6;
    data[AFP::Character::Telepolice].animation[AFP::Character::Stopped].duration = sf::seconds(1);

    data[AFP::Character::Telepolice].animation[AFP::Character::Running].texture = "AFP::Textures::Telepolice";
    data[AFP::Character::Telepolice].animation[AFP::Character::Running].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Telepolice].animation[AFP::Character::Running].frameCount = 1;
    data[AFP::Character::Telepolice].animation[AFP::Character::Running].duration = sf::seconds(1);

    data[AFP::Character::Telepolice].animation[AFP::Character::Jumping].texture = "AFP::Textures::Telepolice";
    data[AFP::Character::Telepolice].animation[AFP::Character::Jumping].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Telepolice].animation[AFP::Character::Jumping].frameCount = 1;
    data[AFP::Character::Telepolice].animation[AFP::Character::Jumping].duration = sf::seconds(1);

    data[AFP::Character::Telepolice].animation[AFP::Character::Falling].texture = "AFP::Textures::Telepolice";
    data[AFP::Character::Telepolice].animation[AFP::Character::Falling].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Telepolice].animation[AFP::Character::Falling].frameCount = 1;
    data[AFP::Character::Telepolice].animation[AFP::Character::Falling].duration = sf::seconds(1);

    data[AFP::Character::Telepolice].animation[AFP::Character::Dying].texture = "AFP::Textures::Telepolice";
    data[AFP::Character::Telepolice].animation[AFP::Character::Dying].frameSize = sf::Vector2i(48,48);
    data[AFP::Character::Telepolice].animation[AFP::Character::Dying].frameCount = 1;
    data[AFP::Character::Telepolice].animation[AFP::Character::Dying].duration = sf::seconds(1);

    return data;
}

/// Initialize projectile data
std::vector<AFP::ProjectileData> AFP::initializeProjectileData()
{
    std::vector<AFP::ProjectileData> data(AFP::Projectile::TypeCount);

    data[AFP::Projectile::Bullet].damage = 10;
    data[AFP::Projectile::Bullet].speed = 40.0f;
    data[AFP::Projectile::Bullet].spread = 60.0f;
    data[AFP::Projectile::Bullet].texture = "AFP::Textures::Bullet";

    data[AFP::Projectile::Shot].damage = 5;
    data[AFP::Projectile::Shot].speed = 40.0f;
    data[AFP::Projectile::Shot].spread = 10.0f;
    data[AFP::Projectile::Shot].texture = "AFP::Textures::Bullet";

    return data;

}

/// Initialize tile data
std::vector<AFP::TileData> AFP::initializeTileData()
{
    std::vector<AFP::TileData> data(AFP::Tile::TypeCount);

    data[AFP::Tile::Grass].hitpoints = 1;
    data[AFP::Tile::Grass].destroyable = false;
    data[AFP::Tile::Grass].texture = "AFP::Textures::GrassTile";

    return data;

}

/// Initialize collectable data
std::vector<AFP::CollectableData> AFP::initializeCollectableData()
{
    std::vector<AFP::CollectableData> data(AFP::Collectable::TypeCount);

    data[AFP::Collectable::Coin].texture = "AFP::Textures::Coin";

    return data;
}

/// Initialize weapon data
std::vector<AFP::WeaponData> AFP::initializeWeaponData()
{
    std::vector<AFP::WeaponData> data(AFP::Character::WeaponTypeCount);

    data[AFP::Character::Pistol].firerate = 300;
    data[AFP::Character::Pistol].recoil = 0.0f;
    data[AFP::Character::Pistol].bullets = AFP::Projectile::Bullet;
    data[AFP::Character::Pistol].sound = AFP::SoundEffect::Pistol;

    data[AFP::Character::Machinegun].firerate = 50;
    data[AFP::Character::Machinegun].recoil = 1.2f;
    data[AFP::Character::Machinegun].bullets = AFP::Projectile::Bullet;
    data[AFP::Character::Machinegun].sound = AFP::SoundEffect::Pistol;

    data[AFP::Character::Shotgun].firerate = 1000;
    data[AFP::Character::Shotgun].recoil = 1.0f;
    data[AFP::Character::Shotgun].bullets = AFP::Projectile::Shot;
    data[AFP::Character::Shotgun].sound = AFP::SoundEffect::Pistol;

    return data;
}

/// Initialize particle data
std::vector<AFP::ParticleData> AFP::initializeParticleData()
{
    std::vector<AFP::ParticleData> data(AFP::Particle::ParticleCount);

    data[AFP::Particle::Smoke].color = sf::Color(255, 255, 50);
    data[AFP::Particle::Smoke].lifetime = sf::seconds(0.6f);

    data[AFP::Particle::Blood].color = sf::Color(255,0,0);
    data[AFP::Particle::Blood].lifetime = sf::seconds(0.6f);

    return data;
}
