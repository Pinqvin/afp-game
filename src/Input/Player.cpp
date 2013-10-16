/// Implementation for Player

#include <AFP/Input/Player.hpp>
#include <AFP/Entity/Character.hpp>

#include <map>
#include <algorithm>
#include <string>

namespace AFP
{
    /// The action function used by command. CharacterMover is a functor
    /// (function object), which adds vx and vy to the player velocity when
    /// the functor is invoked (eg. runs the operator() method)
    struct CharacterMover
    {
        /// Constructor set's the velocity vector
        CharacterMover(float vx): velocity(vx)
        {

        }

        /// This gets called when the CharacterMover functor is called
        void operator() (AFP::Character& character, sf::Time) const
        {
            character.moveHorizontal(velocity);

        }

        float velocity;

    };

}

/// Constructor
///
/// Sets the default keybindings
AFP::Player::Player(): mKeyBinding(), mActionBinding()
{
    /// Set initial key bindings
    mKeyBinding[sf::Keyboard::A] = MoveLeft;
    mKeyBinding[sf::Keyboard::D] = MoveRight;
    mKeyBinding[sf::Keyboard::W] = Jump;
    mKeyBinding[sf::Keyboard::Space] = Jump;

    /// Set initial action bindings
    initializeActions();

    /// Assign all categories to player's character
    for (auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerCharacter;

    }

}

/// Handle real time input. A command is created every frame an arrow
/// key is held down.
void AFP::Player::handleRealtimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for (auto pair : mKeyBinding)
    {
        // If key is pressed, lookup action and trigger corresponding
        // command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);

        }

    }

}

/// Remove all existing keymappings and insert new keybind
void AFP::Player::assignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all the keys that already map to action
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
    {
        if (itr->second == action)
        {
            mKeyBinding.erase(itr++);

        }
        else
        {
            ++itr;

        }

    }

    // Insert new binding
    mKeyBinding[key] = action;

}

/// Return the keybinding associated with action
sf::Keyboard::Key AFP::Player::getAssignedKey(Action action) const
{
    for (auto pair : mKeyBinding)
    {
        if (pair.second == action)
        {
            return pair.first;

        }

    }

    return sf::Keyboard::Unknown;

}

/// Initialize actions
void AFP::Player::initializeActions()
{
    const float playerSpeed = 20.f;

    mActionBinding[MoveLeft].action = derivedAction<Character>(CharacterMover(-playerSpeed));
    mActionBinding[MoveRight].action = derivedAction<Character>(CharacterMover(+playerSpeed));
    mActionBinding[Jump].action = derivedAction<Character>([] (Character& c, sf::Time) { c.jump(); });

}

/// Check if an action is a real-time action
bool AFP::Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
            return true;

        default:
            return false;

    }

}

/// Handle one-time events
void AFP::Player::handleEvent(const sf::Event& event,
        CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command
        // if so
        auto found = mKeyBinding.find(event.key.code);

        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
        {
            commands.push(mActionBinding[found->second]);

        }

    }

}

