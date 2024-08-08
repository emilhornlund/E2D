/**
 * @file Formatter.inl
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
std::string Formatter::format(const std::string& text, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    std::ostringstream oss;
    auto               escapedText = handleEscapedBraces(text);
    formatImpl(oss, escapedText, 0, std::forward<Args>(args)...);
    return oss.str();
}

template <typename T, typename... Args>
void Formatter::formatImpl(std::ostringstream& oss, const std::string& text, size_t pos, T&& arg, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
{
    const size_t nextPos = text.find("{}", pos);
    if (nextPos == std::string::npos)
    {
        formatImpl(oss, text, pos);
        if constexpr (sizeof...(args) == 0)
        {
            throw std::runtime_error("Not enough placeholders in the format string.");
        }
        return;
    }
    oss << text.substr(pos, nextPos - pos);
    oss << std::forward<T>(arg);
    formatImpl(oss, text, nextPos + 2, std::forward<Args>(args)...);
}
