/**
 * @file Application.cpp
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
#include <E2D/Core/Timer.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/CoreSystem.hpp>
#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/FontSystem.hpp>
#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/RendererContext.hpp>
#include <E2D/Engine/Scene.hpp>
#include <E2D/Engine/SceneManager.hpp>
#include <E2D/Engine/SystemManager.hpp>

#include <utility>

e2d::Application::Application(std::string windowTitle) :
m_windowTitle(std::move(windowTitle)),
m_sceneManager(std::make_unique<SceneManager>()),
m_backgroundColor(Color::Black)
{
    log::debug("Constructing Application");
}

e2d::Application::~Application()
{
    log::debug("Destructing Application");
}

int e2d::Application::run()
{
    log::info("Starting application");

    auto& systemManager = SystemManager::getInstance();
    if (!systemManager.initialize<CoreSystem>())
    {
        log::error("Failed to initialize core system. Aborting application startup.");
        return -1;
    }
    if (!systemManager.initialize<GraphicsSystem>())
    {
        log::error("Failed to initialize graphics system. Aborting application startup.");
        return -1;
    }
    if (!systemManager.initialize<FontSystem>())
    {
        log::error("Failed to initialize font system. Aborting application startup.");
        return -1;
    }

    auto& rendererContext = internal::RendererContext::getInstance();
    rendererContext.initialize();

    Timer        targetFrameTimer;
    double const targetFrameTime = 1.0 / 60.0;

    double elapsedTime = 0.0;
    double remainder   = 0.0;

    this->m_running = true;
    this->onRunning();

    while (this->m_running)
    {
        if (this->m_sceneManager->isEmpty())
        {
            this->quit();
        }
        else
        {
            const auto& scene = this->m_sceneManager->getActiveScene();
            if (!scene->isLoaded())
            {
                scene->load();
            }

            targetFrameTimer.start();
            double elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();

            while (const std::optional<Event> event = pollEvent())
            {
                if (event->is<Event::Closed>())
                {
                    this->quit();
                }
                else if (event.has_value())
                {
                    scene->handleEvent(event.value());
                }
            }

            scene->fixedUpdate();

            while (elapsedFrameTimeAsSeconds < targetFrameTime - remainder)
            {
                const auto currentTime    = targetFrameTimer.getElapsedTimeAsSeconds();
                const auto deltaTime      = currentTime - elapsedFrameTimeAsSeconds;
                elapsedFrameTimeAsSeconds = currentTime;

                scene->variableUpdate(deltaTime);
            }

            remainder = elapsedFrameTimeAsSeconds - (targetFrameTime - remainder);
            if (remainder >= targetFrameTime)
            {
                remainder = 0.0;
            }

            scene->draw();

            rendererContext.getRenderer().render(this->m_backgroundColor);

            scene->clean();
            this->m_sceneManager->clean();

            elapsedTime += elapsedFrameTimeAsSeconds;
            if (elapsedTime >= 1.0)
            {
                elapsedTime = 0.0;
            }
        }
    }

    systemManager.shutdown();

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

const e2d::Color& e2d::Application::getBackgroundColor() const
{
    return this->m_backgroundColor;
}

void e2d::Application::setBackgroundColor(const e2d::Color& backgroundColor)
{
    this->m_backgroundColor = backgroundColor;
}

e2d::SceneManager& e2d::Application::getSceneManager() const
{
    return *this->m_sceneManager;
}

void e2d::Application::onRunning()
{
    log::info("Application is running");
}
