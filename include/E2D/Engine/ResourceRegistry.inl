/**
 * ResourceRegistry.inl
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

#ifndef E2D_ENGINE_RESOURCE_REGISTRY_INL
#define E2D_ENGINE_RESOURCE_REGISTRY_INL

#include <E2D/Core/Logger.hpp>

#include <stdexcept>

template <class T>
e2d::ResourceRegistry::TResource<T>::TResource(const std::string& identifier) : IResource(typeid(T).name(), identifier)
{
    log::debug("Constructing TResource with identifier: '{}'", identifier);
}

template <class T>
e2d::ResourceRegistry::TResource<T>::TResource::~TResource()
{
    log::debug("Destructing TResource");
}

template <typename T>
bool e2d::ResourceRegistry::exists(const std::string& identifier) const
{
    auto it = this->m_resources.find(identifier);
    return it != this->m_resources.end() && it->second->getType() == typeid(T).name();
}

template <typename T>
std::shared_ptr<const T> e2d::ResourceRegistry::get(const std::string& identifier) const
{
    auto it = this->m_resources.find(identifier);
    if (it != this->m_resources.end() && it->second->getType() == typeid(T).name())
    {
        auto resource = dynamic_cast<TResource<T>*>(it->second.get());
        if (resource)
        {
            return resource->mValue;
        }
    }
    throw std::runtime_error("The resource `" + identifier + "` has not been loaded.");
}

template <typename T, typename... Args>
bool e2d::ResourceRegistry::loadFromFile(const std::string& identifier,
                                         const std::string& filepath,
                                         Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    static_assert(std::is_base_of<Resource, T>::value, "T must be derived from Resource");
    if (!this->exists<T>(identifier))
    {
        auto resource                   = std::make_unique<TResource<T>>(identifier);
        resource->mValue                = std::make_shared<T>();
        resource->mValue->m_application = this->m_application;
        if (resource->mValue->loadFromFile(filepath, std::forward<Args>(args)...))
        {
            this->m_resources.insert(std::make_pair(identifier, std::move(resource)));
            return true;
        }
        else
        {
            log::error("Failed to load resource with identifier '{}' from file '{}'", identifier, filepath);
        }
    }
    return false;
}

template <typename T, typename... Args>
bool e2d::ResourceRegistry::loadFromMemory(const std::string& identifier,
                                           const void*        data,
                                           std::size_t        size,
                                           Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    static_assert(std::is_base_of<Resource, T>::value, "T must be derived from Resource");
    if (!this->exists<T>(identifier))
    {
        auto resource                   = std::make_unique<TResource<T>>(identifier);
        resource->mValue                = std::make_shared<T>();
        resource->mValue->m_application = this->m_application;
        if (resource->mValue->loadFromMemory(data, size, std::forward<Args>(args)...))
        {
            this->m_resources.insert(std::make_pair(identifier, std::move(resource)));
            return true;
        }
        else
        {
            log::error("Failed to load resource with identifier '{}' from memory", identifier);
        }
    }
    return false;
}

#endif //E2D_ENGINE_RESOURCE_REGISTRY_INL
