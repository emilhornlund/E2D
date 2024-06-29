/**
* ResourceRegistry.hpp
*
* MIT License
*
* Copyright (c) 2023 Emil Hörnlund
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef E2D_ENGINE_RESOURCEREGISTRY_HPP
#define E2D_ENGINE_RESOURCEREGISTRY_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Resource.hpp>

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Renderer; // Forward declaration of Renderer

/**
 * @class ResourceRegistry
 * @brief Manages loading and accessing resources by their identifiers.
 *
 * This class is responsible for loading resources from files and providing
 * access to them by their identifiers. It ensures that resources are type-safe
 * and properly managed in memory.
 */
class E2D_ENGINE_API ResourceRegistry final : NonCopyable
{
private:
    /**
     * @class IResource
     * @brief Represents a generic resource with a type and identifier.
     *
     * This class serves as a base for all specific types of resources, storing
     * the type and identifier of the resource.
     */
    class E2D_ENGINE_API IResource : NonCopyable
    {
    public:
        /**
         * @brief Constructs a new resource with a type and identifier.
         *
         * @param type The type of the resource.
         * @param identifier The identifier of the resource.
         */
        IResource(std::string type, std::string identifier);

        /**
         * @brief Default destructor.
         */
        virtual ~IResource() = default;

        /**
         * @brief Gets the type of the resource.
         *
         * @return The type of the resource.
         */
        const std::string& getType() const;

        /**
         * @brief Gets the identifier of the resource.
         *
         * @return The identifier of the resource.
         */
        const std::string& getIdentifier() const;

    private:
        std::string m_type;       //!< The type of the resource.
        std::string m_identifier; //!< The identifier of the resource.
    };

    /**
     * @class TResource
     * @brief Represents a specific type of resource.
     *
     * This class template extends IResource and holds a value of type T, which
     * is the actual resource.
     *
     * @tparam T The type of the resource.
     */
    template <class T>
    class TResource final : public IResource
    {
    public:
        /**
         * @brief Constructs a new resource with the specified identifier.
         *
         * @param identifier The identifier of the resource.
         */
        explicit TResource(const std::string& identifier);

        /**
         * @brief Default destructor.
         */
        ~TResource() final = default;

        std::shared_ptr<T> mValue; //!< The actual resource of type std::shared_ptr<const T>.
    };

public:
    /**
     * @brief Constructs a ResourceRegistry with the given renderer.
     *
     * @param renderer A reference to the renderer used for resource loading.
     */
    explicit ResourceRegistry(const e2d::Renderer& renderer);

    /**
     * @brief Destroys the ResourceRegistry.
     */
    ~ResourceRegistry();

    /**
     * @brief Checks if a resource of type T exists.
     *
     * @tparam T The type of the resource.
     * @param identifier The identifier of the resource.
     * @return true if the resource exists, false otherwise.
     */
    template <typename T>
    bool exists(const std::string& identifier) const;

    /**
     * @brief Retrieves a resource of type T.
     *
     * @tparam T The type of the resource.
     * @param identifier The identifier of the resource.
     * @return An optional reference to the resource if it exists.
     */
    template <typename T>
    std::shared_ptr<const T> get(const std::string& identifier) const;

    /**
     * @brief Loads a resource of type T from a file.
     *
     * @tparam T The type of the resource.
     * @tparam Args Additional arguments required for loading the resource.
     * @param identifier The identifier for the resource.
     * @param filepath The path to the file from which the resource is loaded.
     * @param args Additional arguments required for loading the resource.
     * @return true if the resource is successfully loaded, false otherwise.
     */
    template <typename T, typename... Args>
    bool loadFromFile(const std::string& identifier, const std::string& filepath, Args&&... args);

    /**
     * @brief Loads a texture from a file.
     *
     * @param identifier The identifier to associate with the texture.
     * @param filepath The path to the texture file.
     * @return True if the texture is loaded successfully, false otherwise.
     */
    bool loadTextureFromFile(const std::string& identifier, const std::string& filepath);

private:
    std::reference_wrapper<const e2d::Renderer>                 m_renderer; //!< Reference to the renderer.
    std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources; //!< Container for storing resources by their identifiers.

}; // class ResourceRegistry

template <class T>
ResourceRegistry::TResource<T>::TResource(const std::string& identifier) : IResource(typeid(T).name(), identifier)
{
}

template <typename T>
bool ResourceRegistry::exists(const std::string& identifier) const
{
    auto it = this->m_resources.find(identifier);
    return it != this->m_resources.end() && it->second->getType() == typeid(T).name();
}

template <typename T>
std::shared_ptr<const T> ResourceRegistry::get(const std::string& identifier) const
{
    auto it = this->m_resources.find(identifier);
    if (it != this->m_resources.end() && it->second->getType() == typeid(T).name())
    {
        auto resource = dynamic_cast<TResource<T>*>(it->second.get());
        if (resource)
        {
            return resource->mValue;
        }
    }
    throw std::runtime_error("The resource `" + identifier + "` has not been loaded.");
}

template <typename T, typename... Args>
bool ResourceRegistry::loadFromFile(const std::string& identifier,
                                    const std::string& filepath,
                                    Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    static_assert(std::is_base_of<Resource, T>::value, "T must be derived from Resource");
    if (!this->exists<T>(identifier))
    {
        auto resource    = std::make_unique<TResource<T>>(identifier);
        resource->mValue = std::make_shared<T>();
        if (resource->mValue->loadFromFile(filepath, std::forward<Args>(args)...))
        {
            this->m_resources.insert(std::make_pair(identifier, std::move(resource)));
            return true;
        }
        else
        {
            std::cerr << "Unable to load `" << identifier << "` from file `" << filepath << "`" << '\n';
        }
    }
    return false;
}

} // namespace e2d

#endif //E2D_ENGINE_RESOURCEREGISTRY_HPP
