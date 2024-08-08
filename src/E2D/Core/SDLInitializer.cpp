/**
 * @file SDLInitializer.cpp
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

#include <E2D/Core/Logger.hpp>
#include <E2D/Core/SDLInitializer.hpp>

// NOLINTBEGIN
#include <cstring> //unused, but must be included before SDL on macOS (bug?)
// NOLINTEND

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool e2d::internal::SDLInitializer::initialize()
{
    log::debug("Initializing SDL core systems");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        log::error("Failed to initialize SDL core systems: {}", SDL_GetError());
        return false;
    }

    log::debug("Initializing SDL image system");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        log::error("Failed to initialize SDL image system: {}", SDL_GetError());
        return false;
    }

    log::debug("Initializing SDL text rendering system");
    if (TTF_Init() != 0)
    {
        log::error("Failed to initialize SDL text rendering system: {}", SDL_GetError());
        return false;
    }
    return true;
}

void e2d::internal::SDLInitializer::shutdown()
{
    log::debug("Shutting down SDL text rendering system");
    TTF_Quit();

    log::debug("Shutting down SDL image system");
    IMG_Quit();

    log::debug("Shutting down SDL core systems");
    SDL_Quit();
}
