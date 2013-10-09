/// Implementation for the Game class

#include "game.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>
#include <string>


/// Updates are handled in fixed-time. Fixed time is set to 60 frames
/// per second
const sf::Time AFP::Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

// Set window size to 640 x 480 and load the player texture
AFP::Game::Game(): mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close), 
    mFont(), mStatisticsText(), mStatisticsUpdateTime(), 
    mStatisticsNumFrames(0), mShowDebug(false), mWorld(mWindow), mPlayer()
{
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

            processInput();
            update(TIME_PER_FRAME);

        }

        if (mShowDebug) {
            updateStatistics(elapsedTime);

        }
        
        render();

    }

}

// Process player input here
void AFP::Game::processInput()
{
    CommandQueue& commands = mWorld.getCommandQueue();

    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, commands);

        if (event.type == sf::Event::Closed)
        {
            mWindow.close();

        }
        
    }

    mPlayer.handleRealtimeInput(commands);

}

// Update game logic in here
void AFP::Game::update(sf::Time deltaTime)
{
    mWorld.update(deltaTime);

}

// Render stuff on the window
void AFP::Game::render()
{
    mWindow.clear();
    mWorld.draw();
    
    mWindow.setView(mWindow.getDefaultView());
    
    if (mShowDebug)
    {
        mWindow.draw(mStatisticsText);

    }

    mWindow.display();

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

