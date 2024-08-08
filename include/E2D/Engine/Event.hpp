/**
 * @file Event.hpp
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

#ifndef E2D_ENGINE_EVENT_HPP
#define E2D_ENGINE_EVENT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Engine/Keyboard.hpp>

namespace e2d
{

/**
 * @struct Event
 * @ingroup engine
 * @brief Represents a generic event, encapsulating various event types such as keyboard inputs.
 *
 * The Event struct is a union of multiple event types that can occur within the E2D engine.
 * It includes keyboard events and window resize events, and enumerates all possible event types.
 */
struct Event
{
    /**
     * @struct KeyEvent
     * @brief Represents a keyboard-related event, storing key details and modifier states.
     *
     * This structure holds information about keyboard events, including the key code,
     * scancode, and the state of modifier keys like Alt, Control, Shift, and System.
     */
    struct KeyEvent
    {
        Keyboard::Key      code     = Keyboard::Key::Unknown;      //!< The key code of the keyboard event.
        Keyboard::Scancode scancode = Keyboard::Scancode::Unknown; //!< The scancode representing the physical key location.

        bool alt     = false; //!< True if the Alt key is pressed during this event.
        bool control = false; //!< True if the Control key is pressed during this event.
        bool shift   = false; //!< True if the Shift key is pressed during this event.
        bool system  = false; //!< True if the System key (like the Windows key) is pressed during this event.
    };

    /**
     * @struct SizeEvent
     * @brief Represents an event related to the resizing of a window.
     *
     * This structure stores information about window resize events,
     * including the new dimensions of the window after the resize operation.
     */
    struct SizeEvent
    {
        unsigned int width  = 0; //!< New width of the window, in pixels.
        unsigned int height = 0; //!< New height of the window, in pixels.
    };

    /**
     * @enum EventType
     * @brief Enumerates the types of events that can be processed.
     *
     * This enum defines the various event types that the E2D engine can handle, including
     * system events such as window closing, resizing, focus changes, and key events.
     */
    enum EventType
    {
        Unknown,      //!< Represents an unknown event.
        Closed,       //!< Represents a window close event.
        Resized,      //!< Represents a window resize event.
        LostFocus,    //!< Represents an event where the window loses focus.
        GainedFocus,  //!< Represents an event where the window gains focus.
        Minimized,    //!< Represents an event where the window is minimized.
        Maximized,    //!< Represents an event where the window is maximized.
        Restored,     //!< Represents an event where the window is restored from minimized or maximized state.
        KeyPressed,   //!< Represents a key press event.
        KeyReleased,  //!< Represents a key release event.
        MouseEntered, //!< Represents an event where the mouse enters the window boundaries.
        MouseLeft,    //!< Represents an event where the mouse leaves the window boundaries.
        Quit,         //!< Represents a quit event, typically triggered by closing the application window.
    };

    EventType type{}; //!< Type of the event, indicating what kind of event occurred.

    union
    {
        KeyEvent  key;  //!< Specific details for a keyboard event, valid when type is KeyPressed or KeyReleased.
        SizeEvent size; //!< Specific details for a window resize event, valid when type is Resized.
    };
};

/**
 * @ingroup engine
 * @brief Polls for an event from the system queue and translates it to an E2D event.
 *
 * This function checks the system's event queue for new events and, if available,
 * translates them into the E2D engine's internal event format. It is used within the
 * main game loop to process input and other system events.
 *
 * @param event Reference to an Event struct where the polled event will be stored.
 * @return True if an event was successfully polled, false if the event queue was empty.
 */
E2D_ENGINE_API bool pollEvent(e2d::Event& event);

} // namespace e2d

#endif //E2D_ENGINE_EVENT_HPP
