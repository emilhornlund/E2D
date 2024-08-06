/**
* RenderQueue.cpp
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

#include <E2D/Core/Logger.hpp>

#include <E2D/Engine/RenderQueue.hpp>

e2d::internal::RenderQueue::RenderQueue()
{
    log::debug("Constructing RenderQueue");
}

e2d::internal::RenderQueue::~RenderQueue()
{
    log::debug("Destructing RenderQueue");
}

void e2d::internal::RenderQueue::push(const e2d::Renderable* renderable)
{
    this->m_queue.push(renderable);
}

const e2d::Renderable* e2d::internal::RenderQueue::pop()
{
    if (!this->m_queue.empty())
    {
        const Renderable* topElement = this->m_queue.top();
        this->m_queue.pop();
        return topElement;
    }
    return nullptr;
}

bool e2d::internal::RenderQueue::isEmpty() const
{
    return this->m_queue.empty();
}
