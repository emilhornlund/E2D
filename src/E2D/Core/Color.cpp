/**
 * Color.cpp
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

#include <E2D/Core/Color.hpp>

constexpr e2d::Color::Color() = default;

constexpr e2d::Color::Color(std::uint8_t redComponent,
                            std::uint8_t greenComponent,
                            std::uint8_t blueComponent,
                            std::uint8_t alphaComponent) :
r(redComponent),
g(greenComponent),
b(blueComponent),
a(alphaComponent)
{
}

constexpr e2d::Color::Color(std::uint32_t color) :
r(static_cast<std::uint8_t>((color & 0xff000000) >> 24)),
g(static_cast<std::uint8_t>((color & 0x00ff0000) >> 16)),
b(static_cast<std::uint8_t>((color & 0x0000ff00) >> 8)),
a(static_cast<std::uint8_t>(color & 0x000000ff))
{
}

constexpr std::uint32_t e2d::Color::toInteger() const
{
    return static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | a);
}

constexpr bool operator==(const e2d::Color& left, const e2d::Color& right)
{
    return (left.r == right.r) && (left.g == right.g) && (left.b == right.b) && (left.a == right.a);
}

constexpr bool operator!=(const e2d::Color& left, const e2d::Color& right)
{
    return !(left == right);
}

constexpr e2d::Color operator+(const e2d::Color& left, const e2d::Color& right)
{
    const auto clampedAdd = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const int intResult = int{lhs} + int{rhs};
        return static_cast<std::uint8_t>(intResult < 255 ? intResult : 255);
    };

    return {clampedAdd(left.r, right.r),
            clampedAdd(left.g, right.g),
            clampedAdd(left.b, right.b),
            clampedAdd(left.a, right.a)};
}

constexpr e2d::Color operator-(const e2d::Color& left, const e2d::Color& right)
{
    const auto clampedSub = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const int intResult = int{lhs} - int{rhs};
        return static_cast<std::uint8_t>(intResult > 0 ? intResult : 0);
    };

    return {clampedSub(left.r, right.r),
            clampedSub(left.g, right.g),
            clampedSub(left.b, right.b),
            clampedSub(left.a, right.a)};
}

constexpr e2d::Color operator*(const e2d::Color& left, const e2d::Color& right)
{
    const auto scaledMul = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const auto uint16Result = static_cast<std::uint16_t>(std::uint16_t{lhs} * std::uint16_t{rhs});
        return static_cast<std::uint8_t>(uint16Result / 255u);
    };

    return {scaledMul(left.r, right.r), scaledMul(left.g, right.g), scaledMul(left.b, right.b), scaledMul(left.a, right.a)};
}

constexpr e2d::Color& operator+=(e2d::Color& left, const e2d::Color& right)
{
    return left = left + right;
}

constexpr e2d::Color& operator-=(e2d::Color& left, const e2d::Color& right)
{
    return left = left - right;
}

constexpr e2d::Color& operator*=(e2d::Color& left, const e2d::Color& right)
{
    return left = left * right;
}

constexpr e2d::Color e2d::Color::black(0, 0, 0);
constexpr e2d::Color e2d::Color::white(255, 255, 255);
constexpr e2d::Color e2d::Color::red(255, 0, 0);
constexpr e2d::Color e2d::Color::green(0, 255, 0);
constexpr e2d::Color e2d::Color::blue(0, 0, 255);
constexpr e2d::Color e2d::Color::yellow(255, 255, 0);
constexpr e2d::Color e2d::Color::magenta(255, 0, 255);
constexpr e2d::Color e2d::Color::cyan(0, 255, 255);
constexpr e2d::Color e2d::Color::transparent(0, 0, 0, 0);
