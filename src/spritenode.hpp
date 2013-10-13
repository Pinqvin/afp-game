/// Spritenode class is used to show a background
/// texture in the SceneNode graph.

#pragma once

#include "scenenode.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace AFP
{
    class SpriteNode : public SceneNode
    {
        public:
            /// Constructors
            ///
            ///
            explicit SpriteNode(const sf::Texture& texture);
            SpriteNode(const sf::Texture& texture,
                    const sf::IntRect& rect);

        private:
            /// Function to draw the current SceneNode
            ///
            ///
            virtual void drawCurrent(sf::RenderTarget& target,
                    sf::RenderStates statest) const;

            /// Sprite for the SpriteNode
            ///
            /// Used as the background sprite in the SceneNode graph.
            sf::Sprite mSprite;

    };

}

