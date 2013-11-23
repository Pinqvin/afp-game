/// PostEffect class
///
/// Full screen effects
#pragma once
#include <SFML/System/NonCopyable.hpp>

namespace sf
{
    class RenderTarget;
    class RenderTexture;
    class Shader;
}

namespace AFP
{

    class PostEffect : sf::NonCopyable
    {
    public:
        /// Destructor
        ///
        /// 
        virtual					~PostEffect();
        
        /// Apply post effect
        ///
        ///
        virtual void			apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;
        
        /// Is supported
        ///
        /// Checks if GPU supports post effects
        static bool				isSupported();


    protected:        
        /// Apply shader
        ///
        /// 
        static void				applyShader(const sf::Shader& shader, sf::RenderTarget& output);
    };

}
