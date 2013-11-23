/// EmitterNode class
///
/// Emits particles into a particle system
#pragma once
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Particles/Particle.hpp>

namespace AFP
{
    /// Forward declaration
    class ParticleNode;

    class EmitterNode: public SceneNode
    {
    public:
        /// Constructor
        ///
        ///
        EmitterNode(Particle::Type type);

    private:
        /// Update
        ///
        /// 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

        /// Emit particles
        ///
        /// Emits particles at a certain rate
        void emitParticles(sf::Time dt);

    private:
        /// Accumulated time
        ///
        ///
        sf::Time mAccumulatedTime;

        /// Type
        ///
        /// Type of the particle
        Particle::Type mType;

        /// Particle system
        ///
        /// Points to the ParticleNode into which the emitter emits particles
        ParticleNode* mParticleSystem;

    };
}
