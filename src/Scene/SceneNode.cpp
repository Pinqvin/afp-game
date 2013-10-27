/// Implementation for scene node

#include <AFP/Scene/SceneNode.hpp>

#include <algorithm>
#include <cassert>

AFP::SceneNode::SceneNode(Category::Type category): mChildren(), mParent(nullptr), mDefaultCategory(category)
{

}

void AFP::SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

AFP::SceneNode::Ptr AFP::SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
        [&] (Ptr& p) -> bool { return p.get() == &node; });
    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void AFP::SceneNode::draw(sf::RenderTarget& target,
                          sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);

}

/// Draw all the children nodes
void AFP::SceneNode::drawChildren(sf::RenderTarget& target,
                                  sf::RenderStates states) const
{
    for (const Ptr& child : mChildren)
    {
        child->draw(target, states);

    }

}

void AFP::SceneNode::drawCurrent(sf::RenderTarget&,
                                 sf::RenderStates) const
{
    /// Do nothing by default
}

/// Update all the nodes
void AFP::SceneNode::update(sf::Time dt, CommandQueue& commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);

}


void AFP::SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
    /// Do nothing by default

}

/// Update all the children
void AFP::SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
    for (const Ptr& child : mChildren)
    {
        child->update(dt, commands);

    }

}

sf::Vector2f AFP::SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

/// Return the transformation relative to world. sf::Transform
/// objects are multiplie from the root to the current node.
sf::Transform AFP::SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr;
        node = node->mParent)
    {
        transform = node->getTransform() * transform;

    }

    return transform;

}

/// Return the category of the game object
unsigned int AFP::SceneNode::getCategory() const
{
    return mDefaultCategory;

}

/// Runs the command on the current node (if the category is of the
/// required type) and all the child nodes (if the category matches)
void AFP::SceneNode::onCommand(const Command& command, sf::Time dt)
{
    /// Check for category match with a bitwise AND
    if (command.category & getCategory())
    {
        command.action(*this, dt);

    }

    /// Relay the same command to all children
    for(Ptr& child : mChildren)
    {
        child->onCommand(command, dt);

    }

}

/// Return position of the parent
sf::Vector2f AFP::SceneNode::getParentPosition()
{
    return mParent->getPosition();
}

/// Remove all destroyed entities
void AFP::SceneNode::removeWrecks()
{
    // Remove all bodies that are marked for removal
    for(Ptr& child : mChildren)
    {
        if(child->isMarkedForRemoval()) 
        {
            child->destroyBody();
        }
    }

    // Remove all children marked for removal
    auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    mChildren.erase(wreckfieldBegin, mChildren.end());

    // Call function recursively
    std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

/// Return true when entity is destroyed
bool AFP::SceneNode::isMarkedForRemoval() const
{
    return isDestroyed();
}

/// Return false by default
bool AFP::SceneNode::isDestroyed() const
{
    return false;
}

void AFP::SceneNode::destroyBody()
{
    // Do nothing by default
}