/// Implementation for the GameOver state

#include <SFML/Graphics/RectangleShape.hpp>

#include <AFP/State/GameOverState.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Resource/ResourceHolder.hpp>

/// Constructor sets the texts
AFP::GameOverState::GameOverState(StateStack& stack, State::Context context):
    State(stack, context), mBackgroundSprite(), mGameOverText(), mInstructionText()
{
    sf::Font& font = context.fonts->get("AFP::Fonts::Debug");
    sf::Vector2f viewSize = context.window->getView().getSize();

    mGameOverText.setFont(font);
    mGameOverText.setString("YOU DIED");
    mGameOverText.setCharacterSize(70);
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    mInstructionText.setFont(font);
    mInstructionText.setString("Press R to retry or Backspace to return to the menu.");
    mInstructionText.setCharacterSize(20);
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

/// Destructor
AFP::GameOverState::~GameOverState()
{


}


/// Draw this state
void AFP::GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    // Set a transparent background shape for the screen we're drawing
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(mGameOverText);
    window.draw(mInstructionText);

}


/// Update does nothing
bool AFP::GameOverState::update(sf::Time)
{
    return false;

}


/// Handle events. Pushes states to stack according to keypresses.
bool AFP::GameOverState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;

    }

    if (event.key.code == sf::Keyboard::R)
    {
        // Clear the stack and reset level
        requestStateClear();
        requestStackPush(States::Game);

    }

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        // Clear the stack and go back to the main menu
        requestStateClear();
        requestStackPush(States::Menu);

    }

    return false;

}

