/**
 * @file CoreSystem.cpp
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

#include <E2D/Engine/CoreSystem.hpp>

#include <SDL.h>

e2d::CoreSystem::CoreSystem()
{
    log::debug("Constructing CoreSystem");
}

e2d::CoreSystem::~CoreSystem()
{
    log::debug("Destructing CoreSystem");
}

bool e2d::CoreSystem::initialize()
{
    log::debug("Initializing SDL timer subsystem");
    if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0)
    {
        log::error("Failed to initialize SDL timer subsystem: {}", SDL_GetError());
        return false;
    }

    log::debug("Initializing SDL events subsystem");
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
    {
        log::error("Failed to initialize SDL events subsystem: {}", SDL_GetError());
        return false;
    }

    return true;
}

void e2d::CoreSystem::shutdown()
{
    log::debug("Shutting down SDL timer subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    log::debug("Shutting down SDL events subsystem");
    SDL_QuitSubSystem(SDL_INIT_TIMER);
}
