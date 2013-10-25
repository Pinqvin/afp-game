/// Category defines the different types of game objects
///
///

#pragma once

namespace AFP
{
    namespace Category
    {
        /// All the different categories besides None have one of
        /// their bits set to 1. This way we can send commands to
        /// multiple object categories at once by using the bitwise
        /// OR operator.
        enum Type
        {
            None = 0,
            Scene = 1 << 0,
            PlayerCharacter = 1 << 1,
            AlliedCharacter = 1 << 2,
            EnemyCharacter = 1 << 3,
            Collectable = 1 << 4,
            AlliedProjectile = 1 << 5,
            EnemyProjectile = 1 << 6,
            DestroyableTile = 1 << 7,
            StaticTile = 1 << 8,

            Tile = DestroyableTile | StaticTile,
            Character = PlayerCharacter | AlliedCharacter | EnemyCharacter,
            Projectile = AlliedProjectile | EnemyProjectile,

        };

    }

}

