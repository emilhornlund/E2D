/**
 * Application.cpp
 *
 * MIT License
 *
 * Copyright (c) 2023 Emil Hörnlund
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

#include <E2D/Core/Timer.hpp>

#include <E2D/Engine/Application.hpp>

#include <SDL.h>

#include <cmath>

#include <iostream>
#include <utility>

e2d::Application::Application(std::string windowTitle) :
m_windowTitle(std::move(windowTitle)),
m_backgroundColor(Color::Black)
{
}

e2d::Application::~Application() = default;

int e2d::Application::run()
{
    if (!this->initSDL())
    {
        return -1;
    }

    Timer        targetFrameTimer;
    double const targetFrameTime = 1.0 / 60.0;

    int    frames      = 0;
    double elapsedTime = 0.0;
    double remainder   = 0.0;

    this->m_running = true;
    while (this->m_running)
    {
        targetFrameTimer.start();
        double elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();

        this->handleEvents();
        // TODO: Update game objects with a fixed frame rate of 1/60

        while (elapsedFrameTimeAsSeconds < targetFrameTime - remainder)
        {
            elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();
        }

        remainder = elapsedFrameTimeAsSeconds - (targetFrameTime - remainder);
        if (remainder >= targetFrameTime)
        {
            remainder = 0.0;
        }

        this->render();
        frames++;

        elapsedTime += elapsedFrameTimeAsSeconds;
        if (elapsedTime >= 1.0)
        {
            int const fps = static_cast<int>(std::round(frames / elapsedTime));
            std::cout << "fps: " << fps << '\n';
            frames      = 0;
            elapsedTime = 0.0;
        }
    }

    this->closeSDL();

    return this->m_exitCode;
}

[[maybe_unused]] bool e2d::Application::isRunning() const
{
    return this->m_running;
}

void e2d::Application::quit(int exitCode)
{
    this->m_exitCode = exitCode;
    this->m_running  = false;
}

bool e2d::Application::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    this->m_window = SDL_CreateWindow(this->m_windowTitle.c_str(),
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      800,
                                      600,
                                      SDL_WINDOW_SHOWN);
    if (this->m_window == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->m_renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void e2d::Application::closeSDL()
{
    if (this->m_renderer != nullptr)
    {
        SDL_DestroyRenderer(this->m_renderer);
        this->m_renderer = nullptr;
    }

    if (this->m_window != nullptr)
    {
        SDL_DestroyWindow(this->m_window);
        this->m_window = nullptr;
    }

    SDL_Quit();
}

void e2d::Application::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            this->quit();
        }
    }
}

void e2d::Application::render()
{
    SDL_SetRenderDrawColor(this->m_renderer,
                           this->m_backgroundColor.r,
                           this->m_backgroundColor.g,
                           this->m_backgroundColor.b,
                           this->m_backgroundColor.a);
    SDL_RenderClear(this->m_renderer);

    //TODO: render other elements here

    SDL_RenderPresent(this->m_renderer);
}

const e2d::Color& e2d::Application::getBackgroundColor() const
{
    return this->m_backgroundColor;
}

void e2d::Application::setBackgroundColor(const e2d::Color& backgroundColor)
{
    this->m_backgroundColor = backgroundColor;
}
