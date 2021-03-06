/// Scene node contains an entity
///
/// Each scene node can store an object that is drawn on the screen, most often this is an entity.
/// Each node may have an arbitrary amount of child nodes, which adapt to the
/// transform of their parent node when rendering. Children only store the position,
/// rotation, and scale relative to their parent.
/// Root node is unique.

#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <Box2D/Box2D.h>

#include <AFP/Command/Category.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>

#include <memory>
#include <vector>

namespace AFP
{

	class SceneNode : public sf::Transformable, public sf::Drawable,
		private sf::NonCopyable
	{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
        typedef std::pair<SceneNode*, SceneNode*> Pair;

		/// Constructor
		///
		/// Sets mParent to nullptr
		explicit SceneNode(Category::Type category = Category::None);

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
        void update(sf::Time dt, CommandQueue& commands);

        /// Gets the transformation relative to the world
        ///
        ///
        sf::Transform getWorldTransform() const;

        /// Gets the node's position in the world
        ///
        /// Returns the absolute position of the node
        sf::Vector2f getWorldPosition() const;

        /// Returns the category of the game object
        ///
        ///
        virtual unsigned int getCategory() const;

        /// Runs a command
        ///
        /// Runs the specified command on all the nodes with the
        /// same category that the command is aimed at
        void onCommand(const Command& command, sf::Time dt);

        /// Get parent nodes position
        ///
        /// Returns the position of this nodes parent
        sf::Vector2f getParentPosition();

        /// Remove entities
        ///
        /// Removes entities which are marked for removal
        void removeWrecks();

        /// Is entity marked for removal
        ///
        /// Returns true if entity is ready to be destroyed
        virtual bool isMarkedForRemoval() const;

        /// Is entity destroyed
        ///
        /// Returns false by default, entities return
        /// values based on hitpoints
        virtual bool isDestroyed() const;

        /// Destroy Body
        ///
        /// Destroys entitys body
        virtual void destroyBody();

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
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

        /// Update all the child nodes
        ///
        /// Update all the nodes in the mChildren vector
        void updateChildren(sf::Time dt, CommandQueue& commands);

    private:

		/// mChildren holds all the children.
		///
		///
		std::vector<Ptr> mChildren;

		/// mParent holds pointer to the parent.
		///
		///
		SceneNode* mParent;

        /// Default category
        ///
        ///
        Category::Type mDefaultCategory;

	};
}

