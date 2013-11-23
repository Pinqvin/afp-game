#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

namespace AFP
{
    struct Particle
    {
        enum Type
        {
            Smoke,
            ParticleCount
        };

        sf::Vector2f position;
        sf::Color color;
        sf::Time lifetime;
    };
}