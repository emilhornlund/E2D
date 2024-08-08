/**
 * @file TextureImpl.hpp
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

#ifndef E2D_ENGINE_TEXTURE_IMPL_HPP
#define E2D_ENGINE_TEXTURE_IMPL_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>
#include <E2D/Core/Vector2.hpp>

#include <cstddef>

struct SDL_Renderer; // Forward declaration of SDL_Renderer
struct SDL_Texture;  // Forward declaration of SDL_Texture

namespace e2d::internal
{

/**
 * @class TextureImpl
 * @ingroup engine
 * @brief @internal Internal implementation class for Texture.
 *
 * This class is responsible for the low-level details of texture management,
 * including loading and maintaining texture resources.
 */
class E2D_ENGINE_API TextureImpl final : NonCopyable
{
public:
    /**
     * @brief Constructs a new TextureImpl object.
     *
     * Initializes a new instance of the TextureImpl class.
     */
    TextureImpl();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~TextureImpl();

    /**
     * @brief Loads a texture using a specified renderer and file path.
     *
     * Loads a texture from the specified file using the provided SDL renderer.
     *
     * @param renderer Pointer to the SDL_Renderer object used for texture loading.
     * @param file Path to the texture file.
     * @return True if the texture is successfully loaded, false otherwise.
     */
    bool loadTexture(SDL_Renderer* renderer, const char* file);

    /**
     * @brief Loads the texture from memory.
     *
     * Loads the texture from a block of memory using the provided SDL renderer.
     *
     * @param renderer Pointer to the SDL renderer.
     * @param data Pointer to the memory block containing the texture data.
     * @param size Size of the memory block in bytes.
     * @return True if the texture is successfully loaded from memory, false otherwise.
     */
    bool loadFromMemory(SDL_Renderer* renderer, const void* data, std::size_t size);

    /**
     * @brief Checks if the texture is loaded and valid.
     *
     * Determines whether the texture is currently loaded and valid for use.
     *
     * @return True if the texture is loaded, false otherwise.
     */
    bool isLoaded() const;

    /**
     * @brief Destroys the texture, freeing associated resources.
     *
     * Frees the resources associated with the SDL texture.
     */
    void destroy();

    /**
     * @brief Retrieves the size of the internal SDL texture.
     *
     * Returns the dimensions of the underlying SDL texture. If the texture is not loaded,
     * this method returns a vector with zero values.
     *
     * @return Reference to a Vector2i object representing the texture's size.
     */
    const e2d::Vector2i& getSize() const;

    /**
     * @brief Retrieves the native SDL texture object.
     *
     * Provides access to the underlying SDL texture used for rendering.
     *
     * @return Pointer to the underlying SDL_Texture object.
     */
    SDL_Texture* getTexture() const;

private:
    SDL_Texture*  m_texture{nullptr}; //!< Pointer to the underlying SDL_Texture object.
    e2d::Vector2i m_textureSize;      //!< Stores the dimensions of the SDL_Texture object.

}; // class TextureImpl

} // namespace e2d::internal

#endif //E2D_ENGINE_TEXTURE_IMPL_HPP
