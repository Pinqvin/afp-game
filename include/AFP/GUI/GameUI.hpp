/// Game UI
///
/// Shows player info. HP, teleport charge, ammo, etc.
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/Character.hpp>

namespace AFP
{
    class GameUI: public sf::Drawable,
        public sf::Transformable
    {
    public:
        /// Default constructor
        ///
        ///
        GameUI(FontHolder& fonts);

        /// Constructor
        ///
        /// TODO: Use this when texture loading has been implemented
        /// outside World class
        GameUI(const TextureHolder& textures, FontHolder& fonts);

        /// Set textures
        ///
        ///
        void setTextures(const TextureHolder& textures);

        /// Set player pointer
        ///
        ///
        void setPlayer(Character* player);

        /// Update
        ///
        /// Updates values
        void update(sf::Vector2f trans);

    private:
        /// Draw
        ///
        /// Draws all parts of the UI
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ///
        ///
        /// Converts string to int
        std::string convertInt(int number);

    private:
        /// Hp bar sprite
        ///
        ///
        sf::Sprite mHpBarSprite;

        /// Teleport bar sprite
        ///
        ///
        sf::Sprite mTeleBarSprite;

        /// Gun icons sprite
        ///
        ///
        sf::Sprite mGunIcons;

        /// Gun chooser sprite
        ///
        ///
        sf::Sprite mGunChooseIcon;

        /// Pointer to player character
        ///
        ///
        Character* mPlayer;

        /// Draw a crosshair
        ///
        /// Draws crosshair under mouse cursor
        sf::Sprite mCrosshair;

        ///
        ///
        /// Draw coin icon
        sf::Sprite mCoinIcon;

        ///
        ///
        /// Draw coin text
        sf::Text mCoinText;

    };
}
