/// Implementation for Game state

#include <AFP/State/GameState.hpp>
#include <AFP/Input/Player.hpp>

/// Constructor
AFP::GameState::GameState(StateStack& stack, State::Context context):
    State(stack, context), mWorld(*context.window, *context.sound, "Media/Maps/lol.tmx"),
    mPlayer(*context.player)
{

}

/// Destructor
AFP::GameState::~GameState()
{

}

/// Draw the game state (the world)
void AFP::GameState::draw()
{
    mWorld.draw();

}

/// Handle game state updates (propagate them down to the
/// world) and handle commands through player.
bool AFP::GameState::update(sf::Time dt)
{
    mWorld.update(dt);

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return true;

}

/// Handle game input and pausing
bool AFP::GameState::handleEvent(const sf::Event& event)
{
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    // If player pressed escape, go to pause state
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPush(States::Pause);

    }

    return true;

}

