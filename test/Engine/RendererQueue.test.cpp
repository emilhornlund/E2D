/**
 * RendererQueue.test.cpp
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

#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/RenderQueue.hpp>

#include <catch2/catch_test_macros.hpp>

class MyRenderable : public e2d::Renderable
{
public:
    void render(const e2d::Renderer& renderer) const final
    {
        (void)renderer; // Explicitly mark as unused
    }
};

TEST_CASE("RenderQueue Functionality", "[RenderQueue]")
{
    e2d::internal::RenderQueue renderQueue;

    MyRenderable obj1;
    obj1.setRenderPriority(10);
    MyRenderable obj2;
    obj2.setRenderPriority(20);
    MyRenderable obj3;
    obj3.setRenderPriority(5);

    SECTION("Queue starts empty")
    {
        REQUIRE(renderQueue.isEmpty() == true);
    }

    SECTION("Objects are ordered by render priority")
    {
        renderQueue.push(&obj1);
        renderQueue.push(&obj2);
        renderQueue.push(&obj3);

        // The order should be obj3, obj1, obj2 based on render priority
        REQUIRE(renderQueue.pop()->getRenderPriority() == 5);  //obj3
        REQUIRE(renderQueue.pop()->getRenderPriority() == 10); //obj1
        REQUIRE(renderQueue.pop()->getRenderPriority() == 20); //obj2
    }

    SECTION("Pop from an empty queue returns nullptr")
    {
        REQUIRE(renderQueue.pop() == nullptr);
    }

    SECTION("Queue is empty after popping all elements")
    {
        renderQueue.push(&obj1);
        renderQueue.push(&obj2);
        renderQueue.pop(); // Pop obj2
        renderQueue.pop(); // Pop obj1

        REQUIRE(renderQueue.isEmpty() == true);
    }
}
