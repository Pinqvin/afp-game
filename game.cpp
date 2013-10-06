/// Implementation for the Game class

#include <iostream>
#include <sstream>
#include <string>
#include "game.hpp"

/// Set constant values
const float AFP::Game::PLAYER_SPEED = 100.f;

/// Updates are handled in fixed-time. Fixed time is set to 60 frames
/// per second
const sf::Time AFP::Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

// Set window size to 640 x 480 and load the player texture
AFP::Game::Game(): mWindow(sf::VideoMode(640, 480), "SFML Application"), 
    mTexture(), mPlayer(), mFont(), mStatisticsText(), mStatisticsUpdateTime(),
    mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
    mIsMovingRight(false), mIsMovingLeft(false), mShowDebug(false)
{
    if (!mTexture.loadFromFile("Media/Textures/Eagle.png"))
    {
        std::cout << "Couldn't load file!" << std::endl;

    }

    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);

    mFont.loadFromFile("Media/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

}

// Main game loop. Updates to the game logic are made in fixed
// time steps
void AFP::Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();        
        timeSinceLastUpdate += elapsedTime;;

        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            processEvents();
            update(TIME_PER_FRAME);

        }

        if (mShowDebug) {
            updateStatistics(elapsedTime);

        }
        
        render();

    }

}

// Process player input here
void AFP::Game::processEvents()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

            default:
                break;

        }

    }

}

// Update game logic in here
void AFP::Game::update(sf::Time deltaTime)
{
    // Movement vector
    sf::Vector2f movement(0.f, 0.f);

    // Handle player movement.
    if (mIsMovingUp)
    {
        movement.y -= PLAYER_SPEED;

    }
    if (mIsMovingDown)
    {
        movement.y += PLAYER_SPEED;

    }
    if (mIsMovingLeft)
    {
        movement.x -= PLAYER_SPEED;

    }
    if (mIsMovingRight)
    {
        movement.x += PLAYER_SPEED;

    }

    mPlayer.move(movement * deltaTime.asSeconds());

}

// Render stuff on the window
void AFP::Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    
    if (mShowDebug)
    {
        mWindow.draw(mStatisticsText);

    }

    mWindow.display();

}

void AFP::Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
    {
        mIsMovingUp = isPressed;
    
    }
    else if (key == sf::Keyboard::S)
    {
        mIsMovingDown = isPressed;
    
    }
    else if (key == sf::Keyboard::A)
    {
        mIsMovingLeft = isPressed;

    }
    else if (key == sf::Keyboard::D)
    {
        mIsMovingRight = isPressed;

    }
    else if (key == sf::Keyboard::F1 && isPressed)
    {
        mShowDebug = !mShowDebug;

    }

}

/// Return a string representation of the provided value
template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();

}

/// Update statistics/debug info
void AFP::Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString(
                "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
                "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;

    }

}

