/// Implementation for the Title state

#include <AFP/State/TitleState.hpp>
#include <AFP/Utility.hpp>
#include <AFP/Resource/ResourceHolder.hpp>

/// Title state constructor
AFP::TitleState::TitleState(StateStack& stack, State::Context context):
    State(stack, context), mText(), mShowText(true),
    mTextEffectTime(sf::Time::Zero)
{
    mText.setFont(context.fonts->get("AFP::Fonts::Debug"));
    mText.setString("Press any key to start");
    centerOrigin(mText);
    mText.setPosition(context.window->getView().getSize() / 2.f);

}

/// Destructor
AFP::TitleState::~TitleState()
{

}


/// Handle key presses in the title state
///
/// If a key is pressed, move on to the next state
/// (menu).
bool AFP::TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        requestStackPop();
        requestStackPush(States::Menu);

    }

    return true;

}

/// Blink the continue text every 0,5 seconds
/// while in the title state
bool AFP::TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;

    }

    return true;

}

/// Draw the title state
void AFP::TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    if (mShowText)
    {
        window.draw(mText);

    }

}

