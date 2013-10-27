/// Sound Node
///
/// Sound node is connected to the node graph
/// so it can be given commands
#pragma once
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Sound/SoundPlayer.hpp>

namespace AFP
{
    class SoundNode : public SceneNode
    {
    public:
        /// Constructor
        ///
        ///
        explicit SoundNode(SoundPlayer& player);

        /// Play sound
        ///
        /// Plays a sound
        void playSound(SoundEffect::ID sound,
            sf::Vector2f position);

        /// Get node category
        ///
        /// Return SoundEffect category
        virtual unsigned int getCategory() const;

    private:
        /// Sound player
        ///
        /// Reference to soundplayer
        SoundPlayer& mSounds;
    };
}
