/**
 * E2D
 * Copyright (C) 2020 (emil.hornlund@me.com)
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

#ifndef E2D_CORE_WINDOW_HPP
#define E2D_CORE_WINDOW_HPP

#include <E2D/Core/Export.hpp>
#include <E2D/System/Vector2.hpp>

#include <string>

struct SDL_Window;

/**
 * @brief Engine2D
 */
namespace e2d {

    /**
     * @brief Window
     */
    class E2D_CORE_API Window final {
    public:
        /**
         * @brief Default constructor
         */
        Window();

        /**
         * @brief Default destructor
         */
        ~Window();

        /**
         * @brief
         *
         * @param title
         * @param size
         */
        void open(const std::string &title, const Vector2<unsigned int> &size);

        /**
         * @brief
         */
        void close();

    private:
        /// The underlying sdl window
        SDL_Window *m_window;

    }; // class Window

} // namespace e2d

#endif //E2D_CORE_WINDOW_HPP
