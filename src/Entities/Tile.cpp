/// Kommentoikaa nyt ne vitun tiedostot ja funktiot

#include <AFP/Entity/Tile.hpp>


AFP::Tile::Tile(void)
{
}

void AFP::Tile::createTile(b2World* world, float posX, float posY, Type type)
{
    switch (type)
    {
    case AFP::Tile::Grass:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f, true);
        break;
    case AFP::Tile::Metal:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.3f, 0.5f, true);
        break;
    case AFP::Tile::Dicks:
        createBody(world, posX, posY, 1.0f, 1.0f, 1.2f, 0.8f, true);
        break;
    default:
        break;
    }

}
