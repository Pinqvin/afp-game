/// Animation class
///
///
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

namespace AFP
{
    class Animation : public sf::Drawable, public sf::Transformable
    {
    public:
        /// Constructor
        ///
        /// Default constructor
        Animation();
        
        /// Constructor
        ///
        ///
        explicit Animation(const sf::Texture& texture);
        
        /// Set texture
        ///
        /// Sets animation texture
        void setTexture(const sf::Texture& texture);
        
        /// Get texture
        ///
        /// Returns animation texture
        const sf::Texture* getTexture() const;
        
        /// Set frame size
        ///
        /// Sets frame size
        void setFrameSize(sf::Vector2i mFrameSize);
        
        /// Get frame size
        ///
        /// Returns frame size
        sf::Vector2i getFrameSize() const;
        
        /// Set number of frames
        ///
        /// Sets number of frames
        void setNumFrames(std::size_t numFrames);
        
        /// Get number of frames
        ///
        /// Returns number of frames
        std::size_t getNumFrames() const;
        
        /// Set duration
        ///
        /// Sets duration
        void setDuration(sf::Time duration);
        
        /// Get duration
        ///
        /// Returns duration
        sf::Time getDuration() const;

        /// Set Repeating
        ///
        /// Sets animation to be repeating
        void setRepeating(bool flag);
        
        /// Is repeating
        ///
        /// Returns true if animation is repeating
        bool isRepeating() const;
        
        /// Restart
        ///
        /// Restarts animation
        void restart();
        
        /// Is finished
        ///
        /// Returns true if animation is finished
        bool isFinished() const;
        
        /// Get local bounds
        ///
        /// 
        sf::FloatRect getLocalBounds() const;
        
        /// Get global bounds
        ///
        ///
        sf::FloatRect getGlobalBounds() const;
        
        /// Update
        ///
        /// Updates the animation
        void update(sf::Time dt);


    private: 
        /// Draw
        ///
        /// Draws the animation
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:   
        /// Sprite
        ///
        ///
        sf::Sprite mSprite;
        
        /// Frame size
        ///
        ///
        sf::Vector2i mFrameSize;
        
        /// Number of frames
        ///
        ///
        std::size_t mNumFrames;
        
        /// Current frame
        ///
        ///
        std::size_t mCurrentFrame;
        
        /// Duration
        ///
        ///
        sf::Time mDuration;
        
        /// Elapsed time
        ///
        ///
        sf::Time mElapsedTime;
        
        /// Repeat
        ///
        ///
        bool mRepeat;

    };

}
