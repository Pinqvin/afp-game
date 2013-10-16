/// Implementation for Application class

#include <AFP/Application.hpp>
#include <AFP/State/StateIdentifiers.hpp>
#include <AFP/State/TitleState.hpp>
#include <AFP/State/MenuState.hpp>
#include <AFP/State/LoadingState.hpp>
#include <AFP/State/GameState.hpp>
#include <AFP/State/PauseState.hpp>
#include <AFP/Utility.hpp>

/// Handle the updates in steps fixed to 60fps
const sf::Time AFP::Application::TIME_PER_FRAME = sf::seconds(AFP::UPDATE_PER_FRAME);

/// Constructor
AFP::Application::Application():
    mWindow(sf::VideoMode(854, 480), "States", sf::Style::Close),
    mTextures(), mFonts(), mPlayer(),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)),
    mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames()
{
    mFonts.load(Fonts::Debug, "Media/Sansation.ttf");
    mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

    mStatisticsText.setFont(mFonts.get(Fonts::Debug));
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

