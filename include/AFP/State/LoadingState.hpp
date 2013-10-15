/// Loading state is an intermediate state shown when
/// loading resources for another state

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <AFP/State/State.hpp>
#include <AFP/ParallelTask.hpp>

namespace AFP
{
    class LoadingState : public State
    {
        public:
            /// Constructor
            LoadingState(StateStack& stack, State::Context context);

            /// Destructor
            ~LoadingState();

            /// Draw function draws the progress bar
            virtual void draw();

            /// Update the loading state
            virtual bool update(sf::Time dt);

            /// Handle events during the loading state
            virtual bool handleEvent(const sf::Event& event);

            /// Sets the current completion percent
            void setCompletion(float percent);

        private:
            /// Text to show on the loading screen
            sf::Text mLoadingText;

            /// Progressbar background
            sf::RectangleShape mProgressBarBackground;

            /// Progressbar
            sf::RectangleShape mProgressBar;

            /// The loading task running in parallel
            ParallelTask mLoadingTask;

    };

}

