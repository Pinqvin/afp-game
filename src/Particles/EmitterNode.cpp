/// Implementation for EmitterNode class
#include <AFP/Particles/EmitterNode.hpp>
#include <AFP/Particles/ParticleNode.hpp>
#include <AFP/Command/Command.hpp>
#include <AFP/Command/CommandQueue.hpp>

/// Constructor
AFP::EmitterNode::EmitterNode(Particle::Type type)
    : SceneNode(), mAccumulatedTime(sf::Time::Zero), mType(type), mParticleSystem(nullptr)
{
}

void AFP::EmitterNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (mParticleSystem)
    {
        emitParticles(dt);
    }
    else
    {
        // Find particle node with the same type as emitter node
        auto finder = [this] (ParticleNode& container, sf::Time)
        {
            if (container.getParticleType() == mType)
                mParticleSystem = &container;
        };

        Command command;
        command.category = Category::ParticleSystem;
        command.action = derivedAction<ParticleNode>(finder);

        commands.push(command);
    }
}

void AFP::EmitterNode::emitParticles(sf::Time dt)
{
    const float emissionRate = 30.f;
    const sf::Time interval = sf::seconds(1.f) / emissionRate;

    mAccumulatedTime += dt;

    while (mAccumulatedTime > interval)
    {
        mAccumulatedTime -= interval;
        mParticleSystem->addParticle(getWorldPosition());
    }
}
