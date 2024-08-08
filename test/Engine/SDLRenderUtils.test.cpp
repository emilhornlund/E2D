/**
 * @file SDLRenderUtils.test.cpp
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

#include <E2D/Engine/SDLRenderUtils.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("toSDLRect", "[SDLRenderUtils]")
{
    SECTION("Converts positive rectangle correctly")
    {
        const e2d::Rect<float> rect({10.5f, 20.5f}, {30.5f, 40.5f});
        const SDL_Rect         sdlRect = e2d::internal::toSDLRect(rect);
        REQUIRE(sdlRect.x == 10);
        REQUIRE(sdlRect.y == 20);
        REQUIRE(sdlRect.w == 30);
        REQUIRE(sdlRect.h == 40);
    }

    SECTION("Converts negative rectangle correctly")
    {
        const e2d::Rect<float> rect({-10.5f, -20.5f}, {-30.5f, -40.5f});
        const SDL_Rect         sdlRect = e2d::internal::toSDLRect(rect);
        REQUIRE(sdlRect.x == -10);
        REQUIRE(sdlRect.y == -20);
        REQUIRE(sdlRect.w == -30);
        REQUIRE(sdlRect.h == -40);
    }
}

TEST_CASE("calculateSDLDestinationRect", "[SDLRenderUtils]")
{
    SECTION("Standard positive scaling")
    {
        const e2d::IntRect  textureRect{{0, 0}, {50, 50}};
        const e2d::Vector2f position{100, 100};
        const e2d::Vector2f origin{25, 25};
        const e2d::Vector2f scale{2, 2};

        const SDL_Rect result = e2d::internal::calculateSDLDestinationRect(textureRect, position, origin, scale);
        REQUIRE(result.x == 50);
        REQUIRE(result.y == 50);
        REQUIRE(result.w == 100);
        REQUIRE(result.h == 100);
    }

    SECTION("Negative scaling")
    {
        const e2d::IntRect  textureRect{{0, 0}, {50, 50}};
        const e2d::Vector2f position{100, 100};
        const e2d::Vector2f origin{25, 25};
        const e2d::Vector2f scale{-2, -2}; // Negative scaling

        const SDL_Rect result = e2d::internal::calculateSDLDestinationRect(textureRect, position, origin, scale);

        // When scaled negatively, the position should adjust for the flipped width and height.
        REQUIRE(result.x == 50);  // 100 - 25*(-2) - 100
        REQUIRE(result.y == 50);  // 100 - 25*(-2) - 100
        REQUIRE(result.w == 100); // 50 * 2
        REQUIRE(result.h == 100); // 50 * 2
    }
}

TEST_CASE("calculateSDLRotationPoint", "[SDLRenderUtils]")
{
    SECTION("Standard rotation point")
    {
        const e2d::Vector2i size{100, 100};
        const e2d::Vector2f origin{25, 25};
        const e2d::Vector2f scale{1, 1};

        const SDL_Point point = e2d::internal::calculateSDLRotationPoint(size, origin, scale);
        REQUIRE(point.x == 25);
        REQUIRE(point.y == 25);
    }

    SECTION("Scaled rotation point")
    {
        const e2d::Vector2i size{200, 200}; // Size after scaling
        const e2d::Vector2f origin{25, 25}; // Original origin
        const e2d::Vector2f scale{2, 2};    // Scaling factor

        const SDL_Point point = e2d::internal::calculateSDLRotationPoint(size, origin, scale);

        // The rotation point should scale with the texture.
        REQUIRE(point.x == 50); // 25 * 2
        REQUIRE(point.y == 50); // 25 * 2
    }
}

TEST_CASE("toSDLRendererFlip", "[SDLRenderUtils]")
{
    SECTION("No flip")
    {
        const e2d::Vector2f    scale{1, 1};
        const SDL_RendererFlip flip = e2d::internal::toSDLRendererFlip(scale);
        REQUIRE(flip == SDL_FLIP_NONE);
    }

    SECTION("Horizontal flip")
    {
        const e2d::Vector2f    scale{-1, 1};
        const SDL_RendererFlip flip = e2d::internal::toSDLRendererFlip(scale);
        REQUIRE(flip == SDL_FLIP_HORIZONTAL);
    }

    SECTION("Vertical flip")
    {
        const e2d::Vector2f    scale{1, -1};
        const SDL_RendererFlip flip = e2d::internal::toSDLRendererFlip(scale);
        REQUIRE(flip == SDL_FLIP_VERTICAL);
    }

    SECTION("Horizontal and Vertical flip")
    {
        const e2d::Vector2f    scale{-1, -1};
        const SDL_RendererFlip flip = e2d::internal::toSDLRendererFlip(scale);
        REQUIRE(flip == (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
    }
}
