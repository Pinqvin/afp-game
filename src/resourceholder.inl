/// Implementation for ResourceHolder class
///
///

/// Constructor
template <typename Resource, typename Identifier>
AFP::ResourceHolder<Resource, Identifier>::ResourceHolder(): mResourceMap()
{

}

/// Loads a Resource and stores the pointer to it in the mResourceMap.
/// Resource should be a type provided by SFML, or it should have a
/// function called loadFromFile, which returns true/false based on
/// load success/failure.
template <typename Resource, typename Identifier>
void AFP::ResourceHolder<Resource, Identifier>::load(Identifier id, 
        const std::string& filename)
{
    /// Create a new resource
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load "
                + filename);

    }

    auto inserted = mResourceMap.insert(std::make_pair(id, 
                std::move(resource)));

    /// Make sure something was inserted
    assert(inserted.second);

}

/// Loads a Resource and stores the pointer to it in mResourceMap.
/// This is an overloaded function which allows for additional parameters
/// in the loadFromFile function.
template <typename Resource, typename Identifier>
template <typename Parameter>
void AFP::ResourceHolder<Resource, Identifier>::load(Identifier id,
        const std::string& filename, const Parameter& secondParam)
{
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename, secondParam))
    {
        std::runtime_error("ResourceHolder::load - Failed to load "
                + filename);

    }

    auto inserted = mResourceMap.insert(std::make_pair(id,
                std::move(resource)));

    /// Make sure something was inserted
    assert(inserted.second);

}

/// Get Resource based on ID
template <typename Resource, typename Identifier>
Resource& AFP::ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    /// Make sure something was found
    assert(found != mResourceMap.end());

    return *found->second;

}

/// Get Resource based on ID
template <typename Resource, typename Identifier>
const Resource& AFP::ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    /// Make sure something was found
    assert(found != mResourceMap.end());

    return *found->second;

}

