/// CommandQueue transports commands to the World and scene graph
///
/// CommandQueue is a FIFO datastructure (first in, first out)

#pragma once

#include <queue>
#include <AFP/Command/Command.hpp>

namespace AFP
{
    class CommandQueue
    {
        public:
            /// Constructor
            ///
            ///
            CommandQueue();

            /// Push a new command in to the queue
            ///
            /// Adds a command in to the mQueue
            void push(const Command& command);

            /// Pop a command from the queue
            ///
            /// Removes a command from the mQueue
            Command pop();

            /// Check if the queue is empty
            ///
            /// Returns true if queue is empty, false otherwise
            bool isEmpty() const;

        private:
            /// Command queue
            ///
            ///
            std::queue<Command> mQueue;

    };

}

