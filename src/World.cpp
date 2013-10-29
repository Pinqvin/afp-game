/// Implementation for the World class.

#include <AFP/World.hpp>
#include <AFP/Scene/SpriteNode.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Sound/SoundNode.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Box2D/Common/b2Draw.h>
#include <iostream>

#include <iostream>

/// Constructor
AFP::World::World(sf::RenderWindow& window, SoundPlayer& sounds,
        std::string mapFile):
    mWindow(window), mWorldView(window.getDefaultView()),
    mTextures(), mSceneGraph(), mSceneLayers(), mMap(),
    mWorldBounds(), mSpawnPosition(), mPlayerCharacter(nullptr),
    mCommandQueue(), mWorldBox(),
    mGroundBody(), mBoxDebugDraw(window, mWorldBounds), mDebugMode(true),
    mContactListener(), mSounds(sounds), mSpaceTimeRipped(false)
{
    mMap.ParseFile(mapFile);

    if (mMap.HasError())
    {
        throw std::runtime_error("World::World (constructor): Map is faulty. "
                "Error: " + mMap.GetErrorText());

    }

    mWorldBounds.left = 0.f;
    mWorldBounds.top = 0.f;
    mWorldBounds.width = static_cast <float>
        (mMap.GetWidth() * mMap.GetTileWidth());
    mWorldBounds.height = static_cast <float>
        (mMap.GetHeight() * mMap.GetTileHeight());

    createWorld();
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);

}

/// Load all the textures and tilesets required for the world.
void AFP::World::loadTextures()
{
    mTextures.load("AFP::Textures::Enemy", "Media/Textures/telepolice_stopped.png");
    mTextures.load("AFP::Textures::Player", "Media/Textures/Rag.png");
    mTextures.load("AFP::Textures::Desert", "Media/Textures/Desert.png");
    mTextures.load("AFP::Textures::GrassTile", "Media/Textures/Grass.png");
    mTextures.load("AFP::Textures::Bullet", "Media/Textures/Grass.png");
    mTextures.load("AFP::Textures::Coin", "Media/Textures/Coin.png");

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

}

/// Add the background layers to the scene graph
void AFP::World::addBackgroundLayers()
{
    /// Initialize the different tiling backround layers
    for (int i = 0; i < mMap.GetNumImageLayers(); ++i)
    {
        SceneNode::Ptr layer(new SceneNode(Category::None));
        mSceneLayers.push_back(layer.get());

        mSceneGraph.attachChild(std::move(layer));

        const Tmx::ImageLayer* imageLayer = mMap.GetImageLayer(i);
        const Tmx::PropertySet layerProperties = imageLayer->GetProperties();

        if (layerProperties.HasProperty("repeat") &&
                layerProperties.GetLiteralProperty("repeat") == "true")
        {
            /// Set backround texture to be tiled
            sf::Texture& texture = mTextures.get(imageLayer->GetName());
            sf::IntRect textureRect(mWorldBounds);
            texture.setRepeated(true);

            /// Make the texture as big as the world bounds
            std::unique_ptr<SpriteNode> backgroundSprite(
                    new SpriteNode(texture, textureRect));

            backgroundSprite->setPosition(
                    mWorldBounds.left,
                    mWorldBounds.top);
            mSceneLayers.back()->attachChild(std::move(backgroundSprite));

        }
        else if (layerProperties.HasProperty("repeatVertical") &&
                layerProperties.GetLiteralProperty("repeatVertical") == "true")
        {
            /// Tile texture vertically
            sf::Texture& texture = mTextures.get(imageLayer->GetName());
            sf::IntRect textureRect(0, 0, mWorldBounds.width,
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
                    mWorldBounds.left,
                    mMap.GetHeight() * mMap.GetTileHeight() - height -
                    texture.getSize().y);
            mSceneLayers.back()->attachChild(std::move(backgroundSprite));

        }

    }

}

/// Add the tile layers to the scene graph
void AFP::World::addTileLayers()
{
    /// Initialize the different scene layers and the tiles in them
    for (int i = 0; i < mMap.GetNumLayers(); ++i)
    {
        const Tmx::Layer* tileLayer = mMap.GetLayer(i);

        SceneNode::Ptr layer(new SceneNode(Category::Scene));
        mSceneLayers.push_back(layer.get());

        mSceneGraph.attachChild(std::move(layer));

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

                int tileWidth = tileset->GetTileWidth();
                int tileHeight = tileset->GetTileHeight();
                int tileSpacing = tileset->GetSpacing();
                int tileMargin = tileset->GetMargin();

                /// Tile position in the world
                sf::Vector2f position;
                position.x = x * tileWidth;
                position.y = y * tileHeight;

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

                sf::Texture& texture = mTextures.get(tileset->GetName());

                std::unique_ptr<SpriteNode> tileSprite(
                        new SpriteNode(texture, tileSpritePosition));

                tileSprite->setPosition(position);
                mSceneLayers.back()->attachChild(std::move(tileSprite));

            }

        }

    }

}

/// Build the scene depicted by the world. Parses the map file to build
/// the scene properly
void AFP::World::buildScene()
{
    addBackgroundLayers();
    addTileLayers();

    int topLayer = mSceneLayers.size() - 1;

    // Point user data to foreground
    mGroundBody->SetUserData(mSceneLayers[topLayer]);

    // Add sound effect node
    std::unique_ptr<SoundNode> soundNode(new SoundNode(mSounds));
    mSceneGraph.attachChild(std::move(soundNode));

    /// Set the player to the world
    std::unique_ptr<Character> leader(new Character(Character::Player, mTextures));
    mPlayerCharacter = leader.get();

    mPlayerCharacter->createCharacter(mWorldBox, mSpawnPosition.x, mSpawnPosition.y);
    mPlayerCharacter->setPosition(mPlayerCharacter->getPosition());
    mCameraPosition = mPlayerCharacter->getPosition();

    mSceneLayers[topLayer]->attachChild(std::move(leader));

    /// Create a test tile in box2D world
    std::unique_ptr<Tile> testTile(new Tile(Tile::Grass, mTextures));

    testTile->createTile(mWorldBox, mSpawnPosition.x - 32.f, 500.f);
    testTile->setPosition(testTile->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testTile));

    /// Create a test coin in box2D world
    std::unique_ptr<Collectable> testCoin(new Collectable(Collectable::Coin, mTextures));

    testCoin->createCollectable(mWorldBox, mSpawnPosition.x + 64.f, 800.f);
    testCoin->setPosition(testCoin->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(testCoin));

    /// Create a test enemy
    std::unique_ptr<Character> enemy(new Character(Character::Enemy, mTextures));

    enemy->createCharacter(mWorldBox, 500.0f, 500.0f);
    enemy->setPosition(enemy->getPosition());

    mSceneLayers[topLayer]->attachChild(std::move(enemy));

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
    groundBox.Set(b2Vec2(0, mWorldBounds.height / 16.f),
        b2Vec2(mWorldBounds.width / 16.f, mWorldBounds.height / 16.f));
    mGroundBody->CreateFixture(&fixtureDef);

    // Rest of the walls
    fixtureDef.friction = 0.0f;
    groundBox.Set(b2Vec2(0, 0), b2Vec2(mWorldBounds.width / 16.f, 0));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(0, 0), b2Vec2(0, mWorldBounds.height / 16.f));
    mGroundBody->CreateFixture(&fixtureDef);

    groundBox.Set(b2Vec2(mWorldBounds.width / 16.f, mWorldBounds.height / 16.f),
        b2Vec2(mWorldBounds.width / 16.f, 0));
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
    mWindow.draw(mSceneGraph);

    if (mDebugMode)
    {
        mWorldBox->DrawDebugData();

    }

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

}

/// Return the command queue
AFP::CommandQueue& AFP::World::getCommandQueue()
{
    return mCommandQueue;

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

