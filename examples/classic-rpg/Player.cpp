/**
 * @file Player.cpp
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

#include "Player.hpp"

#include <E2D/Engine/Event.hpp>
#include <E2D/Engine/ResourceRegistry.hpp>
#include <E2D/Engine/Texture.hpp>

const int           cellSize     = 32;
const float         spriteScale  = 2.f;
const e2d::Vector2i spriteSize   = {52, 72};
const e2d::Vector2f spriteOrigin = {static_cast<float>(spriteSize.x) / 2.f,
                                    static_cast<float>(spriteSize.y) - (static_cast<float>(cellSize) / 2.f)};
const float         playerSpeed  = 100;
const double        frameTime    = 0.2;

Player::Player() : e2d::Sprite("Player")
{
}

Player::~Player() = default;

void Player::onLoad()
{
    if (!e2d::ResourceRegistry::getInstance().loadFromFile<e2d::Texture>("Player", "classic-rpg-player.png"))
    {
        return;
    }
    const auto texture = e2d::ResourceRegistry::getInstance().get<e2d::Texture>("Player");
    this->setTexture(texture);
    this->setPosition({400, 300});
    this->setOrigin(spriteOrigin);
    this->setScale({spriteScale, spriteScale});
}

void Player::onEvent(const e2d::Event& event)
{
    if (event.is<e2d::Event::KeyPressed>())
    {
        if (this->m_state == PlayerState::Idle)
        {
            if (event.key.code == e2d::Keyboard::Key::Up || event.key.code == e2d::Keyboard::Key::Down ||
                event.key.code == e2d::Keyboard::Key::Right || event.key.code == e2d::Keyboard::Key::Left)
            {
                this->m_state = PlayerState::Walk;
                this->resetAnimation(0);
            }

            if (event.key.code == e2d::Keyboard::Key::Up)
                this->m_direction = PlayerDirection::Up;
            if (event.key.code == e2d::Keyboard::Key::Down)
                this->m_direction = PlayerDirection::Down;
            if (event.key.code == e2d::Keyboard::Key::Right)
                this->m_direction = PlayerDirection::Right;
            if (event.key.code == e2d::Keyboard::Key::Left)
                this->m_direction = PlayerDirection::Left;
        }
    }
    if (event.is<e2d::Event::KeyReleased>())
    {
        if (this->m_state == PlayerState::Walk)
        {
            if (event.key.code == e2d::Keyboard::Key::Up || event.key.code == e2d::Keyboard::Key::Down ||
                event.key.code == e2d::Keyboard::Key::Right || event.key.code == e2d::Keyboard::Key::Left)
            {
                this->m_state = PlayerState::Idle;
                this->resetAnimation(1);
            }
        }
    }
}

void Player::applySpriteTextureRect()
{
    e2d::Vector2i spriteTexturePosition;

    if (this->m_direction == PlayerDirection::Up)
        spriteTexturePosition.y = spriteSize.y * 3;
    if (this->m_direction == PlayerDirection::Right)
        spriteTexturePosition.y = spriteSize.y * 2;
    if (this->m_direction == PlayerDirection::Down)
        spriteTexturePosition.y = spriteSize.y * 0;
    if (this->m_direction == PlayerDirection::Left)
        spriteTexturePosition.y = spriteSize.y * 1;

    if (this->m_state == PlayerState::Idle)
        spriteTexturePosition.x = spriteSize.x * 1;

    if (this->m_state == PlayerState::Walk)
        spriteTexturePosition.x = spriteSize.x * this->m_animationFrames[this->m_currentAnimationFrame];

    this->setTextureRect(e2d::IntRect(spriteTexturePosition, spriteSize));
}

void Player::applyAnimation(double deltaTime)
{
    if (this->m_state == PlayerState::Walk)
    {
        this->m_elapsedFrameTime += deltaTime;
        if (this->m_elapsedFrameTime >= frameTime)
            this->resetAnimation((this->m_currentAnimationFrame + 1) % 4);
    }
}

void Player::resetAnimation(int frame)
{
    this->m_currentAnimationFrame = frame;
    this->m_elapsedFrameTime      = 0;
}

void Player::applyMovement(double deltaTime)
{
    if (this->m_state == PlayerState::Walk)
    {
        auto position = this->getPosition();
        if (this->m_direction == PlayerDirection::Up)
            position.y -= playerSpeed * static_cast<float>(deltaTime);
        if (this->m_direction == PlayerDirection::Right)
            position.x += playerSpeed * static_cast<float>(deltaTime);
        if (this->m_direction == PlayerDirection::Down)
            position.y += playerSpeed * static_cast<float>(deltaTime);
        if (this->m_direction == PlayerDirection::Left)
            position.x -= playerSpeed * static_cast<float>(deltaTime);
        this->setPosition(position);
    }
}

void Player::onFixedUpdate()
{
    this->applySpriteTextureRect();
}

void Player::onVariableUpdate(double deltaTime)
{
    this->applyMovement(deltaTime);
    this->applyAnimation(deltaTime);
}
