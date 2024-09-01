/**
 * @file Player.hpp
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

#ifndef E2D_EXAMPLE_CLASSIC_RPG_PLAYER_HPP
#define E2D_EXAMPLE_CLASSIC_RPG_PLAYER_HPP

#include <E2D/Engine/Sprite.hpp>

class Player final : public e2d::Sprite
{
public:
    Player();

    ~Player() final;

    void onLoad() final;

    void onEvent(const e2d::Event& event) final;

    void onFixedUpdate() final;

    void onVariableUpdate(double deltaTime) final;

private:
    enum class PlayerState
    {
        Idle,
        Walk,
    };

    enum class PlayerDirection
    {
        Up,
        Right,
        Down,
        Left,
    };

    void applySpriteTextureRect();

    void applyAnimation(double deltaTime);

    void resetAnimation(int frame);

    void applyMovement(double deltaTime);

    PlayerState     m_state{PlayerState::Idle};
    PlayerDirection m_direction{PlayerDirection::Down};
    double          m_elapsedFrameTime{0};
    int             m_animationFrames[4]{0, 1, 2, 1};
    int             m_currentAnimationFrame{0};
};

#endif //E2D_EXAMPLE_CLASSIC_RPG_PLAYER_HPP
