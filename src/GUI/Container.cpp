/// Implementation for the Container class
#include <AFP/GUI/Container.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Constructor
AFP::GUI::Container::Container(void):
    mChildren(), mSelectedChild(-1), mMousePosition()
{
}

/// Add a component to the container
void AFP::GUI::Container::pack(Component::Ptr component)
{
    mChildren.push_back(component);

    if (!hasSelection() && component->isSelectable())
    {
        select(mChildren.size() - 1);
    }
}

/// Set mouse position
void AFP::GUI::Container::setMousePosition(sf::Vector2f position)
{
    mMousePosition = position;
}

/// Set mouse position
bool AFP::GUI::Container::selectByMousePosition()
{
    // Loop through all components
    for(std::size_t i = 0; i < mChildren.size();i++)
    {
        // If mouse is inside a components bounding rectangle, try to select it
        if (mChildren[i]->getBoundingRect().contains(mMousePosition))
        {
            select(i);
            return true;
        } 
    }

    return false;
}

/// Container is not selectable so return false
bool AFP::GUI::Container::isSelectable() const
{
    return false;
}

/// Handles keyboard events
void AFP::GUI::Container::handleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
    if (hasSelection() && mChildren[mSelectedChild]->isActive())
    {
        mChildren[mSelectedChild]->handleEvent(event);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            selectPrevious();
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            selectNext();
        }
        else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
        {
            if (hasSelection())
                mChildren[mSelectedChild]->activate();
        }
    }
    // Update mouse selection when mouse moves
    else if (event.type == sf::Event::MouseMoved)
    {
        selectByMousePosition();
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        // Check if there is a component in mouse position
        if (hasSelection() && selectByMousePosition())
        {
            mChildren[mSelectedChild]->activate();
        }
    }

}

sf::FloatRect AFP::GUI::Container::getBoundingRect() const
{
    return sf::FloatRect();

}

/// Calls draw for all components
void AFP::GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(const Component::Ptr& child : mChildren)
    {
        target.draw(*child, states);
    }
}

/// Return true if something is selected
bool AFP::GUI::Container::hasSelection()
{
    return mSelectedChild >= 0;
}

/// Select component
void AFP::GUI::Container::select(std::size_t index)
{
    if (mChildren[index]->isSelectable())
    {
        if (hasSelection())
        {
            mChildren[mSelectedChild]->deselect();
        }
        mChildren[index]->select();
        mSelectedChild = index;
    }
}

/// Selects next component that is selectable
void AFP::GUI::Container::selectNext()
{
    if (!hasSelection())
    {
        return;
    }

    // Search next component that is selectable, wrap around if necessary
    int next = mSelectedChild;
    do
    {
        next = (next + 1) % mChildren.size();
    }
    while(!mChildren[next]->isSelectable());

    // Select that component
    select(next);

}

/// Selects previous component that is selectable
void AFP::GUI::Container::selectPrevious()
{
    if (!hasSelection())
    {
        return;
    }

    // Search previous component that is selectable, wrap around if necessary
    int prev = mSelectedChild;
    do
    {
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    }
    while(!mChildren[prev]->isSelectable());

    // Select that component
    select(prev);
}
