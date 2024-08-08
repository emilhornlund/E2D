/**
* @file Formatter.cpp
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

#include <E2D/Core/Formatter.hpp>

void e2d::Formatter::formatImpl(std::ostringstream& oss, const std::string& text, size_t pos)
{
    oss << text.substr(pos);
}

std::string e2d::Formatter::handleEscapedBraces(const std::string& text)
{
    std::string result;
    result.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i)
    {
        if (text[i] == '{' && i + 1 < text.size() && text[i + 1] == '{')
        {
            result.push_back('{');
            ++i;
        }
        else if (text[i] == '}' && i + 1 < text.size() && text[i + 1] == '}')
        {
            result.push_back('}');
            ++i;
        }
        else
        {
            result.push_back(text[i]);
        }
    }
    return result;
}
