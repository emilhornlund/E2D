/**
 * SDLKeyboardUtils.cpp
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

e2d::Keyboard::Key e2d::internal::toKeyCode(const SDL_Keycode& sdlKeyCode)
{
    switch (sdlKeyCode)
    {
        case SDLK_a:
            return e2d::Keyboard::Key::A; // The A key
        case SDLK_b:
            return e2d::Keyboard::Key::B; // The B key
        case SDLK_c:
            return e2d::Keyboard::Key::C; // The C key
        case SDLK_d:
            return e2d::Keyboard::Key::D; // The D key
        case SDLK_e:
            return e2d::Keyboard::Key::E; // The E key
        case SDLK_f:
            return e2d::Keyboard::Key::F; // The F key
        case SDLK_g:
            return e2d::Keyboard::Key::G; // The G key
        case SDLK_h:
            return e2d::Keyboard::Key::H; // The H key
        case SDLK_i:
            return e2d::Keyboard::Key::I; // The I key
        case SDLK_j:
            return e2d::Keyboard::Key::J; // The J key
        case SDLK_k:
            return e2d::Keyboard::Key::K; // The K key
        case SDLK_l:
            return e2d::Keyboard::Key::L; // The L key
        case SDLK_m:
            return e2d::Keyboard::Key::M; // The M key
        case SDLK_n:
            return e2d::Keyboard::Key::N; // The N key
        case SDLK_o:
            return e2d::Keyboard::Key::O; // The O key
        case SDLK_p:
            return e2d::Keyboard::Key::P; // The P key
        case SDLK_q:
            return e2d::Keyboard::Key::Q; // The Q key
        case SDLK_r:
            return e2d::Keyboard::Key::R; // The R key
        case SDLK_s:
            return e2d::Keyboard::Key::S; // The S key
        case SDLK_t:
            return e2d::Keyboard::Key::T; // The T key
        case SDLK_u:
            return e2d::Keyboard::Key::U; // The U key
        case SDLK_v:
            return e2d::Keyboard::Key::V; // The V key
        case SDLK_w:
            return e2d::Keyboard::Key::W; // The W key
        case SDLK_x:
            return e2d::Keyboard::Key::X; // The X key
        case SDLK_y:
            return e2d::Keyboard::Key::Y; // The Y key
        case SDLK_z:
            return e2d::Keyboard::Key::Z; // The Z key
        case SDLK_0:
            return e2d::Keyboard::Key::Num0; // The 0 key
        case SDLK_1:
            return e2d::Keyboard::Key::Num1; // The 1 key
        case SDLK_2:
            return e2d::Keyboard::Key::Num2; // The 2 key
        case SDLK_3:
            return e2d::Keyboard::Key::Num3; // The 3 key
        case SDLK_4:
            return e2d::Keyboard::Key::Num4; // The 4 key
        case SDLK_5:
            return e2d::Keyboard::Key::Num5; // The 5 key
        case SDLK_6:
            return e2d::Keyboard::Key::Num6; // The 6 key
        case SDLK_7:
            return e2d::Keyboard::Key::Num7; // The 7 key
        case SDLK_8:
            return e2d::Keyboard::Key::Num8; // The 8 key
        case SDLK_9:
            return e2d::Keyboard::Key::Num9; // The 9 key
        case SDLK_ESCAPE:
            return e2d::Keyboard::Key::Escape; // The Escape key
        case SDLK_LCTRL:
            return e2d::Keyboard::Key::LControl; // The left Control key
        case SDLK_LSHIFT:
            return e2d::Keyboard::Key::LShift; // The left Shift key
        case SDLK_LALT:
            return e2d::Keyboard::Key::LAlt; // The left Alt key
        case SDLK_LGUI:
            return e2d::Keyboard::Key::LSystem; // The left OS specific key: window (Windows and Linux), apple (macOS), ...
        case SDLK_RCTRL:
            return e2d::Keyboard::Key::RControl; // The right Control key
        case SDLK_RSHIFT:
            return e2d::Keyboard::Key::RShift; // The right Shift key
        case SDLK_RALT:
            return e2d::Keyboard::Key::RAlt; // The right Alt key
        case SDLK_RGUI:
            return e2d::Keyboard::Key::RSystem; // The right OS specific key: window (Windows and Linux), apple (macOS), ...
        case SDLK_MENU:
            return e2d::Keyboard::Key::Menu; // The Menu key
        case SDLK_LEFTBRACKET:
            return e2d::Keyboard::Key::LBracket; // The [ key
        case SDLK_RIGHTBRACKET:
            return e2d::Keyboard::Key::RBracket; // The ] key
        case SDLK_SEMICOLON:
            return e2d::Keyboard::Key::Semicolon; // The ; key
        case SDLK_COMMA:
            return e2d::Keyboard::Key::Comma; // The , key
        case SDLK_PERIOD:
            return e2d::Keyboard::Key::Period; // The . key
        case SDLK_QUOTE:
            return e2d::Keyboard::Key::Apostrophe; // The ' key
        case SDLK_SLASH:
            return e2d::Keyboard::Key::Slash; // The / key
        case SDLK_BACKSLASH:
            return e2d::Keyboard::Key::Backslash; // The \ key
        case SDLK_BACKQUOTE:
            return e2d::Keyboard::Key::Grave; // The ` key
        case SDLK_EQUALS:
            return e2d::Keyboard::Key::Equal; // The = key
        case SDLK_MINUS:
            return e2d::Keyboard::Key::Hyphen; // The - key (hyphen)
        case SDLK_SPACE:
            return e2d::Keyboard::Key::Space; // The Space key
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
            return e2d::Keyboard::Key::Enter; // The Enter/Return keys
        case SDLK_BACKSPACE:
            return e2d::Keyboard::Key::Backspace; // The Backspace key
        case SDLK_TAB:
            return e2d::Keyboard::Key::Tab; // The Tabulation key
        case SDLK_PAGEUP:
            return e2d::Keyboard::Key::PageUp; // The Page up key
        case SDLK_PAGEDOWN:
            return e2d::Keyboard::Key::PageDown; // The Page down key
        case SDLK_END:
            return e2d::Keyboard::Key::End; // The End key
        case SDLK_HOME:
            return e2d::Keyboard::Key::Home; // The Home key
        case SDLK_INSERT:
            return e2d::Keyboard::Key::Insert; // The Insert key
        case SDLK_DELETE:
            return e2d::Keyboard::Key::Delete; // The Delete key
        case SDLK_KP_PLUS:
            return e2d::Keyboard::Key::Add; // The + key
        case SDLK_KP_MINUS:
            return e2d::Keyboard::Key::Subtract; // The - key (minus, usually from numpad)
        case SDLK_KP_MULTIPLY:
            return e2d::Keyboard::Key::Multiply; // The * key
        case SDLK_KP_DIVIDE:
            return e2d::Keyboard::Key::Divide; // The / key
        case SDLK_LEFT:
            return e2d::Keyboard::Key::Left; // Left arrow
        case SDLK_RIGHT:
            return e2d::Keyboard::Key::Right; // Right arrow
        case SDLK_UP:
            return e2d::Keyboard::Key::Up; // Up arrow
        case SDLK_DOWN:
            return e2d::Keyboard::Key::Down; // Down arrow
        case SDLK_KP_0:
            return e2d::Keyboard::Key::Numpad0; // The numpad 0 key
        case SDLK_KP_1:
            return e2d::Keyboard::Key::Numpad1; // The numpad 1 key
        case SDLK_KP_2:
            return e2d::Keyboard::Key::Numpad2; // The numpad 2 key
        case SDLK_KP_3:
            return e2d::Keyboard::Key::Numpad3; // The numpad 3 key
        case SDLK_KP_4:
            return e2d::Keyboard::Key::Numpad4; // The numpad 4 key
        case SDLK_KP_5:
            return e2d::Keyboard::Key::Numpad5; // The numpad 5 key
        case SDLK_KP_6:
            return e2d::Keyboard::Key::Numpad6; // The numpad 6 key
        case SDLK_KP_7:
            return e2d::Keyboard::Key::Numpad7; // The numpad 7 key
        case SDLK_KP_8:
            return e2d::Keyboard::Key::Numpad8; // The numpad 8 key
        case SDLK_KP_9:
            return e2d::Keyboard::Key::Numpad9; // The numpad 9 key
        case SDLK_F1:
            return e2d::Keyboard::Key::F1; // The F1 key
        case SDLK_F2:
            return e2d::Keyboard::Key::F2; // The F2 key
        case SDLK_F3:
            return e2d::Keyboard::Key::F3; // The F3 key
        case SDLK_F4:
            return e2d::Keyboard::Key::F4; // The F4 key
        case SDLK_F5:
            return e2d::Keyboard::Key::F5; // The F5 key
        case SDLK_F6:
            return e2d::Keyboard::Key::F6; // The F6 key
        case SDLK_F7:
            return e2d::Keyboard::Key::F7; // The F7 key
        case SDLK_F8:
            return e2d::Keyboard::Key::F8; // The F8 key
        case SDLK_F9:
            return e2d::Keyboard::Key::F9; // The F9 key
        case SDLK_F10:
            return e2d::Keyboard::Key::F10; // The F10 key
        case SDLK_F11:
            return e2d::Keyboard::Key::F11; // The F11 key
        case SDLK_F12:
            return e2d::Keyboard::Key::F12; // The F12 key
        case SDLK_F13:
            return e2d::Keyboard::Key::F13; // The F13 key
        case SDLK_F14:
            return e2d::Keyboard::Key::F14; // The F14 key
        case SDLK_F15:
            return e2d::Keyboard::Key::F15; // The F15 key
        case SDLK_PAUSE:
            return e2d::Keyboard::Key::Pause; // The Pause key
        default:
            return e2d::Keyboard::Key::Unknown;
    }
}

e2d::Keyboard::Scancode e2d::internal::toScancode(const SDL_Scancode& sdlScanCode)
{
    switch (sdlScanCode)
    {
        case SDL_SCANCODE_A:
            return e2d::Keyboard::Scancode::A; // Keyboard a and A key
        case SDL_SCANCODE_B:
            return e2d::Keyboard::Scancode::B; // Keyboard b and B key
        case SDL_SCANCODE_C:
            return e2d::Keyboard::Scancode::C; // Keyboard c and C key
        case SDL_SCANCODE_D:
            return e2d::Keyboard::Scancode::D; // Keyboard d and D key
        case SDL_SCANCODE_E:
            return e2d::Keyboard::Scancode::E; // Keyboard e and E key
        case SDL_SCANCODE_F:
            return e2d::Keyboard::Scancode::F; // Keyboard f and F key
        case SDL_SCANCODE_G:
            return e2d::Keyboard::Scancode::G; // Keyboard g and G key
        case SDL_SCANCODE_H:
            return e2d::Keyboard::Scancode::H; // Keyboard h and H key
        case SDL_SCANCODE_I:
            return e2d::Keyboard::Scancode::I; // Keyboard i and I key
        case SDL_SCANCODE_J:
            return e2d::Keyboard::Scancode::J; // Keyboard j and J key
        case SDL_SCANCODE_K:
            return e2d::Keyboard::Scancode::K; // Keyboard k and K key
        case SDL_SCANCODE_L:
            return e2d::Keyboard::Scancode::L; // Keyboard l and L key
        case SDL_SCANCODE_M:
            return e2d::Keyboard::Scancode::M; // Keyboard m and M key
        case SDL_SCANCODE_N:
            return e2d::Keyboard::Scancode::N; // Keyboard n and N key
        case SDL_SCANCODE_O:
            return e2d::Keyboard::Scancode::O; // Keyboard o and O key
        case SDL_SCANCODE_P:
            return e2d::Keyboard::Scancode::P; // Keyboard p and P key
        case SDL_SCANCODE_Q:
            return e2d::Keyboard::Scancode::Q; // Keyboard q and Q key
        case SDL_SCANCODE_R:
            return e2d::Keyboard::Scancode::R; // Keyboard r and R key
        case SDL_SCANCODE_S:
            return e2d::Keyboard::Scancode::S; // Keyboard s and S key
        case SDL_SCANCODE_T:
            return e2d::Keyboard::Scancode::T; // Keyboard t and T key
        case SDL_SCANCODE_U:
            return e2d::Keyboard::Scancode::U; // Keyboard u and U key
        case SDL_SCANCODE_V:
            return e2d::Keyboard::Scancode::V; // Keyboard v and V key
        case SDL_SCANCODE_W:
            return e2d::Keyboard::Scancode::W; // Keyboard w and W key
        case SDL_SCANCODE_X:
            return e2d::Keyboard::Scancode::X; // Keyboard x and X key
        case SDL_SCANCODE_Y:
            return e2d::Keyboard::Scancode::Y; // Keyboard y and Y key
        case SDL_SCANCODE_Z:
            return e2d::Keyboard::Scancode::Z; // Keyboard z and Z key
        case SDL_SCANCODE_1:
            return e2d::Keyboard::Scancode::Num1; // Keyboard 1 and ! key
        case SDL_SCANCODE_2:
            return e2d::Keyboard::Scancode::Num2; // Keyboard 2 and @ key
        case SDL_SCANCODE_3:
            return e2d::Keyboard::Scancode::Num3; // Keyboard 3 and # key
        case SDL_SCANCODE_4:
            return e2d::Keyboard::Scancode::Num4; // Keyboard 4 and $ key
        case SDL_SCANCODE_5:
            return e2d::Keyboard::Scancode::Num5; // Keyboard 5 and % key
        case SDL_SCANCODE_6:
            return e2d::Keyboard::Scancode::Num6; // Keyboard 6 and ^ key
        case SDL_SCANCODE_7:
            return e2d::Keyboard::Scancode::Num7; // Keyboard 7 and & key
        case SDL_SCANCODE_8:
            return e2d::Keyboard::Scancode::Num8; // Keyboard 8 and * key
        case SDL_SCANCODE_9:
            return e2d::Keyboard::Scancode::Num9; // Keyboard 9 and ) key
        case SDL_SCANCODE_0:
            return e2d::Keyboard::Scancode::Num0; // Keyboard 0 and ) key
        case SDL_SCANCODE_RETURN:
            return e2d::Keyboard::Scancode::Enter; // Keyboard Enter/Return key
        case SDL_SCANCODE_ESCAPE:
            return e2d::Keyboard::Scancode::Escape; // Keyboard Escape key
        case SDL_SCANCODE_BACKSPACE:
            return e2d::Keyboard::Scancode::Backspace; // Keyboard Backspace key
        case SDL_SCANCODE_TAB:
            return e2d::Keyboard::Scancode::Tab; // Keyboard Tab key
        case SDL_SCANCODE_SPACE:
            return e2d::Keyboard::Scancode::Space; // Keyboard Space key
        case SDL_SCANCODE_MINUS:
            return e2d::Keyboard::Scancode::Hyphen; // Keyboard - and _ key
        case SDL_SCANCODE_EQUALS:
            return e2d::Keyboard::Scancode::Equal; // Keyboard = and + key
        case SDL_SCANCODE_LEFTBRACKET:
            return e2d::Keyboard::Scancode::LBracket; // Keyboard [ and { key
        case SDL_SCANCODE_RIGHTBRACKET:
            return e2d::Keyboard::Scancode::RBracket; // Keyboard ] and } key
        case SDL_SCANCODE_BACKSLASH:
            return e2d::Keyboard::Scancode::Backslash; // Keyboard \ and | key
        case SDL_SCANCODE_SEMICOLON:
            return e2d::Keyboard::Scancode::Semicolon; // Keyboard ; and : key
        case SDL_SCANCODE_APOSTROPHE:
            return e2d::Keyboard::Scancode::Apostrophe; // Keyboard ' and " key
        case SDL_SCANCODE_GRAVE:
            return e2d::Keyboard::Scancode::Grave; // Keyboard ` and ~ key
        case SDL_SCANCODE_COMMA:
            return e2d::Keyboard::Scancode::Comma; // Keyboard , and < key
        case SDL_SCANCODE_PERIOD:
            return e2d::Keyboard::Scancode::Period; // Keyboard . and > key
        case SDL_SCANCODE_SLASH:
            return e2d::Keyboard::Scancode::Slash; // Keyboard / and ? key
        case SDL_SCANCODE_F1:
            return e2d::Keyboard::Scancode::F1; // Keyboard F1 key
        case SDL_SCANCODE_F2:
            return e2d::Keyboard::Scancode::F2; // Keyboard F2 key
        case SDL_SCANCODE_F3:
            return e2d::Keyboard::Scancode::F3; // Keyboard F3 key
        case SDL_SCANCODE_F4:
            return e2d::Keyboard::Scancode::F4; // Keyboard F4 key
        case SDL_SCANCODE_F5:
            return e2d::Keyboard::Scancode::F5; // Keyboard F5 key
        case SDL_SCANCODE_F6:
            return e2d::Keyboard::Scancode::F6; // Keyboard F6 key
        case SDL_SCANCODE_F7:
            return e2d::Keyboard::Scancode::F7; // Keyboard F7 key
        case SDL_SCANCODE_F8:
            return e2d::Keyboard::Scancode::F8; // Keyboard F8 key
        case SDL_SCANCODE_F9:
            return e2d::Keyboard::Scancode::F9; // Keyboard F9 key
        case SDL_SCANCODE_F10:
            return e2d::Keyboard::Scancode::F10; // Keyboard F10 key
        case SDL_SCANCODE_F11:
            return e2d::Keyboard::Scancode::F11; // Keyboard F11 key
        case SDL_SCANCODE_F12:
            return e2d::Keyboard::Scancode::F12; // Keyboard F12 key
        case SDL_SCANCODE_F13:
            return e2d::Keyboard::Scancode::F13; // Keyboard F13 key
        case SDL_SCANCODE_F14:
            return e2d::Keyboard::Scancode::F14; // Keyboard F14 key
        case SDL_SCANCODE_F15:
            return e2d::Keyboard::Scancode::F15; // Keyboard F15 key
        case SDL_SCANCODE_F16:
            return e2d::Keyboard::Scancode::F16; // Keyboard F16 key
        case SDL_SCANCODE_F17:
            return e2d::Keyboard::Scancode::F17; // Keyboard F17 key
        case SDL_SCANCODE_F18:
            return e2d::Keyboard::Scancode::F18; // Keyboard F18 key
        case SDL_SCANCODE_F19:
            return e2d::Keyboard::Scancode::F19; // Keyboard F19 key
        case SDL_SCANCODE_F20:
            return e2d::Keyboard::Scancode::F20; // Keyboard F20 key
        case SDL_SCANCODE_F21:
            return e2d::Keyboard::Scancode::F21; // Keyboard F21 key
        case SDL_SCANCODE_F22:
            return e2d::Keyboard::Scancode::F22; // Keyboard F22 key
        case SDL_SCANCODE_F23:
            return e2d::Keyboard::Scancode::F23; // Keyboard F23 key
        case SDL_SCANCODE_F24:
            return e2d::Keyboard::Scancode::F24; // Keyboard F24 key
        case SDL_SCANCODE_CAPSLOCK:
            return e2d::Keyboard::Scancode::CapsLock; // Keyboard Caps Lock key
        case SDL_SCANCODE_PRINTSCREEN:
            return e2d::Keyboard::Scancode::PrintScreen; // Keyboard Print Screen key
        case SDL_SCANCODE_SCROLLLOCK:
            return e2d::Keyboard::Scancode::ScrollLock; // Keyboard Scroll Lock key
        case SDL_SCANCODE_PAUSE:
            return e2d::Keyboard::Scancode::Pause; // Keyboard Pause key
        case SDL_SCANCODE_INSERT:
            return e2d::Keyboard::Scancode::Insert; // Keyboard Insert key
        case SDL_SCANCODE_HOME:
            return e2d::Keyboard::Scancode::Home; // Keyboard Home key
        case SDL_SCANCODE_PAGEUP:
            return e2d::Keyboard::Scancode::PageUp; // Keyboard Page Up key
        case SDL_SCANCODE_DELETE:
            return e2d::Keyboard::Scancode::Delete; // Keyboard Delete Forward key
        case SDL_SCANCODE_END:
            return e2d::Keyboard::Scancode::End; // Keyboard End key
        case SDL_SCANCODE_PAGEDOWN:
            return e2d::Keyboard::Scancode::PageDown; // Keyboard Page Down key
        case SDL_SCANCODE_RIGHT:
            return e2d::Keyboard::Scancode::Right; // Keyboard Right Arrow key
        case SDL_SCANCODE_LEFT:
            return e2d::Keyboard::Scancode::Left; // Keyboard Left Arrow key
        case SDL_SCANCODE_DOWN:
            return e2d::Keyboard::Scancode::Down; // Keyboard Down Arrow key
        case SDL_SCANCODE_UP:
            return e2d::Keyboard::Scancode::Up; // Keyboard Up Arrow key
        case SDL_SCANCODE_NUMLOCKCLEAR:
            return e2d::Keyboard::Scancode::NumLock; // Keypad Num Lock and Clear key
        case SDL_SCANCODE_KP_DIVIDE:
            return e2d::Keyboard::Scancode::NumpadDivide; // Keypad / key
        case SDL_SCANCODE_KP_MULTIPLY:
            return e2d::Keyboard::Scancode::NumpadMultiply; // Keypad * key
        case SDL_SCANCODE_KP_MINUS:
            return e2d::Keyboard::Scancode::NumpadMinus; // Keypad - key
        case SDL_SCANCODE_KP_PLUS:
            return e2d::Keyboard::Scancode::NumpadPlus; // Keypad + key
        case SDL_SCANCODE_KP_EQUALS:
            return e2d::Keyboard::Scancode::NumpadEqual; // Keypad = key
        case SDL_SCANCODE_KP_ENTER:
            return e2d::Keyboard::Scancode::NumpadEnter; // Keypad Enter/Return key
        case SDL_SCANCODE_KP_DECIMAL:
            return e2d::Keyboard::Scancode::NumpadDecimal; // Keypad . and Delete key
        case SDL_SCANCODE_KP_1:
            return e2d::Keyboard::Scancode::Numpad1; // Keypad 1 and End key
        case SDL_SCANCODE_KP_2:
            return e2d::Keyboard::Scancode::Numpad2; // Keypad 2 and Down Arrow key
        case SDL_SCANCODE_KP_3:
            return e2d::Keyboard::Scancode::Numpad3; // Keypad 3 and Page Down key
        case SDL_SCANCODE_KP_4:
            return e2d::Keyboard::Scancode::Numpad4; // Keypad 4 and Left Arrow key
        case SDL_SCANCODE_KP_5:
            return e2d::Keyboard::Scancode::Numpad5; // Keypad 5 key
        case SDL_SCANCODE_KP_6:
            return e2d::Keyboard::Scancode::Numpad6; // Keypad 6 and Right Arrow key
        case SDL_SCANCODE_KP_7:
            return e2d::Keyboard::Scancode::Numpad7; // Keypad 7 and Home key
        case SDL_SCANCODE_KP_8:
            return e2d::Keyboard::Scancode::Numpad8; // Keypad 8 and Up Arrow key
        case SDL_SCANCODE_KP_9:
            return e2d::Keyboard::Scancode::Numpad9; // Keypad 9 and Page Up key
        case SDL_SCANCODE_KP_0:
            return e2d::Keyboard::Scancode::Numpad0; // Keypad 0 and Insert key
        case SDL_SCANCODE_NONUSBACKSLASH:
            return e2d::Keyboard::Scancode::NonUsBackslash; // Keyboard Non-US \ and | key
        case SDL_SCANCODE_APPLICATION:
            return e2d::Keyboard::Scancode::Application; // Keyboard Application key
        case SDL_SCANCODE_EXECUTE:
            return e2d::Keyboard::Scancode::Execute; // Keyboard Execute key
        case SDL_SCANCODE_MODE:
            return e2d::Keyboard::Scancode::ModeChange; // Keyboard Mode Change key
        case SDL_SCANCODE_HELP:
            return e2d::Keyboard::Scancode::Help; // Keyboard Help key
        case SDL_SCANCODE_MENU:
            return e2d::Keyboard::Scancode::Menu; // Keyboard Menu key
        case SDL_SCANCODE_SELECT:
            return e2d::Keyboard::Scancode::Select; // Keyboard Select key
        case SDL_SCANCODE_AGAIN:
            return e2d::Keyboard::Scancode::Redo; // Keyboard Redo key
        case SDL_SCANCODE_UNDO:
            return e2d::Keyboard::Scancode::Undo; // Keyboard Undo key
        case SDL_SCANCODE_CUT:
            return e2d::Keyboard::Scancode::Cut; // Keyboard Cut key
        case SDL_SCANCODE_COPY:
            return e2d::Keyboard::Scancode::Copy; // Keyboard Copy key
        case SDL_SCANCODE_PASTE:
            return e2d::Keyboard::Scancode::Paste; // Keyboard Paste key
        case SDL_SCANCODE_AUDIOMUTE:
            return e2d::Keyboard::Scancode::VolumeMute; // Keyboard Volume Mute key
        case SDL_SCANCODE_VOLUMEUP:
            return e2d::Keyboard::Scancode::VolumeUp; // Keyboard Volume Up key
        case SDL_SCANCODE_VOLUMEDOWN:
            return e2d::Keyboard::Scancode::VolumeDown; // Keyboard Volume Down key
        case SDL_SCANCODE_AUDIOPLAY:
            return e2d::Keyboard::Scancode::MediaPlayPause; // Keyboard Media Play Pause key
        case SDL_SCANCODE_AUDIOSTOP:
            return e2d::Keyboard::Scancode::MediaStop; // Keyboard Media Stop key
        case SDL_SCANCODE_AUDIONEXT:
            return e2d::Keyboard::Scancode::MediaNextTrack; // Keyboard Media Next Track key
        case SDL_SCANCODE_AUDIOPREV:
            return e2d::Keyboard::Scancode::MediaPreviousTrack; // Keyboard Media Previous Track key
        case SDL_SCANCODE_LCTRL:
            return e2d::Keyboard::Scancode::LControl; // Keyboard Left Control key
        case SDL_SCANCODE_LSHIFT:
            return e2d::Keyboard::Scancode::LShift; // Keyboard Left Shift key
        case SDL_SCANCODE_LALT:
            return e2d::Keyboard::Scancode::LAlt; // Keyboard Left Alt key
        case SDL_SCANCODE_LGUI:
            return e2d::Keyboard::Scancode::LSystem; // Keyboard Left System key
        case SDL_SCANCODE_RCTRL:
            return e2d::Keyboard::Scancode::RControl; // Keyboard Right Control key
        case SDL_SCANCODE_RSHIFT:
            return e2d::Keyboard::Scancode::RShift; // Keyboard Right Shift key
        case SDL_SCANCODE_RALT:
            return e2d::Keyboard::Scancode::RAlt; // Keyboard Right Alt key
        case SDL_SCANCODE_RGUI:
            return e2d::Keyboard::Scancode::RSystem; // Keyboard Right System key
        case SDL_SCANCODE_AC_BACK:
            return e2d::Keyboard::Scancode::Back; // Keyboard Back key
        case SDL_SCANCODE_AC_FORWARD:
            return e2d::Keyboard::Scancode::Forward; // Keyboard Forward key
        case SDL_SCANCODE_AC_REFRESH:
            return e2d::Keyboard::Scancode::Refresh; // Keyboard Refresh key
        case SDL_SCANCODE_AC_STOP:
            return e2d::Keyboard::Scancode::Stop; // Keyboard Stop key
        case SDL_SCANCODE_AC_SEARCH:
            return e2d::Keyboard::Scancode::Search; // Keyboard Search key
        case SDL_SCANCODE_AC_BOOKMARKS:
            return e2d::Keyboard::Scancode::Favorites; // Keyboard Favorites key
        case SDL_SCANCODE_AC_HOME:
            return e2d::Keyboard::Scancode::HomePage; // Keyboard Home Page key
        case SDL_SCANCODE_APP1:
            return e2d::Keyboard::Scancode::LaunchApplication1; // Keyboard Launch Application 1 key
        case SDL_SCANCODE_APP2:
            return e2d::Keyboard::Scancode::LaunchApplication2; // Keyboard Launch Application 2 key
        case SDL_SCANCODE_MAIL:
            return e2d::Keyboard::Scancode::LaunchMail; // Keyboard Launch Mail key
        case SDL_SCANCODE_MEDIASELECT:
            return e2d::Keyboard::Scancode::LaunchMediaSelect; // Keyboard Launch Media Select key
        default:
            return Keyboard::Scancode::Unknown; // Unknown scancode
    }
}
