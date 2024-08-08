/**
 * @file Timer.hpp
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

#ifndef E2D_CORE_TIMER_HPP
#define E2D_CORE_TIMER_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <cstdint>

namespace e2d
{

/**
 * @class Timer
 * @ingroup core
 * @brief A class that provides functionality for a timer that can be paused, stopped, or resumed.
 *
 * The Timer class is designed to measure elapsed time in milliseconds or seconds. It provides methods
 * to start, stop, pause, and resume the timer. Additionally, it offers functionalities to check the timer's
 * current state and retrieve the elapsed time.
 */
class E2D_CORE_API Timer final : NonCopyable
{
public:
    /**
     * @brief Constructs a new Timer object.
     *
     * Initializes a new instance of the Timer class.
     */
    Timer();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Timer();

    /**
     * @brief Starts or resumes the timer.
     *
     * This method starts the timer if it is not already started or resumes it if it is paused.
     */
    void start();

    /**
     * @brief Stops the timer and resets its state.
     *
     * This method stops the timer and resets the elapsed time to zero.
     */
    void stop();

    /**
     * @brief Pauses the timer.
     *
     * This method pauses the timer, allowing it to be resumed later without resetting the elapsed time.
     */
    void pause();

    /**
     * @brief Resumes the timer from the paused state.
     *
     * This method resumes the timer from where it was paused.
     */
    void resume();

    /**
     * @brief Gets the elapsed time in milliseconds since the timer was started or resumed.
     *
     * Retrieves the total elapsed time in milliseconds. If the timer is paused, it returns the time until it was paused.
     *
     * @return The elapsed time in milliseconds.
     */
    std::uint32_t getElapsedTimeAsMilliseconds() const;

    /**
     * @brief Gets the elapsed time in seconds since the timer was started or resumed.
     *
     * Retrieves the total elapsed time in seconds. If the timer is paused, it returns the time until it was paused.
     *
     * @return The elapsed time in seconds.
     */
    [[maybe_unused]] double getElapsedTimeAsSeconds() const;

    /**
     * @brief Checks if the timer is currently started.
     *
     * Determines whether the timer has been started and is currently running or paused.
     *
     * @return True if the timer is started, false otherwise.
     */
    bool isStarted() const;

    /**
     * @brief Checks if the timer is currently paused.
     *
     * Determines whether the timer is currently paused.
     *
     * @return True if the timer is paused, false otherwise.
     */
    bool isPaused() const;

private:
    std::uint32_t m_startTicks  = 0;     //!< The ticks at the start of the timer.
    std::uint32_t m_pausedTicks = 0;     //!< The ticks when the timer was paused.
    bool          m_paused      = false; //!< Flag indicating if the timer is paused.
    bool          m_started     = false; //!< Flag indicating if the timer is started.

}; // Timer class

} // namespace e2d

#endif //E2D_CORE_TIMER_HPP
