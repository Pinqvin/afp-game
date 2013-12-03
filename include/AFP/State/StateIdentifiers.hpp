/// All the different states in the game have
/// their unique identifiers defined here.
///
/// This includes states like game, pause
/// etc.

#pragma once

namespace AFP
{
    namespace States
    {
        enum ID
        {
            None,
            Title,
            Menu,
            Load,
            Game,
            Pause,
            Settings,
            LevelSelect,
        };

    }

}

