/// Implementation for the World class.

#include <AFP/World.hpp>
#include <AFP/Scene/SpriteNode.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Sound/SoundNode.hpp>
#include <AFP/Particles/ParticleNode.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Box2D/Common/b2Draw.h>
#include <iostream>

/// Constructor
AFP::World::World(sf::RenderWindow& window, SoundPlayer& sounds,
        std::string mapFile):
    mWindow(window), mWorldView(window.getDefaultView()), mTextures(),
    mSceneGraph(), mSceneLayers(), mMap(mapFile, mTextures), mWorldBounds(),
    mSpawnPosition(), mPlayerCharacter(nullptr), mCommandQueue(),
    mWorldBox(), mGroundBody(), mBoxDebugDraw(window, mWorldBounds),
    mDebugMode(false), mCameraPosition(), mContactListener(), mSounds(sounds), mGameUI()
{
    mWorldBounds.left = 0.f;
    mWorldBounds.top = 0.f;
    mWorldBounds.width = static_cast <float>
        (mMap.getWorldWidth());
    mWorldBounds.height = static_cast <float>
        (mMap.getWorldHeight());

    createWorld();
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);

}

/// Load all the textures and tilesets required for the world.
void AFP::World::loadTextures()
{
    mTextures.load("AFP::Textures::TelepoliceStopped", "Media/Textures/telepolice_stopped.png");
    mTextures.load("AFP::Textures::TelepoliceRunning", "Media/Textures/telepolice_running.png");
    mTextures.load("AFP::Textures::TelepoliceDying", "Media/Textures/telepolice_dying.png");
    mTextures.load("AFP::Textures::Droid", "Media/Textures/droid.png");
    mTextures.load("AFP::Textures::Explosion", "Media/Textures/explosion.png");
    mTextures.load("AFP::Textures::Box16", "Media/Textures/Box_16.png");
    mTextures.load("AFP::Textures::Box16Destroy", "Media/Textures/Box_16_explode.png");
    mTextures.load("AFP::Textures::Box16Coin", "Media/Textures/Box_16_coin.png");
    mTextures.load("AFP::Textures::Box16CoinDestroy", "Media/Textures/Box_16_coin_explode.png");
    mTextures.load("AFP::Textures::Box16Orb", "Media/Textures/Box_16_orb.png");
    mTextures.load("AFP::Textures::Box16OrbDestroy", "Media/Textures/Box_16_orb_explode.png");
    mTextures.load("AFP::Textures::Box32", "Media/Textures/Box_32.png");
    mTextures.load("AFP::Textures::Box32Destroy", "Media/Textures/Box_32_explode.png");
    mTextures.load("AFP::Textures::Bullet", "Media/Textures/Bullet.png");
    mTextures.load("AFP::Textures::Coin", "Media/Textures/Coin.png");
    mTextures.load("AFP::Textures::Orb", "Media/Textures/orb.png");
    mTextures.load("AFP::Textures::Particle", "Media/Textures/Particle.png");
    mTextures.load("AFP::Textures::PlayerStopped", "Media/Textures/Rag_Stopped.png");
    mTextures.load("AFP::Textures::PlayerRunning", "Media/Textures/Rag_Running.png");
    mTextures.load("AFP::Textures::PlayerJumping", "Media/Textures/Rag_Jumping.png");
    mTextures.load("AFP::Textures::PlayerFalling", "Media/Textures/Rag_Falling.png");
    mTextures.load("AFP::Textures::PlayerDying", "Media/Textures/Rag_Dying.png");
    mTextures.load("AFP::Textures::HpBar", "Media/Textures/hp_bar.png");
    mTextures.load("AFP::Textures::TeleBar", "Media/Textures/tele_bar.png");

}

/// Build the scene depicted by the world. Parses the map file to build
/// the scene properly
void AFP::World::buildScene()
{
    mMap.addBackgroundLayers(mSceneLayers, mSceneGraph, mWorldBounds);
    mMap.addObjectLayers(mGroundBody);

    /// Create a layer for entities
    Category::Type category = Category::Scene;

    SceneNode::Ptr layer(new SceneNode(category));
    mSceneLayers.push_back(layer.get());

    /// Attach it to scenegraph
    mSceneGraph.attachChild(std::move(layer));

    /// Scene layer is the top layer
    int topLayer = mSceneLayers.size() - 1;

    // Point user data to foreground
    mGroundBody->SetUserData(mSceneLayers[topLayer]);

    // Add sound effect node
    std::unique_ptr<SoundNode> soundNode(new SoundNode(mSounds));
    mSceneGraph.attachChild(std::move(soundNode));

    // Add particle node to the scene
    std::unique_ptr<ParticleNode> bloodNode(new ParticleNode(Particle::Blood, mTextures));
    mSceneLayers[topLayer]->attachChild(std::move(bloodNode));

    /// Set the player to the world
    std::unique_ptr<Character> leader(new Character(Character::Player, mTextures));
    mPlayerCharacter = leader.get();

    mPlayerCharacter->createCharacter(mWorldBox, mSpawnPosition.x, mSpawnPosition.y);
    mPlayerCharacter->setPosition(mPlayerCharacter->getPosition());
    mCameraPosition = mPlayerCharacter->getPosition();

    mSceneLayers[topLayer]->attachChild(std::move(leader));

    /// Create a test tile in box2D world
    std::unique_ptr<Tile> testTile(new Tile(Tile::Box16Orb, mTextures));

    testTile->createTile(mWorldBox, 200.f, 400.f);
    testTile->setPosition(testTile->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testTile));

        /// Create a test tile in box2D world
    std::unique_ptr<Tile> testTile2(new Tile(Tile::Box16Coin, mTextures));

    testTile2->createTile(mWorldBox, 230.f, 400.f);
    testTile2->setPosition(testTile2->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testTile2));

        /// Create a test tile in box2D world
    std::unique_ptr<Tile> testTile3(new Tile(Tile::Box32, mTextures));

    testTile3->createTile(mWorldBox, 260.f, 400.f);
    testTile3->setPosition(testTile3->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testTile3));

    /// Create a test coin in box2D world
    std::unique_ptr<Collectable> testCoin(new Collectable(Collectable::Coin, mTextures));

    testCoin->createCollectable(mWorldBox, 200.f, 300.f);
    testCoin->setPosition(testCoin->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testCoin));

    /// Create a test enemy
    std::unique_ptr<Character> enemy(new Character(Character::Telepolice, mTextures));

    enemy->createCharacter(mWorldBox, 500.0f, 200.0f);
    enemy->setPosition(enemy->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(enemy));

    /// Set textures to Game UI
    mGameUI.setTextures(mTextures);

}

/// Create the physics world
void AFP::World::createWorld()
{
    b2Vec2 gravity(0.0f, GRAVITY);
    mWorldBox = new b2World(gravity);

    // Set up contact listener
    mWorldBox->SetContactListener(&mContactListener);

    b2BodyDef bodyDef;
    b2EdgeShape groundBox;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;

    bodyDef.position.Set(0, 0);
    mGroundBody = mWorldBox->CreateBody(&bodyDef);

    // Creates walls around area
    // Ground
    fixtureDef.friction = 0.35f;
    groundBox.Set(b2Vec2(0, mWorldBounds.height / PTM_RATIO),
        b2Vec2(mWorldBounds.width / PTM_RATIO, mWorldBounds.height / PTM_RATIO));
    mGroundBody->CreateFixture(&fixtureDef);

    // Rest of the walls
    fixtureDef.friction = 0.0f;
    groundBox.Set(b2Vec2(0, 0), b2Vec2(mWorldBounds.width / PTM_RATIO, 0));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(0, 0), b2Vec2(0, mWorldBounds.height / PTM_RATIO));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(mWorldBounds.width / PTM_RATIO, mWorldBounds.height / PTM_RATIO),
        b2Vec2(mWorldBounds.width / PTM_RATIO, 0));
    mGroundBody->CreateFixture(&fixtureDef);

    /// Setup debug info
    mWorldBox->SetDebugDraw(&mBoxDebugDraw);

    /// Set basic flags for debug drawing
    mBoxDebugDraw.SetFlags(b2Draw::e_shapeBit);

}

/// Draw the scene to the window
void AFP::World::draw()
{
    mWindow.setView(mWorldView);
    for (auto it = mSceneLayers.begin(); it != mSceneLayers.end() - 1; ++it)
    {
        mWindow.draw(**it);

    }

    mWindow.draw(mMap);
    mWindow.draw(*mSceneLayers[mSceneLayers.size() - 1]);

    if (mDebugMode)
    {
        mWorldBox->DrawDebugData();

    }

    /// Draw Game UI on top of everything
    mWindow.draw(mGameUI);

}

/// Update the world
void AFP::World::update(sf::Time dt)
{

    moveCamera();

    // Calculate mouse translation and pass it to player character
    sf::Vector2f viewCenter = mWorldView.getCenter();
    sf::Vector2f halfExtents = mWorldView.getSize() / 2.0f;
    sf::Vector2f translation = viewCenter - halfExtents;
    mPlayerCharacter->setMouseTranslation(translation);

    /// Forward commands to the scene graph
    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    }

    // Update Box2D world
    mWorldBox->Step(UPDATE_PER_FRAME, 6, 2);

    // Remove destroyed entities
    mSceneGraph.removeWrecks();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt, mCommandQueue);

    // Update sounds
    updateSounds();

    mGameUI.update(translation, mPlayerCharacter->getHitpoints(), mPlayerCharacter->getTeleCharge());

}

/// Return the command queue
AFP::CommandQueue& AFP::World::getCommandQueue()
{
    return mCommandQueue;

}

/// Return true when player is marked for removal
bool AFP::World::isPlayerAlive()
{
    return !mPlayerCharacter->isMarkedForRemoval();
}

void AFP::World::moveCamera()
{
    // Moves world view depending on player position
    sf::Vector2f playerPosition = mPlayerCharacter->getPosition();

    // Moves camera smoothly
    mCameraPosition += (playerPosition - mCameraPosition) / CAMERA_SPEED;

    // If position is too close to world boundaries, camera is not moved
    if ( mCameraPosition.x < (mWorldView.getSize().x / 2) ) {
        mCameraPosition.x = mWorldView.getSize().x / 2;
    } else if ( mCameraPosition. x > (mWorldBounds.width - (mWorldView.getSize().x / 2)) ) {
        mCameraPosition.x = mWorldBounds.width - mWorldView.getSize().x / 2;
    }

    if ( mCameraPosition.y < (mWorldView.getSize().y / 2) ) {
        mCameraPosition.y = mWorldView.getSize().y / 2;
    } else if ( mCameraPosition. y > (mWorldBounds.height - (mWorldView.getSize().y / 2)) ) {
        mCameraPosition.y = mWorldBounds.height - mWorldView.getSize().y / 2;
    }

    mWorldView.setCenter(mCameraPosition);
}

/// Update listener position and remove stopped sounds
void AFP::World::updateSounds()
{
    // Set listener's position to player position
    mSounds.setListenerPosition(mPlayerCharacter->getWorldPosition());

    // Remove unused sounds
    mSounds.removeStoppedSounds();
}

