/**
 * RandomUtils.hpp
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

#ifndef E2D_ENGINE_RANDOM_UTILS_HPP
#define E2D_ENGINE_RANDOM_UTILS_HPP

#include <E2D/Engine/Export.hpp>

#include <string>

namespace e2d::internal
{

/**
 * @brief Generates a random sequence of alphabetic characters.
 *
 * This function creates a string of the specified length consisting of random
 * alphabetic characters (both uppercase and lowercase).
 *
 * @param length The length of the random sequence to generate.
 * @return A string containing the random alphabetic sequence.
 */
E2D_ENGINE_API std::string generateRandomAlphabeticSequence(size_t length);

} // namespace e2d::internal

#endif //E2D_ENGINE_RANDOM_UTILS_HPP
