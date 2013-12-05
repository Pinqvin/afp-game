/// Implementation for MapParser

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <AFP/Parsers/MapParser.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Scene/SpriteNode.hpp>
#include <AFP/Utility.hpp>

#include <stdexcept>
#include <iostream>

AFP::MapParser::MapParser(std::string fileName, TextureHolder& textures): mTileLayers(),
    mTextures(textures)
{
    mMap.ParseFile(fileName);

    if (mMap.HasError())
    {
        throw std::runtime_error("World::World (constructor): Map is faulty. "
                "Error: " + mMap.GetErrorText());

    }

    /// Load tilesets and images to the textureholder
    for (int i = 0; i < mMap.GetNumTilesets(); ++i)
    {
        const Tmx::Tileset* tileSet = mMap.GetTileset(i);

        mTextures.load(tileSet->GetName(),
                "Media/Maps/" + tileSet->GetImage()->GetSource());

    }

    for (int i = 0; i < mMap.GetNumImageLayers(); ++i)
    {
        const Tmx::ImageLayer* imageLayer = mMap.GetImageLayer(i);

        mTextures.load(imageLayer->GetName(),
                "Media/Maps/" + imageLayer->GetImage()->GetSource());

    }

    parseTileLayers();

}

AFP::MapParser::~MapParser()
{

}

float AFP::MapParser::getWorldWidth() const
{
    return static_cast <float> (mMap.GetWidth() * mMap.GetTileWidth());

}

float AFP::MapParser::getWorldHeight() const
{
    return static_cast <float> (mMap.GetHeight() * mMap.GetTileHeight());

}

const Tmx::Map* AFP::MapParser::getMap() const
{
    return &mMap;

}

void AFP::MapParser::parseTileLayers()
{
    /// Initialize the different scene layers and the tiles in them
    for (int i = 0; i < mMap.GetNumLayers(); ++i)
    {
        const Tmx::Layer* tileLayer = mMap.GetLayer(i);
        TileLayer layer;

        /// Allocate as many vertex arrays as there are tilesets
        for (auto it = mMap.GetTilesets().begin(); it != mMap.GetTilesets().end(); ++it)
        {
            layer.vertexArrays.push_back(sf::VertexArray(sf::Quads));

        }

        /// Go through the tiles
        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                unsigned int currentTile = tileLayer->GetTileId(x, y);

                /// There's no tile if it's zero
                if (currentTile == 0)
                {
                    continue;

                }

                const Tmx::Tileset* tileset =
                    mMap.GetTileset(tileLayer->GetTileTilesetIndex(x, y));

                int tileWidth = mMap.GetTileWidth();
                int tileHeight = mMap.GetTileHeight();
                int tileSpacing = tileset->GetSpacing();
                int tileMargin = tileset->GetMargin();

                /// Tile position in the world
                sf::Vector2f position;
                position.x = x * tileWidth;
                position.y = y * tileHeight;

                tileWidth = tileset->GetTileWidth();
                tileHeight = tileset->GetTileHeight();

                sf::Uint8 opacity = static_cast <sf::Uint8> (255.f * layer.opacity);
                sf::Color color = sf::Color(255u, 255u, 255u, opacity);

                /// Tile vertices
                sf::Vertex v0;
                sf::Vertex v1;
                sf::Vertex v2;
                sf::Vertex v3;

                v0.position = sf::Vector2f(static_cast <float> (position.x),
                        static_cast <float> (position.y));
                v1.position = sf::Vector2f(static_cast <float> (position.x) +
                        static_cast <float> (tileWidth), static_cast <float> (position.y));
                v2.position = sf::Vector2f(static_cast <float> (position.x) +
                        static_cast <float> (tileWidth), static_cast <float> (position.y) +
                        static_cast <float> (tileHeight));
                v3.position = sf::Vector2f(static_cast <float> (position.x),
                        static_cast <float> (position.y) + static_cast <float> (tileHeight));

                /// Sprite position in the tilesheet
                sf::IntRect tileSpritePosition;

                /// Tile sprite's coordinates in the tileset
                int tileX = currentTile % ((tileset->GetImage()->GetWidth()
                            - tileMargin) / (tileWidth + tileSpacing));
                int tileY = currentTile / ((tileset->GetImage()->GetWidth()
                            - tileMargin) / (tileHeight + tileSpacing));

                tileSpritePosition.left = tileX * (tileWidth + tileSpacing)
                    + tileMargin;
                tileSpritePosition.top = tileY * (tileHeight + tileSpacing)
                    + tileMargin;
                tileSpritePosition.width = tileWidth;
                tileSpritePosition.height = tileHeight;

                /// Apply half a pixel offset to avoid artifacting when scrolling
                v0.texCoords = sf::Vector2f(static_cast <float> (tileSpritePosition.left),
                        static_cast <float> (tileSpritePosition.top)) + sf::Vector2f(0.5f, 0.5f);
                v1.texCoords = sf::Vector2f(static_cast <float> (tileSpritePosition.left + tileSpritePosition.width),
                        static_cast <float> (tileSpritePosition.top)) + sf::Vector2f(-0.5f, 0.5f);
                v2.texCoords = sf::Vector2f(static_cast <float> (tileSpritePosition.left + tileSpritePosition.width),
                        static_cast <float> (tileSpritePosition.top + tileSpritePosition.height)) +
                        sf::Vector2f(-0.5f, -0.5f);
                v3.texCoords = sf::Vector2f(static_cast <float> (tileSpritePosition.left),
                        static_cast <float> (tileSpritePosition.top + tileSpritePosition.height)) +
                        sf::Vector2f(0.5f, -0.5f);

                v0.color = color;
                v1.color = color;
                v2.color = color;
                v3.color = color;

                int index = tileLayer->GetTileTilesetIndex(x, y);

                layer.vertexArrays[index].append(v0);
                layer.vertexArrays[index].append(v1);
                layer.vertexArrays[index].append(v2);
                layer.vertexArrays[index].append(v3);

            }

        }

        mTileLayers.push_back(layer);

    }

}

void AFP::MapParser::addBackgroundLayers(std::vector <SceneNode*>& sceneLayers,
        SceneNode& spriteGraph, const sf::FloatRect worldBounds)
{
    /// Initialize the different tiling backround layers
    for (int i = 0; i < mMap.GetNumImageLayers(); ++i)
    {
        SceneNode::Ptr layer(new SceneNode(Category::None));
        sceneLayers.push_back(layer.get());

        /// Add background layers to spritegraph
        spriteGraph.attachChild(std::move(layer));

        const Tmx::ImageLayer* imageLayer = mMap.GetImageLayer(i);
        const Tmx::PropertySet layerProperties = imageLayer->GetProperties();

        if (layerProperties.HasProperty("repeat") &&
            layerProperties.GetLiteralProperty("repeat") == "true")
        {
            /// Set backround texture to be tiled
            sf::Texture& texture = mTextures.get(imageLayer->GetName());
            sf::IntRect textureRect(worldBounds);
            texture.setRepeated(true);

            /// Make the texture as big as the world bounds
            std::unique_ptr<SpriteNode> backgroundSprite(
                    new SpriteNode(texture, textureRect));

            backgroundSprite->setPosition(
                    worldBounds.left,
                    worldBounds.top);
            sceneLayers.back()->attachChild(std::move(backgroundSprite));

        }
        else if (layerProperties.HasProperty("repeatVertical") &&
                layerProperties.GetLiteralProperty("repeatVertical") == "true")
        {
            /// Tile texture vertically
            sf::Texture& texture = mTextures.get(imageLayer->GetName());
            sf::IntRect textureRect(0.f, 0.f, worldBounds.width,
                    texture.getSize().y);
            texture.setRepeated(true);

            std::unique_ptr<SpriteNode> backgroundSprite(
                    new SpriteNode(texture, textureRect));

            if (!layerProperties.HasProperty("height"))
            {
                throw std::runtime_error("World::buildScene(): Missing property"
                        " height from vertical image layer!");

            }

            /// Set tiled image to the correct height. In tiled the height is
            /// set as the number of pixels from the bottom
            int height = layerProperties.GetNumericProperty("height");

            backgroundSprite->setPosition(
                    worldBounds.left,
                    mMap.GetHeight() * mMap.GetTileHeight() - height -
                    texture.getSize().y);
            sceneLayers.back()->attachChild(std::move(backgroundSprite));

        }

    }

}

void AFP::MapParser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::View view  = target.getView();
    sf::FloatRect bounds;
    bounds.left = view.getCenter().x - (view.getSize().x / 2.f);
    bounds.top = view.getCenter().y - (view.getSize().y / 2.f);
    bounds.width = view.getSize().x;
    bounds.height = view.getSize().y;

    bounds.left -= static_cast<float>(mMap.GetTileWidth());
    bounds.top -= static_cast<float>(mMap.GetTileHeight());
    bounds.width += static_cast<float>(mMap.GetTileWidth() * 2);
    bounds.height += static_cast<float>(mMap.GetTileHeight() * 2);

    for (auto layer : mTileLayers)
    {
        for (unsigned int i = 0; i < layer.vertexArrays.size(); ++i)
        {
            /// Only draw vertices in view
            if (layer.vertexArrays[i].getBounds().intersects(bounds))
            {
                states.texture = &mTextures.get(mMap.GetTileset(i)->GetName());
                target.draw(layer.vertexArrays[i], states);

            }

        }

    }

}

