/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#pragma once

#include <AFP/Entity/Entity.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
	class Character : public Entity
	{
	public:
        /// Character type
        ///
        ///
        enum Type
        {
            Player,
            Enemy

        };

        /// Constructor
        ///
        ///
		Character(Type type, const TextureHolder& textures);

		/// Draw character sprite
		///
		///
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;

        /// Return character category
        ///
        /// Returns the character category based on the type
        virtual unsigned int getCategory() const;

        /// Create character in Box2D world
        ///
        /// Create character body based on type
        void createCharacter(b2World* world, float posX, float posY);

	private:
        /// Character type
        ///
        ///
        Type mType;

		/// Character sprite
		///
		///
		sf::Sprite mSprite;

	};

}

