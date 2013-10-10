/// World class describes the game world and the players view in to it
///
///

#ifndef WORLD_HPP
#define WORLD_HPP

#include "resourceholder.hpp"
#include "resourceidentifiers.hpp"
#include "scenenode.hpp"
#include "character.hpp"
#include "commandqueue.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <Box2D/Box2D.h>
#include <array>

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
            /// Constructor
            ///
            ///
            explicit World(sf::RenderWindow& window);

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

            /// Adapts the player position
            ///
            /// Don't allow the player to go out of bounds
            void adaptPlayerPosition();

            /// Adapts the player velocity
            ///
            /// If moving diagonaly, reduce velocity
            void adaptPlayerVelocity();

            /// Create world with gravity
            ///
            /// Build the Box2D world.
            void createWorld();

            /// Divite the draws to two different categories: background
            /// (the area the player can't interract with) and foreground
            ///
            /// LayerCount isn't used to differentiate layers, it's used to
            /// keep a count of the different layers.
            enum Layer
            {
                Background,
                Foreground,
                LayerCount
            };

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
            std::array<SceneNode*, LayerCount> mSceneLayers;

            /// Defines the world bounds
            ///
            /// Player can't go out of bounds so we need to define the
            /// limits.
            sf::FloatRect mWorldBounds;
            
            /// Defines the player's spawn position in the world
            ///
            /// 
            sf::Vector2f mSpawnPosition;

            /// Defines the speed the world scrolls at
            ///
            /// Most likely set to the same as the player's speed
            float mScrollSpeed;

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

            /// Ground body definition
            ///
            ///
            b2BodyDef mBodyDef;

            /// Ground body
            ///
            ///
            b2Body* mGroundBody;

            /// Ground polygon
            ///
            ///
            b2PolygonShape mGroundBox;

    };

}

#endif // WORLD_HPP

