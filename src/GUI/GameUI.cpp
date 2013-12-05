/// Implementation for GameUI class
#include <AFP/GUI/GameUI.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <sstream>

AFP::GameUI::GameUI(FontHolder& fonts):
    mHpBarSprite(), mTeleBarSprite(), mGunIcons(), mGunChooseIcon(), mPlayer(), mCrosshair(), mCoinText()
{
    sf::Font& font = fonts.get("AFP::Fonts::Debug");

    mCoinText.setFont(font);
    mCoinText.setCharacterSize(30);
    centerOrigin(mCoinText);

}

AFP::GameUI::GameUI(const TextureHolder& textures, FontHolder&):
    mHpBarSprite(textures.get("AFP::Textures::HpBar")), mTeleBarSprite(textures.get("AFP::Textures::TeleBar")),
    mGunIcons(textures.get("AFP::Textures::GunIcons")), mGunChooseIcon(textures.get("AFP::Textures::Arrow")),
    mPlayer(), mCoinText()
{
    mHpBarSprite.setPosition(100.f, 100.f);
    mTeleBarSprite.setPosition(200.f, 200.f);
    mGunIcons.setPosition(300.f, 300.f);
}

void AFP::GameUI::setTextures(const TextureHolder& textures)
{
    mHpBarSprite.setTexture(textures.get("AFP::Textures::HpBar"));
    mTeleBarSprite.setTexture(textures.get("AFP::Textures::TeleBar"));
    mGunIcons.setTexture(textures.get("AFP::Textures::GunIcons"));
    mGunChooseIcon.setTexture(textures.get("AFP::Textures::Arrow"));
    mCrosshair.setTexture(textures.get("AFP::Textures::Crosshair"));
    mCoinIcon.setTexture(textures.get("AFP::Textures::CoinIcon"));

    mCrosshair.setOrigin(16.f / 2.f, 16.f / 2.f);
}

void AFP::GameUI::setPlayer(Character* player)
{
    mPlayer = player;
}

void AFP::GameUI::update(sf::Vector2f trans)
{
    mHpBarSprite.setPosition(trans.x + 5.f,trans.y + 430.f);
    mTeleBarSprite.setPosition(trans.x + 728.f,trans.y + 430.f);
    mGunIcons.setPosition(trans.x + 10.f, trans.y + 10.f);
    mGunChooseIcon.setPosition(trans.x, trans.y + 14.f + (20.f * mPlayer->getWeapon()));
    mCrosshair.setPosition(trans.x + mPlayer->getMousePosition().x, trans.y + mPlayer->getMousePosition().y);
    mCoinIcon.setPosition(trans.x + 400.f, trans.y + 430.f);

    mCoinText.setString(convertInt(mPlayer->getCoins()));
    mCoinText.setPosition(trans.x + 440.f, trans.y + 425.f);

    /// Calculate correct sprite for the amount of hp/teleport charge
    sf::IntRect textureRectHp = sf::IntRect(123 * static_cast<int>(floor(mPlayer->getHitpoints() * 0.18f)), 0, 123, 44);
    sf::IntRect textureRectTele = sf::IntRect(123 * static_cast<int>(floor(mPlayer->getTeleCharge() * 0.18f)), 0, 123, 44);

    sf::IntRect textureRectCrosshair;

    if (mPlayer->isInLineOfSight(mPlayer->getPosition(), sf::Vector2f(trans.x + mPlayer->getMousePosition().x, trans.y + mPlayer->getMousePosition().y)))
    {
        textureRectCrosshair = sf::IntRect(0, 0, 16, 16);
    } 
    else
    {
        textureRectCrosshair = sf::IntRect(16, 0, 16, 16);
    }
    

    /// Set texture rectangle to correct place
    mHpBarSprite.setTextureRect(textureRectHp);
    mTeleBarSprite.setTextureRect(textureRectTele);
    mCrosshair.setTextureRect(textureRectCrosshair);

}

void AFP::GameUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mTeleBarSprite, states);
    target.draw(mHpBarSprite, states);
    target.draw(mGunIcons, states);
    target.draw(mGunChooseIcon, states);
    target.draw(mCrosshair, states);
    target.draw(mCoinIcon, states);
    target.draw(mCoinText, states);
}

std::string AFP::GameUI::convertInt(int number)
{
   std::stringstream ss;
   ss << number;
   return ss.str();
}