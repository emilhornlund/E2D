/**
 * @file RendererContext.test.cpp
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

#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/RendererContext.hpp>
#include <E2D/Engine/Window.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("RendererContext Initialization and Destruction", "[RendererContext]")
{
    SECTION("Initialize RendererContext")
    {
        auto& rendererContext = e2d::internal::RendererContext::getInstance();

        REQUIRE_FALSE(rendererContext.isInitialized());
        REQUIRE_FALSE(rendererContext.getWindow().isCreated());
        REQUIRE_FALSE(rendererContext.getRenderer().isCreated());

        rendererContext.initialize();

        REQUIRE(rendererContext.isInitialized());
        REQUIRE(rendererContext.getWindow().isCreated());
        REQUIRE(rendererContext.getRenderer().isCreated());
    }

    SECTION("Destroy RendererContext")
    {
        auto& rendererContext = e2d::internal::RendererContext::getInstance();

        rendererContext.initialize();

        REQUIRE(rendererContext.isInitialized());
        REQUIRE(rendererContext.getWindow().isCreated());
        REQUIRE(rendererContext.getRenderer().isCreated());

        rendererContext.destroy();

        REQUIRE_FALSE(rendererContext.isInitialized());
        REQUIRE_FALSE(rendererContext.getWindow().isCreated());
        REQUIRE_FALSE(rendererContext.getRenderer().isCreated());
    }
}
