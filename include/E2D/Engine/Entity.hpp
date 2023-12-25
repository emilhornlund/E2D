/**
* Entity.hpp
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

#ifndef E2D_ENGINE_ENTITY_HPP
#define E2D_ENGINE_ENTITY_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Object.hpp>
#include <E2D/Engine/Renderable.hpp>

#include <memory>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @class Entity
 * @brief Represents a base entity in the E2D Engine.
 *
 * Entity serves as a foundational class for all game entities. It combines the functionalities
 * of Object and Renderable. Entities in the E2D engine can interact with the game world and
 * be rendered on the screen. They can also possess properties like position, rotation, and scale.
 *
 * @see Object
 * @see Renderable
 */
class E2D_ENGINE_API Entity : public Object, public Renderable
{
public:
    /**
     * @brief Constructs an Entity object with a specific identifier.
     *
     * @param identifier A string representing the unique identifier of the entity.
     */
    explicit Entity(const std::string& identifier);

    /**
     * @brief Destructor for Entity.
     *
     * Ensures proper destruction of Entity objects and any resources they might hold.
     */
    ~Entity() override = 0;

}; // class Entity

} // namespace e2d

#endif //E2D_ENGINE_ENTITY_HPP
