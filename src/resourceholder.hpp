/// ResourceHolder handles all the resource loading in the game
///
///

#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <memory>
#include <cassert>
#include <stdexcept>
#include <string>

namespace AFP
{
    template <typename Resource, typename Identifier>
    class ResourceHolder
    {
        public:
            /// Constructor
            ///
            ///
            ResourceHolder();

            /// Return a resource based on ID
            ///
            /// Returns the resource specified by the ID provided
            Resource& get(Identifier id);

            /// Return a resource based on ID
            ///
            /// Returns the resource specified by the ID provided
            const Resource& get(Identifier id) const;

            /// Load resource to mResourceMap
            ///
            /// Resource is saved as a ID-unique_ptr key-value pair in
            /// the mResourceMap
            void load(Identifier id, const std::string& filename);

            /// Load resource to mResourceMap
            ///
            /// Resource is saved as a ID-uniqe_ptr key-value pair
            /// in the mResourceMap. Overloaded method can be used for
            /// resources that take multiple parameters for for their load
            /// function (for example, sf::Shader).
            template <typename Parameter>
            void load(Identifier id, const std::string& filename,
                    const Parameter& secondParam);

        private:
            /// TextureMap holds all the textures
            ///
            /// The texture pointers are identified by their ID
            /// enums.
            std::map<Identifier,
                    std::unique_ptr<Resource>> mResourceMap;

    };

}

/// Templated classes need to have their functions defined in the header
#include "resourceholder.inl"
#endif // RESOURCEHOLDER_HPP

