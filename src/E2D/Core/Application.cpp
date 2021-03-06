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
#include <E2D/Core/Window.hpp>

#include "EventHandler.hpp"

#include "SDL.h"

e2d::Application::Application() :
        m_exitCode(0),
        m_running(false),
        m_window(std::make_shared<Window>()) {}

e2d::Application::~Application() = default;

bool e2d::Application::isRunning() const {
    return this->m_running;
}

int e2d::Application::run() {
    this->m_running = true;

    this->m_window->open("E2D", {800, 600});

    auto eventHandler = std::unique_ptr<EventHandler>(new EventHandler(*this));

    while (this->m_running) {
        eventHandler->pollEvent();
    }

    this->m_window->close();

    return this->m_exitCode;
}

void e2d::Application::quit(int exitCode) {
    this->m_running = false;
    this->m_exitCode = exitCode;
}
