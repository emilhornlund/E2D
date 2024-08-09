/**
 * @file GraphicsSystem.cpp
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

#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/RendererContext.hpp>

#include <SDL.h>
#include <SDL_image.h>

e2d::GraphicsSystem::GraphicsSystem()
{
    log::debug("Constructing GraphicsSystem");
}

e2d::GraphicsSystem::~GraphicsSystem()
{
    log::debug("Destructing GraphicsSystem");
}

bool e2d::GraphicsSystem::initialize()
{
    log::debug("Initializing SDL video subsystem");
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        log::error("Failed to initialize SDL video subsystem: {}", SDL_GetError());
        return false;
    }

    log::debug("Initializing SDL image subsystem");
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        log::error("Failed to initialize SDL image system: {}", SDL_GetError());
        return false;
    }

    log::debug("Initializing renderer context");
    if (!internal::RendererContext::getInstance().initialize())
    {
        log::error("Failed to initialize renderer context");
        return false;
    }

    return true;
}

void e2d::GraphicsSystem::shutdown()
{
    log::debug("Destroying renderer context");
    internal::RendererContext::getInstance().destroy();

    log::debug("Shutting down SDL image system");
    IMG_Quit();

    log::debug("Shutting down SDL video subsystem");
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
