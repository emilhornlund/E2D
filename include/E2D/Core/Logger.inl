/**
* @file Logger.inl
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

template <typename... Args>
void e2d::Logger::log(LogLevel level, const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    getInstance().logImpl(level, Formatter::format(message, std::forward<Args>(args)...));
}

template <typename... Args>
void e2d::log::debug(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    Logger::log(E2D_LOG_LEVEL_DEBUG, message, std::forward<Args>(args)...);
}

template <typename... Args>
void e2d::log::info(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    Logger::log(E2D_LOG_LEVEL_INFO, message, std::forward<Args>(args)...);
}

template <typename... Args>
void e2d::log::warn(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    Logger::log(E2D_LOG_LEVEL_WARN, message, std::forward<Args>(args)...);
}

template <typename... Args>
void e2d::log::error(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    Logger::log(E2D_LOG_LEVEL_ERROR, message, std::forward<Args>(args)...);
}
