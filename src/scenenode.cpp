/// Implementation for scene node

#include "scenenode.hpp"

#include <algorithm>
#include <cassert>

AFP::SceneNode::SceneNode(): mChildren(), mParent(nullptr)
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
void AFP::SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);

}


void AFP::SceneNode::updateCurrent(sf::Time)
{
    /// Do nothing by default

}

/// Update all the children
void AFP::SceneNode::updateChildren(sf::Time dt)
{
    for (const Ptr& child : mChildren)
    {
        child->update(dt);

    }

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
    /// Return the scene category by default
    return Category::Scene;

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

