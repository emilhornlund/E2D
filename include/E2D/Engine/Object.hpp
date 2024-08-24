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
class Application;    // Forward declaration of Application
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
    friend class ObjectRegistry;

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
     * @brief Fixed update method for consistent, time-sensitive updates.
     *
     * This method is called at a consistent rate, typically 60 times per second,
     * and is used for updates where consistent timing is crucial. This is ideal
     * for physics updates, collision detection, and other time-sensitive operations
     * where a fixed time step is necessary to maintain consistent behavior.
     */
    virtual void fixedUpdate() = 0;

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
    virtual void variableUpdate(double deltaTime) = 0;

    /**
     * @brief Gets the unique identifier of the Object.
     *
     * Retrieves the unique identifier assigned to this Object.
     *
     * @return The identifier as a const reference to a string.
     */
    const std::string& getIdentifier() const;

protected:
    /**
     * @brief Gets the application reference for this object.
     *
     * Provides access to the application instance managing this Object.
     *
     * @return A reference to the application.
     */
    Application& getApplication() const;

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

    static std::atomic<std::uint64_t> s_counter;              //!< Counter for unique identifiers.
    static std::mutex                 s_counterMutex;         //!< Mutex to protect the counter.
    const std::string                 m_identifier;           //!< The object's unique identifier.
    Application*                      m_application{nullptr}; //!< Raw pointer to the application, non-owning.

}; // class Object

} // namespace e2d

#endif //E2D_ENGINE_OBJECT_HPP
