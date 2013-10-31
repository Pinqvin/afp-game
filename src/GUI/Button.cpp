/// Implementation for the Button class
#include <AFP/GUI/Button.hpp>
#include <AFP/Utility.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

/// Constructor
AFP::GUI::Button::Button(const FontHolder& fonts, const TextureHolder& textures):
    mCallback(), mNormalTexture(textures.get("AFP::Textures::ButtonNormal")),
    mSelectedTexture(textures.get("AFP::Textures::ButtonSelected")),
    mPressedTexture(textures.get("AFP::Textures::ButtonPressed")), mSprite(),
    mText("", fonts.get("AFP::Fonts::Debug"), 16), mIsToggle(false)
{
    mSprite.setTexture(mNormalTexture);

    // Center sprite and text
    centerOrigin(mSprite);
    centerOrigin(mText);

}

/// Set callback
void AFP::GUI::Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

/// Set a label for the button
void AFP::GUI::Button::setText(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}

/// Set the button to be toggleable
void AFP::GUI::Button::setToggle(bool flag)
{
    mIsToggle = flag;
}

/// Button is a selectable component so return true
bool AFP::GUI::Button::isSelectable() const
{
    return true;
}

/// Selects the button
void AFP::GUI::Button::select()
{
    Component::select();

    mSprite.setTexture(mSelectedTexture);
}

/// Deselects the button
void AFP::GUI::Button::deselect()
{
    Component::deselect();

    mSprite.setTexture(mNormalTexture);
}

/// Activate button
void AFP::GUI::Button::activate()
{
    Component::activate();

    // If button is toggle, set button as toggled
    if (mIsToggle)
    {
        mSprite.setTexture(mPressedTexture);
    }

    if (mCallback)
    {
        mCallback();
    }

    // If button is not toggle, deactivate it
    if (!mIsToggle)
    {
        deactivate();
    }

}

/// Deactivate button
void AFP::GUI::Button::deactivate()
{
    Component::deactivate();

    if (mIsToggle)
    {
        // Reset texture to correct if button is a toggle
        if (isSelected())
        {
            mSprite.setTexture(mSelectedTexture);
        }
        else 
        {
            mSprite.setTexture(mNormalTexture);
        }
    }
}

/// Handle event
void AFP::GUI::Button::handleEvent(const sf::Event&)
{
}

/// Draws the button
void AFP::GUI::Button::draw(sf::RenderTarget& target
                          , sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

/// Return button bounding rectangle
sf::FloatRect AFP::GUI::Button::getBoundingRect() const
{
    // Get rectangle size and position
    sf::Vector2f size(mSprite.getLocalBounds().width, 
                      mSprite.getLocalBounds().height);
    sf::Vector2f position(getPosition());

    // Set position to the up left corner of the button
    position -= size / 2.f;

    // Create new rectangle in button position and return it
    return sf::FloatRect(position, size);

}