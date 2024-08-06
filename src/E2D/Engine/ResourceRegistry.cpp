/**
 * ResourceRegistry.cpp
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

#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/Texture.hpp>

#include <utility>

e2d::ResourceRegistry::ResourceRegistry(Application* application) : m_application(application)
{
    log::debug("Constructing ResourceRegistry");
}

e2d::ResourceRegistry::~ResourceRegistry()
{
    log::debug("Destructing ResourceRegistry");
}

e2d::ResourceRegistry::IResource::IResource(std::string type, std::string identifier) :
m_type(std::move(type)),
m_identifier(std::move(identifier))
{
    log::debug("Constructing IResource of type: '{}' with identifier: '{}'", this->m_type, this->m_identifier);
}

e2d::ResourceRegistry::IResource::~IResource()
{
    log::debug("Destructing IResource of type: '{}' with identifier: '{}'", this->m_type, this->m_identifier);
}

const std::string& e2d::ResourceRegistry::IResource::getType() const
{
    return this->m_type;
}

const std::string& e2d::ResourceRegistry::IResource::getIdentifier() const
{
    return this->m_identifier;
}
