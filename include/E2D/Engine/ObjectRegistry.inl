/**
 * ObjectRegistry.inl
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

#ifndef E2D_ENGINE_OBJECT_REGISTRY_INL
#define E2D_ENGINE_OBJECT_REGISTRY_INL

#include <stdexcept>

template <typename T, typename... Args>
T& e2d::ObjectRegistry::createObject(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    static_assert(std::is_base_of<Object, T>::value, "T must be derived from Object");

    auto object = std::make_unique<T>(std::forward<Args>(args)...);

    const auto& id = object->getIdentifier();
    const auto  it = this->m_objects.find(id);
    if (it != this->m_objects.end())
    {
        throw std::runtime_error("Object `" + id + "` already exists");
    }

    object->m_application = this->m_application;
    T& ref                = *object;
    this->m_objects.insert(std::make_pair(id, std::move(object)));

    return ref;
}

template <typename T>
std::vector<T*> e2d::ObjectRegistry::getAllObjectsOfType() const
{
    std::vector<T*> objectsOfType;
    for (const auto& pair : this->m_objects)
    {
        T* castedObject = dynamic_cast<T*>(pair.second.get());
        if (castedObject)
        {
            objectsOfType.push_back(castedObject);
        }
    }
    return objectsOfType;
}

#endif //E2D_ENGINE_OBJECT_REGISTRY_INL
