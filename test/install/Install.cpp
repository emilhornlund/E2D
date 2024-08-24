/**
 * @file Install.cpp
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

#include <E2D/Core.hpp>

#include <E2D/Engine.hpp>

class InstallApplication final : public e2d::Application
{
public:
    InstallApplication() : e2d::Application("Test Install Application")
    {
    }

    ~InstallApplication() final = default;
};

int main()
{
    // Core
    [[maybe_unused]] const e2d::Color      color;
    [[maybe_unused]] const e2d::DoubleRect doubleRect;
    [[maybe_unused]] const e2d::FloatRect  floatRect;
    [[maybe_unused]] const e2d::IntRect    intRect;
    [[maybe_unused]] const e2d::Timer      timer;
    [[maybe_unused]] const e2d::Vector2d   doubleVector;
    [[maybe_unused]] const e2d::Vector2f   floatVector;
    [[maybe_unused]] const e2d::Vector2i   intVector;
    [[maybe_unused]] const e2d::Vector2u   unsignedVector;

    // Engine
    [[maybe_unused]] const InstallApplication  application;
    [[maybe_unused]] const e2d::Sprite         sprite("MySprite");
    [[maybe_unused]] const e2d::ObjectRegistry objectRegistry(nullptr);
    [[maybe_unused]] const e2d::Texture        texture;
}
