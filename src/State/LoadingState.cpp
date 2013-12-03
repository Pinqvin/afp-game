/// Implementation for the loading task

#include <AFP/State/LoadingState.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Resource/ResourceHolder.hpp>

/// Constructor sets the loading texts and starts
/// the parallel loading task
AFP::LoadingState::LoadingState(StateStack& stack, State::Context context):
    State(stack, context), mLoadingText(), mProgressBarBackground(), mProgressBar(), mLoadingTask()
{
    sf::Font& font = context.fonts->get("AFP::Fonts::Debug");
    sf::RenderWindow& window = *getContext().window;

    mLoadingText.setFont(font);
    mLoadingText.setString("Loading...");
    centerOrigin(mLoadingText);
    mLoadingText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 50);

    mProgressBarBackground.setFillColor(sf::Color::White);
    mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20.f, 10.f));
    mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

    mProgressBar.setFillColor(sf::Color(100, 100, 100, 100));
    mProgressBar.setSize(sf::Vector2f(200, 10));
    mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);

    setCompletion(0.f);

    mLoadingTask.execute();

}

/// Destructor
AFP::LoadingState::~LoadingState()
{

}

/// Set the current completion
void AFP::LoadingState::setCompletion(float percent)
{
    if (percent > 1.f)
    {
        // Clamp the progress at 100% max
        percent = 1.f;

    }

    mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * percent,
                mProgressBar.getSize().y));

}

/// Update method checks if the loading task is done, otherwise
/// updates the progressbar
bool AFP::LoadingState::update(sf::Time)
{
    // If we are finished, move to the game state
    if (mLoadingTask.isFinished())
    {
        requestStackPop();
        requestStackPush(States::Game);

    }
    else
    {
        setCompletion(mLoadingTask.getCompletion());

    }

    return true;

}

/// Draw the loading bar
void AFP::LoadingState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mLoadingText);
    window.draw(mProgressBarBackground);
    window.draw(mProgressBar);

}

/// There are no events to handle in the loading state,
/// allow events to be handled lower in the stack though
bool AFP::LoadingState::handleEvent(const sf::Event&)
{
    return true;

}

