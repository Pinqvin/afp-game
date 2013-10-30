/// Implementation for Component class
#include <AFP/GUI/Component.hpp>

/// Constructor
AFP::GUI::Component::Component(void):
    mIsSelected(false), mIsActive(false)
{
}

/// Destructor
AFP::GUI::Component::~Component()
{
}

/// Return mIsSelected
bool AFP::GUI::Component::isSelected() const
{
    return mIsSelected;
}

/// Select component
void AFP::GUI::Component::select()
{
    mIsSelected = true;
}

/// Deselect component
void AFP::GUI::Component::deselect()
{
    mIsSelected = false;
}

/// Is component active
bool AFP::GUI::Component::isActive() const
{
    return mIsActive;
}

/// Activate component
void AFP::GUI::Component::activate()
{
    mIsActive = true;
}

/// Deactivate component
void AFP::GUI::Component::deactivate()
{
    mIsActive = false;
}