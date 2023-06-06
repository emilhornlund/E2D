/**
 * Timer.cpp
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

#include <E2D/Core/Timer.hpp>

// NOLINTBEGIN
#include <cstring> //unused, but must be included before SDL on macOS (bug?)
// NOLINTEND

#include <SDL.h>

void e2d::Timer::start()
{
    this->m_started     = true;
    this->m_paused      = false;
    this->m_startTicks  = SDL_GetTicks();
    this->m_pausedTicks = 0;
}

void e2d::Timer::stop()
{
    this->m_started     = false;
    this->m_paused      = false;
    this->m_startTicks  = 0;
    this->m_pausedTicks = 0;
}

void e2d::Timer::pause()
{
    if (this->m_started && !this->m_paused)
    {
        this->m_paused      = true;
        this->m_pausedTicks = SDL_GetTicks() - this->m_startTicks;
        this->m_startTicks  = 0;
    }
}

void e2d::Timer::resume()
{
    if (this->m_started && this->m_paused)
    {
        this->m_paused      = false;
        this->m_startTicks  = SDL_GetTicks() - this->m_pausedTicks;
        this->m_pausedTicks = 0;
    }
}

std::uint32_t e2d::Timer::getElapsedTimeAsMilliseconds() const
{
    std::uint32_t elapsedTicks = 0;
    if (this->m_started)
    {
        if (this->m_paused)
        {
            elapsedTicks = this->m_pausedTicks;
        }
        else
        {
            elapsedTicks = SDL_GetTicks() - this->m_startTicks;
        }
    }
    return elapsedTicks;
}

[[maybe_unused]] double e2d::Timer::getElapsedTimeAsSeconds() const
{
    const std::uint32_t elapsedTicksAsMilliseconds = this->getElapsedTimeAsMilliseconds();
    return static_cast<double>(elapsedTicksAsMilliseconds) / 1000.0;
}

bool e2d::Timer::isStarted() const
{
    return this->m_started;
}

bool e2d::Timer::isPaused() const
{
    return this->m_paused && this->m_started;
}
