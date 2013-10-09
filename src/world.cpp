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
	mScrollSpeed(-50.f), mPlayer(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

	/// Box2D
	createWorld();

}

/// Load all the textures required for the world
void AFP::World::loadTextures()
{
	mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
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
	std::unique_ptr<Player> leader(new Player(mTextures));
	mPlayer = leader.get();

	mPlayer->setPosition(mSpawnPosition);
	mPlayer->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Foreground]->attachChild(std::move(leader));

	/// Add some new planes to follow the player plane
	std::unique_ptr<Player> leftEscort(new Player(mTextures));
	/// Position is relative to the leader (player)
	leftEscort->setPosition(-80.f, 50.f);
	mPlayer->attachChild(std::move(leftEscort));

	std::unique_ptr<Player> rightEscort(new Player(mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayer->attachChild(std::move(rightEscort));

}

void AFP::World::createWorld() 
{
	b2Vec2 gravity(0.0f, -9.81f); 
	mWorldBox = new b2World(gravity);

	mBodyDef.position.Set(0.0f, -10.0f);
	mGroundBody = mWorldBox->CreateBody(&mBodyDef);	mGroundBox.SetAsBox(50.0f, 10.0f);	mGroundBody->CreateFixture(&mGroundBox, 0.0f);
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

	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();

	if (position.x <= mWorldBounds.left + 150
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayer->setVelocity(velocity);

	}

	mSceneGraph.update(dt);

}

