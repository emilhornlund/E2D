/**
 * E2D
 * Copyright (C) 2020 (emil.hornlund@me.com)
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

#ifndef E2D_SYSTEM_SIZE_HPP
#define E2D_SYSTEM_SIZE_HPP

#include <E2D/System/Export.hpp>

/**
 * @brief Engine2D
 */
namespace e2d {

    /**
     * @brief Window
     */
    template <typename T>
    class E2D_SYSTEM_API Vector2 final {
    public:
        /**
         * @brief Default constructor
         */
        Vector2();

        /**
         * @brief Construct the vector from its coordinates
         *
         * @param x X coordinate
         * @param y Y coordinate
         */
        Vector2(T x, T y);

        /**
         * @brief Construct the vector from another type of vector
         *
         * @param vector Vector to convert
         */
        template <typename U>
        explicit Vector2(const Vector2<U>& vector);

        /// X coordinate of the vector
        T x;

        /// Y coordinate of the vector
        T y;

    }; // class Size

    template<typename T>
    Vector2<T>::Vector2() : x(0), y(0) {}

    template<typename T>
    Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

    template<typename T>
    template<typename U>
    Vector2<T>::Vector2(const Vector2<U> &vector) :
            x(static_cast<T>(vector.x)),
            y(static_cast<T>(vector.y)) {}

    /**
     * @brief Overload of unary operator -
     *
     * @param right Vector to negate
     *
     * @return Memberwise opposite of the vector
     */
    template<typename T>
    Vector2<T> operator -(const Vector2<T>& right) {
        return Vector2<T>(-right.x, -right.y);
    }

    /**
     * @brief Overload of binary operator +=
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return Reference to \a left
     */
    template<typename T>
    Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right) {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    /**
     * @brief Overload of binary operator -=
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return Reference to \a left
     */
    template<typename T>
    Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right) {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    /**
     * @brief Overload of binary operator +
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return
     */
    template<typename T>
    Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }

    /**
     * @brief Overload of binary operator -
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return
     */
    template<typename T>
    Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    /**
     * @brief Overload of binary operator *
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return
     */
    template<typename T>
    Vector2<T> operator *(const Vector2<T>& left, T right) {
        return Vector2<T>(left.x * right, left.y * right);
    }

    /**
     * @brief Overload of binary operator *
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return
     */
    template<typename T>
    Vector2<T> operator *(T left, const Vector2<T>& right) {
        return Vector2<T>(right.x * left, right.y * left);
    }

    /**
     * @brief Overload of binary operator *=
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return Reference to \a left
     */
    template<typename T>
    Vector2<T>& operator *=(Vector2<T>& left, T right) {
        left.x *= right;
        left.y *= right;

        return left;
    }

    /**
     * @brief Overload of binary operator /
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return
     */
    template<typename T>
    Vector2<T> operator /(const Vector2<T>& left, T right) {
        return Vector2<T>(left.x / right, left.y / right);
    }

    /**
     * @brief Overload of binary operator /=
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return Reference to \a left
     */
    template<typename T>
    Vector2<T>& operator /=(Vector2<T>& left, T right) {
        left.x /= right;
        left.y /= right;

        return left;
    }

    /**
     * @brief Overload of binary operator ==
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return True if \a left is equal to \a right
     */
    template<typename T>
    bool operator ==(const Vector2<T>& left, const Vector2<T>& right) {
        return (left.x == right.x) && (left.y == right.y);
    }

    /**
     * @brief Overload of binary operator !=
     *
     * @param left  Left operand (a vector)
     * @param right Right operand (a vector)
     *
     * @return True if \a left is not equal to \a right
     */
    template<typename T>
    bool operator !=(const Vector2<T>& left, const Vector2<T>& right) {
        return (left.x != right.x) || (left.y != right.y);
    }

} // namespace e2d

#endif //E2D_SYSTEM_SIZE_HPP
