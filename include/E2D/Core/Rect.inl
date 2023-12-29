/**
* Rect.inl
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

template <typename T>
constexpr Rect<T>::Rect() = default;

template <typename T>
constexpr Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) :
left(position.x),
top(position.y),
width(size.x),
height(size.y)
{
}

template <typename T>
template <typename U>
constexpr Rect<T>::Rect(const Rect<U>& rectangle) :
left(static_cast<T>(rectangle.left)),
top(static_cast<T>(rectangle.top)),
width(static_cast<T>(rectangle.width)),
height(static_cast<T>(rectangle.height))
{
}

template <typename T>
constexpr bool Rect<T>::contains(const Vector2<T>& point) const
{
    const auto min = [](T a, T b) { return (a < b) ? a : b; };
    const auto max = [](T a, T b) { return (a < b) ? b : a; };

    const T minX = min(left, static_cast<T>(left + width));
    const T maxX = max(left, static_cast<T>(left + width));
    const T minY = min(top, static_cast<T>(top + height));
    const T maxY = max(top, static_cast<T>(top + height));

    return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}

template <typename T>
constexpr std::optional<Rect<T>> Rect<T>::findIntersection(const Rect<T>& rectangle) const
{
    const auto min = [](T a, T b) { return (a < b) ? a : b; };
    const auto max = [](T a, T b) { return (a < b) ? b : a; };

    const T r1MinX = min(left, static_cast<T>(left + width));
    const T r1MaxX = max(left, static_cast<T>(left + width));
    const T r1MinY = min(top, static_cast<T>(top + height));
    const T r1MaxY = max(top, static_cast<T>(top + height));

    const T r2MinX = min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    const T r2MaxX = max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    const T r2MinY = min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
    const T r2MaxY = max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

    const T interLeft   = max(r1MinX, r2MinX);
    const T interTop    = max(r1MinY, r2MinY);
    const T interRight  = min(r1MaxX, r2MaxX);
    const T interBottom = min(r1MaxY, r2MaxY);

    if ((interLeft < interRight) && (interTop < interBottom))
    {
        return Rect<T>({interLeft, interTop}, {interRight - interLeft, interBottom - interTop});
    }
    else
    {
        return std::nullopt;
    }
}

template <typename T>
constexpr Vector2<T> Rect<T>::getPosition() const
{
    return Vector2<T>(left, top);
}

template <typename T>
constexpr Vector2<T> Rect<T>::getSize() const
{
    return Vector2<T>(width, height);
}

template <typename T>
constexpr Vector2<T> Rect<T>::getCenter() const
{
    return getPosition() + getSize() / T{2};
}

template <typename T>
constexpr bool operator==(const Rect<T>& left, const Rect<T>& right)
{
    return (left.left == right.left) && (left.width == right.width) && (left.top == right.top) &&
           (left.height == right.height);
}

template <typename T>
constexpr bool operator!=(const Rect<T>& left, const Rect<T>& right)
{
    return !(left == right);
}
