/**
 * Vector2.hpp
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

#pragma once

#include <cassert>

namespace e2d
{

/**
 * @class Vector2
 * @brief Represents a 2-dimensional vector.
 *
 * The Vector2 class provides functionalities to define and manipulate 2D vectors.
 * It supports basic vector operations such as addition, subtraction, and scaling.
 *
 * @tparam T The numerical type of the vector's components (e.g., int, unsigned int, float, double).
 */
template <typename T>
class Vector2
{
public:
    /**
     * @brief Constructs a default vector with both x and y set to zero.
     *
     * Initializes the vector with x and y coordinates set to zero.
     */
    constexpr Vector2();

    /**
     * @brief Constructs a vector with the specified x and y values.
     *
     * Initializes the vector with the given x and y coordinates.
     *
     * @param x The value for the x-coordinate.
     * @param y The value for the y-coordinate.
     */
    constexpr Vector2(T x, T y);

    /**
     * @brief Constructs a Vector2 from another Vector2 of a different type.
     *
     * Initializes the vector by converting the components of another vector to this vector's type.
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
 * @relates Vector2
 * @brief Unary minus operator, negates the vector.
 *
 * Negates the x and y components of the vector.
 *
 * @tparam T The type of the vector elements.
 * @param right The vector to negate.
 * @return The negated vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Addition assignment operator, adds another vector to this vector.
 *
 * Adds the x and y components of the right vector to the left vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to which the right vector is added.
 * @param right The vector to add.
 * @return Reference to the modified left vector.
 */
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Subtraction assignment operator, subtracts another vector from this vector.
 *
 * Subtracts the x and y components of the right vector from the left vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector from which the right vector is subtracted.
 * @param right The vector to subtract.
 * @return Reference to the modified left vector.
 */
template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Addition operator, adds two vectors.
 *
 * Adds the x and y components of the left and right vectors.
 *
 * @tparam T The type of the vector elements.
 * @param left The first vector.
 * @param right The second vector.
 * @return The result of the addition.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Subtraction operator, subtracts two vectors.
 *
 * Subtracts the x and y components of the right vector from the left vector.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector from which to subtract.
 * @param right The vector to subtract.
 * @return The result of the subtraction.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Multiplication operator, multiplies a vector by a scalar.
 *
 * Multiplies the x and y components of the vector by the scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector.
 * @param right The scalar value.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(const Vector2<T>& left, T right);

/**
 * @relates Vector2
 * @brief Multiplication operator, multiplies a scalar by a vector.
 *
 * Multiplies the x and y components of the vector by the scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The scalar value.
 * @param right The vector.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(T left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Multiplication assignment operator, scales this vector by a scalar.
 *
 * Multiplies the x and y components of the left vector by the scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to scale.
 * @param right The scalar value.
 * @return Reference to the modified vector.
 */
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right);

/**
 * @relates Vector2
 * @brief Division operator, divides a vector by a scalar.
 *
 * Divides the x and y components of the vector by the scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector.
 * @param right The scalar value.
 * @return The scaled vector.
 */
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator/(const Vector2<T>& left, T right);

/**
 * @relates Vector2
 * @brief Division assignment operator, scales this vector down by a scalar.
 *
 * Divides the x and y components of the left vector by the scalar.
 *
 * @tparam T The type of the vector elements.
 * @param left The vector to scale down.
 * @param right The scalar value.
 * @return Reference to the modified vector.
 */
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right);

/**
 * @relates Vector2
 * @brief Equality comparison operator, checks if two vectors are equal.
 *
 * Compares the x and y components of the left and right vectors for equality.
 *
 * @tparam T The type of the vector elements.
 * @param left The first vector.
 * @param right The second vector.
 * @return True if vectors are equal, false otherwise.
 */
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right);

/**
 * @relates Vector2
 * @brief Inequality comparison operator, checks if two vectors are not equal.
 *
 * Compares the x and y components of the left and right vectors for inequality.
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
