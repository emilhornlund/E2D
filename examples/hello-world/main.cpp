/**
 * main.cpp
 *
 * MIT License
 *
 * Copyright (c) 2023 Emil Hörnlund
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

#include <E2D/Engine/Application.hpp>

#include <algorithm>
#include <iostream>

class HelloWorldApplication final: public e2d::Application {
public:
    HelloWorldApplication();

    ~HelloWorldApplication() final;
};

HelloWorldApplication::HelloWorldApplication() : e2d::Application("Hello World Example") {}

HelloWorldApplication::~HelloWorldApplication() = default;

int main(int argc, char *argv[]) {
    std::copy(argv, argv + argc, std::ostream_iterator<char *>(std::cout, "\n"));

    auto *application = new HelloWorldApplication();

    int exitCode = application->run();

    delete application;
    application = nullptr;

    return exitCode;
}
