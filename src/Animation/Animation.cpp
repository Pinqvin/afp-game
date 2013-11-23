#include <AFP/Animation/Animation.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

/// Constructor
AFP::Animation::Animation()
    : mSprite(), mFrameSize(), mNumFrames(0), mCurrentFrame(0), mDuration(sf::Time::Zero),
    mElapsedTime(sf::Time::Zero), mRepeat(false)
{
}

/// Constructor
AFP::Animation::Animation(const sf::Texture& texture)
    : mSprite(texture), mFrameSize(), mNumFrames(0), mCurrentFrame(0), mDuration(sf::Time::Zero)
    , mElapsedTime(sf::Time::Zero), mRepeat(false)
{
}

/// Sets animation texture
void AFP::Animation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

/// Returns animation texture
const sf::Texture* AFP::Animation::getTexture() const
{
    return mSprite.getTexture();
}

/// Sets frame size
void AFP::Animation::setFrameSize(sf::Vector2i frameSize)
{
    mFrameSize = frameSize;
}

/// Returns frame size
sf::Vector2i AFP::Animation::getFrameSize() const
{
    return mFrameSize;
}

/// Sets number of frames
void AFP::Animation::setNumFrames(std::size_t numFrames)
{
    mNumFrames = numFrames;
}

/// Returns number of frames
std::size_t AFP::Animation::getNumFrames() const
{
    return mNumFrames;
}

/// Sets duration
void AFP::Animation::setDuration(sf::Time duration)
{
    mDuration = duration;
}

/// Returns duration
sf::Time AFP::Animation::getDuration() const
{
    return mDuration;
}

/// Sets animation to be repeating
void AFP::Animation::setRepeating(bool flag)
{
    mRepeat = flag;
}

/// Returns true if animation is repeating
bool AFP::Animation::isRepeating() const
{
    return mRepeat;
}

/// Restarts animation
void AFP::Animation::restart()
{
    mCurrentFrame = 0;
}

/// Returns true if animation is finished
bool AFP::Animation::isFinished() const
{
    return mCurrentFrame >= mNumFrames;
}

/// Returns local bounding rectangle
sf::FloatRect AFP::Animation::getLocalBounds() const
{
    return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

/// Returns global bounding rectangle
sf::FloatRect AFP::Animation::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

/// Updates the animation
void AFP::Animation::update(sf::Time dt)
{
    sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
    mElapsedTime += dt;

    sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
    sf::IntRect textureRect = mSprite.getTextureRect();

    if (mCurrentFrame == 0)
        textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);

    // While we have a frame to process
    while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
    {
        // Move the texture rect left
        textureRect.left += textureRect.width;

        // If we reach the end of the texture
        if (textureRect.left + textureRect.width > textureBounds.x)
        {
            // Move it down one line
            textureRect.left = 0;
            textureRect.top += textureRect.height;
        }

        // And progress to next frame
        mElapsedTime -= timePerFrame;
        if (mRepeat)
        {
            mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

            if (mCurrentFrame == 0)
                textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
        }
        else
        {
            mCurrentFrame++;
        }
    }

    mSprite.setTextureRect(textureRect);
}

/// Draws the animation
void AFP::Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
