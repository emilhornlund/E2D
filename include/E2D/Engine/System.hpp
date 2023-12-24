/**
* System.hpp
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

#ifndef E2D_ENGINE_SYSTEM_HPP
#define E2D_ENGINE_SYSTEM_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class System
 * @brief Abstract base class for different systems in E2D Engine.
 *
 * System serves as a base class for various systems like graphics, audio, etc., providing a common interface for initialization and shutdown.
 */
class E2D_ENGINE_API System : NonCopyable
{
public:
    /**
     * @brief Virtual destructor for the System class.
     */
    virtual ~System() = default;

    /**
     * @brief Initializes the system.
     *
     * Pure virtual function that must be implemented by derived classes to handle system-specific initialization.
     *
     * @return bool Returns true if initialization is successful, false otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Shuts down the system.
     *
     * Pure virtual function that must be implemented by derived classes to handle system-specific shutdown procedures.
     */
    virtual void shutdown() = 0;

}; // class System

} // namespace e2d

#endif //E2D_ENGINE_SYSTEM_HPP
