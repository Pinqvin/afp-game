/// Implementation for StateStack

#include <cassert>
#include <AFP/State/StateStack.hpp>

/// State stack constructor
AFP::StateStack::StateStack(State::Context context):
   mStack(), mPendingList(), mContext(context), mFactories()
{

}

/// Return a pointer to the newly created state.
AFP::State::Ptr AFP::StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();

}

/// Send all events to the state stack
void AFP::StateStack::handleEvent(const sf::Event& event)
{
    // Iterate the stack from the highest state to the lowest.
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
        {
            // Stop propagating updates to lower states
            break;

        }

    }

    applyPendingChanges();

}

/// Send updates to all the states in the stack
void AFP::StateStack::update(sf::Time dt)
{
    // Iterate the stack from the highest state to the lowest
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
        {
            // Stop propagating updates to lower states
            return;

        }

    }

    applyPendingChanges();

}

/// Draw all the active states
void AFP::StateStack::draw()
{
    // Iterate the stack from the lowest to the highest (pause screen
    // gets drawn over game etc.)
    for (State::Ptr& state : mStack)
    {
        state->draw();

    }

}

/// Pending changes are applied when we are no longer
/// iterating through the active stack so we can
/// guarantee the operations are safe
void AFP::StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;

            default:
                break;

        }

    }

    // Clear the handled states
    mPendingList.clear();

}

/// Push a new state to the pending tasks list
void AFP::StateStack::pushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));

}

/// Pop a state, put the pop action to the pending tasks list
void AFP::StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));

}

/// Clear the state stack (push the action to the pending tasks list)
void AFP::StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));

}

/// Check to see if the state stack is empty
bool AFP::StateStack::isEmpty() const
{
    return mStack.empty();

}

/// Change level
void AFP::StateStack::setLevel(std::string level)
{
    mContext.level = new State::Level(level);
}

/// Constructor for a pending change
AFP::StateStack::PendingChange::PendingChange(Action action, States::ID stateID):
    action(action), stateID(stateID)
{

}

