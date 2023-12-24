/**
* TextRenderingSystem.hpp
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

#ifndef E2D_ENGINE_TEXT_RENDERING_SYSTEM_HPP
#define E2D_ENGINE_TEXT_RENDERING_SYSTEM_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/System.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class TextRenderingSystem
 * @brief Class responsible for text rendering in the E2D Engine.
 *
 * TextRenderingSystem is a concrete implementation of the System class, specialized in handling text rendering tasks.
 */
class E2D_ENGINE_API TextRenderingSystem final : public System
{
public:
    /**
     * @brief Destructor for TextRenderingSystem.
     *
     * Destroys the TextRenderingSystem object, releasing its resources.
     */
    ~TextRenderingSystem() final = default;

    /**
     * @brief Initializes the text rendering system.
     *
     * Implements the System's initialize method to set up text rendering-related components.
     *
     * @return bool Returns true if the text rendering system is successfully initialized, false otherwise.
     */
    bool initialize() final;

    /**
     * @brief Shuts down the text rendering system.
     *
     * Implements the System's shutdown method to clean up text rendering-related components.
     */
    void shutdown() final;

}; // class TextRenderingSystem

} // namespace e2d

#endif //E2D_ENGINE_TEXT_RENDERING_SYSTEM_HPP
