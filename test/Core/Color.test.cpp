/**
 * Color.test.cpp
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

#include <E2D/Core/Color.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Color Tests", "[Color]")
{
    SECTION("Default constructor creates opaque Black color")
    {
        const e2d::Color color;
        REQUIRE(color.r == 0);
        REQUIRE(color.g == 0);
        REQUIRE(color.b == 0);
        REQUIRE(color.a == 255);
    }

    SECTION("Constructor creates color with specified RGBA components")
    {
        const e2d::Color color(255, 128, 0, 200);
        REQUIRE(color.r == 255);
        REQUIRE(color.g == 128);
        REQUIRE(color.b == 0);
        REQUIRE(color.a == 200);
    }

    SECTION("Constructor creates color from 32-bit unsigned integer")
    {
        const e2d::Color color(0xFF00FF00); // Green color
        REQUIRE(color.r == 255);
        REQUIRE(color.g == 0);
        REQUIRE(color.b == 255);
        REQUIRE(color.a == 0);
    }

    SECTION("toInteger returns the color as a 32-bit unsigned integer")
    {
        const e2d::Color color(127, 127, 127, 127);
        REQUIRE(color.toInteger() == 0x7F7F7F7F);
    }

    SECTION("Colors can be compared for equality")
    {
        e2d::Color       color1(255, 0, 0, 255); // Red color
        const e2d::Color color2(255, 0, 0, 255); // Red color
        const e2d::Color color3(0, 255, 0, 255); // Green color

        REQUIRE(color1 == color2);
        REQUIRE(color1 != color3);
    }

    SECTION("Colors can be added together")
    {
        const e2d::Color color1(255, 0, 0, 255); // Red color
        const e2d::Color color2(0, 255, 0, 255); // Green color
        const e2d::Color result = color1 + color2;

        REQUIRE(result.r == 255);
        REQUIRE(result.g == 255);
        REQUIRE(result.b == 0);
        REQUIRE(result.a == 255);
    }

    SECTION("Colors can be subtracted")
    {
        const e2d::Color color1(255, 255, 255, 255); // White color
        const e2d::Color color2(0, 255, 0, 255);     // Green color
        const e2d::Color result = color1 - color2;

        REQUIRE(result.r == 255);
        REQUIRE(result.g == 0);
        REQUIRE(result.b == 255);
        REQUIRE(result.a == 0);
    }

    SECTION("Colors can be multiplied (modulated)")
    {
        const e2d::Color color1(255, 255, 0, 255); // Yellow color
        const e2d::Color color2(0, 255, 255, 255); // Cyan color
        const e2d::Color result = color1 * color2;

        REQUIRE(result.r == 0);
        REQUIRE(result.g == 255);
        REQUIRE(result.b == 0);
        REQUIRE(result.a == 255);
    }

    SECTION("Colors can be added and assigned")
    {
        e2d::Color       color1(255, 0, 0, 255); // Red color
        const e2d::Color color2(0, 255, 0, 255); // Green color
        color1 += color2;

        REQUIRE(color1.r == 255);
        REQUIRE(color1.g == 255);
        REQUIRE(color1.b == 0);
        REQUIRE(color1.a == 255);
    }

    SECTION("Colors can be subtracted and assigned")
    {
        e2d::Color       color1(255, 255, 255, 255); // White color
        const e2d::Color color2(0, 255, 0, 255);     // Green color
        color1 -= color2;

        REQUIRE(color1.r == 255);
        REQUIRE(color1.g == 0);
        REQUIRE(color1.b == 255);
        REQUIRE(color1.a == 0);
    }

    SECTION("Colors can be multiplied (modulated) and assigned")
    {
        e2d::Color       color1(255, 255, 0, 255); // Yellow color
        const e2d::Color color2(0, 255, 255, 255); // Cyan color
        color1 *= color2;

        REQUIRE(color1.r == 0);
        REQUIRE(color1.g == 255);
        REQUIRE(color1.b == 0);
        REQUIRE(color1.a == 255);
    }
}
