/**
 * @file Rect.test.cpp
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

#include <E2D/Core/Rect.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Rect Tests", "[Rect]")
{
    SECTION("Default Constructor")
    {
        const e2d::Rect<float> rect;
        REQUIRE(rect.left == 0.0f);
        REQUIRE(rect.top == 0.0f);
        REQUIRE(rect.width == 0.0f);
        REQUIRE(rect.height == 0.0f);
    }

    SECTION("Constructor with Negative Width and Height")
    {
        const e2d::Rect<int> rect({10, 20}, {-30, -40});
        REQUIRE(rect.left == 10);
        REQUIRE(rect.top == 20);
        REQUIRE(rect.width == -30);
        REQUIRE(rect.height == -40);
    }

    SECTION("Parameterized Constructor")
    {
        const e2d::Rect<int> rect(e2d::Vector2i{10, 20}, e2d::Vector2i{30, 40});
        REQUIRE(rect.left == 10);
        REQUIRE(rect.top == 20);
        REQUIRE(rect.width == 30);
        REQUIRE(rect.height == 40);
    }

    SECTION("Copy Constructor with Different Type")
    {
        const e2d::Rect<int>   intRect({1, 2}, {3, 4});
        const e2d::Rect<float> floatRect(intRect);
        REQUIRE(floatRect.left == 1.0f);
        REQUIRE(floatRect.top == 2.0f);
        REQUIRE(floatRect.width == 3.0f);
        REQUIRE(floatRect.height == 4.0f);
    }

    SECTION("Contains Method - Point Inside")
    {
        const e2d::Rect<int> rect({0, 0}, {10, 10});
        REQUIRE(rect.contains(e2d::Vector2i{5, 5}));
        REQUIRE_FALSE(rect.contains(e2d::Vector2i{-1, -1}));
    }

    SECTION("Contains Method - Point Outside")
    {
        const e2d::Rect<int> rect({0, 0}, {10, 10});
        REQUIRE_FALSE(rect.contains(e2d::Vector2i{11, 11}));
        REQUIRE_FALSE(rect.contains(e2d::Vector2i{0, 11}));
        REQUIRE_FALSE(rect.contains(e2d::Vector2i{-1, 5}));
    }

    SECTION("Contains Method - Point On Boundary")
    {
        const e2d::Rect<int> rect({0, 0}, {10, 10});
        REQUIRE_FALSE(rect.contains(e2d::Vector2i{10, 10}));
        REQUIRE(rect.contains(e2d::Vector2i{0, 0}));
    }

    SECTION("Find Intersection Method")
    {
        const e2d::Rect<int> rect1({0, 0}, {10, 10});
        const e2d::Rect<int> rect2({5, 5}, {10, 10});
        auto                 intersection = rect1.findIntersection(rect2);
        REQUIRE(intersection.has_value());
        REQUIRE(intersection->left == 5);
        REQUIRE(intersection->top == 5);
        REQUIRE(intersection->width == 5);
        REQUIRE(intersection->height == 5);
    }

    SECTION("Find Intersection Method - No Intersection (Completely Separate)")
    {
        const e2d::Rect<int> rect1({0, 0}, {10, 10});
        const e2d::Rect<int> rect2({20, 20}, {10, 10});
        auto                 intersection = rect1.findIntersection(rect2);
        REQUIRE_FALSE(intersection.has_value());
    }

    SECTION("Find Intersection Method - Edge Touching")
    {
        const e2d::Rect<int> rect1({0, 0}, {10, 10});
        const e2d::Rect<int> rect2({10, 0}, {10, 10});
        auto                 intersection = rect1.findIntersection(rect2);
        REQUIRE_FALSE(intersection.has_value());
    }

    SECTION("Find Intersection Method - One Inside Another")
    {
        const e2d::Rect<int> rect1({0, 0}, {10, 10});
        const e2d::Rect<int> rect2({2, 2}, {5, 5});
        auto                 intersection = rect1.findIntersection(rect2);
        REQUIRE(intersection.has_value());
        REQUIRE(intersection->left == 2);
        REQUIRE(intersection->top == 2);
        REQUIRE(intersection->width == 5);
        REQUIRE(intersection->height == 5);
    }

    SECTION("GetPosition Method")
    {
        const e2d::Rect<int> rect({10, 20}, {30, 40});
        auto                 position = rect.getPosition();
        REQUIRE(position.x == 10);
        REQUIRE(position.y == 20);
    }

    SECTION("GetSize Method")
    {
        const e2d::Rect<int> rect({10, 20}, {30, 40});
        auto                 size = rect.getSize();
        REQUIRE(size.x == 30);
        REQUIRE(size.y == 40);
    }

    SECTION("GetCenter Method")
    {
        const e2d::Rect<int> rect({10, 20}, {30, 40});
        auto                 center = rect.getCenter();
        REQUIRE(center.x == 25);
        REQUIRE(center.y == 40);
    }

    SECTION("GetCenter Method - Negative Dimensions")
    {
        const e2d::Rect<int> rect({10, 20}, {-30, -40});
        const e2d::Vector2i  center = rect.getCenter();
        REQUIRE(center.x == -5);
        REQUIRE(center.y == 0);
    }

    SECTION("Equality Operator")
    {
        const e2d::Rect<int> rect1({10, 20}, {30, 40});
        const e2d::Rect<int> rect2({10, 20}, {30, 40});
        REQUIRE(rect1 == rect2);
    }

    SECTION("Inequality Operator")
    {
        const e2d::Rect<int> rect1({10, 20}, {30, 40});
        const e2d::Rect<int> rect2({20, 30}, {40, 50});
        REQUIRE(rect1 != rect2);
    }
}
