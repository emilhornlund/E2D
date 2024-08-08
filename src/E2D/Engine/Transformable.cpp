/**
 * @file Transformable.cpp
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

// NOLINTBEGIN
#define _USE_MATH_DEFINES
#include <cmath>
// NOLINTEND

#include <E2D/Engine/Transformable.hpp>

#include <algorithm>

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

e2d::FloatRect e2d::Transformable::getLocalBounds() const
{
    return {{0, 0}, this->getSize()};
}

e2d::FloatRect e2d::Transformable::getGlobalBounds() const
{
    Vector2f size = this->getSize();

    // Compute the four corners in local space
    Vector2f corners[4] = {{0, 0}, {size.x, 0}, {size.x, size.y}, {0, size.y}};

    // Apply scale and origin
    for (auto& corner : corners)
    {
        corner.x = (corner.x - this->m_origin.x) * this->m_scale.x;
        corner.y = (corner.y - this->m_origin.y) * this->m_scale.y;
    }

    // Convert rotation to radians
    const double rotationRadians = this->m_rotation * M_PI / 180.0;

    // Compute the cosine and sine of the rotation
    const auto cosTheta = static_cast<float>(std::cos(rotationRadians));
    const auto sinTheta = static_cast<float>(std::sin(rotationRadians));

    // Apply rotation and translation
    for (auto& corner : corners)
    {
        const float x = corner.x * cosTheta - corner.y * sinTheta + this->m_position.x;
        const float y = corner.x * sinTheta + corner.y * cosTheta + this->m_position.y;
        corner        = {x, y};
    }

    // Find the min and max coordinates
    const float minX = std::min({corners[0].x, corners[1].x, corners[2].x, corners[3].x});
    const float minY = std::min({corners[0].y, corners[1].y, corners[2].y, corners[3].y});
    const float maxX = std::max({corners[0].x, corners[1].x, corners[2].x, corners[3].x});
    const float maxY = std::max({corners[0].y, corners[1].y, corners[2].y, corners[3].y});

    return {{minX, minY}, {maxX - minX, maxY - minY}};
}
