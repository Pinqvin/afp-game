/// Implementation of RayCast class
#include <AFP/RayCast.hpp>
#include <AFP/Scene/SceneNode.hpp>

AFP::RayCast::RayCast(): mHit(false)
{
}

float32 AFP::RayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{

    void* bodyUserData = fixture->GetBody()->GetUserData();

    if ( bodyUserData )
    {
        SceneNode* data = static_cast<SceneNode*>(bodyUserData);
        if (data->getCategory() == Category::Scene)
        {
            mHit = true;
            return -1;
        }
    }

    mHit = false;
    return fraction;
}

bool AFP::RayCast::hasHit() const
{
    return mHit;
}
