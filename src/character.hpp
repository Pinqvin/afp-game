/// This is the class for the player entity
///
/// Contains functionality only needed by the player

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "entity.hpp"
#include "resourceidentifiers.hpp"

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

#endif // CHARACTER_HPP

