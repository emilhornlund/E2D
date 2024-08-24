/**
 * @file Object.hpp
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

#ifndef E2D_ENGINE_OBJECT_HPP
#define E2D_ENGINE_OBJECT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <atomic>
#include <mutex>
#include <string>

namespace e2d
{
struct Event;         // Forward declaration of Event
class ObjectRegistry; // Forward declaration of ObjectRegistry

/**
 * @class Object
 * @ingroup engine
 * @brief Abstract base class for all game objects.
 *
 * Object is the superclass for all types of objects in the game, providing a common interface
 * and shared functionality. Every Object has a unique identifier and can be updated regularly
 * through fixed and variable update methods.
 */
class E2D_ENGINE_API Object : NonCopyable
{
public:
    /**
     * @brief Constructs a new Object object.
     *
     * Initializes a new instance of the Object class with a unique identifier.
     */
    Object();

    /**
     * @brief Constructs an Object with a given identifier.
     *
     * Initializes a new instance of the Object class with the specified unique identifier.
     *
     * @param identifier A string representing the unique identifier of the object.
     */
    explicit Object(std::string identifier);

    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    virtual ~Object() = 0;

    /**
     * @brief Called when the object is loaded.
     *
     * This method is called when the object is first created and loaded into the system.
     * Derived classes can override this method to perform any initialization or resource
     * allocation required when the object is loaded.
     */
    virtual void onLoad();

    /**
     * @brief Called when the object is unloaded.
     *
     * This method is called when the object is removed from the registry or when the
     * application is shutting down. Derived classes can override this method to perform
     * any cleanup or resource deallocation required when the object is unloaded.
     */
    virtual void onUnload();

    /**
     * @brief Handles events directed to this object.
     *
     * This method is called when an event relevant to this object occurs. Derived classes
     * can override this method to handle specific types of events, such as input events,
     * window events, or custom events defined by the application.
     *
     * @param event The event that has occurred, which this object should process.
     */
    virtual void onEvent(const Event& event);

    /**
     * @brief Fixed update method for consistent, time-sensitive updates.
     *
     * This method is called at a consistent rate, typically 60 times per second,
     * and is used for updates where consistent timing is crucial. This is ideal
     * for physics updates, collision detection, and other time-sensitive operations
     * where a fixed time step is necessary to maintain consistent behavior.
     */
    virtual void onFixedUpdate();

    /**
     * @brief Variable update method for frame-dependent updates.
     *
     * This method is called as often as possible, typically every frame, and receives
     * the time elapsed since the last update as a parameter. Use this method for updates
     * that can vary with the frame rate, such as animations, general game logic, and
     * operations that are not time-sensitive. The deltaTime parameter helps in creating
     * frame rate independent behavior.
     *
     * @param deltaTime The time elapsed since the last variable update in seconds.
     */
    virtual void onVariableUpdate(double deltaTime);

    /**
     * @brief Gets the unique identifier of the Object.
     *
     * Retrieves the unique identifier assigned to this Object.
     *
     * @return The identifier as a const reference to a string.
     */
    const std::string& getIdentifier() const;

private:
    /**
     * @brief Generates a unique identifier for an object.
     *
     * This function generates a unique identifier using an atomic counter, ensuring thread safety
     * with the use of a mutex. The identifier is a string prefixed with "Object" followed by a
     * numeric value.
     *
     * @return A string representing the unique identifier.
     */
    static std::string generateUniqueIdentifier();

    static std::atomic<std::uint64_t> s_counter;      //!< Counter for unique identifiers.
    static std::mutex                 s_counterMutex; //!< Mutex to protect the counter.
    const std::string                 m_identifier;   //!< The object's unique identifier.

}; // class Object

} // namespace e2d

#endif //E2D_ENGINE_OBJECT_HPP
