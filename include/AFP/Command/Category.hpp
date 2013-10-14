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

        };

    }

}

