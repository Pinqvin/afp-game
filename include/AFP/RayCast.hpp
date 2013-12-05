/// Ray cast callback class
///
/// Used when raycasting to determine if the cast hit
/// an object
#pragma once
#include <Box2D/Box2D.h>

namespace AFP
{
    class RayCast: public b2RayCastCallback
    {
    public:
        /// Constructor
        ///
        ///
        RayCast();

        /// Overrided ReportFixture function
        ///
        /// Function gets called when a ray cast hits a fixture
        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

        bool hasHit() const;

    private:
        /// Set to true when ray cast hits a scene object
        ///
        ///
        bool mHit;

    };
}
