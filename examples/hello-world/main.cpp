/**
 * main.cpp
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

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/ObjectRegistry.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/Texture.hpp>

#include <utility>

class MySprite final : public e2d::Sprite
{
public:
    MySprite() : e2d::Sprite("MySprite")
    {
    }

    int getRenderPriority() const final
    {
        return 0;
    }

    void fixedUpdate() final
    {
    }

    void variableUpdate(double) final
    {
    }
};

class HelloWorldApplication final : public e2d::Application
{
public:
    HelloWorldApplication() : e2d::Application("Hello World Example")
    {
    }

    ~HelloWorldApplication() final = default;

    void onRunning() final
    {
        e2d::Application::onRunning();

        if (!this->getResourceRegistry().loadTextureFromFile("Hero", "gabe-idle-run.png"))
        {
            std::cerr << "Failed to load texture: gabe-idle-run.png" << std::endl;
            return;
        }
        const auto texture = this->getResourceRegistry().get<e2d::Texture>("Hero");

        auto sprite = std::make_unique<MySprite>();
        sprite->setTexture(texture);
        sprite->setTextureRect(e2d::IntRect({0, 0}, {24, 24}));
        sprite->setPosition({60, 60});
        sprite->setOrigin({12, 12});
        sprite->setScale({5, 5});
        sprite->setRotation(0);

        this->getObjectRegistry().addObject(std::move(sprite));
    }
};

int main()
{
    auto* application = new HelloWorldApplication();

    const auto exitCode = application->run();

    delete application;

    return exitCode;
}
