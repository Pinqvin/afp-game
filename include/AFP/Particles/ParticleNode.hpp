/// ParticleNode class
///
///
#pragma once
#include <AFP/Scene/SceneNode.hpp>
#include <AFP/Particles/Particle.hpp>
#include <AFP/Resource/ResourceIdentifiers.hpp>

#include <SFML/Graphics/VertexArray.hpp>

#include <deque>

namespace AFP
{
    class ParticleNode: public SceneNode
    {
    public:
        /// Constructor
        ///
        ///
        ParticleNode(Particle::Type type, const TextureHolder& textures);

        /// Add particle
        ///
        /// Inserts a new particle to the system
        void addParticle(sf::Vector2f position);

        /// Get particle type
        ///
        /// Returns particle type
        Particle::Type getParticleType() const;

        /// Get category
        ///
        /// Returns ParticleSystem category
        virtual unsigned int getCategory() const;

    private:
        /// Update
        ///
        /// Removes all particles of which the lifetime has expired.
        /// Decreases lifetime of all particles.
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

        /// Draw
        ///
        ///
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        /// Add vertex
        ///
        ///
        void addVertex(float worldX, float worldY, float texCoordX,
            float texCoordY, const sf::Color& color) const;

        /// Compute vertices
        ///
        /// Rebuilds the vertex array.
        void computeVertices() const;

    private:
        /// Particles
        ///
        ///
        std::deque<Particle> mParticles;

        /// Texture
        ///
        /// Particle texture
        const sf::Texture& mTexture;

        /// Type
        ///
        /// Particle type
        Particle::Type mType;

        /// Vertex array
        ///
        /// Stores vertices
        mutable sf::VertexArray mVertexArray;

        ///
        ///
        /// Vertices are updated only if the need to be
        mutable bool mNeedsVertexUpdate;

    };
}
