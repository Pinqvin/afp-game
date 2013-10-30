/// Implementation for the menu state

#include <AFP/Utility.hpp>
#include <AFP/State/MenuState.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Sound/MusicPlayer.hpp>
#include <AFP/GUI/Button.hpp>

///  Constructor sets the different menu options
AFP::MenuState::MenuState(StateStack& stack, Context context):
    State(stack, context), mBackgroundSprite(), mGUIContainer()
{
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(100,250);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });

    // Settings not yet implemented so this part is left out
    /*
    auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->setPosition(100, 300);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this] ()
    {
        requestStackPush(States::Settings);
    });
    */

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(100, 350);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    // mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);

    context.music->play(Music::MenuTheme);

}

/// Destructor
AFP::MenuState::~MenuState()
{

}

/// Draw the menu state
void AFP::MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);

}


/// There's no background logic to update in this state
bool AFP::MenuState::update(sf::Time)
{
    return true;

}


/// Handle state changes and selected option changes
bool AFP::MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;

}
