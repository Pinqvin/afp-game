/// Implementation for the menu state

#include "utility.hpp"
#include "menustate.hpp"
#include "resourceholder.hpp"

///  Constructor sets the different menu options
AFP::MenuState::MenuState(StateStack& stack, Context context):
    State(stack, context), mBackgroundSprite(), mOptions(), mOptionIndex(0)
{
    sf::Font& font = context.fonts->get(Fonts::Debug);

    // A rudimentary menu
    sf::Text playOption;

    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);

    updateOptionText();

}

/// Destructor
AFP::MenuState::~MenuState()
{

}


/// Update the option text based on selected option
void AFP::MenuState::updateOptionText()
{
    if (mOptions.empty())
    {
        return;

    }

    /// Set all the text to white
    for (sf::Text& option : mOptions)
    {
        option.setColor(sf::Color::White);

    }

    /// Set the selected option to red
    mOptions[mOptionIndex].setColor(sf::Color::Red);

}


/// Handle state changes and selected option changes
bool AFP::MenuState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;

    }


    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Load);

        }
        else if (mOptionIndex == Exit)
        {
            /// Game will quit due to the stack being empty
            requestStackPop();

        }

    }

    /// Switch selected option based on event
    if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
        {
            --mOptionIndex;

        }
        else
        {
            mOptionIndex = mOptions.size() - 1;

        }

        updateOptionText();

    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
        {
            ++mOptionIndex;

        }
        else
        {
            mOptionIndex = 0;

        }

        updateOptionText();

    }

    return true;

}


/// Draw the menu state
void AFP::MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    
    for (const sf::Text& option : mOptions)
    {
        window.draw(option);

    }

}


/// There's no background logic to update in this state
bool AFP::MenuState::update(sf::Time)
{
    return true;

}

