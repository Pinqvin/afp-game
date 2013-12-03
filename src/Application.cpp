/// Implementation for Application class

#include <AFP/Application.hpp>
#include <AFP/State/StateIdentifiers.hpp>
#include <AFP/State/TitleState.hpp>
#include <AFP/State/MenuState.hpp>
#include <AFP/State/LoadingState.hpp>
#include <AFP/State/GameState.hpp>
#include <AFP/State/PauseState.hpp>
#include <AFP/State/SettingsState.hpp>
#include <AFP/State/LevelSelectState.hpp>
#include <AFP/Utility.hpp>

/// Handle the updates in steps fixed to 60fps
const sf::Time AFP::Application::TIME_PER_FRAME = sf::seconds(AFP::UPDATE_PER_FRAME);

/// Constructor
AFP::Application::Application():
    mWindow(sf::VideoMode(854, 480), "States", sf::Style::Close),
    mTextures(), mFonts(), mPlayer(),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusicPlayer, mSoundPlayer, State::Level("Media/Maps/level1.tmx"))),
    mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames()
{
    mFonts.load("AFP::Fonts::Debug", "Media/Sansation.ttf");

    mTextures.load("AFP::Textures::TitleScreen", "Media/Menu/Menu_Background.png");
    mTextures.load("AFP::Textures::ButtonNormal", "Media/Menu/Menu_Block_Blue.png");
    mTextures.load("AFP::Textures::ButtonSelected", "Media/Menu/Menu_Block_Yellow.png");
    mTextures.load("AFP::Textures::ButtonPressed", "Media/Menu/Menu_Block_Yellow.png");

    mStatisticsText.setFont(mFonts.get("AFP::Fonts::Debug"));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10u);

    registerStates();
    mStateStack.pushState(States::Title);

    mWindow.setFramerateLimit(60);

}

/// Register all the different states the game can have to
/// the state stack.
void AFP::Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<LoadingState>(States::Load);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<LevelSelectState>(States::LevelSelect);

}

/// Main game/application loop
void AFP::Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            processInput();
            update(TIME_PER_FRAME);

            /// If the state stack is empty, quit the game
            if (mStateStack.isEmpty())
            {
                mWindow.close();

            }

        }

        updateStatistics(dt);
        render();

    }

}

/// Propagate input event processing to the states
void AFP::Application::processInput()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
        {
            mWindow.close();

        }
        // If mouse moved, update new place to player
        else if (event.type == sf::Event::MouseMoved)
        {
            mPlayer.setMousePosition(sf::Vector2f(sf::Mouse::getPosition(mWindow)));

        }

    }

}

/// Propagate game updates to the states
void AFP::Application::update(sf::Time dt)
{
    mStateStack.update(dt);

}

/// Draw the statestack
void AFP::Application::render()
{
    mWindow.clear();

    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);

    mWindow.display();

}

void AFP::Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS " + std::to_string(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;

    }

}

