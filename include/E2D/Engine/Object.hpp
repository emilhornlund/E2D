/**
 * Object.hpp
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

#ifndef E2D_ENGINE_OBJECT_HPP
#define E2D_ENGINE_OBJECT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <string>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Application;    // Forward declaration of Application
class ObjectRegistry; // Forward declaration of ObjectRegistry

/**
 * @class Object
 * @brief Base class for all game objects in the E2D Engine.
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
     * @brief Default constructor for the Object class.
     */
    Object();

    /**
     * @brief Constructs an Object with a given identifier.
     *
     * @param identifier A string representing the unique identifier of the object.
     */
    explicit Object(std::string identifier);

    /**
     * @brief Virtual destructor for Object.
     *
     * Allows for polymorphic destruction of Object instances.
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
     * @return The identifier as a const reference to a string.
     */
    const std::string& getIdentifier() const;

protected:
    /**
     * @brief Gets the application reference for this object.
     *
     * @return A reference to the application.
     */
    Application& getApplication() const;

private:
    const std::string m_identifier;           //!< The object's unique identifier.
    Application*      m_application{nullptr}; //!< Raw pointer to the application, non-owning

}; // class Object

} // namespace e2d

#endif //E2D_ENGINE_OBJECT_HPP
