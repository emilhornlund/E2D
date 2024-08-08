/**
 * @file Transformable.hpp
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

#ifndef E2D_ENGINE_TRANSFORMABLE_HPP
#define E2D_ENGINE_TRANSFORMABLE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>
#include <E2D/Core/Rect.hpp>
#include <E2D/Core/Vector2.hpp>

namespace e2d
{

/**
 * @class Transformable
 * @ingroup engine
 * @brief Provides an interface for objects that can be transformed.
 *
 * The Transformable class provides methods for setting and retrieving the position,
 * origin, scale, and rotation of objects. It also includes methods for calculating
 * local and global bounding rectangles.
 */
class E2D_ENGINE_API Transformable : NonCopyable
{
public:
    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    virtual ~Transformable() = 0;

    /**
     * @brief Retrieves the current position of the object.
     *
     * Returns the position of the object's origin in the world or screen space.
     *
     * @return The current position as a Vector2f object.
     */
    const Vector2f& getPosition() const;

    /**
     * @brief Sets the position of the object.
     *
     * Updates the position of the object's origin in the world or screen space.
     *
     * @param position The Vector2f object representing the new position.
     */
    void setPosition(const Vector2f& position);

    /**
     * @brief Retrieves the origin point of the object.
     *
     * Returns the point used as a pivot for transformations such as scaling and rotation.
     *
     * @return The current origin as a Vector2f object.
     */
    const Vector2f& getOrigin() const;

    /**
     * @brief Sets the origin point of the object.
     *
     * Updates the point used as a pivot for transformations such as scaling and rotation.
     * Setting the origin to the center, for example, will rotate and scale the object around its center.
     *
     * @param origin The Vector2f object representing the new origin.
     */
    void setOrigin(const Vector2f& origin);

    /**
     * @brief Retrieves the current scaling factors of the object.
     *
     * Returns the scaling factors of the object in the x and y directions.
     *
     * @return The current scale as a Vector2f object.
     */
    const Vector2f& getScale() const;

    /**
     * @brief Sets the scaling factors of the object.
     *
     * Updates the scaling factors of the object in the x and y directions. Negative scaling factors will flip the object horizontally or vertically.
     *
     * @param scale The Vector2f object representing the new scaling factors.
     */
    void setScale(const Vector2f& scale);

    /**
     * @brief Retrieves the current rotation angle of the object in degrees.
     *
     * Returns the rotation angle of the object.
     *
     * @return The current rotation angle.
     */
    double getRotation() const;

    /**
     * @brief Sets the rotation angle of the object.
     *
     * Updates the rotation angle of the object.
     *
     * @param angle The new rotation angle in degrees.
     */
    void setRotation(double angle);

    /**
     * @brief Gets the size of the object.
     *
     * Pure virtual method to retrieve the size of the object.
     *
     * @return Size of the object.
     */
    virtual Vector2f getSize() const = 0;

    /**
     * @brief Gets the local bounding rectangle of the object.
     *
     * Returns the bounding rectangle of the object in its local coordinate space.
     *
     * @return Local bounding rectangle of the object.
     */
    FloatRect getLocalBounds() const;

    /**
     * @brief Gets the global bounding rectangle of the object.
     *
     * Returns the bounding rectangle of the object in the global coordinate space.
     *
     * @return Global bounding rectangle of the object.
     */
    FloatRect getGlobalBounds() const;

private:
    Vector2f m_position;    //!< The position of the object in the world or screen space.
    Vector2f m_origin;      //!< The origin point of the object, used as a pivot for transformations.
    Vector2f m_scale{1, 1}; //!< The scaling factors of the object in the x and y directions.
    double   m_rotation{0}; //!< The rotation angle of the object in degrees.

}; // Transformable class

} // namespace e2d

#endif //E2D_ENGINE_TRANSFORMABLE_HPP
