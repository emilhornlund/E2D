/**
 * @file SDLKeyboardUtils.test.cpp
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

#include <E2D/Engine/SDLKeyboardUtils.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("toKeyCode", "[SDLKeyboardUtils]")
{
    SECTION("Translates SDL_Keycode to E2D Keyboard::Key")
    {
        REQUIRE(e2d::internal::toKeyCode(SDLK_a) == e2d::Keyboard::Key::A);
        REQUIRE(e2d::internal::toKeyCode(SDLK_b) == e2d::Keyboard::Key::B);
        REQUIRE(e2d::internal::toKeyCode(SDLK_c) == e2d::Keyboard::Key::C);
        REQUIRE(e2d::internal::toKeyCode(SDLK_d) == e2d::Keyboard::Key::D);
        REQUIRE(e2d::internal::toKeyCode(SDLK_e) == e2d::Keyboard::Key::E);
        REQUIRE(e2d::internal::toKeyCode(SDLK_f) == e2d::Keyboard::Key::F);
        REQUIRE(e2d::internal::toKeyCode(SDLK_g) == e2d::Keyboard::Key::G);
        REQUIRE(e2d::internal::toKeyCode(SDLK_h) == e2d::Keyboard::Key::H);
        REQUIRE(e2d::internal::toKeyCode(SDLK_i) == e2d::Keyboard::Key::I);
        REQUIRE(e2d::internal::toKeyCode(SDLK_j) == e2d::Keyboard::Key::J);
        REQUIRE(e2d::internal::toKeyCode(SDLK_k) == e2d::Keyboard::Key::K);
        REQUIRE(e2d::internal::toKeyCode(SDLK_l) == e2d::Keyboard::Key::L);
        REQUIRE(e2d::internal::toKeyCode(SDLK_m) == e2d::Keyboard::Key::M);
        REQUIRE(e2d::internal::toKeyCode(SDLK_n) == e2d::Keyboard::Key::N);
        REQUIRE(e2d::internal::toKeyCode(SDLK_o) == e2d::Keyboard::Key::O);
        REQUIRE(e2d::internal::toKeyCode(SDLK_p) == e2d::Keyboard::Key::P);
        REQUIRE(e2d::internal::toKeyCode(SDLK_q) == e2d::Keyboard::Key::Q);
        REQUIRE(e2d::internal::toKeyCode(SDLK_r) == e2d::Keyboard::Key::R);
        REQUIRE(e2d::internal::toKeyCode(SDLK_s) == e2d::Keyboard::Key::S);
        REQUIRE(e2d::internal::toKeyCode(SDLK_t) == e2d::Keyboard::Key::T);
        REQUIRE(e2d::internal::toKeyCode(SDLK_u) == e2d::Keyboard::Key::U);
        REQUIRE(e2d::internal::toKeyCode(SDLK_v) == e2d::Keyboard::Key::V);
        REQUIRE(e2d::internal::toKeyCode(SDLK_w) == e2d::Keyboard::Key::W);
        REQUIRE(e2d::internal::toKeyCode(SDLK_x) == e2d::Keyboard::Key::X);
        REQUIRE(e2d::internal::toKeyCode(SDLK_y) == e2d::Keyboard::Key::Y);
        REQUIRE(e2d::internal::toKeyCode(SDLK_z) == e2d::Keyboard::Key::Z);
        REQUIRE(e2d::internal::toKeyCode(SDLK_0) == e2d::Keyboard::Key::Num0);
        REQUIRE(e2d::internal::toKeyCode(SDLK_1) == e2d::Keyboard::Key::Num1);
        REQUIRE(e2d::internal::toKeyCode(SDLK_2) == e2d::Keyboard::Key::Num2);
        REQUIRE(e2d::internal::toKeyCode(SDLK_3) == e2d::Keyboard::Key::Num3);
        REQUIRE(e2d::internal::toKeyCode(SDLK_4) == e2d::Keyboard::Key::Num4);
        REQUIRE(e2d::internal::toKeyCode(SDLK_5) == e2d::Keyboard::Key::Num5);
        REQUIRE(e2d::internal::toKeyCode(SDLK_6) == e2d::Keyboard::Key::Num6);
        REQUIRE(e2d::internal::toKeyCode(SDLK_7) == e2d::Keyboard::Key::Num7);
        REQUIRE(e2d::internal::toKeyCode(SDLK_8) == e2d::Keyboard::Key::Num8);
        REQUIRE(e2d::internal::toKeyCode(SDLK_9) == e2d::Keyboard::Key::Num9);
        REQUIRE(e2d::internal::toKeyCode(SDLK_ESCAPE) == e2d::Keyboard::Key::Escape);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LCTRL) == e2d::Keyboard::Key::LControl);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LSHIFT) == e2d::Keyboard::Key::LShift);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LALT) == e2d::Keyboard::Key::LAlt);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LGUI) == e2d::Keyboard::Key::LSystem);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RCTRL) == e2d::Keyboard::Key::RControl);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RSHIFT) == e2d::Keyboard::Key::RShift);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RALT) == e2d::Keyboard::Key::RAlt);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RGUI) == e2d::Keyboard::Key::RSystem);
        REQUIRE(e2d::internal::toKeyCode(SDLK_MENU) == e2d::Keyboard::Key::Menu);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LEFTBRACKET) == e2d::Keyboard::Key::LBracket);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RIGHTBRACKET) == e2d::Keyboard::Key::RBracket);
        REQUIRE(e2d::internal::toKeyCode(SDLK_SEMICOLON) == e2d::Keyboard::Key::Semicolon);
        REQUIRE(e2d::internal::toKeyCode(SDLK_COMMA) == e2d::Keyboard::Key::Comma);
        REQUIRE(e2d::internal::toKeyCode(SDLK_PERIOD) == e2d::Keyboard::Key::Period);
        REQUIRE(e2d::internal::toKeyCode(SDLK_QUOTE) == e2d::Keyboard::Key::Apostrophe);
        REQUIRE(e2d::internal::toKeyCode(SDLK_SLASH) == e2d::Keyboard::Key::Slash);
        REQUIRE(e2d::internal::toKeyCode(SDLK_BACKSLASH) == e2d::Keyboard::Key::Backslash);
        REQUIRE(e2d::internal::toKeyCode(SDLK_BACKQUOTE) == e2d::Keyboard::Key::Grave);
        REQUIRE(e2d::internal::toKeyCode(SDLK_EQUALS) == e2d::Keyboard::Key::Equal);
        REQUIRE(e2d::internal::toKeyCode(SDLK_MINUS) == e2d::Keyboard::Key::Hyphen);
        REQUIRE(e2d::internal::toKeyCode(SDLK_SPACE) == e2d::Keyboard::Key::Space);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RETURN) == e2d::Keyboard::Key::Enter);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_ENTER) == e2d::Keyboard::Key::Enter);
        REQUIRE(e2d::internal::toKeyCode(SDLK_BACKSPACE) == e2d::Keyboard::Key::Backspace);
        REQUIRE(e2d::internal::toKeyCode(SDLK_TAB) == e2d::Keyboard::Key::Tab);
        REQUIRE(e2d::internal::toKeyCode(SDLK_PAGEUP) == e2d::Keyboard::Key::PageUp);
        REQUIRE(e2d::internal::toKeyCode(SDLK_PAGEDOWN) == e2d::Keyboard::Key::PageDown);
        REQUIRE(e2d::internal::toKeyCode(SDLK_END) == e2d::Keyboard::Key::End);
        REQUIRE(e2d::internal::toKeyCode(SDLK_HOME) == e2d::Keyboard::Key::Home);
        REQUIRE(e2d::internal::toKeyCode(SDLK_INSERT) == e2d::Keyboard::Key::Insert);
        REQUIRE(e2d::internal::toKeyCode(SDLK_DELETE) == e2d::Keyboard::Key::Delete);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_PLUS) == e2d::Keyboard::Key::Add);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_MINUS) == e2d::Keyboard::Key::Subtract);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_MULTIPLY) == e2d::Keyboard::Key::Multiply);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_DIVIDE) == e2d::Keyboard::Key::Divide);
        REQUIRE(e2d::internal::toKeyCode(SDLK_LEFT) == e2d::Keyboard::Key::Left);
        REQUIRE(e2d::internal::toKeyCode(SDLK_RIGHT) == e2d::Keyboard::Key::Right);
        REQUIRE(e2d::internal::toKeyCode(SDLK_UP) == e2d::Keyboard::Key::Up);
        REQUIRE(e2d::internal::toKeyCode(SDLK_DOWN) == e2d::Keyboard::Key::Down);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_0) == e2d::Keyboard::Key::Numpad0);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_1) == e2d::Keyboard::Key::Numpad1);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_2) == e2d::Keyboard::Key::Numpad2);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_3) == e2d::Keyboard::Key::Numpad3);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_4) == e2d::Keyboard::Key::Numpad4);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_5) == e2d::Keyboard::Key::Numpad5);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_6) == e2d::Keyboard::Key::Numpad6);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_7) == e2d::Keyboard::Key::Numpad7);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_8) == e2d::Keyboard::Key::Numpad8);
        REQUIRE(e2d::internal::toKeyCode(SDLK_KP_9) == e2d::Keyboard::Key::Numpad9);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F1) == e2d::Keyboard::Key::F1);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F2) == e2d::Keyboard::Key::F2);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F3) == e2d::Keyboard::Key::F3);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F4) == e2d::Keyboard::Key::F4);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F5) == e2d::Keyboard::Key::F5);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F6) == e2d::Keyboard::Key::F6);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F7) == e2d::Keyboard::Key::F7);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F8) == e2d::Keyboard::Key::F8);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F9) == e2d::Keyboard::Key::F9);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F10) == e2d::Keyboard::Key::F10);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F11) == e2d::Keyboard::Key::F11);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F12) == e2d::Keyboard::Key::F12);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F13) == e2d::Keyboard::Key::F13);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F14) == e2d::Keyboard::Key::F14);
        REQUIRE(e2d::internal::toKeyCode(SDLK_F15) == e2d::Keyboard::Key::F15);
        REQUIRE(e2d::internal::toKeyCode(SDLK_PAUSE) == e2d::Keyboard::Key::Pause);
        REQUIRE(e2d::internal::toKeyCode(SDLK_UNKNOWN) == e2d::Keyboard::Key::Unknown);
    }
}

TEST_CASE("toScancode", "[SDLKeyboardUtils]")
{
    SECTION("Translates SDL_Scancode to E2D Keyboard::Scancode")
    {
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_A) == e2d::Keyboard::Scancode::A);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_B) == e2d::Keyboard::Scancode::B);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_C) == e2d::Keyboard::Scancode::C);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_D) == e2d::Keyboard::Scancode::D);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_E) == e2d::Keyboard::Scancode::E);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F) == e2d::Keyboard::Scancode::F);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_G) == e2d::Keyboard::Scancode::G);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_H) == e2d::Keyboard::Scancode::H);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_I) == e2d::Keyboard::Scancode::I);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_J) == e2d::Keyboard::Scancode::J);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_K) == e2d::Keyboard::Scancode::K);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_L) == e2d::Keyboard::Scancode::L);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_M) == e2d::Keyboard::Scancode::M);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_N) == e2d::Keyboard::Scancode::N);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_O) == e2d::Keyboard::Scancode::O);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_P) == e2d::Keyboard::Scancode::P);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_Q) == e2d::Keyboard::Scancode::Q);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_R) == e2d::Keyboard::Scancode::R);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_S) == e2d::Keyboard::Scancode::S);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_T) == e2d::Keyboard::Scancode::T);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_U) == e2d::Keyboard::Scancode::U);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_V) == e2d::Keyboard::Scancode::V);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_W) == e2d::Keyboard::Scancode::W);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_X) == e2d::Keyboard::Scancode::X);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_Y) == e2d::Keyboard::Scancode::Y);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_Z) == e2d::Keyboard::Scancode::Z);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_1) == e2d::Keyboard::Scancode::Num1);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_2) == e2d::Keyboard::Scancode::Num2);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_3) == e2d::Keyboard::Scancode::Num3);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_4) == e2d::Keyboard::Scancode::Num4);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_5) == e2d::Keyboard::Scancode::Num5);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_6) == e2d::Keyboard::Scancode::Num6);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_7) == e2d::Keyboard::Scancode::Num7);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_8) == e2d::Keyboard::Scancode::Num8);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_9) == e2d::Keyboard::Scancode::Num9);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_0) == e2d::Keyboard::Scancode::Num0);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RETURN) == e2d::Keyboard::Scancode::Enter);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_ESCAPE) == e2d::Keyboard::Scancode::Escape);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_BACKSPACE) == e2d::Keyboard::Scancode::Backspace);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_TAB) == e2d::Keyboard::Scancode::Tab);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_SPACE) == e2d::Keyboard::Scancode::Space);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_MINUS) == e2d::Keyboard::Scancode::Hyphen);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_EQUALS) == e2d::Keyboard::Scancode::Equal);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LEFTBRACKET) == e2d::Keyboard::Scancode::LBracket);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RIGHTBRACKET) == e2d::Keyboard::Scancode::RBracket);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_BACKSLASH) == e2d::Keyboard::Scancode::Backslash);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_SEMICOLON) == e2d::Keyboard::Scancode::Semicolon);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_APOSTROPHE) == e2d::Keyboard::Scancode::Apostrophe);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_GRAVE) == e2d::Keyboard::Scancode::Grave);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_COMMA) == e2d::Keyboard::Scancode::Comma);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PERIOD) == e2d::Keyboard::Scancode::Period);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_SLASH) == e2d::Keyboard::Scancode::Slash);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F1) == e2d::Keyboard::Scancode::F1);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F2) == e2d::Keyboard::Scancode::F2);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F3) == e2d::Keyboard::Scancode::F3);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F4) == e2d::Keyboard::Scancode::F4);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F5) == e2d::Keyboard::Scancode::F5);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F6) == e2d::Keyboard::Scancode::F6);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F7) == e2d::Keyboard::Scancode::F7);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F8) == e2d::Keyboard::Scancode::F8);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F9) == e2d::Keyboard::Scancode::F9);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F10) == e2d::Keyboard::Scancode::F10);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F11) == e2d::Keyboard::Scancode::F11);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F12) == e2d::Keyboard::Scancode::F12);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F13) == e2d::Keyboard::Scancode::F13);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F14) == e2d::Keyboard::Scancode::F14);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F15) == e2d::Keyboard::Scancode::F15);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F16) == e2d::Keyboard::Scancode::F16);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F17) == e2d::Keyboard::Scancode::F17);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F18) == e2d::Keyboard::Scancode::F18);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F19) == e2d::Keyboard::Scancode::F19);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F20) == e2d::Keyboard::Scancode::F20);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F21) == e2d::Keyboard::Scancode::F21);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F22) == e2d::Keyboard::Scancode::F22);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F23) == e2d::Keyboard::Scancode::F23);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_F24) == e2d::Keyboard::Scancode::F24);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_CAPSLOCK) == e2d::Keyboard::Scancode::CapsLock);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PRINTSCREEN) == e2d::Keyboard::Scancode::PrintScreen);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_SCROLLLOCK) == e2d::Keyboard::Scancode::ScrollLock);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PAUSE) == e2d::Keyboard::Scancode::Pause);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_INSERT) == e2d::Keyboard::Scancode::Insert);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_HOME) == e2d::Keyboard::Scancode::Home);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PAGEUP) == e2d::Keyboard::Scancode::PageUp);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_DELETE) == e2d::Keyboard::Scancode::Delete);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_END) == e2d::Keyboard::Scancode::End);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PAGEDOWN) == e2d::Keyboard::Scancode::PageDown);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RIGHT) == e2d::Keyboard::Scancode::Right);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LEFT) == e2d::Keyboard::Scancode::Left);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_DOWN) == e2d::Keyboard::Scancode::Down);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_UP) == e2d::Keyboard::Scancode::Up);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_NUMLOCKCLEAR) == e2d::Keyboard::Scancode::NumLock);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_DIVIDE) == e2d::Keyboard::Scancode::NumpadDivide);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_MULTIPLY) == e2d::Keyboard::Scancode::NumpadMultiply);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_MINUS) == e2d::Keyboard::Scancode::NumpadMinus);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_PLUS) == e2d::Keyboard::Scancode::NumpadPlus);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_EQUALS) == e2d::Keyboard::Scancode::NumpadEqual);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_ENTER) == e2d::Keyboard::Scancode::NumpadEnter);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_DECIMAL) == e2d::Keyboard::Scancode::NumpadDecimal);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_1) == e2d::Keyboard::Scancode::Numpad1);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_2) == e2d::Keyboard::Scancode::Numpad2);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_3) == e2d::Keyboard::Scancode::Numpad3);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_4) == e2d::Keyboard::Scancode::Numpad4);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_5) == e2d::Keyboard::Scancode::Numpad5);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_6) == e2d::Keyboard::Scancode::Numpad6);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_7) == e2d::Keyboard::Scancode::Numpad7);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_8) == e2d::Keyboard::Scancode::Numpad8);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_9) == e2d::Keyboard::Scancode::Numpad9);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_KP_0) == e2d::Keyboard::Scancode::Numpad0);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_NONUSBACKSLASH) == e2d::Keyboard::Scancode::NonUsBackslash);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_APPLICATION) == e2d::Keyboard::Scancode::Application);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_EXECUTE) == e2d::Keyboard::Scancode::Execute);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_MODE) == e2d::Keyboard::Scancode::ModeChange);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_HELP) == e2d::Keyboard::Scancode::Help);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_MENU) == e2d::Keyboard::Scancode::Menu);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_SELECT) == e2d::Keyboard::Scancode::Select);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AGAIN) == e2d::Keyboard::Scancode::Redo);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_UNDO) == e2d::Keyboard::Scancode::Undo);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_CUT) == e2d::Keyboard::Scancode::Cut);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_COPY) == e2d::Keyboard::Scancode::Copy);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_PASTE) == e2d::Keyboard::Scancode::Paste);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AUDIOMUTE) == e2d::Keyboard::Scancode::VolumeMute);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_VOLUMEUP) == e2d::Keyboard::Scancode::VolumeUp);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_VOLUMEDOWN) == e2d::Keyboard::Scancode::VolumeDown);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AUDIOPLAY) == e2d::Keyboard::Scancode::MediaPlayPause);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AUDIOSTOP) == e2d::Keyboard::Scancode::MediaStop);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AUDIONEXT) == e2d::Keyboard::Scancode::MediaNextTrack);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AUDIOPREV) == e2d::Keyboard::Scancode::MediaPreviousTrack);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LCTRL) == e2d::Keyboard::Scancode::LControl);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LSHIFT) == e2d::Keyboard::Scancode::LShift);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LALT) == e2d::Keyboard::Scancode::LAlt);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_LGUI) == e2d::Keyboard::Scancode::LSystem);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RCTRL) == e2d::Keyboard::Scancode::RControl);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RSHIFT) == e2d::Keyboard::Scancode::RShift);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RALT) == e2d::Keyboard::Scancode::RAlt);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_RGUI) == e2d::Keyboard::Scancode::RSystem);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_BACK) == e2d::Keyboard::Scancode::Back);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_FORWARD) == e2d::Keyboard::Scancode::Forward);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_REFRESH) == e2d::Keyboard::Scancode::Refresh);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_STOP) == e2d::Keyboard::Scancode::Stop);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_SEARCH) == e2d::Keyboard::Scancode::Search);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_BOOKMARKS) == e2d::Keyboard::Scancode::Favorites);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_AC_HOME) == e2d::Keyboard::Scancode::HomePage);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_APP1) == e2d::Keyboard::Scancode::LaunchApplication1);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_APP2) == e2d::Keyboard::Scancode::LaunchApplication2);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_MAIL) == e2d::Keyboard::Scancode::LaunchMail);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_MEDIASELECT) == e2d::Keyboard::Scancode::LaunchMediaSelect);
        REQUIRE(e2d::internal::toScancode(SDL_SCANCODE_UNKNOWN) == e2d::Keyboard::Scancode::Unknown);
    }
}
