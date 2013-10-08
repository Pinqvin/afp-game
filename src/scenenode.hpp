/// Scene node contains an entity
///
/// Each scene node can store an object that is drawn on the screen, most often this is an entity.
/// Each node may have an arbitrary amount of child nodes, which adapt to the 
/// transform of their parent node when rendering. Children only store the position, 
/// rotation, and scale relative to their parent.
/// Root node is unique.

#include <SFML\Graphics.hpp>

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

namespace AFP
{

	class SceneNode : public sf::Transformable, public sf::Drawable,
		private sf::NonCopyable
	{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

	public:

		/// Constructor
		///
		/// Sets mParent to nullptr
		SceneNode(void);

		/// Insert child
		///
		/// Takes a unique_ptr<SceneNode> by value, taking ownership 
		/// of the scene node
		void attachChild(Ptr child);

		/// Remove child
		///
		/// Searches for an occurrence of the specified node, releases
		/// it from the container, and returns it to the caller, wrapped in a 
		/// unique_ptr.
		Ptr detachChild(const SceneNode& node);

	private:
		/// Draw SceneNode
		///
		/// Draws this node and children.
		virtual void draw(sf::RenderTarget& target, 
			sf::RenderStates states) const;

		/// Draw SceneNode
		///
		/// Draws only this node.
		virtual void drawCurrent(sf::RenderTarget& target, 
			sf::RenderStates states) const;

		/// mChildren holds all the children.
		/// 
		/// 
		std::vector<Ptr> mChildren;

		/// mParent holds pointer to the parent.
		/// 
		/// 
		SceneNode* mParent;

	};
}

#endif
