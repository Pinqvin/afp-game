/// Implementation for the command queue

#include <AFP/Command/CommandQueue.hpp>
#include <AFP/Scene/SceneNode.hpp>

AFP::CommandQueue::CommandQueue(): mQueue()
{


}

/// Add a command to the end
void AFP::CommandQueue::push(const Command& command)
{
    mQueue.push(command);

}

/// Return the next command
AFP::Command AFP::CommandQueue::pop()
{
    /// Take the first item and remove it from the queue
    Command command = mQueue.front();
    mQueue.pop();

    return command;

}

/// Check if the queue is empty
bool AFP::CommandQueue::isEmpty() const
{
    return mQueue.empty();

}

