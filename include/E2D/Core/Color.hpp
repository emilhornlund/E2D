/**
 * Color.hpp
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

#ifndef E2D_CORE_COLOR_HPP
#define E2D_CORE_COLOR_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <cstdint>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @brief Utility class for manipulating RGBA colors
 */
class Color final
{
public:
    /**
     * @brief Default constructor
     *
     * Constructs an opaque black color. It is equivalent to
     * e2d::Color(0, 0, 0, 255).
     */
    constexpr Color();

    /**
     * @brief Construct the color from its 4 RGBA components
     *
     * @param redComponent   Red component (in the range [0, 255])
     * @param greenComponent Green component (in the range [0, 255])
     * @param blueComponent  Blue component (in the range [0, 255])
     * @param alphaComponent Alpha (opacity) component (in the range [0, 255])
     */
    constexpr Color(std::uint8_t redComponent,
                    std::uint8_t greenComponent,
                    std::uint8_t blueComponent,
                    std::uint8_t alphaComponent = 255);

    /**
     * @brief Construct the color from 32-bit unsigned integer
     *
     * @param color Number containing the RGBA components (in that order)
     */
    constexpr explicit Color(std::uint32_t color);

    /**
     * @brief Retrieve the color as a 32-bit unsigned integer
     *
     * @return Color represented as a 32-bit unsigned integer
     */
    [[nodiscard]] constexpr std::uint32_t toInteger() const;

    /// The red component
    std::uint8_t r{};
    /// The green component
    std::uint8_t g{};
    /// The blue component
    std::uint8_t b{};
    /// The alpha (opacity) component
    std::uint8_t a{255};

    // NOLINTBEGIN(readability-identifier-naming)
    /// Black predefined color
    static const Color Black;
    /// White predefined color
    static const Color White;
    /// Red predefined color
    static const Color Red;
    /// Green predefined color
    static const Color Green;
    /// Blue predefined color
    static const Color Blue;
    /// Yellow predefined color
    static const Color Yellow;
    /// Magenta predefined color
    static const Color Magenta;
    /// Cyan predefined color
    static const Color Cyan;
    /// Transparent (Black) predefined color
    static const Color Transparent;
    // NOLINTEND(readability-identifier-naming)
};

/**
 * @relates Color
 * @brief Overload of the == operator
 *
 * This operator compares two colors and check if they are equal.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return True if colors are equal, false if they are different
 */
[[nodiscard]] constexpr bool operator==(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the != operator
 *
 * This operator compares two colors and check if they are different.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return True if colors are different, false if they are equal
 */
[[nodiscard]] constexpr bool operator!=(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary + operator
 *
 * This operator returns the component-wise sum of two colors.
 * Components that exceed 255 are clamped to 255.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Result of \a left + \a right
 */
[[nodiscard]] constexpr Color operator+(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary - operator
 *
 * This operator returns the component-wise subtraction of two colors.
 * Components below 0 are clamped to 0.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Result of \a left - \a right
 */
[[nodiscard]] constexpr Color operator-(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary * operator
 *
 * This operator returns the component-wise multiplication
 * (also called "modulation") of two colors.
 * Components are then divided by 255 so that the result is
 * still in the range [0, 255].
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Result of \a left * \a right
 */
[[nodiscard]] constexpr Color operator*(const Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary += operator
 *
 * This operator computes the component-wise sum of two colors,
 * and assigns the result to the left operand.
 * Components that exceed 255 are clamped to 255.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Reference to \a left
 */
constexpr Color& operator+=(Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary -= operator
 *
 * This operator computes the component-wise subtraction of two colors,
 * and assigns the result to the left operand.
 * Components below 0 are clamped to 0.
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Reference to \a left
 */
constexpr Color& operator-=(Color& left, const Color& right);

/**
 * @relates Color
 * @brief Overload of the binary *= operator
 *
 * This operator returns the component-wise multiplication
 * (also called "modulation") of two colors, and assigns
 * the result to the left operand.
 * Components are then divided by 255 so that the result is
 * still in the range [0, 255].
 *
 * @param left  Left operand
 * @param right Right operand
 *
 * @return Reference to \a left
 */
constexpr Color& operator*=(Color& left, const Color& right);

#include <E2D/Core/Color.inl>

} // namespace e2d

#endif //E2D_CORE_COLOR_HPP
