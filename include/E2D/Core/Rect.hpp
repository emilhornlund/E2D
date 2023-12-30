/**
* Rect.hpp
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

#pragma once

#include <E2D/Core/Vector2.hpp>

#include <optional>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class e2d::Rect
 * @brief Represents a rectangle defined by a position (top-left corner) and a size (width and height).
 *
 * @tparam T The numerical type of the rectangle's components (e.g., int, float, double).
 */
template <typename T>
class Rect
{
public:
    /**
     * @brief Constructs a default rectangle with zeroed position and size.
     */
    constexpr Rect();

    /**
     * @brief Constructs a rectangle with specified position and size.
     *
     * @param position The position of the top-left corner of the rectangle.
     * @param size The size of the rectangle.
     */
    constexpr Rect(const Vector2<T>& position, const Vector2<T>& size);

    /**
     * @brief Constructs a rectangle by converting from another rectangle of a different type.
     *
     * @tparam U The type of the source rectangle.
     * @param rectangle The rectangle to convert from.
     */
    template <typename U>
    constexpr explicit Rect(const Rect<U>& rectangle);

    /**
     * @brief Checks if the rectangle contains a given point.
     *
     * @param point The point to check.
     * @return true if the rectangle contains the point, false otherwise.
     */
    constexpr bool contains(const Vector2<T>& point) const;

    /**
     * @brief Finds the intersection with another rectangle.
     *
     * @param rectangle The other rectangle to find the intersection with.
     * @return An optional containing the intersection rectangle if it exists, std::nullopt otherwise.
     */
    constexpr std::optional<Rect<T>> findIntersection(const Rect<T>& rectangle) const;

    /**
     * @brief Gets the position of the rectangle.
     *
     * @return The position of the top-left corner of the rectangle.
     */
    constexpr Vector2<T> getPosition() const;

    /**
     * @brief Gets the size of the rectangle.
     *
     * @return The size of the rectangle.
     */
    constexpr Vector2<T> getSize() const;

    /**
     * @brief Gets the center point of the rectangle.
     *
     * @return The center point of the rectangle.
     */
    constexpr Vector2<T> getCenter() const;

    T left{};   //!< The left coordinate of the rectangle.
    T top{};    //!< The top coordinate of the rectangle.
    T width{};  //!< The width of the rectangle.
    T height{}; //!< The height of the rectangle.
};

using IntRect    = Rect<int>;    //!< Specialization of Rect for int type.
using FloatRect  = Rect<float>;  //!< Specialization of Rect for float type.
using DoubleRect = Rect<double>; //!< Specialization of Rect for double type.

/**
 * @brief Compares two rectangles for equality.
 *
 * @tparam T The numerical type of the rectangle's components.
 * @param left The first rectangle.
 * @param right The second rectangle.
 * @return true if the rectangles are equal, false otherwise.
 */
template <typename T>
[[nodiscard]] constexpr bool operator==(const Rect<T>& left, const Rect<T>& right);

/**
 * @brief Compares two rectangles for inequality.
 *
 * @tparam T The numerical type of the rectangle's components.
 * @param left The first rectangle.
 * @param right The second rectangle.
 * @return true if the rectangles are not equal, false otherwise.
 */
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Rect<T>& left, const Rect<T>& right);

#include <E2D/Core/Rect.inl>

} // namespace e2d