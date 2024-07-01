/**
 * ObjectRegistry.hpp
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

#ifndef E2D_ENGINE_OBJECT_REGISTRY_HPP
#define E2D_ENGINE_OBJECT_REGISTRY_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Object.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Application; // Forward declaration of Application

/**
 * @class ObjectRegistry
 * @brief Manages a registry of all game objects in the E2D Engine.
 *
 * ObjectRegistry is responsible for managing the lifecycle of all game objects. It provides
 * methods to add, retrieve, and remove objects from the game. The registry can also return
 * all objects or objects of a specific type.
 */
class E2D_ENGINE_API ObjectRegistry final : NonCopyable
{
public:
    /**
     * @brief Default constructor for ObjectRegistry.
     *
     * Initializes a new instance of the ObjectRegistry class.
     */
    explicit ObjectRegistry(Application* application);

    /**
     * @brief Destructor for ObjectRegistry.
     *
     * Cleans up resources used by the ObjectRegistry object.
     */
    ~ObjectRegistry();

    /**
     * @brief Creates and registers an object of type T.
     *
     * This method constructs an object of type T with the provided arguments and
     * registers it in the object registry. The object must derive from the base
     * class Object. If an object with the same identifier already exists in the
     * registry, an exception is thrown.
     *
     * @tparam T The type of the object to be created. Must derive from Object.
     * @tparam Args Variadic template parameter pack for the constructor arguments of T.
     * @param args Arguments to be forwarded to the constructor of T.
     * @return A reference to the newly created object of type T.
     * @throws std::runtime_error If an object with the same identifier already exists.
     */
    template <typename T, typename... Args>
    T& createObject(Args&&... args);

    /**
     * @brief Retrieves an object from the registry based on its identifier.
     *
     * @param identifier The unique identifier of the object to retrieve.
     * @return A pointer to the Object if found, nullptr otherwise.
     */
    Object* getObject(const std::string& identifier) const;

    /**
     * @brief Removes an object from the registry based on its identifier.
     *
     * @param identifier The unique identifier of the object to remove.
     * @return True if the object was removed successfully, false if no such object exists.
     */
    bool removeObject(const std::string& identifier);

    /**
     * @brief Retrieves all objects currently in the registry.
     *
     * @return A vector of pointers to all Objects in the registry.
     */
    std::vector<Object*> getAllObjects() const;

    /**
     * @brief Template method to retrieve all objects of a specific type.
     *
     * @tparam T The type of objects to retrieve. Must be a descendant of Object.
     * @return A vector of pointers to Objects of type T.
     */
    template <typename T>
    std::vector<T*> getAllObjectsOfType() const;

private:
    Application* m_application;                                         //!< Raw pointer to the application, non-owning.
    std::unordered_map<std::string, std::unique_ptr<Object>> m_objects; //!< Map storing all objects by their unique identifiers.

}; // class ObjectRegistry

} // namespace e2d

#include <E2D/Engine/ObjectRegistry.inl>

#endif //E2D_ENGINE_OBJECT_REGISTRY_HPP
