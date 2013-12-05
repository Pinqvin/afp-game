/// Implementation for SettingsState class
#include <AFP/State/SettingsState.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Resource/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


AFP::SettingsState::SettingsState(StateStack& stack, Context context):
    State(stack, context), mBackgroundSprite(context.textures->get("AFP::Textures::TitleScreen")), mGUIContainer(), mBindingButtons(), mBindingLabels()
{
    auto titleText = std::make_shared<GUI::Label>("Settings", *context.fonts, 30);
    titleText->setPosition(450,30);

    auto keybindText = std::make_shared<GUI::Label>("Key bindings:", *context.fonts, 16);
    keybindText->setPosition(450,70);

    auto mousebindText = std::make_shared<GUI::Label>("Mouse bindings:", *context.fonts, 16);
    mousebindText->setPosition(450,300);

    // Build key binding buttons and labels
    addButtonLabel(Player::MoveLeft, 300.f, 120.f, "Move Left", context);
    addButtonLabel(Player::MoveRight, 300.f, 180.f, "Move Right", context);
    addButtonLabel(Player::Jump, 300.f, 240.f, "Jump", context);
    addButtonLabel(Player::Fire, 300.f, 350.f, "Fire", context);
    addButtonLabel(Player::Teleport, 600.f, 350.f, "Teleport", context);
    addButtonLabel(Player::Weapon1, 600.f, 120.f, "Weapon 1", context);
    addButtonLabel(Player::Weapon2, 600.f, 180.f, "Weapon 2", context);
    addButtonLabel(Player::Weapon3, 600.f, 240.f, "Weapon 3", context);

    updateLabels();

    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backButton->setPosition(450.f, 430.f);
    backButton->setText("Back");
    backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

    mGUIContainer.pack(backButton);
    mGUIContainer.pack(titleText);
    mGUIContainer.pack(keybindText);
    mGUIContainer.pack(mousebindText);
}

void AFP::SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool AFP::SettingsState::update(sf::Time)
{
    return true;
}

bool AFP::SettingsState::handleEvent(const sf::Event& event)
{
    bool isKeyBinding = false;

    // Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
    for (std::size_t action = 0; action < Player::ActionCount; ++action)
    {
        if (mBindingButtons[action]->isActive())
        {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased)
            {
                getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
                mBindingButtons[action]->deactivate();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                getContext().player->assignMouseButton(static_cast<Player::Action>(action), event.mouseButton.button);
                mBindingButtons[action]->deactivate();
            }

            break;
        }
    }

    // Set new mouse position if mouse moved
    if (event.type == sf::Event::MouseMoved)
    {
        mGUIContainer.setMousePosition(sf::Vector2f(sf::Mouse::getPosition(*getContext().window)));
    }

    // If pressed button changed key bindings, update labels; otherwise consider other buttons in container
    if (isKeyBinding)
        updateLabels();
    else
        mGUIContainer.handleEvent(event);

    return false;
}

void AFP::SettingsState::updateLabels()
{
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::ActionCount; ++i)
    {
        sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
        if (key == sf::Keyboard::Key::Unknown)
        {
            sf::Mouse::Button button = player.getAssignedButton(static_cast<Player::Action>(i));
            mBindingLabels[i]->setText(toString(button));
        } else
        {
            mBindingLabels[i]->setText(toString(key));
        }
    }
}

void AFP::SettingsState::addButtonLabel(Player::Action action, float x, float y, const std::string& text, Context context)
{
    mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    mBindingButtons[action]->setPosition(x, y);
    mBindingButtons[action]->setText(text);
    mBindingButtons[action]->setToggle(true);

    mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts, 16);
    mBindingLabels[action]->setPosition(x + 110.f, y - 10.f);

    mGUIContainer.pack(mBindingButtons[action]);
    mGUIContainer.pack(mBindingLabels[action]);
}
