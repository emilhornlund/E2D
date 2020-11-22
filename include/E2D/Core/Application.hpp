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

#ifndef E2D_CORE_APPLICATION_HPP
#define E2D_CORE_APPLICATION_HPP

#include <E2D/Core/Export.hpp>

/**
 * @brief Engine2D
 */
namespace e2d {

    /**
     * @brief Main application
     */
    class E2D_CORE_API Application {
    public:
        /**
         * @brief Default constructor
         */
        Application();

        /**
         * @brief Default destructor
         */
        virtual ~Application() = 0;

        /**
         * @brief Whether the application is running or not
         *
         * @return True if the application is running, false otherwise
         */
        bool isRunning() const;

        /**
         * @brief Starts the application game loop
         *
         * @return Exitcode after finished run
         */
        int run();

        /**
         * @brief Quits the application
         *
         * @param exitCode Exitcode that should be returned
         */
        void quit(int exitCode = 0);

    private:
        /// Code used when returning from application running state
        int m_exitCode;

        /// Whether the application is running or not
        bool m_running;

    }; // class Application

} // namespace e2d

#endif //E2D_CORE_APPLICATION_HPP
