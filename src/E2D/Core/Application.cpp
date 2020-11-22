/**
 * E2D
 * Copyright (C) 2020 (emil.hornlund@me.com)
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

#include <E2D/Core/Application.hpp>

#include "SDL.h"

e2d::Application::Application() :
        m_exitCode(0),
        m_running(false) {}

e2d::Application::~Application() = default;

bool e2d::Application::isRunning() const {
    return this->m_running;
}

int e2d::Application::run() {
    this->m_running = true;

    int SCREEN_HEIGHT = 800;
    int SCREEN_WIDTH = 600;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL Game", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_HIDDEN);
    SDL_ShowWindow(window);

    SDL_Event event;
    while (this->m_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->quit(0);
            }
        }
        SDL_Delay(32);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return this->m_exitCode;
}

void e2d::Application::quit(int exitCode) {
    this->m_running = false;
    this->m_exitCode = exitCode;
}
