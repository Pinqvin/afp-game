#include "scenenode.hpp"


AFP::SceneNode::SceneNode(void)
{
	mParent = nullptr;
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

	/// Iterate through children and draw them.
	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}

void AFP::SceneNode::drawCurrent(sf::RenderTarget& target, 
						  sf::RenderStates states) const
{
}