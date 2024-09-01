/**
 * @file Scene.cpp
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

#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/ObjectRegistry.hpp>
#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/RendererContext.hpp>
#include <E2D/Engine/Scene.hpp>

std::atomic<std::uint64_t> e2d::Scene::s_counter{1};
std::mutex                 e2d::Scene::s_counterMutex;

e2d::Scene::Scene() : Scene(generateUniqueIdentifier())
{
    log::debug("Constructing Scene with identifier '{}'", this->m_identifier);
}

e2d::Scene::Scene(std::string identifier) :
m_identifier(std::move(identifier)),
m_objectRegistry(std::make_unique<ObjectRegistry>())
{
    log::debug("Constructing Scene with identifier '{}'", this->m_identifier);
}

e2d::Scene::~Scene()
{
    log::debug("Destructing Scene with identifier '{}'", this->m_identifier);
}

const std::string& e2d::Scene::getIdentifier() const
{
    return this->m_identifier;
}

e2d::SceneManager& e2d::Scene::getSceneManager() const
{
    return *this->m_sceneManager;
}

void e2d::Scene::load()
{
    if (!this->m_loaded)
    {
        log::info("Loading Scene with identifier '{}'", this->m_identifier);
        this->onLoad();
        this->m_loaded = true;
    }
}

void e2d::Scene::unload()
{
    if (this->m_loaded)
    {
        log::info("Unloading Scene with identifier '{}'", this->m_identifier);
        this->onUnload();
        this->m_loaded = false;
    }
}

void e2d::Scene::pause()
{
    if (!this->m_paused)
    {
        this->m_paused = true;
        log::info("Pausing Scene with with identifier '{}'", this->m_identifier);
        this->onPause();
    }
}

void e2d::Scene::resume()
{
    if (this->m_paused)
    {
        this->m_paused = false;
        log::info("Resuming Scene with with identifier '{}'", this->m_identifier);
        this->onResume();
    }
}

bool e2d::Scene::isLoaded() const
{
    return this->m_loaded;
}

bool e2d::Scene::isPaused() const
{
    return this->m_paused;
}

void e2d::Scene::handleEvent(const e2d::Event& event)
{
    if (event.is<e2d::Event::LostFocus>())
    {
        this->pause();
    }
    if (event.is<e2d::Event::GainedFocus>())
    {
        this->resume();
    }

    if (!this->m_paused)
    {
        for (const auto& object : this->m_objectRegistry->getAllObjects())
        {
            object->onEvent(event);
        }
    }
}

void e2d::Scene::fixedUpdate()
{
    for (const auto& object : this->m_objectRegistry->getAllObjects())
    {
        object->onFixedUpdate();
    }
}

void e2d::Scene::variableUpdate(double deltaTime)
{
    for (const auto& object : this->m_objectRegistry->getAllObjects())
    {
        object->onVariableUpdate(deltaTime);
    }
}

void e2d::Scene::draw()
{
    for (const auto& entity : this->m_objectRegistry->getAllObjectsOfType<Renderable>())
    {
        internal::RendererContext::getInstance().getRenderer().draw(entity);
    }
}

void e2d::Scene::clean()
{
    this->m_objectRegistry->clean();
}

void e2d::Scene::onLoad()
{
}

void e2d::Scene::onUnload()
{
}

void e2d::Scene::onPause()
{
}

void e2d::Scene::onResume()
{
}

std::string e2d::Scene::generateUniqueIdentifier()
{
    const std::lock_guard<std::mutex> lock(s_counterMutex);
    const std::uint64_t               uniqueId = s_counter++;
    return "Object" + std::to_string(uniqueId);
}
