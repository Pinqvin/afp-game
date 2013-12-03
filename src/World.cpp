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
    mSceneGraph(), mSpriteGraph(), mSceneLayers(), mMap(), mWorldBounds(),
    mSpawnPosition(), mPlayerCharacter(nullptr), mCommandQueue(),
    mWorldBox(), mGroundBody(), mBoxDebugDraw(window, mWorldBounds),
    mDebugMode(true), mCameraPosition(), mContactListener(), mSounds(sounds), mGameUI()
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
    mTextures.load("AFP::Textures::Bullet", "Media/Textures/Bullet.png");
    mTextures.load("AFP::Textures::Coin", "Media/Textures/Coin.png");
    mTextures.load("AFP::Textures::Particle", "Media/Textures/Particle.png");
    mTextures.load("AFP::Textures::PlayerStopped", "Media/Textures/Rag_Stopped.png");
    mTextures.load("AFP::Textures::PlayerRunning", "Media/Textures/Rag_Running.png");
    mTextures.load("AFP::Textures::PlayerJumping", "Media/Textures/Rag_Jumping.png");
    mTextures.load("AFP::Textures::PlayerFalling", "Media/Textures/Rag_Falling.png");
    mTextures.load("AFP::Textures::HpBar", "Media/Textures/hp_bar_empty.png");
    mTextures.load("AFP::Textures::TeleBar", "Media/Textures/teleport_bar_empty.png");

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

        /// Add background layers to spritegraph
        mSpriteGraph.attachChild(std::move(layer));

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
            sf::IntRect textureRect(0.f, 0.f, mWorldBounds.width,
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

        /// Tiles are added to spritegraph
        mSpriteGraph.attachChild(std::move(layer));

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

/// Add collision objects to the box2D world
void AFP::World::addCollisionObjects(const Tmx::ObjectGroup* objectGroup)
{
    for (int i = 0; i < objectGroup->GetNumObjects(); ++i)
    {
        const Tmx::Object* collisionObject = objectGroup->GetObject(i);

        /// Cast the object to all the possible types and check for the non
        /// null pointer
        const Tmx::Ellipse* ellipseCollision = collisionObject->GetEllipse();
        const Tmx::Polygon* polygonCollision = collisionObject->GetPolygon();
        const Tmx::Polyline* polylineCollision = collisionObject->GetPolyline();

        b2FixtureDef fixtureDef;

        if (ellipseCollision != NULL) {
            /// TODO: Polygon approximation for ellipses? Not sure if necessary
            b2CircleShape circle;
            circle.m_radius = (ellipseCollision->GetRadiusX() +
                        ellipseCollision->GetRadiusY()) / 2.f / PTM_RATIO;
            circle.m_p = b2Vec2(ellipseCollision->GetCenterX() / PTM_RATIO,
                        ellipseCollision->GetCenterY() / PTM_RATIO);
            fixtureDef.shape = &circle;
            fixtureDef.friction = 0.35f;
            mGroundBody->CreateFixture(&fixtureDef);

        }
        else if (polygonCollision != NULL)
        {
            /// Maximum vertex count supported by Box2D is 8 (by default). If
            /// larger or concave polygon shapes are used, the program will
            /// crash
            b2PolygonShape polygonShape;
            int polyCount = polygonCollision->GetNumPoints();
            b2Vec2* vertices = new b2Vec2[polyCount];

            for (int k = 0; k < polyCount; ++k)
            {
                const Tmx::Point point = polygonCollision->GetPoint(k);

                vertices[k].x = (collisionObject->GetX() + point.x) / PTM_RATIO;
                vertices[k].y = (collisionObject->GetY() + point.y) / PTM_RATIO;

            }

            polygonShape.Set(vertices, polyCount);
            delete vertices;
            fixtureDef.shape = &polygonShape;
            fixtureDef.friction = 0.2f;
            mGroundBody->CreateFixture(&fixtureDef);

        }
        else if (polylineCollision != NULL)
        {
            b2EdgeShape line;
            int pointCount = polylineCollision->GetNumPoints();
            int x = collisionObject->GetX();
            int y = collisionObject->GetY();

            for (int i = 0; i < pointCount - 1; ++i)
            {
                Tmx::Point currentPoint = polylineCollision->GetPoint(i);
                Tmx::Point nextPoint = polylineCollision->GetPoint(i + 1);

                line.Set(b2Vec2((currentPoint.x + x) / PTM_RATIO, (currentPoint.y + y) / PTM_RATIO),
                        b2Vec2((nextPoint.x + x) / PTM_RATIO, (nextPoint.y + y) / PTM_RATIO));
                fixtureDef.shape = &line;
                fixtureDef.friction = 0.2f;
                mGroundBody->CreateFixture(&fixtureDef);

            }

        }
        else
        {
            /// If it was none of the above, it's a box eg. the default object
            /// type/shape
            b2PolygonShape polygonShape;
            float width = collisionObject->GetWidth() / PTM_RATIO;
            float height = collisionObject->GetHeight() / PTM_RATIO;
            float x = collisionObject->GetX() / PTM_RATIO;
            float y = collisionObject->GetY() / PTM_RATIO;

            polygonShape.SetAsBox(width / 2.f,
                    height / 2.f, b2Vec2(x + width / 2.f, y + height / 2.f), 0.f);
            fixtureDef.shape = &polygonShape;
            fixtureDef.friction = 0.05f;
            mGroundBody->CreateFixture(&fixtureDef);

        }

    }

}

/// Parse and add object layer data
void AFP::World::addObjectLayers()
{
    for (int i = 0; i < mMap.GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup* objectGroup = mMap.GetObjectGroup(i);

        if (objectGroup->GetName() == "Collisions")
        {
            addCollisionObjects(objectGroup);

        }

    }

}

/// Build the scene depicted by the world. Parses the map file to build
/// the scene properly
void AFP::World::buildScene()
{
    addBackgroundLayers();
    addTileLayers();
    addObjectLayers();

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
    mWindow.draw(mSpriteGraph);
    mWindow.draw(mSceneGraph);

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

