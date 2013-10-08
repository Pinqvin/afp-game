/// Scene node contains an entity
///
/// Each scene node can store an object that is drawn on the screen, most often this is an entity.
/// Each node may have an arbitrary amount of child nodes, which adapt to the 
/// transform of their parent node when rendering. Children only store the position, 
/// rotation, and scale relative to their parent.
/// Root node is unique.

#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>

namespace AFP
{

	class SceneNode : public sf::Transformable, public sf::Drawable,
		private sf::NonCopyable
	{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

		/// Constructor
		///
		/// Sets mParent to nullptr
		SceneNode();

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

        /// Update the nodes
        ///
        /// Updates the node and all of its children
        void update(sf::Time dt);

        /// Gets the transformation relative to the world
        ///
        ///
        sf::Transform getWorldTransform() const;

        /// Gets the node's position in the world
        ///
        /// Returns the absolute position of the node
        void getWorldPosition();

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

        /// Draw all the children nodes
        ///
        /// Draws all the child nodes
        void drawChildren(sf::RenderTarget& target,
            sf::RenderStates states) const;

        /// Update the current node
        ///
        /// Only updates the node currently being worked on
        virtual void updateCurrent(sf::Time dt);

        /// Update all the child nodes
        ///
        /// Update all the nodes in the mChildren vector
        void updateChildren(sf::Time dt);

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

#endif // SCENENODE_HPP

