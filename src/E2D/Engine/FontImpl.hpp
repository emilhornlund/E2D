/**
 * FontImpl.hpp
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

#ifndef E2D_ENGINE_FONTIMPL_HPP
#define E2D_ENGINE_FONTIMPL_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <cstdint>

#include <string>
#include <vector>

using TTF_Font = struct _TTF_Font; // NOLINT(bugprone-reserved-identifier)

/**
 * @brief Namespace for E2D internal
 */
namespace e2d::internal
{

/**
 * @class FontImpl
 * @brief Internal implementation of the Font class, responsible for loading and managing font data.
 */
class E2D_ENGINE_API FontImpl final : NonCopyable
{
public:
    /**
     * @brief Default constructor for FontImpl.
     *
     * Constructs a FontImpl object.
     */
    FontImpl();

    /**
     * @brief Destructor for FontImpl.
     *
     * Destroys the FontImpl object, releasing its resources.
     */
    ~FontImpl();

    /**
     * @brief Loads a font from a file.
     *
     * @param filepath Path to the font.
     * @return True if the font is loaded successfully, false otherwise.
     */
    bool loadFromFile(const std::string& filepath);

    /**
     * @brief Loads the font from memory.
     *
     * This method loads the font from a block of memory.
     *
     * @param data Pointer to the memory block containing the font data.
     * @param size Size of the memory block in bytes.
     * @return true if the font is loaded successfully, false otherwise.
     */
    bool loadFromMemory(const void* data, std::size_t size);

    /**
     * @brief Retrieves the native TTF font object.
     *
     * @param fontSize The size of the font to be retrieved.
     * @return Pointer to the underlying TTF_Font object.
     */
    TTF_Font* getFont(unsigned int fontSize) const;

private:
    std::vector<uint8_t> m_fontData; //!< Buffer containing the font data loaded from file or memory.

}; // FontImpl class

} // namespace e2d::internal

#endif //E2D_ENGINE_FONTIMPL_HPP
