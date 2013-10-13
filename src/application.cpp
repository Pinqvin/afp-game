/// Implementation for Application class

#include "application.hpp"
#include "stateidentifiers.hpp"
#include "titlestate.hpp"
#include "menustate.hpp"
#include "gamestate.hpp"
#include "pausestate.hpp"

/// Handle the updates in steps fixed to 60fps
const sf::Time AFP::Application::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

/// Constructor
AFP::Application::Application():
    mWindow(sf::VideoMode(640, 480), "States", sf::Style::Close),
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
}

/// Register all the different states the game can have to
/// the state stack.
void AFP::Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
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

