/**
 * Timer.test.cpp
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

#include <catch2/catch_test_macros.hpp>

#include <thread>

TEST_CASE("Timer starts and returns elapsed time", "[Timer]")
{
    e2d::Timer timer;

    timer.start();
    const std::uint32_t elapsedTicks = timer.getElapsedTicks();

    REQUIRE(elapsedTicks == 0);
}

TEST_CASE("Timer pauses and resumes correctly", "[Timer]")
{
    e2d::Timer timer;

    timer.start();
    const std::uint32_t elapsedTicksBeforePause = timer.getElapsedTicks();

    // Simulate the passage of time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.pause();

    // Simulate the passage of time while the timer is paused
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.resume();
    const std::uint32_t elapsedTicksAfterResume = timer.getElapsedTicks();

    REQUIRE(elapsedTicksBeforePause < elapsedTicksAfterResume);
}

TEST_CASE("Timer stops and resets correctly", "[Timer]")
{
    e2d::Timer timer;

    timer.start();

    // Simulate the passage of time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.stop();
    const std::uint32_t elapsedTicksAfterStop = timer.getElapsedTicks();

    REQUIRE(timer.isStarted() == false);
    REQUIRE(timer.isPaused() == false);
    REQUIRE(elapsedTicksAfterStop == 0);
}

TEST_CASE("Timer can be started, paused, and resumed multiple times", "[Timer]")
{
    e2d::Timer timer;

    timer.start();
    const std::uint32_t elapsedTicks1 = timer.getElapsedTicks();

    // Simulate the passage of time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.pause();
    const std::uint32_t elapsedTicksAfterPause1 = timer.getElapsedTicks();

    // Simulate the passage of time while the timer is paused
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    const std::uint32_t elapsedTicksAfterPause2 = timer.getElapsedTicks();

    timer.resume();
    const std::uint32_t elapsedTicksAfterResume1 = timer.getElapsedTicks();

    // Simulate the passage of time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.pause();
    const std::uint32_t elapsedTicksAfterPause3 = timer.getElapsedTicks();

    // Simulate the passage of time while the timer is paused
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    timer.resume();
    const std::uint32_t elapsedTicksAfterResume2 = timer.getElapsedTicks();

    REQUIRE(elapsedTicks1 < elapsedTicksAfterPause1);
    REQUIRE(elapsedTicksAfterPause1 == elapsedTicksAfterPause2);
    REQUIRE(elapsedTicksAfterResume1 < elapsedTicksAfterPause3);
    REQUIRE(elapsedTicksAfterPause3 <= elapsedTicksAfterResume2);
}
