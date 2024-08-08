/**
 * @file NonCopyable.hpp
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

#ifndef E2D_CORE_NONCOPYABLE_HPP
#define E2D_CORE_NONCOPYABLE_HPP

#include <E2D/Core/Export.hpp>

namespace e2d
{

/**
 * @class NonCopyable
 * @ingroup core
 * @brief The NonCopyable class provides a base class to make derived classes non-copyable.
 *
 * This class is intended to be used as a base class for other classes to prevent copying.
 * It deletes the copy constructor and copy assignment operator, ensuring that objects
 * of derived classes cannot be copied.
 */
class E2D_CORE_API NonCopyable
{
public:
    /**
     * @brief Deleted copy constructor to prevent copying of objects.
     *
     * Prevents copying of the NonCopyable object.
     *
     * @param other The object to be copied.
     */
    NonCopyable(const NonCopyable&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment of objects.
     *
     * Prevents assignment of the NonCopyable object.
     *
     * @param other The object to be assigned.
     * @return A reference to the current object.
     */
    NonCopyable& operator=(const NonCopyable&) = delete;

protected:
    /**
     * @brief Default constructor.
     *
     * Allows derived classes to be constructed.
     */
    NonCopyable() = default;

    /**
     * @brief Default destructor.
     *
     * Allows derived classes to be destructed.
     */
    ~NonCopyable() = default;
};

} // namespace e2d

#endif //E2D_CORE_NONCOPYABLE_HPP
