/**
 * @file LoggerImpl.cpp
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

#include <E2D/Core/Logger.hpp>

#include <chrono>
#include <ctime>

#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

// ANSI color codes
#define RESET_COLOR  "\033[0m"
#define BLUE_COLOR   "\033[34m"
#define GREEN_COLOR  "\033[32m"
#define ORANGE_COLOR "\033[33m"
#define RED_COLOR    "\033[31m"

namespace
{
void enableVirtualTerminalProcessing()
{
#ifdef _WIN32
    // Enable VT100 on Windows 10 and later
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}
} // namespace

e2d::internal::LoggerImpl::LoggerImpl()
{
#ifdef E2D_DEBUG
    this->m_currentLevel = E2D_LOG_LEVEL_DEBUG;
#endif
    enableVirtualTerminalProcessing();
}

e2d::internal::LoggerImpl& e2d::internal::LoggerImpl::getInstance()
{
    static LoggerImpl instance;
    return instance;
}

void e2d::internal::LoggerImpl::logImpl(LogLevel level, const std::string& message)
{
    if (level < this->m_currentLevel)
    {
        return;
    }

    std::ostringstream logStream;
    logStream << "[" << currentDateTime() << "] " << getColorForLogLevel(level) << padLogLevel(logLevelToString(level))
              << " " << RESET_COLOR << message << "\n";

    const std::lock_guard<std::mutex> lock(this->m_mutex);

    std::cout << logStream.str();
}

std::string e2d::internal::LoggerImpl::currentDateTime()
{
    auto       now       = std::chrono::system_clock::now();
    auto       ms        = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto nowC      = std::chrono::system_clock::to_time_t(now);
    const auto localTime = *std::localtime(&nowC);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %X") << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

std::string e2d::internal::LoggerImpl::logLevelToString(e2d::internal::LogLevel level)
{
    switch (level)
    {
        case E2D_LOG_LEVEL_DEBUG:
            return "DEBUG";
        case E2D_LOG_LEVEL_INFO:
            return "INFO";
        case E2D_LOG_LEVEL_WARN:
            return "WARN";
        case E2D_LOG_LEVEL_ERROR:
            return "ERROR";
    }
    return "UNKNOWN";
}

std::string e2d::internal::LoggerImpl::padLogLevel(const std::string& logLevel)
{
    const size_t maxLength = 5; // Maximum length of log levels
    if (logLevel.length() < maxLength)
    {
        return logLevel + std::string(maxLength - logLevel.length(), ' ');
    }
    return logLevel;
}

const char* e2d::internal::LoggerImpl::getColorForLogLevel(e2d::internal::LogLevel level)
{
    switch (level)
    {
        case E2D_LOG_LEVEL_DEBUG:
            return BLUE_COLOR;
        case E2D_LOG_LEVEL_INFO:
            return GREEN_COLOR;
        case E2D_LOG_LEVEL_WARN:
            return ORANGE_COLOR;
        case E2D_LOG_LEVEL_ERROR:
            return RED_COLOR;
    }
    return RESET_COLOR;
}
