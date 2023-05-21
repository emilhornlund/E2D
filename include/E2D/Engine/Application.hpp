/**
 * Application.hpp
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

#ifndef E2D_ENGINE_APPLICATION_HPP
#define E2D_ENGINE_APPLICATION_HPP

#include <E2D/Engine/Export.hpp>

#include <string>

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief Namespace for E2D
 */
namespace e2d {

    /**
     * @brief Represents the application class.
     */
    class E2D_ENGINE_API Application {
    public:
        /**
         * @brief Constructs an Application object.
         *
         * @param windowTitle The windowTitle of the window
         */
        explicit Application(std::string windowTitle);

        /**
         * @brief Virtual destructor for Application.
         */
        virtual ~Application() = 0;

        /**
         * @brief Runs the application.
         *
         * @return The exit code of the application.
         */
        int run();

        /**
         * @brief Quits the application.
         *
         * @param exitCode The exit code of the application (default is 0).
         */
        void quit(int exitCode = 0);

    private:
        /// The exit code of the application.
        int m_exitCode;

        /// Flag indicating whether the application is running.
        bool m_running;

        /// The title of the window.
        const std::string m_windowTitle;

        /// Pointer to the SDL window.
        SDL_Window* m_window;

        /// Pointer to the SDL renderer.
        SDL_Renderer* m_renderer;

        /**
         * @brief Initializes the SDL library and creates the window and renderer.
         *
         * @return True if initialization is successful, false otherwise.
         */
        bool initSDL();

        /**
         * @brief Closes the SDL library and destroys the window and renderer.
         */
        void closeSDL();

        /**
         * @brief Handles SDL events such as window close event.
         */
        void handleEvents();

        /**
         * @brief Renders the application content.
         */
        void render();

    }; //Application class

} //e2d namespace

#endif //E2D_ENGINE_APPLICATION_HPP
