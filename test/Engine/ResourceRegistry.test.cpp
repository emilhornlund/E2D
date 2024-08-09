/**
 * @file ResourceRegistry.test.cpp
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

#include "helloworld.bin.hpp"
#include "opensans.bin.hpp"

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/CoreSystem.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/SystemManager.hpp>
#include <E2D/Engine/Texture.hpp>
#include <E2D/Engine/Window.hpp>

#include <catch2/catch_test_macros.hpp>

class DummyFileResource final : public e2d::Resource
{
public:
    DummyFileResource() = default;

    bool loadFromFile(const std::string& filepath) final
    {
        return !filepath.empty();
    }

    bool loadFromMemory(const void* data, std::size_t size) final
    {
        (void)data;
        (void)size;
        return false;
    }

    int mTest{123};
};

class ResourceRegistryTestApplication final : public e2d::Application
{
public:
    ResourceRegistryTestApplication() : e2d::Application("ResourceRegistryTestApp")
    {
    }

    ~ResourceRegistryTestApplication() final = default;
};

class ResourceRegistryTest
{
public:
    ResourceRegistryTest()
    {
        // Setup (runs before each SECTION)
        e2d::SystemManager::getInstance().initialize<e2d::CoreSystem>();
        e2d::SystemManager::getInstance().initialize<e2d::GraphicsSystem>();
    }

    ~ResourceRegistryTest()
    {
        e2d::SystemManager::getInstance().shutdown();
    }
};

TEST_CASE_METHOD(ResourceRegistryTest, "ResourceRegistry Tests", "[ResourceRegistry]")
{
    e2d::ResourceRegistry resourceRegistry;

    SECTION("A resource does not exist initially")
    {
        REQUIRE_FALSE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource"));

        REQUIRE_THROWS(resourceRegistry.get<DummyFileResource>("MyDummyFileResource"));
    }

    SECTION("A generic resource was loaded and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<DummyFileResource>("MyDummyFileResource",
                                                                 "/some/path/to/MyDummyFileResource.ext"));

        REQUIRE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource"));

        auto dummyResource = resourceRegistry.get<DummyFileResource>("MyDummyFileResource");

        REQUIRE_FALSE(dummyResource == nullptr);
        REQUIRE(dummyResource->mTest == 123);
    }

    SECTION("A generic resource was loaded unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<DummyFileResource>("MyDummyFileResource", ""));

        REQUIRE_FALSE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource"));

        REQUIRE_THROWS(resourceRegistry.get<DummyFileResource>("MyDummyFileResource"));
    }

    SECTION("A texture resource was loaded from file and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<e2d::Texture>("HelloWorld", "resources/hello-world.png"));

        REQUIRE(resourceRegistry.exists<e2d::Texture>("HelloWorld"));

        auto helloWorldTextureResource = resourceRegistry.get<e2d::Texture>("HelloWorld");

        REQUIRE_FALSE(helloWorldTextureResource == nullptr);
        REQUIRE(helloWorldTextureResource->isLoaded() == true);
        REQUIRE(helloWorldTextureResource->getSize() == e2d::Vector2i{320, 240});
    }

    SECTION("A texture resource was loaded from file unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<e2d::Texture>("HelloWorld", ""));

        REQUIRE_FALSE(resourceRegistry.exists<e2d::Texture>("HelloWorld"));

        REQUIRE_THROWS(resourceRegistry.get<e2d::Texture>("HelloWorld"));
    }

    SECTION("A texture resource was loaded from memory and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromMemory<e2d::Texture>("HelloWorld", helloworld_data, helloworld_data_length));

        REQUIRE(resourceRegistry.exists<e2d::Texture>("HelloWorld"));

        auto helloWorldTextureResource = resourceRegistry.get<e2d::Texture>("HelloWorld");

        REQUIRE_FALSE(helloWorldTextureResource == nullptr);
        REQUIRE(helloWorldTextureResource->isLoaded() == true);
        REQUIRE(helloWorldTextureResource->getSize() == e2d::Vector2i{320, 240});
    }

    SECTION("A font resource was loaded from file and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<e2d::Font>("OpenSans", "resources/OpenSans.ttf"));

        REQUIRE(resourceRegistry.exists<e2d::Font>("OpenSans"));

        auto resource = resourceRegistry.get<e2d::Font>("OpenSans");

        REQUIRE_FALSE(resource == nullptr);
    }

    SECTION("A font resource was loaded from file unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<e2d::Font>("OpenSans", ""));

        REQUIRE_FALSE(resourceRegistry.exists<e2d::Font>("OpenSans"));

        REQUIRE_THROWS(resourceRegistry.get<e2d::Font>("OpenSans"));
    }

    SECTION("A font resource was loaded from memory and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromMemory<e2d::Font>("OpenSans", open_sans_data, open_sans_data_length));

        REQUIRE(resourceRegistry.exists<e2d::Font>("OpenSans"));

        auto resource = resourceRegistry.get<e2d::Font>("OpenSans");

        REQUIRE_FALSE(resource == nullptr);
    }
}
