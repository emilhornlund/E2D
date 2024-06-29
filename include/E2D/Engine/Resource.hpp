/**
* Resource.hpp
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

#ifndef E2D_ENGINE_RESOURCE_HPP
#define E2D_ENGINE_RESOURCE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <string>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class Resource
 *
 * @brief Abstract base class for all resource types in the E2D engine.
 *
 * The Resource class provides a common interface for all resources managed by the engine.
 */
class E2D_ENGINE_API Resource : NonCopyable
{
public:
    /**
     * @brief Pure virtual destructor for Resource.
     */
    virtual ~Resource() = 0;

    /**
     * @brief Loads the resource from a file.
     *
     * This method must be implemented by all derived resource classes.
     *
     * @param filepath The path to the resource file.
     * @return True if the resource is loaded successfully, false otherwise.
     */
    virtual bool loadFromFile(const std::string& filepath) = 0;

}; // Resource class

inline Resource::~Resource() = default; // NOLINT(readability-redundant-inline-specifier)

} // namespace e2d

#endif //E2D_ENGINE_RESOURCE_HPP
