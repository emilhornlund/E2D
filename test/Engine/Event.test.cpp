/**
 * @file Event.test.cpp
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

#include <E2D/Core/System.hpp>

#include <E2D/Engine/Event.hpp>

#include <catch2/catch_test_macros.hpp>
#include <SDL.h>

class EventTest
{
public:
    EventTest()
    {
        // Setup (runs before each SECTION)
        e2d::System::initialize();
    }

    ~EventTest()
    {
        // Teardown (runs after each SECTION)
        e2d::System::shutdown();
    }
};

TEST_CASE_METHOD(EventTest, "pollEvent", "[Event]")
{
    SDL_Event  sdlEvent{};
    e2d::Event actualEvent{};
    bool       wasPolled;

    SECTION("Handle Key Down Event")
    {
        sdlEvent.type                = SDL_KEYDOWN;
        sdlEvent.key.keysym.sym      = SDLK_a;
        sdlEvent.key.keysym.scancode = SDL_SCANCODE_A;
        sdlEvent.key.keysym.mod      = KMOD_NONE;
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::KeyPressed);
        REQUIRE(actualEvent.key.code == e2d::Keyboard::Key::A);
        REQUIRE(actualEvent.key.scancode == e2d::Keyboard::Scancode::A);
        REQUIRE(actualEvent.key.alt == false);
        REQUIRE(actualEvent.key.control == false);
        REQUIRE(actualEvent.key.shift == false);
        REQUIRE(actualEvent.key.system == false);
    }

    SECTION("Handle Key Down Event with Modifiers")
    {
        sdlEvent.type                = SDL_KEYDOWN;
        sdlEvent.key.keysym.sym      = SDLK_a;
        sdlEvent.key.keysym.scancode = SDL_SCANCODE_A;
        sdlEvent.key.keysym.mod      = KMOD_SHIFT | KMOD_CTRL | KMOD_ALT | KMOD_GUI;
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::KeyPressed);
        REQUIRE(actualEvent.key.code == e2d::Keyboard::Key::A);
        REQUIRE(actualEvent.key.scancode == e2d::Keyboard::Scancode::A);
        REQUIRE(actualEvent.key.alt == true);
        REQUIRE(actualEvent.key.control == true);
        REQUIRE(actualEvent.key.shift == true);
        REQUIRE(actualEvent.key.system == true);
    }

    SECTION("Handle Key Up Event")
    {
        sdlEvent.type                = SDL_KEYUP;
        sdlEvent.key.keysym.sym      = SDLK_a;
        sdlEvent.key.keysym.scancode = SDL_SCANCODE_A;
        sdlEvent.key.keysym.mod      = KMOD_NONE;
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::KeyReleased);
        REQUIRE(actualEvent.key.code == e2d::Keyboard::Key::A);
        REQUIRE(actualEvent.key.scancode == e2d::Keyboard::Scancode::A);
        REQUIRE(actualEvent.key.alt == false);
        REQUIRE(actualEvent.key.control == false);
        REQUIRE(actualEvent.key.shift == false);
        REQUIRE(actualEvent.key.system == false);
    }

    SECTION("Handle Key Up Event with Modifiers")
    {
        sdlEvent.type                = SDL_KEYUP;
        sdlEvent.key.keysym.sym      = SDLK_a;
        sdlEvent.key.keysym.scancode = SDL_SCANCODE_A;
        sdlEvent.key.keysym.mod      = KMOD_SHIFT | KMOD_CTRL | KMOD_ALT | KMOD_GUI;
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::KeyReleased);
        REQUIRE(actualEvent.key.code == e2d::Keyboard::Key::A);
        REQUIRE(actualEvent.key.scancode == e2d::Keyboard::Scancode::A);
        REQUIRE(actualEvent.key.alt == true);
        REQUIRE(actualEvent.key.control == true);
        REQUIRE(actualEvent.key.shift == true);
        REQUIRE(actualEvent.key.system == true);
    }

    SECTION("Handle Window Close Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_CLOSE;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Closed);
    }

    SECTION("Handle Window Resize Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
        sdlEvent.window.data1 = 800;
        sdlEvent.window.data2 = 600;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Resized);
        REQUIRE(actualEvent.size.width == 800);
        REQUIRE(actualEvent.size.height == 600);
    }

    SECTION("Handle Window Focus Lost Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_FOCUS_LOST;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::LostFocus);
    }

    SECTION("Handle Window Focus Gained Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::GainedFocus);
    }

    SECTION("Handle Window Minimized Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_MINIMIZED;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Minimized);
    }

    SECTION("Handle Window Maximized Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_MAXIMIZED;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Maximized);
    }

    SECTION("Handle Window Restored Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_RESTORED;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Restored);
    }

    SECTION("Handle Window Mouse Entered Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_ENTER;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::MouseEntered);
    }

    SECTION("Handle Window Mouse Left Event")
    {
        sdlEvent.type         = SDL_WINDOWEVENT;
        sdlEvent.window.event = SDL_WINDOWEVENT_LEAVE;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::MouseLeft);
    }

    SECTION("Handle Quit Event")
    {
        sdlEvent.type = SDL_QUIT;
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        SDL_PushEvent(&sdlEvent);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == true);
        REQUIRE(actualEvent.type == e2d::Event::Quit);
    }

    SECTION("No Event Polled")
    {
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

        wasPolled = e2d::pollEvent(actualEvent);

        REQUIRE(wasPolled == false);
        REQUIRE(actualEvent.type == e2d::Event::Unknown);
    }
}
