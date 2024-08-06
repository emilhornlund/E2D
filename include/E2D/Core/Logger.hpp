/**
 * Logger.hpp
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

#ifndef E2D_CORE_LOGGER_HPP
#define E2D_CORE_LOGGER_HPP

#include <E2D/Core/Export.hpp>

#include <E2D/Core/Format.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <mutex>
#include <string>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @brief Namespace for E2D internal
 */
namespace internal
{

/**
 * @enum LogLevel
 * @brief Represents the different levels of logging severity.
 */
enum LogLevel
{
    E2D_LOG_LEVEL_DEBUG, //!< Detailed information, typically of interest only when diagnosing problems.
    E2D_LOG_LEVEL_INFO,  //!< Confirmation that things are working as expected.
    E2D_LOG_LEVEL_WARN, //!< An indication that something unexpected happened, or indicative of some problem in the near future.
    E2D_LOG_LEVEL_ERROR, //!< An error has occurred.
};

/**
 * @class LoggerImpl
 * @brief Provides logging functionality with different log levels.
 */
class E2D_CORE_API LoggerImpl final : NonCopyable
{
public:
    /**
     * @brief Logs a message with the given log level and arguments.
     *
     * Formats the message with the provided arguments and logs it with the specified log level.
     *
     * @tparam Args The types of the arguments to format the message.
     * @param level The log level of the message.
     * @param message The message to log, containing placeholders for the arguments.
     * @param args The arguments to replace the placeholders in the message.
     */
    template <typename... Args>
    static void log(LogLevel level, const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        getInstance().logImpl(level, format(message, std::forward<Args>(args)...));
    }

private:
    /**
     * @brief Constructs a LoggerImpl instance.
     */
    LoggerImpl();

    /**
     * @brief Destructs the LoggerImpl instance.
     */
    ~LoggerImpl() = default;

    /**
     * @brief Gets the singleton instance of the LoggerImpl.
     *
     * @return A reference to the LoggerImpl instance.
     */
    static LoggerImpl& getInstance();

    /**
     * @brief Logs a message with the given log level.
     *
     * @param level The log level.
     * @param message The message to log.
     */
    void logImpl(LogLevel level, const std::string& message);

    /**
     * @brief Gets the current date and time as a string.
     *
     * @return The current date and time as a string.
     */
    std::string currentDateTime();

    /**
     * @brief Converts a log level to its string representation.
     *
     * @param level The log level to convert.
     * @return The string representation of the log level.
     */
    std::string logLevelToString(LogLevel level);

    /**
     * @brief Pads the log level string to a consistent length.
     *
     * @param logLevel The log level string.
     * @return The padded log level string.
     */
    std::string padLogLevel(const std::string& logLevel);

    /**
     * @brief Gets the color code for the specified log level.
     *
     * @param level The log level for which to get the color code.
     * @return The ANSI color code as a C-string.
     */
    const char* getColorForLogLevel(LogLevel level);

    LogLevel   m_currentLevel{E2D_LOG_LEVEL_INFO}; //!< The current log level.
    std::mutex m_mutex;                            //!< Mutex for synchronizing log access.
};

} // namespace internal

/**
 * @brief Namespace for E2D log
 */
namespace log
{

/**
 * @brief Logs a debug message.
 *
 * Formats the message with the provided arguments and logs it with the DEBUG log level.
 *
 * @tparam Args The types of the arguments to format the message.
 * @param message The message to log, containing placeholders for the arguments.
 * @param args The arguments to replace the placeholders in the message.
 */
template <typename... Args>
inline void debug(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    internal::LoggerImpl::log(internal::E2D_LOG_LEVEL_DEBUG, message, std::forward<Args>(args)...);
}

/**
 * @brief Logs an info message.
 *
 * Formats the message with the provided arguments and logs it with the INFO log level.
 *
 * @tparam Args The types of the arguments to format the message.
 * @param message The message to log, containing placeholders for the arguments.
 * @param args The arguments to replace the placeholders in the message.
 */
template <typename... Args>
inline void info(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    internal::LoggerImpl::log(internal::E2D_LOG_LEVEL_INFO, message, std::forward<Args>(args)...);
}

/**
 * @brief Logs a warning message.
 *
 * Formats the message with the provided arguments and logs it with the WARN log level.
 *
 * @tparam Args The types of the arguments to format the message.
 * @param message The message to log, containing placeholders for the arguments.
 * @param args The arguments to replace the placeholders in the message.
 */
template <typename... Args>
inline void warn(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    internal::LoggerImpl::log(internal::E2D_LOG_LEVEL_WARN, message, std::forward<Args>(args)...);
}

/**
 * @brief Logs an error message.
 *
 * Formats the message with the provided arguments and logs it with the ERROR log level.
 *
 * @tparam Args The types of the arguments to format the message.
 * @param message The message to log, containing placeholders for the arguments.
 * @param args The arguments to replace the placeholders in the message.
 */
template <typename... Args>
inline void error(const std::string& message, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    internal::LoggerImpl::log(internal::E2D_LOG_LEVEL_ERROR, message, std::forward<Args>(args)...);
}

} // namespace log

} // namespace e2d

#endif //E2D_CORE_LOGGER_HPP
