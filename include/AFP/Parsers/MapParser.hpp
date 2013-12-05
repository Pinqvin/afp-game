/// @brief Map parser utilises TMXParser to parse Tiled (.tmx) based maps
///
/// MapParser itself handles the drawing off the map. It can also parse
/// object layers and image layers for the World, but it doesn't handle the
/// parsed objects or images itself.

#pragma once

#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Scene/SceneNode.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <TmxParser/Tmx.h>

#include <string>

namespace AFP
{

    /// @brief Tile layer defines one tile layer object from the tmx map
    struct TileLayer
    {
        /// @brief Constructor
        TileLayer(): opacity(1.f), vertexArrays()
        {

        };

        /// @brief Opacity from 0 to 1
        float opacity;

        /// @brief Holds all the vertex arrays
        ///
        /// Each map layer has at least as many vertex arrays as there are
        /// tilesets in the map
        std::vector <sf::VertexArray> vertexArrays;

    };

    class MapParser : public sf::Drawable, public sf::NonCopyable
    {
        public:
            /// @brief Constructor
            ///
            /// Loads the map and initializes all the map layers for drawing.
            /// Object- and imagelayer parsing is called for in the World class
            ///
            /// @param fileName file path/name to load the map from
            /// @param textures Used to save texture resources for tile drawing
            explicit MapParser(std::string fileName, TextureHolder& textures);

            /// @brief Destructor
            ~MapParser();

            /// @brief Returns the world width
            ///
            /// The world width is calculated by map width times the tile width
            ///
            /// @return World width in pixels
            float getWorldWidth();

            /// @brief Returns the world height
            ///
            /// The world height is calculated by map height times the tile height
            ///
            /// @return World height in pixels
            float getWorldHeight();

            /// @brief Parses the background layers and adds them in to the
            /// scenegraph
            ///
            /// @param sceneLayers Reference to the scene layers in World
            /// @param sceneGraph Reference to the scene graph in world
            /// @param worldBounds Bounds of the world (map)
            void addBackgroundLayers(std::vector <SceneNode*>& sceneLayers,
                    SceneNode& sceneGraph, const sf::FloatRect worldBounds);

            /// @brief Parses the object layers and adds them in to the
            /// scenegraph
            ///
            /// Called after MapParser initialization in the World constructor
            ///
            /// @param groundBody The Box2D body where the collision objects are
            /// added to
            void addObjectLayers(b2Body* groundBody);

        private:
            /// @brief Parses all the tile layers and adds them to the layers
            /// vector
            ///
            /// Gets called by the constructor
            void parseTileLayers();

            /// @brief Draw the tile layers
            ///
            /// @param target Target to draw in to
            /// @param states Defines the states used to draw in to target
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            /// @brief Adds the collision objects in the object layer to the
            /// scenegraph and Box2D physics world
            ///
            /// Called after MapParser initialization in the World constructor
            ///
            /// @param objectGroup The object group that needs to be parsed
            /// @param groundBody The Box2D body that the objects are added to
            void addCollisionObjects(const Tmx::ObjectGroup* objectGroup, b2Body* groundBody);

            /// @brief Used to parse all the map data from the tmx map file
            Tmx::Map mMap;

            /// @brief Holds all the tile layers
            ///
            /// The tile layers are rendered in the order they are added in to
            /// this vector
            std::vector <TileLayer> mTileLayers;

            /// @brief Used to store the tilesheets and image layers
            TextureHolder& mTextures;

    };

}

