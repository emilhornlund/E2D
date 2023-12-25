/**
* Vector2.hpp
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

#include <cassert>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class Vector2
 * @brief Represents a 2-dimensional vector.
 *
 * @tparam T The type of the elements in the vector.
 */
template <typename T>
class Vector2
{
public:
    /**
     * @brief Default constructor, initializes both x and y to zero.
     */
    constexpr Vector2();

    /**
     * @brief Constructor initializing x and y with the provided values.
     *
     * @param x The value for the x-coordinate.
     * @param y The value for the y-coordinate.
     */
    constexpr Vector2(T x, T y);

    /**
     * @brief Constructs a Vector2 from another Vector2 of different type.
     *
     * @tparam U The type of the elements in the provided vector.
     * @param vector The vector from which to copy the values.
     */
    template <typename U>
    constexpr explicit Vector2(const Vector2<U>& vector);

    T x{}; //!< X coordinate of the vector.
    T y{}; //!< Y coordinate of the vector.
};

using Vector2i = Vector2<int>;          //!< Typedef for Vector2 with int type.
using Vector2u = Vector2<unsigned int>; //!< Typedef for Vector2 with unsigned int type.
using Vector2f = Vector2<float>;        //!< Typedef for Vector2 with float type.
using Vector2d = Vector2<double>;       //!< Typedef for Vector2 with double type.

/**
 * @brief Unary minus operator, negates the vector.
 *
 * @tparam T The type of the vector elements.
 * @param right The vector to negate.
 * @return The negated vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& right);

/**
 * @brief Addition assignment operator, adds another vector to this vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to which the right vector is added.
 * @param right The vector to add.
 * @return Reference to the modified left vector.
 */
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

/**
 * @brief Subtraction assignment operator, subtracts another vector from this vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector from which the right vector is subtracted.
 * @param right The vector to subtract.
 * @return Reference to the modified left vector.
 */
template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

/**
 * @brief Addition operator, adds two vectors.
 *
 * @tparam T The type of the vector elements.
 * @param left The first vector.
 * @param right The second vector.
 * @return The result of the addition.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @brief Subtraction operator, subtracts two vectors.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector from which to subtract.
 * @param right The vector to subtract.
 * @return The result of the subtraction.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @brief Multiplication operator, multiplies a vector by a scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector.
 * @param right The scalar value.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(const Vector2<T>& left, T right);

/**
 * @brief Multiplication operator, multiplies a scalar by a vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The scalar value.
 * @param right The vector.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(T left, const Vector2<T>& right);

/**
 * @brief Multiplication assignment operator, scales this vector by a scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to scale.
 * @param right The scalar value.
 * @return Reference to the modified vector.
 */
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right);

/**
 * @brief Division operator, divides a vector by a scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector.
 * @param right The scalar value.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator/(const Vector2<T>& left, T right);

/**
 * @brief Division assignment operator, scales this vector down by a scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to scale down.
 * @param right The scalar value.
 * @return Reference to the modified vector.
 */
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right);

/**
 * @brief Equality comparison operator, checks if two vectors are equal.
 *
 * @tparam T The type of the vector elements.
 * @param left The first vector.
 * @param right The second vector.
 * @return True if vectors are equal, false otherwise.
 */
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @brief Inequality comparison operator, checks if two vectors are not equal.
 *
 * @tparam T The type of the vector elements.
 * @param left The first vector.
 * @param right The second vector.
 * @return True if vectors are not equal, false otherwise.
 */
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right);

#include <E2D/Core/Vector2.inl>

} // namespace e2d
