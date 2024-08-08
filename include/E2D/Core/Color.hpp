/**
 * Color.hpp
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

#include <cstdint>

namespace e2d
{

/**
 * @class Color
 * @brief Utility class for manipulating RGBA colors.
 *
 * The Color class provides a representation of colors with red, green, blue, and alpha (opacity) components.
 * It includes predefined colors and supports various operations for manipulating color values.
 */
class Color final
{
public:
    /**
     * @brief Constructs a new Color object.
     *
     * Constructs an opaque black color. It is equivalent to e2d::Color(0, 0, 0, 255).
     */
    constexpr Color();

    /**
     * @brief Construct a new Color object from its 4 RGBA components.
     *
     * Initializes the color with the specified red, green, blue, and alpha components.
     *
     * @param redComponent   Red component (in the range [0, 255]).
     * @param greenComponent Green component (in the range [0, 255]).
     * @param blueComponent  Blue component (in the range [0, 255]).
     * @param alphaComponent Alpha (opacity) component (in the range [0, 255]).
     */
    constexpr Color(std::uint8_t redComponent,
                    std::uint8_t greenComponent,
                    std::uint8_t blueComponent,
                    std::uint8_t alphaComponent = 255);

    /**
     * @brief Constructs a new Color object from a 32-bit unsigned integer.
     *
     * Initializes the color using a 32-bit unsigned integer that contains the RGBA components.
     *
     * @param color Number containing the RGBA components (in that order).
     */
    constexpr explicit Color(std::uint32_t color);

    /**
     * @brief Retrieves the color as a 32-bit unsigned integer.
     *
     * Converts the color to a 32-bit unsigned integer representation.
     *
     * @return Color represented as a 32-bit unsigned integer.
     */
    [[nodiscard]] constexpr std::uint32_t toInteger() const;

    std::uint8_t r{};    //!< The red component
    std::uint8_t g{};    //!< The green component
    std::uint8_t b{};    //!< The blue component
    std::uint8_t a{255}; //!< The alpha (opacity) component

    // NOLINTBEGIN(readability-identifier-naming)
    static const Color Black;       //!< Black predefined color
    static const Color White;       //!< White predefined color
    static const Color Red;         //!< Red predefined color
    static const Color Green;       //!< Green predefined color
    static const Color Blue;        //!< Blue predefined color
    static const Color Yellow;      //!< Yellow predefined color
    static const Color Magenta;     //!< Magenta predefined color
    static const Color Cyan;        //!< Cyan predefined color
    static const Color Transparent; //!< Transparent (Black) predefined color
    // NOLINTEND(readability-identifier-naming)
};

/**
 * @relates Color
 * @brief Overload of the == operator.
 *
 * This operator compares two colors and checks if they are equal.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return True if colors are equal, false if they are different.
 */
[[nodiscard]] constexpr bool operator==(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the != operator.
 *
 * This operator compares two colors and checks if they are different.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return True if colors are different, false if they are equal.
 */
[[nodiscard]] constexpr bool operator!=(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary + operator.
 *
 * This operator returns the component-wise sum of two colors.
 * Components that exceed 255 are clamped to 255.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Result of left + right.
 */
[[nodiscard]] constexpr Color operator+(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary - operator.
 *
 * This operator returns the component-wise subtraction of two colors.
 * Components below 0 are clamped to 0.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Result of left - right.
 */
[[nodiscard]] constexpr Color operator-(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary * operator.
 *
 * This operator returns the component-wise multiplication (also called "modulation") of two colors.
 * Components are then divided by 255 so that the result is still in the range [0, 255].
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Result of left * right.
 */
[[nodiscard]] constexpr Color operator*(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary += operator.
 *
 * This operator computes the component-wise sum of two colors, and assigns the result to the left operand.
 * Components that exceed 255 are clamped to 255.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Reference to left.
 */
constexpr Color& operator+=(Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary -= operator.
 *
 * This operator computes the component-wise subtraction of two colors, and assigns the result to the left operand.
 * Components below 0 are clamped to 0.
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Reference to left.
 */
constexpr Color& operator-=(Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary *= operator.
 *
 * This operator computes the component-wise multiplication (also called "modulation") of two colors,
 * and assigns the result to the left operand.
 * Components are then divided by 255 so that the result is still in the range [0, 255].
 *
 * @param left  Left operand.
 * @param right Right operand.
 *
 * @return Reference to left.
 */
constexpr Color& operator*=(Color& left, const Color& right);

#include <E2D/Core/Color.inl>

} // namespace e2d
