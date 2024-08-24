/**
 * @file Engine.hpp
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

#ifndef E2D_ENGINE_HPP
#define E2D_ENGINE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/CoreSystem.hpp>
#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/FontSystem.hpp>
#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/Keyboard.hpp>
#include <E2D/Engine/Object.hpp>
#include <E2D/Engine/ObjectRegistry.hpp>
#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/Resource.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/System.hpp>
#include <E2D/Engine/SystemManager.hpp>
#include <E2D/Engine/Text.hpp>
#include <E2D/Engine/Texture.hpp>
#include <E2D/Engine/Transformable.hpp>

#endif //E2D_ENGINE_HPP

/**
 * @defgroup engine Engine module
 * @brief Manages the main game loop and high-level systems integration in the E2D game engine.
 *
 * The Engine module is responsible for orchestrating the main game loop, integrating core systems such as rendering,
 * input handling, physics, and audio. It serves as the central hub that coordinates various subsystems to work together
 * seamlessly. The Engine module ensures that the game's components are updated and rendered in a consistent and
 * synchronized manner, providing a robust framework for game development.
 */
