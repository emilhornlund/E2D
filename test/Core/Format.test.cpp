/**
 * @file Format.test.cpp
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

#include <E2D/Core/Format.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Format Tests", "[Format]")
{
    SECTION("Basic formatting")
    {
        std::string result = e2d::format("Hello, {}!", "world");
        REQUIRE(result == "Hello, world!");
    }

    SECTION("Multiple placeholders")
    {
        std::string result = e2d::format("{} + {} = {}", 1, 1, 2);
        REQUIRE(result == "1 + 1 = 2");
    }

    SECTION("No placeholders")
    {
        std::string result = e2d::format("No placeholders");
        REQUIRE(result == "No placeholders");
    }

    SECTION("Extra arguments without placeholders")
    {
        std::string result = e2d::format("Extra args", "arg1", 2, 3.0);
        REQUIRE(result == "Extra args");
    }

    SECTION("Insufficient arguments")
    {
        REQUIRE_THROWS_AS(e2d::format("This is {} test", "a", "extra"), std::runtime_error);
    }

    SECTION("Different types")
    {
        std::string result = e2d::format("String: {}, Integer: {}, Float: {}", "test", 42, 3.14);
        REQUIRE(result == "String: test, Integer: 42, Float: 3.14");
    }

    SECTION("Empty string")
    {
        const std::string result = e2d::format("");
        REQUIRE(result.empty());
    }

    SECTION("Escape braces")
    {
        std::string result = e2d::format("Escaped braces {{}} not replaced");
        REQUIRE(result == "Escaped braces {} not replaced");
    }
}
