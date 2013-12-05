/// Implementation for Collectable class

#include <AFP/Entity/Collectable.hpp>
#include <AFP/Resource/ResourceHolder.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>
#include <AFP/Entity/DataTables.hpp>
#include <AFP/Sound/SoundNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// Character data table
namespace
{
    const std::vector<AFP::CollectableData> Table = AFP::initializeCollectableData();
}

/// Constructor
AFP::Collectable::Collectable(Type type, const TextureHolder& textures):
    Entity(1), mType(type), mAnimation(textures.get(Table[type].texture)), mPickedUp(false), mSoundPlayed(false)
{
    switch (mType)
    {
    case AFP::Collectable::Coin:
        mAnimation.setFrameSize(sf::Vector2i(16,16));
        mAnimation.setNumFrames(14);
        mAnimation.setDuration(sf::seconds(1));
        mAnimation.setRepeating(true);
        break;
    case AFP::Collectable::Medkit:
        mAnimation.setFrameSize(sf::Vector2i(16,16));
        mAnimation.setNumFrames(1);
        mAnimation.setDuration(sf::seconds(1));
        mAnimation.setRepeating(true);
        break;
    case AFP::Collectable::Orb:
        mAnimation.setFrameSize(sf::Vector2i(16,16));
        mAnimation.setNumFrames(7);
        mAnimation.setDuration(sf::seconds(1));
        mAnimation.setRepeating(true);
        break;
    case AFP::Collectable::GameEnd:
    default:
        break;
    }

    centerOrigin(mAnimation);

}

/// Return category
unsigned int AFP::Collectable::getCategory() const
{
    return Category::Collectable;

}

/// Creates a collectable item
void AFP::Collectable::createCollectable(b2World* world, float posX, float posY)
{
    createBody(world, posX, posY, 1.0f, 1.0f, 1.0f, 0.3f);

}

/// Apply collectable
bool AFP::Collectable::apply(Character& player)
{
    switch (mType)
    {
    case Coin:
        mPickedUp = true;
        player.addCoin();
        break;
    case Medkit:
        mPickedUp = player.heal(25);
        break;
    case Orb:
        mPickedUp = player.recharge(25);
        break;
    case GameEnd:
        player.win();
        break;
    default:
        break;
    }

    return mPickedUp;
}

bool AFP::Collectable::isMarkedForRemoval() const
{
    return mSoundPlayed;
}

void AFP::Collectable::drawCurrent(sf::RenderTarget& target,
                                   sf::RenderStates states) const
{
    target.draw(mAnimation, states);

}

/// Play sound
void AFP::Collectable::playLocalSound(CommandQueue& commands, SoundEffect::ID effect)
{
    sf::Vector2f worldPosition = getPosition();

    Command command;
    command.category = Category::SoundEffect;
    command.action = derivedAction<SoundNode>(
        [effect, worldPosition] (SoundNode& node, sf::Time)
    {
        node.playSound(effect, worldPosition);
    });

    commands.push(command);
}

void AFP::Collectable::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    mAnimation.update(dt);
    if (mPickedUp && !mSoundPlayed)
    {
        mSoundPlayed = true;
        playLocalSound(commands, Table[mType].effect);
    }
}
