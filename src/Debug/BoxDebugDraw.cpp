/// Implementation for the Box2D debug draw

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <AFP/Debug/BoxDebugDraw.hpp>

/// Constructor
AFP::BoxDebugDraw::BoxDebugDraw(sf::RenderWindow& window, sf::FloatRect worldBounds):
    b2Draw(), mWindow(&window), mWorldBounds(worldBounds)
{


}

/// Destructor
AFP::BoxDebugDraw::~BoxDebugDraw()
{

}


/// Draw polygon
void AFP::BoxDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        sf::Vector2f transformedVector = B2VecToSFVec(vertices[i]);
        polygon.setPoint(i, sf::Vector2f(std::floor(transformedVector.x), std::floor(transformedVector.y)));

    }

    polygon.setOutlineThickness(-1.f);
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setOutlineColor(GLColorToSFML(color));

    mWindow->draw(polygon);

}

/// Draw a polygon with a color fill
void AFP::BoxDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
        sf::Vector2f transformedVector = B2VecToSFVec(vertices[i]);
        polygon.setPoint(i, sf::Vector2f(std::floor(transformedVector.x), std::floor(transformedVector.y)));

    }

    polygon.setOutlineThickness(-1.f);
    polygon.setFillColor(GLColorToSFML(color, 60));
    polygon.setOutlineColor(GLColorToSFML(color));

    mWindow->draw(polygon);

}

/// Draw a transparent circle
void AFP::BoxDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle(radius * PTM_RATIO);
    circle.setOrigin(radius * PTM_RATIO, radius * PTM_RATIO);

    circle.setPosition(B2VecToSFVec(center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(-1.f);
    circle.setOutlineColor(GLColorToSFML(color));

    mWindow->draw(circle);

}

/// Draw a circle with color fill
void AFP::BoxDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape circle(radius * PTM_RATIO);
    circle.setOrigin(radius * PTM_RATIO, radius * PTM_RATIO);
    circle.setPosition(B2VecToSFVec(center));

    circle.setFillColor(GLColorToSFML(color, 60));
    circle.setOutlineThickness(-1.f);
    circle.setOutlineColor(GLColorToSFML(color));

    b2Vec2 endPoint = center + radius * axis;

    sf::Vertex line[2] =
    {
        sf::Vertex(B2VecToSFVec(center), GLColorToSFML(color)),
        sf::Vertex(B2VecToSFVec(endPoint), GLColorToSFML(color)),

    };

    mWindow->draw(circle);
    mWindow->draw(line, 2, sf::Lines);

}


/// Draws a line between two points
void AFP::BoxDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Vertex line[] =
    {
        sf::Vertex(B2VecToSFVec(p1), GLColorToSFML(color)),
        sf::Vertex(B2VecToSFVec(p2), GLColorToSFML(color)),

    };

    mWindow->draw(line, 2, sf::Lines);

}

/// Draw a transform
void AFP::BoxDebugDraw::DrawTransform(const b2Transform& xf)
{
    float lineLength = 0.4f;

    b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
    sf::Vertex redLine[] =
    {
        sf::Vertex(B2VecToSFVec(xf.p), sf::Color::Red),
        sf::Vertex(B2VecToSFVec(xAxis), sf::Color::Red),

    };

    b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
    sf::Vertex greenLine[] =
    {
        sf::Vertex(B2VecToSFVec(xf.p), sf::Color::Green),
        sf::Vertex(B2VecToSFVec(yAxis), sf::Color::Green),

    };

    mWindow->draw(redLine, 2, sf::Lines);
    mWindow->draw(greenLine, 2, sf::Lines);

}

