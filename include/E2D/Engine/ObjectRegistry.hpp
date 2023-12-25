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

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class ObjectRegistry
 * @brief Manages a registry of all game objects in the E2D Engine.
 *
 * ObjectRegistry is responsible for managing the lifecycle of all game objects. It provides
 * methods to add, retrieve, and remove objects from the game. The registry can also return
 * all objects or objects of a specific type.
 */
namespace e2d
{
class Object; // Forward declaration of Object

/**
 * @class ObjectRegistry
 * @brief
 */
class E2D_ENGINE_API ObjectRegistry final : NonCopyable
{
public:
    /**
     * @brief Default constructor for ObjectRegistry.
     *
     * Initializes a new instance of the ObjectRegistry class.
     */
    ObjectRegistry();

    /**
     * @brief Destructor for ObjectRegistry.
     *
     * Cleans up resources used by the ObjectRegistry object.
     */
    ~ObjectRegistry();

    /**
     * @brief Adds an object to the registry.
     *
     * This method adds a unique_ptr to an Object to the registry. Each object must have
     * a unique identifier.
     *
     * @param object The unique_ptr to the Object to add.
     * @return True if the object was added successfully, false if an object with the same
     *         identifier already exists in the registry.
     */
    bool addObject(std::unique_ptr<Object> object);

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
    std::unordered_map<std::string, std::unique_ptr<Object>> m_objects; //!< Map storing all objects by their unique identifiers.

}; // class ObjectRegistry

template <typename T>
std::vector<T*> e2d::ObjectRegistry::getAllObjectsOfType() const
{
    static_assert(std::is_base_of<Object, T>::value, "T must be a descendant of Object");
    std::vector<T*> objectsOfType;
    for (const auto& pair : m_objects)
    {
        T* castedObject = dynamic_cast<T*>(pair.second.get());
        if (castedObject)
        {
            objectsOfType.push_back(castedObject);
        }
    }
    return objectsOfType;
}

} // namespace e2d

#endif //E2D_ENGINE_OBJECT_REGISTRY_HPP
