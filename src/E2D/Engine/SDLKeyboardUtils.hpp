/**
* SDLKeyboardUtils.hpp
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

#ifndef E2D_ENGINE_SDL_KEYBOARD_UTILS_HPP
#define E2D_ENGINE_SDL_KEYBOARD_UTILS_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/Keyboard.hpp>

// NOLINTBEGIN
#include <cstring> //unused, but must be included before SDL on macOS (bug?)
// NOLINTEND

#include <SDL.h>

/**
 * @brief Namespace for E2D internal
 */
namespace e2d::internal
{

/**
 * @brief Translates an SDL_Keycode to the corresponding E2D Keyboard::Key enum value.
 *
 * @param sdlKeyCode The SDL_Keycode to translate.
 * @return The corresponding E2D Keyboard::Key value.
 */
E2D_ENGINE_API Keyboard::Key toKeyCode(const SDL_Keycode& sdlKeyCode);

/**
 * @brief Translates an SDL_Scancode to the corresponding E2D Keyboard::Scancode enum value.
 *
 * @param sdlScanCode The SDL_Scancode to translate.
 * @return The corresponding E2D Keyboard::Scancode value.
 */
E2D_ENGINE_API Keyboard::Scancode toScancode(const SDL_Scancode& sdlScanCode);

} // namespace e2d::internal

#endif //E2D_ENGINE_SDL_KEYBOARD_UTILS_HPP
