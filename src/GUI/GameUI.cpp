/// Implementation for GameUI class
#include <AFP/GUI/GameUI.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

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
    mHpBarSprite.setPosition(trans.x + 5.f,trans.y + 420.f);
    mTeleBarSprite.setPosition(trans.x + 700.f,trans.y + 420.f);

}

void AFP::GameUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mTeleBarSprite, states);
    target.draw(mHpBarSprite, states);
}
