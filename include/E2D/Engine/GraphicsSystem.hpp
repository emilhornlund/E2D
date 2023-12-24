/**
* GraphicsSystem.hpp
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

#ifndef E2D_ENGINE_GRAPHICS_SYSTEM_HPP
#define E2D_ENGINE_GRAPHICS_SYSTEM_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/System.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class GraphicsSystem
 * @brief Class responsible for managing graphics in the E2D Engine.
 *
 * GraphicsSystem is a concrete implementation of the System class, specialized in handling graphics-related tasks.
 */
class E2D_ENGINE_API GraphicsSystem final : public System
{
public:
    /**
     * @brief Destructor for GraphicsSystem.
     *
     * Destroys the GraphicsSystem object, releasing its resources.
     */
    ~GraphicsSystem() final = default;

    /**
     * @brief Initializes the graphics system.
     *
     * Implements the System's initialize method to set up graphics-related components.
     *
     * @return bool Returns true if the graphics system is successfully initialized, false otherwise.
     */
    bool initialize() final;

    /**
     * @brief Shuts down the graphics system.
     *
     * Implements the System's shutdown method to clean up graphics-related components.
     */
    void shutdown() final;

}; // class GraphicsSystem

} // namespace e2d

#endif //E2D_ENGINE_GRAPHICS_SYSTEM_HPP
