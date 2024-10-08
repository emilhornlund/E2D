/**
 * @file Vector2.inl
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

template <typename T>
constexpr Vector2<T>::Vector2() = default;

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#endif
template <typename T>
constexpr Vector2<T>::Vector2(T x, T y) : x(x), y(y)
{
}
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

template <typename T>
template <typename U>
constexpr Vector2<T>::Vector2(const Vector2<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
{
}

template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}


template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

template <typename T>
constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
constexpr Vector2<T> operator*(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
constexpr Vector2<T> operator*(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
constexpr Vector2<T> operator/(const Vector2<T>& left, T right)
{
    assert(right != 0 && "Vector2::operator/ cannot divide by 0");
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right)
{
    assert(right != 0 && "Vector2::operator/= cannot divide by 0");
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T>
constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
