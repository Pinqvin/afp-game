/// Implementation for LevelSelectState class
#include <AFP/State/LevelSelectState.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Entity/DataTables.hpp>

AFP::LevelSelectState::LevelSelectState(StateStack& stack, Context context):
    State(stack, context), mBackgroundSprite(context.textures->get("AFP::Textures::TitleScreen"))
    , mGUIContainer()
{
    /// Add buttons for levels
    auto level1Button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    level1Button->setPosition(600,200);
    level1Button->setText("Level 1");

    level1Button->setCallback([this, &stack] ()
    {
        requestStackPop();
        stack.setLevel("Media/Maps/level3.tmx");
        requestStackPush(States::Game);

    });

    auto level2Button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    level2Button->setPosition(600,300);
    level2Button->setText("Level 2");
    level2Button->setCallback([this, &stack] ()
    {
        requestStackPop();
        stack.setLevel("Media/Maps/level2.tmx");
        requestStackPush(States::Game);

    });

    auto level3Button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    level3Button->setPosition(600, 400);
    level3Button->setText("Level 3");
    level3Button->setCallback([this, &stack] ()
    {
        requestStackPop();
        stack.setLevel("Media/Maps/level3.tmx");
        requestStackPush(States::Game);
    });

    mGUIContainer.pack(level1Button);
    mGUIContainer.pack(level2Button);
    mGUIContainer.pack(level3Button);
}


void AFP::LevelSelectState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool AFP::LevelSelectState::update(sf::Time)
{
    return true;
}

bool AFP::LevelSelectState::handleEvent(const sf::Event& event)
{
    // Set new mouse position if mouse moved
    if (event.type == sf::Event::MouseMoved)
    {
        mGUIContainer.setMousePosition(sf::Vector2f(sf::Mouse::getPosition(*getContext().window)));
    }

    mGUIContainer.handleEvent(event);

    return false;

}
