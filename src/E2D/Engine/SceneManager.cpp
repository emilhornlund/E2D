/**
 * @file SceneManager.cpp
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

#include <E2D/Engine/Scene.hpp>
#include <E2D/Engine/SceneManager.hpp>

#include <stdexcept>

e2d::SceneManager::SceneManager()
{
    log::debug("Constructing SceneManager");
}

e2d::SceneManager::~SceneManager()
{
    log::debug("Destructing SceneManager and cleaning up all scenes");
    while (!this->isEmpty())
    {
        this->popScene();
    }
    this->clean();
}

bool e2d::SceneManager::isEmpty() const
{
    return this->m_scenes.empty();
}

const std::shared_ptr<e2d::Scene>& e2d::SceneManager::getActiveScene() const
{
    if (this->m_scenes.empty())
    {
        log::error("Failed to get the active scene since no scenes are loaded");
        throw std::runtime_error("Scenes are empty");
    }
    return this->m_scenes.back();
}

void e2d::SceneManager::popScene()
{
    if (this->m_scenes.empty())
    {
        log::error("Failed to pop a scene since no scenes are loaded");
        throw std::runtime_error("Scenes are empty");
    }

    auto it = this->m_scenes.back();
    it->pause();
    it->unload();
    this->m_unloadedScenes.push_back(it);
    this->m_scenes.pop_back();

    if (!this->m_scenes.empty())
    {
        this->m_scenes.back()->resume();
    }
}

void e2d::SceneManager::clean()
{
    if (!this->m_unloadedScenes.empty())
    {
        const auto unloadedScenesCount = this->m_unloadedScenes.size();
        this->m_unloadedScenes.clear();
        log::debug("Cleaned a total of {} unloaded scenes", unloadedScenesCount);
    }
}
