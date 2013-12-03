/// Implementation for GameUI class
#include <AFP/GUI/GameUI.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>

AFP::GameUI::GameUI():
    mHpBarSprite(), mTeleBarSprite()
{
}

AFP::GameUI::GameUI(const TextureHolder& textures):
    mHpBarSprite(textures.get("AFP::Textures::HpBar")), mTeleBarSprite(textures.get("AFP::Textures::TeleBar"))
{
    mHpBarSprite.setPosition(100.f, 100.f);
    mTeleBarSprite.setPosition(200.f, 200.f);
}

void AFP::GameUI::setTextures(const TextureHolder& textures)
{
    mHpBarSprite.setTexture(textures.get("AFP::Textures::HpBar"));
    mTeleBarSprite.setTexture(textures.get("AFP::Textures::TeleBar"));

}

void AFP::GameUI::update(sf::Vector2f trans, int hp, int tele)
{
    mHpBarSprite.setPosition(trans.x + 5.f,trans.y + 430.f);
    mTeleBarSprite.setPosition(trans.x + 728.f,trans.y + 430.f);

    /// Calculate correct sprite for the amount of hp/teleport charge
    sf::IntRect textureRectHp = sf::IntRect(123 * static_cast<int>(floor(hp * 0.18f)), 0, 123, 44);
    sf::IntRect textureRectTele = sf::IntRect(123 * static_cast<int>(floor(tele * 0.18f)), 0, 123, 44);

    /// Set texture rectangle to correct place
    mHpBarSprite.setTextureRect(textureRectHp);
    mTeleBarSprite.setTextureRect(textureRectTele);

}

void AFP::GameUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mTeleBarSprite, states);
    target.draw(mHpBarSprite, states);
}
