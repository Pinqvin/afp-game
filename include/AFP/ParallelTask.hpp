/// Dummy implementation for parallel tasks (loading)

#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>

namespace AFP
{
    class ParallelTask
    {
        public:
            /// Constructor
            ParallelTask();

            /// Destructor
            ~ParallelTask();

            /// Start the thread and execute the provied function
            void execute();

            /// Returns true if task is finished, false otherwise
            bool isFinished();

            /// Returns the completion percent for the task
            float getCompletion();

        private:
            /// Run the task
            void runTask();

            /// The thread we run the specified task on
            sf::Thread mThread;

            /// True if task is finished, false otherwise
            bool mFinished;

            /// Keep track of the time elapsed
            sf::Clock mElapsedTime;

            /// Mutex to disallow critical area clashes
            sf::Mutex mMutex;

    };

}

