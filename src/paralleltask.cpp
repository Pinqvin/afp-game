/// Implementation for the (dummy) parallel task

#include <SFML/System/Lock.hpp>
#include "paralleltask.hpp"

/// Constructor
AFP::ParallelTask::ParallelTask():
    mThread(&ParallelTask::runTask, this), mFinished(false),
    mElapsedTime(), mMutex()
{

}

/// Destructor
AFP::ParallelTask::~ParallelTask()
{

}

/// Check if execution is finished
bool AFP::ParallelTask::isFinished()
{
    sf::Lock lock(mMutex);
    return mFinished;

}

/// Dummy task for the thread to run
void AFP::ParallelTask::runTask()
{
    bool ended = false;

    while(!ended)
    {
        sf::Lock lock(mMutex);

        if (mElapsedTime.getElapsedTime().asSeconds() >= 2.f)
        {
            ended = true;

        }

    }

    {
        sf::Lock lock(mMutex);
        mFinished = true;

    }

}

/// Execute the thread
void AFP::ParallelTask::execute()
{
    mFinished = false;
    mElapsedTime.restart();
    mThread.launch();

}

/// Return the completion percentage
float AFP::ParallelTask::getCompletion()
{
    sf::Lock lock(mMutex);

    return mElapsedTime.getElapsedTime().asSeconds() / 2.f;

}
