/**
 * @file Formatter.hpp
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

#ifndef E2D_CORE_FORMATTER_HPP
#define E2D_CORE_FORMATTER_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <iostream>
#include <sstream>
#include <string>

namespace e2d
{

/**
 * @class Formatter
 * @ingroup core
 * @brief A utility class for formatting strings with placeholders.
 *
 * This class provides static methods to format strings with placeholders and arguments.
 */
class E2D_CORE_API Formatter final : NonCopyable
{
public:
    /**
     * @brief Formats a string with the given arguments.
     *
     * Replaces placeholders "{}" in the text with the provided arguments.
     *
     * @tparam Args The types of the arguments to format.
     * @param text The format string containing placeholders.
     * @param args The arguments to replace the placeholders.
     * @return A formatted string with placeholders replaced by the arguments.
     */
    template <typename... Args>
    static std::string format(const std::string& text, Args&&... args);

private:
    /**
     * @brief Constructs a new Formatter object.
     *
     * Initializes a new instance of the Formatter class.
     */
    Formatter() = default;

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Formatter() = default;

    /**
     * @brief Base case for the recursive formatImpl method.
     *
     * Appends the remaining text after the last placeholder to the output stream.
     *
     * @param oss The output string stream.
     * @param text The format string.
     * @param pos The current position in the format string.
     */
    static void formatImpl(std::ostringstream& oss, const std::string& text, size_t pos);

    /**
     * @brief Recursive method to process each argument and replace placeholders.
     *
     * Replaces the next placeholder "{}" in the text with the provided argument, then recursively processes the remaining arguments.
     *
     * @tparam T The type of the current argument.
     * @tparam Args The types of the remaining arguments.
     * @param oss The output string stream.
     * @param text The format string.
     * @param pos The current position in the format string.
     * @param arg The current argument to replace the placeholder.
     * @param args The remaining arguments to replace subsequent placeholders.
     */
    template <typename T, typename... Args>
    static void formatImpl(std::ostringstream& oss, const std::string& text, size_t pos, T&& arg, Args&&... args);

    /**
     * @brief Handles escaped braces by replacing double braces with single braces.
     *
     * Replaces occurrences of "{{" with "{" and "}}" with "}" in the input format string.
     *
     * @param text The input format string.
     * @return The modified format string with double braces replaced by single braces.
     */
    static std::string handleEscapedBraces(const std::string& text);
};

// class Formatter

#include <E2D/Core/Formatter.inl>

} // namespace e2d

#endif //E2D_CORE_FORMATTER_HPP
