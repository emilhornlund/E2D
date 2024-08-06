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

#ifndef E2D_CORE_SYSTEM_HPP
#define E2D_CORE_SYSTEM_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class e2d::System
 * @brief Manages the initialization and shutdown of the engine's core subsystems.
 *
 * The System class is responsible for setting up and tearing down essential components required for the engine's operation.
 * It provides a unified interface to ensure that these components are correctly prepared before the engine starts and
 * properly released when the engine shuts down.
 */
class E2D_CORE_API System final : NonCopyable
{
public:
    /**
     * @brief Default constructor for the System class.
     *
     * Constructs an instance of the System class.
     */
    System();

    /**
     * @brief Default destructor for the System class.
     *
     * Destroys the instance of the System class.
     */
    ~System();

    /**
     * @brief Initializes the engine's core subsystems.
     *
     * Ensures that all necessary components and subsystems for the engine are properly initialized.
     * This method must be called before using any engine functionality.
     *
     * @return bool Returns true if initialization is successful, false otherwise.
     */
    static bool initialize();

    /**
     * @brief Shuts down the engine's core subsystems.
     *
     * Properly releases resources and performs clean-up of the components initialized by the engine.
     * This method should be called during the engine's shutdown process.
     */
    static void shutdown();

}; // class System

} // namespace e2d

#endif //E2D_CORE_SYSTEM_HPP
