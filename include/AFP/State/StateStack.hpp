/// State stack handles all the different states in the game
/// (menus, levels etc.). Only one state should be active at
/// a time, pause screen being the exception to this rule.

#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <map>
#include <functional>
#include <AFP/State/State.hpp>
#include <AFP/State/StateIdentifiers.hpp>

namespace AFP
{
    class StateStack : private sf::NonCopyable
    {
        public:
            /// Describes the action to be done on the
            /// stack.
            enum Action
            {
                Push,
                Pop,
                Clear

            };

            /// Constructor
            ///
            ///
            explicit StateStack(State::Context context);

            /// Register's a new state in to the stack
            ///
            ///
            template <typename T>
            void registerState(States::ID stateID);

            /// Update the states in the stack
            ///
            ///
            void update(sf::Time dt);

            /// Draw the active state
            ///
            /// Draws the state on top of the stack
            void draw();

            /// Handles event's to the states in the stack
            ///
            ///
            void handleEvent(const sf::Event& event);

            /// Push a new state in to the stack
            ///
            /// Pushes a state in to the top of the stack
            void pushState(States::ID stateID);

            /// Pop a state from the stack
            ///
            ///
            void popState();

            /// Clears the stack
            ///
            /// Removes all the states from the stack
            void clearStates();

            /// Check if the state stack is empty
            ///
            /// Returns true if stack is empty, false otherwise
            bool isEmpty() const;

        private:
            /// Create a new state
            ///
            ///
            State::Ptr createState(States::ID stateID);

            /// Apply pending changes
            ///
            /// Apply changes not yet done to the state stack
            void applyPendingChanges();

            /// Change to a state we need to do
            ///
            /// PendingChanges are directed at specific state IDs
            struct PendingChange
            {
                /// Constructor
                explicit PendingChange(Action action, States::ID stateID = States::None);

                /// Action that needs to be done
                Action action;

                /// The state that action should be directed on
                States::ID stateID;

            };

            /// The state stack
            ///
            /// All the states are stored in this stack
            std::vector<State::Ptr> mStack;

            /// A list of the pending changes
            ///
            /// Changes that are yet to be done on the state
            /// stack
            std::vector<PendingChange> mPendingList;

            /// StateContext
            ///
            ///
            State::Context mContext;

            /// mFactories
            ///
            ///
            std::map<States::ID,
                std::function<State::Ptr()>> mFactories;

    };

    /// Register a new state in the stack
    template <typename T>
    void StateStack::registerState(States::ID stateID)
    {
        mFactories[stateID] = [this] ()
        {
            return State::Ptr(new T(*this, mContext));

        };

    }

}

