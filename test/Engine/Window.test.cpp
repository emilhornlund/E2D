/**
 * Window.test.cpp
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

#include <E2D/Core/System.hpp>

#include <E2D/Engine/Window.hpp>

#include <catch2/catch_test_macros.hpp>

class WindowTest
{
public:
    WindowTest()
    {
        // Setup (runs before each SECTION)
        e2d::System::initialize();
    }

    ~WindowTest()
    {
        // Teardown (runs after each SECTION)
        e2d::System::shutdown();
    }
};

TEST_CASE_METHOD(WindowTest, "Window Creation and Destruction", "[Window]")
{
    e2d::Window window;

    SECTION("Create Window")
    {
        REQUIRE(window.create("Test Window", 800, 600) == true);
        REQUIRE(window.isCreated() == true);
    }

    SECTION("Destroy Window")
    {
        REQUIRE(window.create("Test Window", 800, 600) == true);
        window.destroy();
        REQUIRE(window.isCreated() == false);
    }
}
