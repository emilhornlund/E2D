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

#include <E2D/Core/System.hpp>
#include <E2D/Core/Timer.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/Entity.hpp>
#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/Object.hpp>
#include <E2D/Engine/ObjectRegistry.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/Window.hpp>

#include <utility>

e2d::Application::Application(std::string windowTitle) :
m_windowTitle(std::move(windowTitle)),
m_window(std::make_unique<Window>()),
m_renderer(std::make_unique<Renderer>()),
m_objectRegistry(std::make_unique<ObjectRegistry>()),
m_backgroundColor(Color::Black)
{
}

e2d::Application::~Application() = default;

int e2d::Application::run()
{
    if (!System::initialize())
    {
        return -1;
    }
    if (!this->m_window->create(this->m_windowTitle.c_str(), 800, 600))
    {
        return -1;
    }
    if (!this->m_renderer->create(*this->m_window))
    {
        return -1;
    }

    Timer        targetFrameTimer;
    double const targetFrameTime = 1.0 / 60.0;

    double elapsedTime = 0.0;
    double remainder   = 0.0;

    this->m_running = true;
    this->onRunning();

    while (this->m_running)
    {
        targetFrameTimer.start();
        double elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();

        e2d::Event event{};
        while (pollEvent(event))
        {
            if (event.type == Event::EventType::Quit)
            {
                this->quit();
            }
        }

        for (const auto& object : this->m_objectRegistry->getAllObjects())
        {
            object->fixedUpdate();
        }

        while (elapsedFrameTimeAsSeconds < targetFrameTime - remainder)
        {
            const auto currentTime    = targetFrameTimer.getElapsedTimeAsSeconds();
            const auto deltaTime      = currentTime - elapsedFrameTimeAsSeconds;
            elapsedFrameTimeAsSeconds = currentTime;

            for (const auto& object : this->m_objectRegistry->getAllObjects())
            {
                object->variableUpdate(deltaTime);
            }
        }

        remainder = elapsedFrameTimeAsSeconds - (targetFrameTime - remainder);
        if (remainder >= targetFrameTime)
        {
            remainder = 0.0;
        }

        for (const auto& entity : this->m_objectRegistry->getAllObjectsOfType<Entity>())
        {
            this->m_renderer->draw(entity);
        }

        this->m_renderer->render(this->m_backgroundColor);

        elapsedTime += elapsedFrameTimeAsSeconds;
        if (elapsedTime >= 1.0)
        {
            elapsedTime = 0.0;
        }
    }

    this->m_window->destroy();
    this->m_renderer->destroy();

    System::shutdown();

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

e2d::Renderer& e2d::Application::getRenderer() const
{
    return *this->m_renderer;
}

e2d::ObjectRegistry& e2d::Application::getObjectRegistry() const
{
    return *this->m_objectRegistry;
}

const e2d::Color& e2d::Application::getBackgroundColor() const
{
    return this->m_backgroundColor;
}

void e2d::Application::setBackgroundColor(const e2d::Color& backgroundColor)
{
    this->m_backgroundColor = backgroundColor;
}

void e2d::Application::onRunning()
{
}
