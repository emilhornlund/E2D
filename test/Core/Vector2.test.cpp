/**
 * Vector2.test.cpp
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

#include <E2D/Core/Vector2.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector2 Tests", "[Vector2]")
{
    SECTION("Default Constructor")
    {
        const e2d::Vector2f vec;
        REQUIRE(vec.x == 0.0f);
        REQUIRE(vec.y == 0.0f);
    }

    SECTION("Parameterized Constructor")
    {
        const e2d::Vector2i vec(5, -3);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == -3);
    }

    SECTION("Copy Constructor with Same Type")
    {
        const e2d::Vector2f vec1(3.0f, 4.0f);
        const e2d::Vector2f vec2 = vec1;
        REQUIRE(vec2.x == 3.0f);
        REQUIRE(vec2.y == 4.0f);
    }

    SECTION("Copy Constructor with Different Type")
    {
        const e2d::Vector2i vec1(3, 4);
        const e2d::Vector2f vec2(vec1);
        REQUIRE(vec2.x == 3.0f);
        REQUIRE(vec2.y == 4.0f);
    }

    SECTION("Unary Minus Operator")
    {
        const e2d::Vector2i vec(1, -2);
        auto                negVec = -vec;
        REQUIRE(negVec.x == -1);
        REQUIRE(negVec.y == 2);
    }

    SECTION("Addition Assignment Operator")
    {
        e2d::Vector2f vec(1.5f, 2.5f);
        vec += e2d::Vector2f(2.0f, 3.5f);
        REQUIRE(vec.x == 3.5f);
        REQUIRE(vec.y == 6.0f);
    }

    SECTION("Subtraction Assignment Operator")
    {
        e2d::Vector2f vec(10.0f, 5.0f);
        vec -= e2d::Vector2f(3.0f, 2.0f);
        REQUIRE(vec.x == 7.0f);
        REQUIRE(vec.y == 3.0f);
    }

    SECTION("Addition Operator")
    {
        auto vec = e2d::Vector2f(1.0f, 2.0f) + e2d::Vector2f(3.0f, 4.0f);
        REQUIRE(vec.x == 4.0f);
        REQUIRE(vec.y == 6.0f);
    }

    SECTION("Subtraction Operator")
    {
        auto vec = e2d::Vector2f(5.0f, 5.0f) - e2d::Vector2f(2.0f, 3.0f);
        REQUIRE(vec.x == 3.0f);
        REQUIRE(vec.y == 2.0f);
    }

    SECTION("Multiplication Operator with Scalar")
    {
        auto vec = e2d::Vector2f(1.0f, 2.0f) * 2.0f;
        REQUIRE(vec.x == 2.0f);
        REQUIRE(vec.y == 4.0f);
    }

    SECTION("Multiplication Assignment Operator with Scalar")
    {
        e2d::Vector2f vec(1.0f, 2.0f);
        vec *= 3.0f;
        REQUIRE(vec.x == 3.0f);
        REQUIRE(vec.y == 6.0f);
    }

    SECTION("Division Operator with Scalar")
    {
        auto vec = e2d::Vector2f(4.0f, 8.0f) / 2.0f;
        REQUIRE(vec.x == 2.0f);
        REQUIRE(vec.y == 4.0f);
    }

    SECTION("Division Assignment Operator with Scalar")
    {
        e2d::Vector2f vec(9.0f, 18.0f);
        vec /= 3.0f;
        REQUIRE(vec.x == 3.0f);
        REQUIRE(vec.y == 6.0f);
    }

    SECTION("Equality Operator")
    {
        REQUIRE(e2d::Vector2i(1, 2) == e2d::Vector2i(1, 2));
        REQUIRE_FALSE(e2d::Vector2i(1, 2) == e2d::Vector2i(2, 1));
    }

    SECTION("Inequality Operator")
    {
        REQUIRE(e2d::Vector2i(1, 2) != e2d::Vector2i(2, 1));
        REQUIRE_FALSE(e2d::Vector2i(1, 2) != e2d::Vector2i(1, 2));
    }
}
