/// Implementation for the World class.

#include <AFP/World.hpp>
#include <AFP/Scene/SpriteNode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/// Constructor
AFP::World::World(sf::RenderWindow& window):
    mWindow(window), mWorldView(window.getDefaultView()),
    mTextures(), mSceneGraph(), mSceneLayers(),
    mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
    mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f),
    mScrollSpeed(-50.f), mPlayerCharacter(nullptr), mCommandQueue(), mWorldBox(),
    mGroundBody()
{

    createWorld();
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);

}

/// Load all the textures required for the world
void AFP::World::loadTextures()
{
    mTextures.load(Textures::Enemy, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Player, "Media/Textures/Rag.png");
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
    mPlayerCharacter->createCharacter(mWorldBox, mSpawnPosition.x, mSpawnPosition.y);

    mSceneLayers[Foreground]->attachChild(std::move(leader));

    /// Create a test tile in box2D world
    /// Tile testTile;
    /// testTile.createTile(mWorldBox, mSpawnPosition.x - 32.f, 1700.f, AFP::Tile::Type::Grass);
}

/// Create the physics world
void AFP::World::createWorld()
{
    b2Vec2 gravity(0.0f, -9.81f);
    mWorldBox = new b2World(gravity);

    b2BodyDef bodyDef;
    b2EdgeShape groundBox;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;

    bodyDef.position.Set(0, 0);
    mGroundBody = mWorldBox->CreateBody(&bodyDef);

    // Creates walls around area
    groundBox.Set(b2Vec2(0, 0), b2Vec2(mWorldBounds.width / 16.f, 0));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(0, 0), b2Vec2(0, mWorldBounds.height / 16.f));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(0, mWorldBounds.height / 16.f),
        b2Vec2(mWorldBounds.width / 16.f, mWorldBounds.height / 16.f));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(mWorldBounds.width / 16.f, mWorldBounds.height / 16.f),
        b2Vec2(mWorldBounds.width / 16.f, 0));
    mGroundBody->CreateFixture(&fixtureDef);



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

    /// Moves world view depending on player position
    sf::Vector2f cameraPosition = mPlayerCharacter->getBodyPosition();

    // If position is too close to world boundaries, camera is not moved
    if ( cameraPosition.x < (mWorldView.getSize().x / 2) ) {
        cameraPosition.x = mWorldView.getSize().x / 2;
    } else if ( cameraPosition. x > (mWorldBounds.width - (mWorldView.getSize().x / 2)) ) {
        cameraPosition.x = mWorldBounds.width - mWorldView.getSize().x / 2;
    }

    if ( cameraPosition.y < (mWorldView.getSize().y / 2) ) {
        cameraPosition.y = mWorldView.getSize().y / 2;
    } else if ( cameraPosition. y > (mWorldBounds.height - (mWorldView.getSize().y / 2)) ) {
        cameraPosition.y = mWorldBounds.height - mWorldView.getSize().y / 2;
    }

    mWorldView.setCenter(cameraPosition);

    /// Forward commands to the scene graph
    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    }

    adaptPlayerVelocity();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt);
    adaptPlayerPosition();

    // Update Box2D world
    mWorldBox->Step(1.0f / 60.0f, 6, 2);

    /// Update position of rag norris
    mPlayerCharacter->setPosition(mPlayerCharacter->getBodyPosition());
    mPlayerCharacter->setRotation(mPlayerCharacter->getBodyAngle());

}

/// Adapt player position and correct it if out of bounds
void AFP::World::adaptPlayerPosition()
{
}

/// Adapt player velocity
void AFP::World::adaptPlayerVelocity()
{
}

/// Return the command queue
AFP::CommandQueue& AFP::World::getCommandQueue()
{
    return mCommandQueue;

}
