/**
 * Transformable.cpp
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

#include <E2D/Engine/Transformable.hpp>

e2d::Transformable::~Transformable() = default;

const e2d::Vector2f& e2d::Transformable::getPosition() const
{
    return this->m_position;
}

void e2d::Transformable::setPosition(const e2d::Vector2f& position)
{
    this->m_position = position;
}

const e2d::Vector2f& e2d::Transformable::getOrigin() const
{
    return this->m_origin;
}

void e2d::Transformable::setOrigin(const e2d::Vector2f& origin)
{
    this->m_origin = origin;
}

const e2d::Vector2f& e2d::Transformable::getScale() const
{
    return this->m_scale;
}

void e2d::Transformable::setScale(const e2d::Vector2f& scale)
{
    this->m_scale = scale;
}

double e2d::Transformable::getRotation() const
{
    return this->m_rotation;
}

void e2d::Transformable::setRotation(double angle)
{
    this->m_rotation = angle;
}
