/// Implementation for the menu state

#include <AFP/Utility.hpp>
#include <AFP/State/MenuState.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Sound/MusicPlayer.hpp>
#include <AFP/GUI/Button.hpp>
#include <AFP/GUI/Label.hpp>

///  Constructor sets the different menu options
AFP::MenuState::MenuState(StateStack& stack, Context context):
    State(stack, context), mBackgroundSprite(context.textures->get("AFP::Textures::TitleScreen")), mGUIContainer()
{
    auto titleText = std::make_shared<GUI::Label>("TELEPORT HERO ACTION SHOOTER GAME", *context.fonts, 20);
    titleText->setPosition(600,100);

    auto copyrightText = std::make_shared<GUI::Label>("COPYRIGHT 2013 ANAL FISSURE PRODUCTIONS PRODUCTIONS (C)", *context.fonts, 16);
    copyrightText->setPosition(600,450);

    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(600,200);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::LevelSelect);
    });

    // Settings not yet implemented so this part is left out
    
    auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->setPosition(600, 270);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this] ()
    {
        requestStackPush(States::Settings);
    });
    

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(600, 340);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(titleText);
    mGUIContainer.pack(copyrightText);
    mGUIContainer.pack(playButton);
    mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);

    context.music->setVolume(60.f);
    context.music->play(Music::MenuTheme);

    context.window->setMouseCursorVisible(true);

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
    // Set new mouse position if mouse moved
    if (event.type == sf::Event::MouseMoved)
    {
        mGUIContainer.setMousePosition(sf::Vector2f(sf::Mouse::getPosition(*getContext().window)));
    }

    mGUIContainer.handleEvent(event);
    return false;

}
