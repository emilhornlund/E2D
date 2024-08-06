/**
 * ObjectRegistry.cpp
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

#include <E2D/Core/Logger.hpp>

#include <E2D/Engine/ObjectRegistry.hpp>

e2d::ObjectRegistry::ObjectRegistry(Application* application) : m_application(application)
{
    log::debug("Constructing ObjectRegistry");
}

e2d::ObjectRegistry::~ObjectRegistry()
{
    log::debug("Destructing ObjectRegistry");
}

e2d::Object* e2d::ObjectRegistry::getObject(const std::string& identifier) const
{
    auto it = this->m_objects.find(identifier);
    if (it != this->m_objects.end())
    {
        return it->second.get();
    }
    return nullptr;
}

bool e2d::ObjectRegistry::removeObject(const std::string& identifier)
{
    auto it = this->m_objects.find(identifier);
    if (it != this->m_objects.end())
    {
        this->m_objects.erase(it);
        return true;
    }
    return false;
}

std::vector<e2d::Object*> e2d::ObjectRegistry::getAllObjects() const
{
    std::vector<Object*> allObjects;
    allObjects.reserve(this->m_objects.size());
    for (const auto& pair : this->m_objects)
    {
        allObjects.push_back(pair.second.get());
    }
    return allObjects;
}
