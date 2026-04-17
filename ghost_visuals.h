// GhostVisuals.h
#pragma once

#include "ghost_direction.h"

// ─────────────────────────────────────────────
//  Ghost Face Renderer (Eyes + Mood Overlays)
// ─────────────────────────────────────────────
inline void drawGhostFace(sf::RenderWindow &window, sf::Vector2f pos,
                           Direction dir, int mood)
{
    sf::Vector2f lk(0, 0);
    if (dir == Direction::Left)  lk.x = -1.5f;
    if (dir == Direction::Right) lk.x =  1.5f;
    if (dir == Direction::Up)    lk.y = -1.5f;
    if (dir == Direction::Down)  lk.y =  1.5f;

    sf::CircleShape eye(3.0f);
    eye.setFillColor(sf::Color::White);
    eye.setOrigin({1.5f, 1.5f});

    sf::CircleShape pupil(1.5f);
    pupil.setFillColor((mood == 1) ? sf::Color::Red : sf::Color::Blue);
    pupil.setOrigin({0.75f, 0.75f});

    for (int side = -1; side <= 1; side += 2) {
        eye.setPosition(pos + sf::Vector2f(side * 3.5f, -2.0f) + lk);
        window.draw(eye);
        pupil.setPosition(eye.getPosition() + lk);
        window.draw(pupil);
    }

    if (mood == 1) {
        sf::RectangleShape brow({5.0f, 1.5f});
        brow.setFillColor(sf::Color::Black);
        brow.setOrigin({2.5f, 0.75f});
        brow.setPosition(pos + sf::Vector2f(-3.5f, -5.5f));
        brow.setRotation(sf::degrees(25));
        window.draw(brow);
        brow.setPosition(pos + sf::Vector2f(3.5f, -5.5f));
        brow.setRotation(sf::degrees(-25));
        window.draw(brow);
    }
    else if (mood == 2) {
        sf::ConvexShape horn(3);
        horn.setPoint(0, {0, 0});
        horn.setPoint(1, {2, 0});
        horn.setPoint(2, {1, -4});
        horn.setFillColor(sf::Color::Red);
        horn.setPosition(pos + sf::Vector2f(-5, -8));
        window.draw(horn);
        horn.setPosition(pos + sf::Vector2f(3, -8));
        window.draw(horn);
    }
}

// ─────────────────────────────────────────────
//  Public Ghost Renderer (Body + Face combined)
// ─────────────────────────────────────────────
inline void drawGhost(sf::RenderWindow &window, sf::Vector2f pos,
                      sf::Color color, Direction dir,
                      int mood, float animTime, float tileSize)
{
    drawGhostBody(window, pos, color, animTime, tileSize);
    drawGhostFace(window, pos, dir, mood);
}
