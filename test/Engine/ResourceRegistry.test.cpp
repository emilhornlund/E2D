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

#include <E2D/Engine/CoreSystem.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/SystemManager.hpp>
#include <E2D/Engine/Texture.hpp>

#include <catch2/catch_test_macros.hpp>

#include <filesystem>

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
    auto& resourceRegistry = e2d::ResourceRegistry::getInstance();

    SECTION("A resource does not exist initially")
    {
        REQUIRE_FALSE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource1"));

        REQUIRE_THROWS(resourceRegistry.get<DummyFileResource>("MyDummyFileResource1"));
    }

    SECTION("A generic resource was loaded and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<DummyFileResource>("MyDummyFileResource2",
                                                                 "/some/path/to/MyDummyFileResource.ext"));

        REQUIRE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource2"));

        auto dummyResource = resourceRegistry.get<DummyFileResource>("MyDummyFileResource2");

        REQUIRE_FALSE(dummyResource == nullptr);
        REQUIRE(dummyResource->mTest == 123);
    }

    SECTION("A generic resource was loaded unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<DummyFileResource>("MyDummyFileResource3", ""));

        REQUIRE_FALSE(resourceRegistry.exists<DummyFileResource>("MyDummyFileResource3"));

        REQUIRE_THROWS(resourceRegistry.get<DummyFileResource>("MyDummyFileResource3"));
    }

    SECTION("A texture resource was loaded from file and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<e2d::Texture>("HelloWorld1", "resources/hello-world.png"));

        REQUIRE(resourceRegistry.exists<e2d::Texture>("HelloWorld1"));

        auto helloWorldTextureResource = resourceRegistry.get<e2d::Texture>("HelloWorld1");

        REQUIRE_FALSE(helloWorldTextureResource == nullptr);
        REQUIRE(helloWorldTextureResource->isLoaded() == true);
        REQUIRE(helloWorldTextureResource->getSize() == e2d::Vector2i{320, 240});
    }

    SECTION("A texture resource was loaded from file unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<e2d::Texture>("HelloWorld2", ""));

        REQUIRE_FALSE(resourceRegistry.exists<e2d::Texture>("HelloWorld2"));

        REQUIRE_THROWS(resourceRegistry.get<e2d::Texture>("HelloWorld2"));
    }

    SECTION("A texture resource was loaded from memory and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromMemory<e2d::Texture>("HelloWorld3", helloworld_data, helloworld_data_length));

        REQUIRE(resourceRegistry.exists<e2d::Texture>("HelloWorld3"));

        auto helloWorldTextureResource = resourceRegistry.get<e2d::Texture>("HelloWorld3");

        REQUIRE_FALSE(helloWorldTextureResource == nullptr);
        REQUIRE(helloWorldTextureResource->isLoaded() == true);
        REQUIRE(helloWorldTextureResource->getSize() == e2d::Vector2i{320, 240});
    }

    SECTION("A font resource was loaded from file and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromFile<e2d::Font>("OpenSans1", "resources/OpenSans.ttf"));

        REQUIRE(resourceRegistry.exists<e2d::Font>("OpenSans1"));

        auto resource = resourceRegistry.get<e2d::Font>("OpenSans1");

        REQUIRE_FALSE(resource == nullptr);
    }

    SECTION("A font resource was loaded from file unsuccessfully")
    {
        REQUIRE_FALSE(resourceRegistry.loadFromFile<e2d::Font>("OpenSans2", ""));

        REQUIRE_FALSE(resourceRegistry.exists<e2d::Font>("OpenSans2"));

        REQUIRE_THROWS(resourceRegistry.get<e2d::Font>("OpenSans2"));
    }

    SECTION("A font resource was loaded from memory and retrieved successfully")
    {
        REQUIRE(resourceRegistry.loadFromMemory<e2d::Font>("OpenSans3", open_sans_data, open_sans_data_length));

        REQUIRE(resourceRegistry.exists<e2d::Font>("OpenSans3"));

        auto resource = resourceRegistry.get<e2d::Font>("OpenSans3");

        REQUIRE_FALSE(resource == nullptr);
    }
}
