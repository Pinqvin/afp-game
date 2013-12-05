/// World class describes the game world and the player's view in to it
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
#include <AFP/GUI/GameUI.hpp>
#include <AFP/Parsers/MapParser.hpp>

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
            explicit World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds,
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

            /// Return player status
            ///
            /// Returns true when player is destroyed and
            /// is marked for removal.
            bool isPlayerAlive();

            ///
            ///
            /// Check level win condition
            bool hasPlayerReachedTheEnd();

            ///
            ///
            /// Return next level
            std::string getNextLevel();

            /// @brief Sets the debug mode to on or off
            ///
            /// Debug mode is set in the game state when F12 is pressed
            void setDebug();

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

            /// @brief Parses the Tmx file for different object layers
            /// and adds the objects to the scenegraph
            void addObjectLayers();

            /// @brief Adds collision objects to the Box2D ground body
            ///
            /// @param objectGroup The collision object group
            void addCollisionObjects(const Tmx::ObjectGroup* objectGroup);

            /// @brief Adds the character entities to the scene graph
            ///
            /// @param objectGroup The character object group
            void addCharacterObjects(const Tmx::ObjectGroup* objectGroup);

            /// @brief Adds the object entities to the scene graph
            ///
            /// @param objectGroup The object entity object group
            void addObjects(const Tmx::ObjectGroup* objectGroup);

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

            /// Differentiate scene nodes by their layer
            ///
            ///
            std::vector<SceneNode*> mSceneLayers;

            /// @brief The parsed map file. Used to draw the tile layers
            ///
            /// Also used to parse object and image layers in to the scenegraph
            MapParser mMap;

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

            /// Game UI
            ///
            /// Used for displaying various types of information
            /// on the screen.
            GameUI mGameUI;

            /// Next level
            ///
            ///
            std::string mNextLevel;

    };

}

