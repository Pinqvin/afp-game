/// Game UI
///
/// Shows player info. HP, teleport charge, ammo, etc.
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <AFP/Resource/ResourceIdentifiers.hpp>

namespace AFP
{
    class GameUI: public sf::Drawable, 
        public sf::Transformable
    {
    public:
        /// Default constructor
        ///
        ///
        GameUI();

        /// Constructor
        ///
        /// TODO: Use this when texture loading has been implemented
        /// outside World class
        GameUI(const TextureHolder& textures);

        /// Set textures
        ///
        ///
        void setTextures(const TextureHolder& textures);

        /// Update
        ///
        /// Updates values
        void update(sf::Vector2f trans, int hp, int tele);

    private:
        /// Draw
        ///
        /// Draws all parts of the UI
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        /// Hp bar sprite
        ///
        ///
        sf::Sprite mHpBarSprite;

        /// Teleport bar sprite
        ///
        ///
        sf::Sprite mTeleBarSprite;

    };
}