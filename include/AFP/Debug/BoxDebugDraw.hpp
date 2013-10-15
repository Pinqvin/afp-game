/// @brief Box2D debug drawing
///
/// This class utilized SFML features to draw Box2D entities when
/// wanted.

#pragma once

#include <Box2D/Common/b2Draw.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <AFP/Utility.hpp>

namespace AFP
{
    class BoxDebugDraw : public b2Draw
    {
        public:
            /// @brief Constructor
            ///
            /// @param window Window instance we draw the debug info to
            BoxDebugDraw(sf::RenderWindow& window, sf::FloatRect worldBounds);

            /// @brief Destructor
            ~BoxDebugDraw();

            /// @brief Draw the polygon shape specified by its vertices
            ///
            /// @param vertices The vertices of the polygon
            /// @param vertexCount Number of vertexes in the vertices vector
            /// @param color Color of the polygon
            void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

            /// @brief Draw the solid polygon specified by its vertices
            ///
            /// @param vertices The vertices of the polygon
            /// @param vertexCount Number of vertexes in the vertices vector
            /// @param color Color of the polygon
            void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

            /// @brief Draws a circle in the center coordinates with the provided radius
            ///
            /// @param center Center point for the circle
            /// @param radius Radius of the circle
            /// @param color Circle color
            void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

            /// @brief Draws a solid circle in the center coordinates with the provided radius
            ///
            /// @param center Center point for the circle
            /// @param radius Radius of the circle
            /// @param color Circle color
            void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

            /// @brief Draws a line between the specified points
            ///
            /// @param p1 Point one
            /// @param p2 Point two
            /// @param color Line color
            void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

            /// @brief Draws a transform
            ///
            /// @param xf Transform to draw
            void DrawTransform(const b2Transform& xf);

        private:
            /// @brief Reference to the rendering window.
            ///
            /// The place where we can draw the debug information
            sf::RenderWindow* mWindow;

            /// @brief Returns a SFML style color represantation of a Box2D style color
            ///
            /// @param color Color to be converted
            /// @param alpha Optional alpha channel (transparency)
            ///
            /// @return Returns the SFML style color definition
            static sf::Color GLColorToSFML(const b2Color& color, sf::Uint8 alpha = 255)
            {
                return sf::Color(static_cast<sf::Uint8>(color.r * 255), static_cast<sf::Uint8>(color.g * 255), static_cast<sf::Uint8>(color.b * 255), alpha);

            }

            /// @brief Returns a SFML style vector representation of a Box2D style vector
            ///
            /// Scales the SFML vector by using the PTM_RATIO defined in Utility
            /// header
            ///
            /// @param vector Box2D style vector to be converted
            /// @param scaleToPixels Scale it to pixels (from meters). Defaults to true
            ///
            /// @return SFML style vector presentation of the original Box2D style
            static sf::Vector2f B2VecToSFVec(const b2Vec2& vector, bool scaleToPixels = true)
            {
                return sf::Vector2f(vector.x * (scaleToPixels ? PTM_RATIO : 1.f), vector.y * (scaleToPixels ? PTM_RATIO : 1.f));

            }

            /// @brief We need the world bounds so we can flip the y-axis
            sf::FloatRect mWorldBounds;


    };

}

