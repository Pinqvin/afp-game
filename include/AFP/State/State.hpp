/// State describes one individual state in the stack
///
///

#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <AFP/State/StateIdentifiers.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

// Forward declaration
namespace AFP
{
    class StateStack;
    class Player;
    class MusicPlayer;
    class SoundPlayer;

}

namespace AFP
{
    class State
    {
        public:
            /// Typedef for State unique pointer
            ///
            ///
            typedef std::unique_ptr<State> Ptr;

            /// Context
            ///
            ///
            struct Context
            {
                /// Constructorr
                ///
                ///
                Context(sf::RenderWindow& window,
                        TextureHolder& textures,
                        FontHolder& fonts,
                        Player& player,
                        MusicPlayer& music,
                        SoundPlayer& sound);

                /// Window to render to
                sf::RenderWindow* window;

                /// Loaded textures
                TextureHolder* textures;

                /// Loaded fonts
                FontHolder* fonts;

                /// Player
                Player* player;

                /// Music player
                MusicPlayer* music;

                /// Sound player
                SoundPlayer* sound;

            };

            /// Constructor
            ///
            ///
            State(StateStack& stack, Context context);

            /// Destructor
            ///
            ///
            virtual ~State();

            /// Draw function for the state
            ///
            ///
            virtual void draw() = 0;

            /// Update function for the state
            ///
            ///
            virtual bool update(sf::Time dt) = 0;

            /// Handle events in the state
            ///
            ///
            virtual bool handleEvent(const sf::Event& event) = 0;

        protected:
            /// RequestStackPush
            ///
            ///
            void requestStackPush(States::ID stateID);

            /// RequestStackPop
            ///
            ///
            void requestStackPop();

            /// RequestStateCLear
            ///
            ///
            void requestStateClear();

            /// Return the context of the state
            ///
            ///
            Context getContext() const;

        private:
            /// Pointer to the state stack the state is in
            ///
            ///
            StateStack* mStack;

            /// Context of the state
            ///
            ///
            Context mContext;

    };

}

