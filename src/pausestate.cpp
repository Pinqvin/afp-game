/// Implementation for the pause state

#include <SFML/Graphics/RectangleShape.hpp>

#include "pausestate.hpp"
#include "utility.hpp"
#include "resourceholder.hpp"

/// Constructor sets the pause texts
AFP::PauseState::PauseState(StateStack& stack, State::Context context):
    State(stack, context), mBackgroundSprite(), mPausedText(),
    mInstructionText()
{
    sf::Font& font = context.fonts->get(Fonts::Debug);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPausedText.setFont(font);
    mPausedText.setString("Game is paused.");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    mInstructionText.setFont(font);
    mInstructionText.setString("Press backspace to return to the menu.");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

}

/// Destructor
AFP::PauseState::~PauseState()
{


}


/// Pause state is a transparent state, so we can see the state under it
/// (game state).
void AFP::PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    // Set a transparent background shape for the screen we're drawing
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);

}


/// Update does nothing in the pause state, but the
/// underlying states aren't allowed to update either
bool AFP::PauseState::update(sf::Time)
{
    return false;

}


/// Handle events in the pause state. We can either
/// return to the main menu or back in to the game.
/// Events aren't allowed to propagate further down
/// the stack.
bool AFP::PauseState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;

    }

    if (event.key.code == sf::Keyboard::Escape)
    {
        // Remove pause state and go back to the game
        requestStackPop();

    }

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        // Clear the stack and go back to the main menu
        requestStateClear();
        requestStackPush(States::Menu);

    }

    return false;

}

