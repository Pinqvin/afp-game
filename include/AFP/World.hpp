/// World class describes the game world and the players view in to it
///
///

#pragma once

#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Entity/Character.hpp>
#include <AFP/Entity/Tile.hpp>
#include <AFP/Entity/Collectable.hpp>
#include <AFP/Command/CommandQueue.hpp>
#include <AFP/Debug/BoxDebugDraw.hpp>
#include <AFP/ContactListener.hpp>
#include <AFP/Sound/SoundPlayer.hpp>

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <TmxParser/Tmx.h>
#include <Box2D/Box2D.h>
#include <vector>

/// Forward declaration
namespace sf
{
    class RenderWindow;

}

namespace AFP
{
    class World : private sf::NonCopyable
    {
        public:
            /// @brief World constructor
            ///
            /// Loads the necessary resources and sets the world dimensions
            /// @param window Window we render the world to
            /// @param sounds Sounds loaded in Game state are passed to the world
            /// @param mapFile Path to the map file we parse for the world
            explicit World(sf::RenderWindow& window, SoundPlayer& sounds,
                    std::string mapFile);

            /// Update the SceneGraph
            ///
            /// Updates the scenegraph
            void update(sf::Time dt);

            /// Draws the scenegraph
            ///
            /// Draws all the sprites inside the scenegraph
            void draw();

            /// Return the current command queue
            ///
            /// Allows command queue to be accessed from outside
            /// of the world
            CommandQueue& getCommandQueue();

        private:
            /// Loads all the textures required for the world
            ///
            /// Textures are stored in the mTextures TextureHolder
            void loadTextures();

            /// Builds the scene for the world
            ///
            /// Builds the scene using the textures loaded in the
            /// TextureHolder.
            void buildScene();

            /// @brief Parses and adds the image layers to the scenegraph
            ///
            /// Background layers are represented as image layers in the tiled
            /// editor. They can be either repeated on the whole worldbox
            /// (property repeat = true) or repeated vertically at a certain
            /// height (property repeatVertical = true and height = height in
            /// pixels from the bottom).
            void addBackgroundLayers();

            /// @brief Parses and adds the tile layers to the scenegraph
            ///
            /// The maps can have multiple tile layers with varying tilesets.
            /// The individual tiles themselves don't have hitboxes, ground
            /// areas are defined by an object layer
            void addTileLayers();

            /// @brief Parses and adds the object layers to the Box2D world
            ///
            /// Object layers can be used for collision layers, triggers, spawn
            /// points etc.
            void addObjectLayers();

            /// @brief Parse and add all the collision objects in the group
            ///
            /// @param objectGroup Holds all the collision objects
            void addCollisionObjects(const Tmx::ObjectGroup* objectGroup);

            /// Create world with gravity
            ///
            /// Build the Box2D world.
            void createWorld();

            /// Move camera
            ///
            /// Moves the camera towards the player
            void moveCamera();

            /// Update sounds
            ///
            /// Update listener positon and remove stopped sounds
            void updateSounds();

            /// Reference to the render window
            ///
            /// Used to draw all the scene nodes
            sf::RenderWindow& mWindow;

            /// The view the player has on the world
            ///
            /// Used to determine which part of the world
            /// the player can see.
            sf::View mWorldView;

            /// Holds all the textures for the world
            ///
            /// Textures are loaded during loadTextures() call.
            TextureHolder mTextures;

            /// Scene graph holds all the entities together
            ///
            ///
            SceneNode mSceneGraph;

            /// Sprite graph
            ///
            /// Sprite graph holds tiles and background
            /// No update function is called for spritegraph
            /// only draw
            SceneNode mSpriteGraph;

            /// Differentiate scene nodes by their layer
            ///
            ///
            std::vector<SceneNode*> mSceneLayers;

            /// @brief Map file holds all the physical boundaries of the map,
            /// all the objects, tile layers and their positions
            Tmx::Map mMap;

            /// Defines the world bounds
            ///
            /// Player can't go out of bounds so we need to define the
            /// limits.
            sf::FloatRect mWorldBounds;

            /// Defines the player's spawn position in the world
            ///
            ///
            sf::Vector2f mSpawnPosition;

            /// Pointer to the player entity
            ///
            ///
            Character* mPlayerCharacter;

            /// Command queue
            ///
            /// Holds all the commands which are yet to be sent to the
            /// scene.
            CommandQueue mCommandQueue;

            /// The physics world
            ///
            /// Box2D world.
            b2World* mWorldBox;

            /// Ground body
            ///
            ///
            b2Body* mGroundBody;

            /// @brief Debug class used to visualize Box2D physics world
            BoxDebugDraw mBoxDebugDraw;

            /// @brief Debug mode draws additional information like Box2D visualizations
            bool mDebugMode;

            /// Camera position
            ///
            /// Camera position in a 2D-vector
            sf::Vector2f mCameraPosition;

            /// Contact listener
            ///
            /// Contact listener instance
            AFP::ContactListener mContactListener;

            /// Sound player
            ///
            /// Sound player reference
            SoundPlayer& mSounds;

    };

}

