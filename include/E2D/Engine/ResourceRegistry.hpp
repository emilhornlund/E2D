/**
 * @file ResourceRegistry.hpp
 *
 * MIT License
 *
 * Copyright (c) 2024 Emil Hörnlund
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
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace e2d
{

/**
 * @class ResourceRegistry
 * @ingroup engine
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
         * @brief Constructs a new IResource object with a type and identifier.
         *
         * Initializes a new IResource instance with the specified type and identifier.
         *
         * @param type The type of the resource.
         * @param identifier The identifier of the resource.
         */
        IResource(std::string type, std::string identifier);

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of resources upon destruction.
         */
        virtual ~IResource();

        /**
         * @brief Gets the type of the resource.
         *
         * Retrieves the type of this resource.
         *
         * @return The type of the resource.
         */
        const std::string& getType() const;

        /**
         * @brief Gets the identifier of the resource.
         *
         * Retrieves the identifier of this resource.
         *
         * @return The identifier of the resource.
         */
        const std::string& getIdentifier() const;

    private:
        std::string m_type;       //!< The type of the resource.
        std::string m_identifier; //!< The identifier of the resource.

    }; // IResource class

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
         * @brief Constructs a new TResource object.
         *
         * Initializes a new instance of the TResource class with the specified identifier.
         *
         * @param identifier The identifier of the resource.
         */
        explicit TResource(const std::string& identifier);

        /**
         * @brief Destructor.
         *
         * Ensures proper cleanup of resources upon destruction.
         */
        ~TResource() final;

        std::shared_ptr<T> mValue; //!< The actual resource of type std::shared_ptr<const T>.

    }; // TResource class

public:
    /**
     * @brief Constructs a new ResourceRegistry object.
     *
     * Initializes a new instance of the ResourceRegistry class.
     */
    ResourceRegistry();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~ResourceRegistry();

    /**
     * @brief Checks if a resource of type T exists.
     *
     * Determines whether a resource with the given identifier exists in the registry.
     *
     * @tparam T The type of the resource.
     * @param identifier The identifier of the resource.
     * @return True if the resource exists, false otherwise.
     */
    template <typename T>
    bool exists(const std::string& identifier) const;

    /**
     * @brief Retrieves a resource of type T.
     *
     * Retrieves the resource with the given identifier from the registry if it exists.
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
     * Loads the resource from the specified file and registers it with the given identifier.
     *
     * @tparam T The type of the resource.
     * @tparam Args Additional arguments required for loading the resource.
     * @param identifier The identifier for the resource.
     * @param filepath The path to the file from which the resource is loaded.
     * @param args Additional arguments required for loading the resource.
     * @return True if the resource is successfully loaded, false otherwise.
     */
    template <typename T, typename... Args>
    bool loadFromFile(const std::string& identifier, const std::string& filepath, Args&&... args);

    /**
     * @brief Loads a resource of type T from memory.
     *
     * Loads the resource from the specified memory block and registers it with the given identifier.
     *
     * @tparam T The type of the resource.
     * @tparam Args Additional arguments required for loading the resource.
     * @param identifier The identifier for the resource.
     * @param data Pointer to the memory block containing the resource data.
     * @param size Size of the memory block in bytes.
     * @param args Additional arguments required for loading the resource.
     * @return True if the resource is successfully loaded, false otherwise.
     */
    template <typename T, typename... Args>
    bool loadFromMemory(const std::string& identifier, const void* data, std::size_t size, Args&&... args);

private:
    std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources; //!< Container for storing resources by their identifiers.

}; // class ResourceRegistry

} // namespace e2d

#include <E2D/Engine/ResourceRegistry.inl>

#endif //E2D_ENGINE_RESOURCEREGISTRY_HPP
