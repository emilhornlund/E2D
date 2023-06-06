/**
 * Timer.hpp
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

#ifndef E2D_CORE_TIMER_HPP
#define E2D_CORE_TIMER_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <cstdint>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class Timer
 * @brief A class that provides functionality for a timer that can be paused, stopped, or resumed.
 */
class E2D_CORE_API Timer final : NonCopyable
{
public:
    /**
     * @brief Starts or resumes the timer.
     */
    void start();

    /**
     * @brief Stops the timer and resets its state.
     */
    void stop();

    /**
     * @brief Pauses the timer.
     */
    void pause();

    /**
     * @brief Resumes the timer from the paused state.
     */
    void resume();

    /**
     * @brief Returns the elapsed time in ticks since the timer was started or resumed.
     *
     * @return The elapsed time in ticks.
     */
    std::uint32_t getElapsedTicks() const;

    /**
     * @brief Checks if the timer is currently started.
     *
     * @return True if the timer is started, false otherwise.
     */
    bool isStarted() const;

    /**
     * @brief Checks if the timer is currently paused.
     *
     * @return True if the timer is paused, false otherwise.
     */
    bool isPaused() const;

private:
    std::uint32_t m_startTicks  = 0;     ///< The ticks at the start of the timer.
    std::uint32_t m_pausedTicks = 0;     ///< The ticks when the timer was paused.
    bool          m_paused      = false; ///< Flag indicating if the timer is paused.
    bool          m_started     = false; ///< Flag indicating if the timer is started.
};

} // namespace e2d

#endif //E2D_CORE_TIMER_HPP
