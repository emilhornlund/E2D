/**
 * Event.cpp
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

#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/SDLKeyboardUtils.hpp>

bool toKeyboardEvent(const SDL_Event& sdlEvent, e2d::Event& event);

bool toWindowEvent(const SDL_Event& sdlEvent, e2d::Event& event);

bool e2d::pollEvent(e2d::Event& event)
{
    SDL_Event sdlEvent{};
    bool      valid = false;

    while (SDL_PollEvent(&sdlEvent) && !valid)
    {
        event = {};
        switch (sdlEvent.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                valid = toKeyboardEvent(sdlEvent, event);
                break;
            case SDL_WINDOWEVENT:
                valid = toWindowEvent(sdlEvent, event);
                break;
            case SDL_QUIT:
                event.type = e2d::Event::Quit;
                valid      = true;
                break;
            default:
                event.type = e2d::Event::Unknown;
                valid      = false;
                break;
        }
    }
    return valid;
}

/**
 * @brief Converts an SDL_KeyboardEvent to an E2D KeyEvent.
 *
 * This function is responsible for converting SDL keyboard events (SDL_KeyboardEvent)
 * into the E2D engine's KeyEvent format. It maps SDL key codes and scancodes to the
 * corresponding E2D key codes and scancodes. Additionally, it determines the state
 * of modifier keys (like Alt, Control, Shift, and System) at the time of the key event.
 *
 * The function is called within the event polling loop and is responsible for populating
 * the KeyEvent structure within an E2D Event when a keyboard-related SDL event occurs.
 *
 * @param sdlEvent The SDL_Event, specifically a keyboard event, to be translated.
 * @param event Reference to an E2D Event where the translated keyboard information will be stored.
 * @return True if the SDL event is a keyboard event and the conversion was successful, false otherwise.
 */
bool toKeyboardEvent(const SDL_Event& sdlEvent, e2d::Event& event)
{
    if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
    {
        event.type         = (sdlEvent.type == SDL_KEYDOWN) ? e2d::Event::KeyPressed : e2d::Event::KeyReleased;
        event.key.code     = e2d::internal::toKeyCode(sdlEvent.key.keysym.sym);
        event.key.scancode = e2d::internal::toScancode(sdlEvent.key.keysym.scancode);
        event.key.alt      = (sdlEvent.key.keysym.mod & KMOD_ALT) != 0;
        event.key.control  = (sdlEvent.key.keysym.mod & KMOD_CTRL) != 0;
        event.key.shift    = (sdlEvent.key.keysym.mod & KMOD_SHIFT) != 0;
        event.key.system   = (sdlEvent.key.keysym.mod & KMOD_GUI) != 0;
        return true;
    }
    return false;
}

/**
 * @brief Converts an SDL_WindowEvent to an E2D SizeEvent.
 *
 * This function translates an SDL window event into an E2D engine's SizeEvent format,
 * specifically handling window resize events. It extracts the new width and height
 * from the SDL event and populates an E2D SizeEvent structure.
 *
 * @param sdlEvent The SDL_Event to be translated.
 * @param event Reference to an E2D Event to store the translated information.
 * @return True if the conversion was successful, false otherwise.
 */
bool toWindowEvent(const SDL_Event& sdlEvent, e2d::Event& event)
{
    if (sdlEvent.type == SDL_WINDOWEVENT)
    {
        switch (sdlEvent.window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                event.type = e2d::Event::Closed;
                return true;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                event.type        = e2d::Event::Resized;
                event.size.width  = static_cast<unsigned int>(sdlEvent.window.data1);
                event.size.height = static_cast<unsigned int>(sdlEvent.window.data2);
                return true;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                event.type = e2d::Event::LostFocus;
                return true;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                event.type = e2d::Event::GainedFocus;
                return true;
            case SDL_WINDOWEVENT_MINIMIZED:
                event.type = e2d::Event::Minimized;
                return true;
            case SDL_WINDOWEVENT_MAXIMIZED:
                event.type = e2d::Event::Maximized;
                return true;
            case SDL_WINDOWEVENT_RESTORED:
                event.type = e2d::Event::Restored;
                return true;
            case SDL_WINDOWEVENT_ENTER:
                event.type = e2d::Event::MouseEntered;
                return true;
            case SDL_WINDOWEVENT_LEAVE:
                event.type = e2d::Event::MouseLeft;
                return true;
            default:
                break;
        }
    }
    return false;
}
