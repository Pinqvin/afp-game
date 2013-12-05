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
    mWindow.setMouseCursorVisible(false);

    mGameUI.setPlayer(mPlayerCharacter);

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
    mTextures.load("AFP::Textures::GunIcons", "Media/Textures/gun_icons.png");
    mTextures.load("AFP::Textures::Arrow", "Media/Textures/arrow.png");
    mTextures.load("AFP::Textures::Crosshair", "Media/Textures/crosshair.png");
    mTextures.load("AFP::Textures::Barrel", "Media/Textures/Barrel_32.png");

}

/// Build the scene depicted by the world. Parses the map file to build
/// the scene properly
void AFP::World::buildScene()
{
    mMap.addBackgroundLayers(mSceneLayers, mSceneGraph, mWorldBounds);

    /// Create a layer for entities
    Category::Type category = Category::Scene;

    SceneNode::Ptr layer(new SceneNode(category));
    mSceneLayers.push_back(layer.get());

    /// Attach it to the scene
    mSceneGraph.attachChild(std::move(layer));

    /// Scene layer is the top layer
    int topLayer = mSceneLayers.size() - 1;

    // Point user data to foreground
    mGroundBody->SetUserData(mSceneLayers[topLayer]);

    addObjectLayers();

    // Add sound effect node
    std::unique_ptr<SoundNode> soundNode(new SoundNode(mSounds));
    mSceneGraph.attachChild(std::move(soundNode));

    // Add particle node to the scene
    std::unique_ptr<ParticleNode> bloodNode(new ParticleNode(Particle::Blood, mTextures));
    mSceneLayers[topLayer]->attachChild(std::move(bloodNode));

    /// Set textures to Game UI
    mGameUI.setTextures(mTextures);

}

void AFP::World::addObjectLayers()
{
    const Tmx::Map* map = mMap.getMap();

    for (int i = 0; i < map->GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup* objectGroup = map->GetObjectGroup(i);

        if (objectGroup->GetName() == "Collisions")
        {
            addCollisionObjects(objectGroup);

        }
        else if (objectGroup->GetName() == "Characters")
        {
            addCharacterObjects(objectGroup);

        }
        else if (objectGroup->GetName() == "Objects")
        {
            addObjects(objectGroup);

        }

    }

}

void AFP::World::addObjects(const Tmx::ObjectGroup* objectGroup)
{
    int topLayer = mSceneLayers.size() - 1;

    for (auto it = objectGroup->GetObjects().begin(); it != objectGroup->GetObjects().end(); ++it)
    {
        const Tmx::Object* object = *it;

        if (object->GetType() == "Box32")
        {
            std::unique_ptr<Tile> box32(new Tile(Tile::Box32, mTextures));

            box32->createTile(mWorldBox, object->GetX() + 16, object->GetY() - 16);
            box32->setPosition(box32->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(box32));

        }
        else if (object->GetType() == "Box16")
        {
            std::unique_ptr<Tile> box16(new Tile(Tile::Box16, mTextures));

            box16->createTile(mWorldBox, object->GetX() + 8, object->GetY() - 8);
            box16->setPosition(box16->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(box16));

        }
        else if (object->GetType() == "Box16Orb")
        {
            std::unique_ptr<Tile> box16Orb(new Tile(Tile::Box16Orb, mTextures));

            box16Orb->createTile(mWorldBox, object->GetX() + 8, object->GetY() - 8);
            box16Orb->setPosition(box16Orb->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(box16Orb));

        }
        else if (object->GetType() == "Box16Coin")
        {
            std::unique_ptr<Tile> box16Coin(new Tile(Tile::Box16Coin, mTextures));

            box16Coin->createTile(mWorldBox, object->GetX() + 8, object->GetY() - 8);
            box16Coin->setPosition(box16Coin->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(box16Coin));

        }
        else if (object->GetType() == "Coin")
        {
            /// Create a test coin in box2D world
            std::unique_ptr<Collectable> coin(new Collectable(Collectable::Coin, mTextures));

            coin->createCollectable(mWorldBox, object->GetX() + 8, object->GetY() - 8);
            coin->setPosition(coin->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(coin));

        }
        else if (object->GetType() == "Orb")
        {
            std::unique_ptr<Collectable> orb(new Collectable(Collectable::Orb, mTextures));

            orb->createCollectable(mWorldBox, object->GetX() + 8, object->GetY() - 8);
            orb->setPosition(orb->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(orb));

        }
        else if (object->GetType() == "Barrell")
        {
            std::unique_ptr<Tile> barrel(new Tile(Tile::Barrel, mTextures));

            barrel->createTile(mWorldBox, object->GetX() + 16, object->GetY() - 16);
            barrel->setPosition(barrel->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(barrel));

        }

    }

}

void AFP::World::addCharacterObjects(const Tmx::ObjectGroup* objectGroup)
{
    int topLayer = mSceneLayers.size() - 1;

    for (auto it = objectGroup->GetObjects().begin(); it != objectGroup->GetObjects().end(); ++it)
    {
        const Tmx::Object* object = *it;

        if (object->GetType() == "Player")
        {
            sf::Vector2f spawnPosition;

            spawnPosition.x = object->GetX();
            spawnPosition.y = object->GetY();

            /// Set the player to the world
            std::unique_ptr<Character> leader(new Character(Character::Player, mTextures));

            if (mPlayerCharacter != nullptr)
            {
                throw std::runtime_error ("AFP::World::addCharacterObjects - "
                    "Multiple player spawn points defined!");

            }

            mPlayerCharacter = leader.get();

            mPlayerCharacter->createCharacter(mWorldBox, spawnPosition.x, spawnPosition.y);
            mPlayerCharacter->setPosition(mPlayerCharacter->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(leader));

        }
        else if (object->GetType() == "Telepolice")
        {
            std::unique_ptr<Character> enemy(new Character(Character::Telepolice, mTextures));

            enemy->createCharacter(mWorldBox, object->GetX(), object->GetY());
            enemy->setPosition(enemy->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(enemy));

        }
        else if (object->GetType() == "Droid")
        {
            std::unique_ptr<Character> droid(new Character(Character::Droid, mTextures));

            droid->createCharacter(mWorldBox, object->GetX(), object->GetY());
            droid->setPosition(droid->getPosition());

            mSceneLayers[topLayer]->attachChild(std::move(droid));

        }

    }

}

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

    // Pass world view translation to Game UI
    mGameUI.update(translation);

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

