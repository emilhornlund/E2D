/**
 * @file main.cpp
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

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/Scene.hpp>
#include <E2D/Engine/SceneManager.hpp>
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/Text.hpp>
#include <E2D/Engine/Texture.hpp>

class HelloWordScene final : public e2d::Scene
{
public:
    HelloWordScene() : e2d::Scene("HelloWorldScene")
    {
    }

    ~HelloWordScene() final = default;

    void onLoad() final
    {
        if (!e2d::ResourceRegistry::getInstance().loadFromFile<e2d::Font>("OpenSans", "OpenSans.ttf"))
        {
            std::cerr << "Failed to load font: OpenSans.ttf" << std::endl;
            return;
        }
        const auto font = e2d::ResourceRegistry::getInstance().get<e2d::Font>("OpenSans");

        auto& text = this->createObject<e2d::Text>();
        text.setFont(font);
        text.setFontSize(28);
        text.setString("Hello, World!");
        text.setPosition({(800 - text.getGlobalBounds().width) / 2, (600 - text.getGlobalBounds().height) / 2});

        if (!e2d::ResourceRegistry::getInstance().loadFromFile<e2d::Texture>("Hero", "gabe-idle-run.png"))
        {
            std::cerr << "Failed to load texture: gabe-idle-run.png" << std::endl;
            return;
        }
        const auto texture = e2d::ResourceRegistry::getInstance().get<e2d::Texture>("Hero");

        auto& sprite = this->createObject<e2d::Sprite>();
        sprite.setTexture(texture);
        sprite.setTextureRect(e2d::IntRect({0, 0}, {24, 24}));
        sprite.setPosition({60, 60});
        sprite.setOrigin({12, 12});
        sprite.setScale({5, 5});
        sprite.setRotation(0);
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
        this->getSceneManager().pushScene<HelloWordScene>();
    }
};

int main()
{
    auto* application = new HelloWorldApplication();

    const auto exitCode = application->run();

    delete application;

    return exitCode;
}
