/**
 * @file SceneManager.test.cpp
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

#include "derived/TestScene.hpp"

#include <E2D/Engine/SceneManager.hpp>

#include <catch2/catch_test_macros.hpp>
TEST_CASE("SceneManager Tests", "[SceneManager]")
{
    e2d::SceneManager sceneManager;

    SECTION("Pushing and popping scenes")
    {
        REQUIRE(sceneManager.isEmpty());

        const auto& scene1 = sceneManager.pushScene<TestScene>("TestScene1");

        REQUIRE_FALSE(sceneManager.isEmpty());
        REQUIRE(sceneManager.getActiveScene()->getIdentifier() == scene1.getIdentifier());

        const auto& scene2 = sceneManager.pushScene<TestScene>("TestScene2");
        REQUIRE_FALSE(sceneManager.isEmpty());
        REQUIRE(sceneManager.getActiveScene()->getIdentifier() == scene2.getIdentifier());

        sceneManager.popScene();

        REQUIRE_FALSE(sceneManager.isEmpty());
        REQUIRE(sceneManager.getActiveScene()->getIdentifier() == scene1.getIdentifier());

        sceneManager.popScene();
        REQUIRE(sceneManager.isEmpty());
    }

    SECTION("Get active scene when no scenes are loaded")
    {
        REQUIRE(sceneManager.isEmpty());

        REQUIRE_THROWS_AS(sceneManager.getActiveScene(), std::runtime_error);
    }

    SECTION("Popping scenes when no scenes are loaded")
    {
        REQUIRE(sceneManager.isEmpty());

        REQUIRE_THROWS_AS(sceneManager.popScene(), std::runtime_error);
    }
}
