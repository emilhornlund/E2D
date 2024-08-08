/**
 * Font.hpp
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

#ifndef E2D_ENGINE_FONT_HPP
#define E2D_ENGINE_FONT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Resource.hpp>

#include <memory>

namespace e2d
{

namespace internal
{
class FontImpl; // Forward declaration of FontImpl
}

/**
 * @class Font
 * @brief Represents a font resource that can be used for rendering text.
 *
 * The Font class provides functionality to load and manage font resources.
 * It supports loading fonts from files and memory, and provides access to the
 * native font handle for rendering operations.
 */
class E2D_ENGINE_API Font final : public Resource
{
public:
    /**
     * @brief Constructs a new Font object.
     *
     * Initializes a new instance of the Font class.
     */
    Font();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Font() final;

    /**
     * @brief Loads a font from a file.
     *
     * This function loads the font from a specified file path.
     *
     * @param filepath Path to the font file.
     * @return True if the font is loaded successfully, false otherwise.
     */
    bool loadFromFile(const std::string& filepath) final;

    /**
     * @brief Loads the font from memory.
     *
     * This function loads the font from a block of memory.
     *
     * @param data Pointer to the memory block containing the font data.
     * @param size Size of the memory block in bytes.
     * @return True if the font is loaded successfully, false otherwise.
     */
    bool loadFromMemory(const void* data, std::size_t size) final;

    /**
     * @brief Retrieves a handle to the native font object.
     *
     * This function is used internally to link the font with rendering operations.
     *
     * @param fontSize The size of the font for which to retrieve the handle.
     * @return A pointer to the native font handle.
     */
    void* getNativeFontHandle(unsigned int fontSize) const;

private:
    std::unique_ptr<internal::FontImpl> m_fontImpl; //!< Pointer to the font implementation.

}; // Font class

} // namespace e2d

#endif //E2D_ENGINE_FONT_HPP
