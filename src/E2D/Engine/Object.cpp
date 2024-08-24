/**
 * @file Object.cpp
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

#include <E2D/Engine/Object.hpp>

#include <utility>

std::atomic<std::uint64_t> e2d::Object::s_counter{1};
std::mutex                 e2d::Object::s_counterMutex;

e2d::Object::Object() : m_identifier(generateUniqueIdentifier())
{
    log::debug("Constructing Object with identifier '{}'", this->m_identifier);
}

e2d::Object::Object(std::string identifier) : m_identifier(std::move(identifier))
{
    log::debug("Constructing Object with identifier '{}'", this->m_identifier);
}

e2d::Object::~Object()
{
    log::debug("Destructing Object with identifier '{}'", this->m_identifier);
}

std::string e2d::Object::generateUniqueIdentifier()
{
    const std::lock_guard<std::mutex> lock(s_counterMutex);
    const std::uint64_t               uniqueId = s_counter++;
    return "Object" + std::to_string(uniqueId);
}

const std::string& e2d::Object::getIdentifier() const
{
    return this->m_identifier;
}

void e2d::Object::onLoad()
{
    log::debug("Loading Object with identifier '{}'", this->m_identifier);
}

void e2d::Object::onUnload()
{
    log::debug("Unloading Object with identifier '{}'", this->m_identifier);
}
