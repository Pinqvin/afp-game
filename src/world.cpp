/// Implementation for the World class.

#include "world.hpp"
#include "spritenode.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

/// Constructor
AFP::World::World(sf::RenderWindow& window):
    mWindow(window), mWorldView(window.getDefaultView()),
    mTextures(), mSceneGraph(), mSceneLayers(),
    mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
    mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f),
    mScrollSpeed(-50.f), mPlayerCharacter(nullptr), mCommandQueue()
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);

    createWorld();

}

/// Load all the textures required for the world
void AFP::World::loadTextures()
{
    mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Enemy, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

}

/// Build the scene depicted by the world
void AFP::World::buildScene()
{
    /// Initialize the different scene layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));

    }

    /// Set the background texture to be tiled
    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    /// Make the background sprite as big as the whole world
    std::unique_ptr<SpriteNode> backgroundSprite(
            new SpriteNode(texture, textureRect));

    backgroundSprite->setPosition(
            mWorldBounds.left,
            mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    /// Set the player to the world
    std::unique_ptr<Character> leader(new Character(Character::Player, mTextures));
    mPlayerCharacter = leader.get();

    mPlayerCharacter->setPosition(mSpawnPosition);
    mPlayerCharacter->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Foreground]->attachChild(std::move(leader));

    /// Add some new planes to follow the player plane
    std::unique_ptr<Character> leftEscort(new Character(Character::Enemy, mTextures));
    /// Position is relative to the leader (player)
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerCharacter->attachChild(std::move(leftEscort));

    std::unique_ptr<Character> rightEscort(new Character(Character::Enemy, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerCharacter->attachChild(std::move(rightEscort));
    
}

/// Create the physics world
void AFP::World::createWorld()
{
    b2Vec2 gravity(0.0f, -9.81f);
    mWorldBox = new b2World(gravity);

    mBodyDef.position.Set(0.0f, -10.0f);
    mGroundBody = mWorldBox->CreateBody(&mBodyDef);   
    mGroundBox.SetAsBox(50.0f, 10.0f);    
    mGroundBody->CreateFixture(&mGroundBox, 0.0f);
}

/// Draw the scene to the window
void AFP::World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);

}

/// Update the world
void AFP::World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    mPlayerCharacter->setVelocity(0.f, 0.f);

    /// Forward commands to the scene graph
    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    }

    adaptPlayerVelocity();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt);
    adaptPlayerPosition();

}

/// Adapt player position and correct it if out of bounds
void AFP::World::adaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, at least
    // borderDistance units from the border.
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    float borderDistance = 40.f;

    sf::Vector2f position = mPlayerCharacter->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

    mPlayerCharacter->setPosition(position);

}

/// Adapt player velocity
void AFP::World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayerCharacter->getVelocity();

    // If moving diagonally, redce velocity (to have alway same
    // velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        mPlayerCharacter->setVelocity(velocity / std::sqrt(2.f));

    }

    // Add scrolling velocity
    mPlayerCharacter->accelerate(0.f, mScrollSpeed);

}

/// Return the command queue
AFP::CommandQueue& AFP::World::getCommandQueue()
{
    return mCommandQueue;

}
