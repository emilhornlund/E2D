/**
 * NonCopyable.hpp
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

#ifndef E2D_CORE_NONCOPYABLE_HPP
#define E2D_CORE_NONCOPYABLE_HPP

#include <E2D/Core/Export.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @brief The NonCopyable class provides a base class to make derived classes non-copyable.
 */
class E2D_CORE_API NonCopyable
{
public:
    /**
     * @brief Deleted copy constructor to prevent copying of objects.
     *
     * @param other The object to be copied.
     */
    NonCopyable(const NonCopyable&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment of objects.
     *
     * @param other The object to be assigned.
     *
     * @return NonCopyable& A reference to the current object.
     */
    NonCopyable& operator=(const NonCopyable&) = delete;

protected:
    /**
     * @brief Default constructor.
     */
    NonCopyable() = default;

    /**
     * @brief Default destructor.
     */
    ~NonCopyable() = default;
};

} // namespace e2d

#endif //E2D_CORE_NONCOPYABLE_HPP
