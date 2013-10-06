#include "game.hpp"

// Set window size to 640 x 480
AFP::Game::Game(): mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayer()
{
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);

}

// Main game loop
void AFP::Game::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        update();
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
void AFP::Game::update()
{
    // Movement vector
    sf::Vector2f movement(0.f, 0.f);

    // Handle player movement.
    if (mIsMovingUp)
    {
        movement.y -= 1.f;

    }
    if (mIsMovingDown)
    {
        movement.y += 1.f;

    }
    if (mIsMovingLeft)
    {
        movement.x -= 1.f;

    }
    if (mIsMovingRight)
    {
        movement.x += 1.f;

    }

    mPlayer.move(movement);

}

// Render stuff on the window
void AFP::Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
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

}

