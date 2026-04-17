// Direction.h
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

// ─────────────────────────────────────────────
//  Direction Enum + Math Helpers
// ─────────────────────────────────────────────
enum class Direction { None, Up, Down, Left, Right };

inline sf::Vector2f getDirectionVector(Direction dir) {
    switch (dir) {
        case Direction::Up:    return {0, -1};
        case Direction::Down:  return {0,  1};
        case Direction::Left:  return {-1, 0};
        case Direction::Right: return {1,  0};
        default:               return {0,  0};
    }
}

inline float calcDist(sf::Vector2f a, sf::Vector2f b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

// ─────────────────────────────────────────────
//  Ghost Body Renderer (Dome + Torso + Skirt)
// ─────────────────────────────────────────────
inline void drawGhostBody(sf::RenderWindow &window, sf::Vector2f pos,
                           sf::Color color, float animTime, float tileSize)
{
    float radius = tileSize / 2.0f * 0.8f;

    sf::CircleShape dome(radius);
    dome.setOrigin({radius, radius});
    dome.setPosition(pos);
    dome.setFillColor(color);
    window.draw(dome);

    sf::RectangleShape body({radius * 2, radius});
    body.setOrigin({radius, 0});
    body.setPosition(pos);
    body.setFillColor(color);
    window.draw(body);

    float offset = std::sin(animTime * 15.0f) * 1.5f;
    sf::VertexArray tri(sf::PrimitiveType::Triangles, 9);
    float w = (radius * 2) / 3.0f;
    for (int i = 0; i < 3; ++i) {
        float sx = -radius + i * w;
        tri[i*3+0] = sf::Vertex{pos + sf::Vector2f(sx,       radius),                                     color};
        tri[i*3+1] = sf::Vertex{pos + sf::Vector2f(sx + w/2, radius + 3 + ((i%2==0) ? offset : -offset)), color};
        tri[i*3+2] = sf::Vertex{pos + sf::Vector2f(sx + w,   radius),                                     color};
    }
    window.draw(tri);
}
