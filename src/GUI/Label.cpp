/// Implementation for Label class
#include <AFP/GUI/Label.hpp>
#include <AFP/Utility.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// Constructor
AFP::GUI::Label::Label(const std::string& text, const FontHolder& fonts, int size):
    mText(text, fonts.get("AFP::Fonts::Debug"), size)
{
    centerOrigin(mText);
}

/// Is selectable
bool AFP::GUI::Label::isSelectable() const
{
    return false;
}

/// Set label text to text
void AFP::GUI::Label::setText(const std::string& text)
{
    mText.setString(text);
}

/// Handle event
void AFP::GUI::Label::handleEvent(const sf::Event&)
{
}

/// Returns a empty rectangle
sf::FloatRect AFP::GUI::Label::getBoundingRect() const
{
    return sf::FloatRect();

}

/// Draw label
void AFP::GUI::Label::draw(sf::RenderTarget& target
                         , sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mText, states);
}
