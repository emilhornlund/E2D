/**
 * Texture.hpp
 * ResourceRegistry.hpp
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

#ifndef E2D_ENGINE_TEXTURE_HPP
#define E2D_ENGINE_TEXTURE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>
#include <E2D/Core/Vector2.hpp>

#include <E2D/Engine/Resource.hpp>

#include <memory>
#include <string>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Renderer; // Forward declaration of Renderer

namespace internal
{
class TextureImpl; // Forward declaration of TextureImpl
}

/**
 * @class Texture
 * @brief Manages texture resources.
 *
 * The Texture class encapsulates the functionality for loading and handling texture resources.
 * It abstracts the underlying implementation to provide an easy-to-use interface for textures.
 */
class E2D_ENGINE_API Texture final : public Resource
{
public:
    /**
     * @brief Default constructor for Texture.
     *
     * Constructs a Texture object.
     */
    Texture();

    /**
     * @brief Destructor for Texture.
     *
     * Destroys the Texture object, releasing its resources.
     */
    ~Texture() final;

    /**
     * @brief Loads a texture from a file.
     *
     * @param filepath Path to the texture filepath.
     * @return True if the texture is loaded successfully, false otherwise.
     */
    bool loadFromFile(const std::string& filepath) final;

    /**
     * @brief Loads the texture from memory.
     *
     * @param data Pointer to the memory block containing the texture data.
     * @param size Size of the memory block in bytes.
     * @return true if the texture is successfully loaded from memory, false otherwise.
     */
    bool loadFromMemory(const void* data, std::size_t size) final;

    /**
     * @brief Checks if the texture is loaded and valid.
     *
     * @return True if the texture is loaded, false otherwise.
     */
    bool isLoaded() const;

    /**
     * @brief Destroys the texture, freeing associated resources.
     */
    void destroy();

    /**
     * @brief Retrieves the size of the texture.
     *
     * This method returns the dimensions of the texture as a Vector2i,
     * where x represents the width and y represents the height of the texture.
     * If the texture is not loaded, this method returns a vector with zero values.
     *
     * @return const Vector2i& Reference to a Vector2i object representing the texture's size.
     */
    const Vector2i& getSize() const;

    /**
     * @brief Retrieves a handle to the native texture object.
     *
     * This function is used internally to link the texture with rendering operations.
     *
     * @return A pointer to the native texture handle.
     */
    void* getNativeTextureHandle() const;

private:
    std::unique_ptr<internal::TextureImpl> m_textureImpl; //!< Pointer to the texture implementation.

}; // class Texture

} // namespace e2d

#endif //E2D_ENGINE_TEXTURE_HPP
