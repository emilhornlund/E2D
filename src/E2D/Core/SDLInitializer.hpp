/**
 * SDLInitializer.hpp
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

#ifndef E2D_CORE_SDL_INITIALIZER_HPP
#define E2D_CORE_SDL_INITIALIZER_HPP

namespace e2d::internal
{

/**
 * @class SDLInitializer
 * @brief High-level wrapper for initializing and shutting down SDL subsystems.
 *
 * SDLInitializer provides static methods to initialize and shut down all required SDL subsystems.
 * This internal class encapsulates the details of starting and stopping SDL, SDL_image, and SDL_ttf,
 * ensuring that these subsystems are properly set up and torn down in a controlled manner.
 */
class SDLInitializer
{
public:
    /**
     * @brief Constructs a new SDLInitializer object.
     *
     * Initializes a new instance of the SDLInitializer class.
     */
    SDLInitializer() = default;

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~SDLInitializer() = default;

    /**
     * @brief Initializes the SDL subsystems.
     *
     * This method initializes the SDL library and its related subsystems (SDL_image, SDL_ttf).
     * It is responsible for setting up the video, image, and text rendering systems used by the engine.
     *
     * @return Returns true if all subsystems are successfully initialized, false otherwise.
     *         On failure, detailed error messages are logged to standard error output.
     */
    static bool initialize();

    /**
     * @brief Shuts down the SDL subsystems.
     *
     * Properly shuts down and cleans up the resources used by SDL, SDL_image, and SDL_ttf.
     * This method is responsible for ensuring that all SDL-related subsystems are closed cleanly.
     */
    static void shutdown();

}; // class SDLInitializer

} // namespace e2d::internal

#endif //E2D_CORE_SDL_INITIALIZER_HPP
