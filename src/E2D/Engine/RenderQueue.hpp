/**
* RenderQueue.hpp
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

#ifndef E2D_ENGINE_RENDER_QUEUE_HPP
#define E2D_ENGINE_RENDER_QUEUE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Renderable.hpp>

#include <functional>
#include <queue>

/**
 * @brief Namespace for E2D
 */
namespace e2d::internal
{

/**
 * @class RenderQueue
 * @brief Manages a priority queue of Renderable objects.
 *
 * RenderQueue is a utility class that manages a queue of Renderable objects,
 * sorting them based on their render priority. This ensures that objects
 * are rendered in the correct order. The class uses a priority queue where
 * objects with higher render priorities are rendered later.
 */
class E2D_ENGINE_API RenderQueue final : NonCopyable
{
public:
    /**
     * @brief Default constructor for RenderQueue.
     *
     * Constructs a RenderQueue object.
     */
    RenderQueue();

    /**
     * @brief Destructor for RenderQueue.
     *
     * Destroys the RenderQueue object, releasing its resources.
     */
    ~RenderQueue();

    /**
     * @brief Adds a Renderable object to the queue.
     *
     * Inserts the provided Renderable object into the queue. The object
     * is ordered within the queue based on its render priority.
     *
     * @param renderable Pointer to the Renderable object to be added to the queue.
     */
    void push(const Renderable* renderable);

    /**
     * @brief Removes and returns the Renderable object with the highest priority.
     *
     * Pops the Renderable object with the highest render priority from the queue
     * and returns it. If the queue is empty, returns nullptr.
     *
     * @return const Renderable* Pointer to the Renderable object with the highest priority,
     *         or nullptr if the queue is empty.
     */
    const Renderable* pop();

    /**
     * @brief Checks if the queue is empty.
     *
     * @return bool True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

private:
    /**
     * @struct RenderableCompare
     * @brief Function for comparing two Renderable objects based on render priority.
     *
     * This struct is used to define the comparison criteria for ordering
     * Renderable objects within the RenderQueue. It compares two Renderable
     * objects based on their render priority.
     */
    struct RenderableCompare
    {
        /**
         * @brief Compares two Renderable objects.
         *
         * Determines the order of the Renderable objects in the queue
         * based on their render priority.
         *
         * @param lhs Pointer to the first Renderable object.
         * @param rhs Pointer to the second Renderable object.
         * @return bool True if the first object has higher render priority than the second, false otherwise.
         */
        bool operator()(const Renderable* lhs, const Renderable* rhs) const
        {
            return lhs->getRenderPriority() > rhs->getRenderPriority();
        }
    };

    std::priority_queue<const Renderable*, std::vector<const Renderable*>, RenderableCompare> m_queue; //!< Priority queue of Renderable objects.

}; // class RenderQueue

} // namespace e2d::internal

#endif //E2D_ENGINE_RENDER_QUEUE_HPP
