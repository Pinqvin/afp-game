/// Implementation for state

#include "state.hpp"
#include "statestack.hpp"

/// Constructor for context
AFP::State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
        FontHolder& fonts, Player& player):
    window(&window), textures(&textures), fonts(&fonts), player(&player)
{

}


/// State constructor
AFP::State::State(StateStack& stack, Context context):
    mStack(&stack), mContext(context)
{

}

/// State destructor
AFP::State::~State()
{

}

/// Add stack push to pending changes
void AFP::State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);

}

/// Add stack pop to pending changes
void AFP::State::requestStackPop()
{
    mStack->popState();

}

/// Add state clear to pending changes (remove all states)
void AFP::State::requestStateClear()
{
    mStack->clearStates();

}

/// Return the context
AFP::State::Context AFP::State::getContext() const
{
    return mContext;

}

