/// This is a class for tile objects in the game
///
/// Tiles are static box2d objects

#pragma once

#include "entity.hpp"

namespace AFP
{
    class Tile : public Entity
    {

    public:
        Tile(void);

        enum Type {
            Grass,
            Metal,
            Dicks
        };

        /// Creates a tile
        ///
        /// Create a tile based on tile type.
        void createTile(b2World* world, float posX, float posY, Type type);

    private:
        
        Type mType;

    };
}
