/// Implementation for Game state

#include <AFP/State/GameState.hpp>
#include <AFP/Input/Player.hpp>
#include <AFP/Sound/MusicPlayer.hpp>
#include <AFP/Parsers/MapParser.hpp>

#include <iostream>

/// Constructor
AFP::GameState::GameState(StateStack& stack, Context context):
    State(stack, context), mWorld(*context.window, *context.fonts, *context.sound, context.level->filename),
    mPlayer(*context.player)
{
    context.music->setVolume(40.f);
    context.music->play(Music::MainTheme);
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

    /// Move to GameOver screen if player is dead
    if (!mWorld.isPlayerAlive())
    {
        requestStackPush(States::GameOver);
    }

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
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F12)
    {
        mWorld.setDebug();

    }

    return true;

}

