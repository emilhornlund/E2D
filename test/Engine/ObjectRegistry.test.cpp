/**
 * RendererQueue.test.cpp
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

#include <E2D/Engine/ObjectRegistry.hpp>
#include <E2D/Engine/Sprite.hpp>

#include <catch2/catch_test_macros.hpp>

#include <memory>

class MySprite final : public e2d::Sprite
{
public:
    explicit MySprite(const std::string& identifier) : e2d::Sprite(identifier)
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

class MyObject final : public e2d::Object
{
public:
    explicit MyObject(const std::string& identifier) : e2d::Object(identifier)
    {
    }

    void fixedUpdate() final
    {
    }

    void variableUpdate(double) final
    {
    }
};

TEST_CASE("ObjectRegistry Tests", "[ObjectRegistry]")
{
    e2d::ObjectRegistry objectRegistry;

    SECTION("Adding and Retrieving Objects")
    {
        auto mySprite = std::make_unique<MySprite>("Sprite1");
        REQUIRE(objectRegistry.addObject(std::move(mySprite)) == true);

        e2d::Object* retrievedObject = objectRegistry.getObject("Sprite1");
        REQUIRE(retrievedObject != nullptr);
        REQUIRE(retrievedObject->getIdentifier() == "Sprite1");
    }

    SECTION("Preventing Duplicate Identifiers")
    {
        auto sprite1 = std::make_unique<MySprite>("Sprite2");
        REQUIRE(objectRegistry.addObject(std::move(sprite1)) == true);

        auto duplicateSprite = std::make_unique<MySprite>("Sprite2");
        REQUIRE(objectRegistry.addObject(std::move(duplicateSprite)) == false);
    }

    SECTION("Removing Objects")
    {
        auto spriteToRemove = std::make_unique<MySprite>("Sprite3");
        objectRegistry.addObject(std::move(spriteToRemove));
        REQUIRE(objectRegistry.removeObject("Sprite3") == true);

        REQUIRE(objectRegistry.getObject("Sprite3") == nullptr);
    }

    SECTION("Listing All Objects")
    {
        auto sprite1 = std::make_unique<MySprite>("Sprite4");
        auto sprite2 = std::make_unique<MySprite>("Sprite5");

        objectRegistry.addObject(std::move(sprite1));
        objectRegistry.addObject(std::move(sprite2));

        auto allObjects = objectRegistry.getAllObjects();
        REQUIRE(allObjects.size() == 2);
    }

    SECTION("Retrieving Objects of Specific Type")
    {
        auto sprite1 = std::make_unique<MySprite>("TypeSprite1");
        auto sprite2 = std::make_unique<MySprite>("TypeSprite2");
        objectRegistry.addObject(std::move(sprite1));
        objectRegistry.addObject(std::move(sprite2));

        auto nonSprite = std::make_unique<MyObject>("NonSprite");
        objectRegistry.addObject(std::move(nonSprite));

        auto sprites = objectRegistry.getAllObjectsOfType<MySprite>();
        REQUIRE(sprites.size() == 2);
        REQUIRE((sprites[0]->getIdentifier() == "TypeSprite1" || sprites[0]->getIdentifier() == "TypeSprite2"));
        REQUIRE((sprites[1]->getIdentifier() == "TypeSprite1" || sprites[1]->getIdentifier() == "TypeSprite2"));

        auto nonSprites = objectRegistry.getAllObjectsOfType<MyObject>();
        REQUIRE(nonSprites.size() == 1);
        REQUIRE(nonSprites[0]->getIdentifier() == "NonSprite");
    }
}
