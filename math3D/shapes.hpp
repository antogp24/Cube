#pragma once
#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "vector.hpp"

namespace shapes
{
    void line(float ax, float ay, float bx, float by, sf::RenderWindow& window)
    {
        sf::Vertex l[] =
        {
            sf::Vertex(sf::Vector2f(ax, ay)),
            sf::Vertex(sf::Vector2f(bx, by))
        };
        window.draw(l, 2, sf::Lines);
    }

    void circle(short x, short y, short radius, sf::RenderWindow& window)
    {
        sf::CircleShape c(30, 30);
        c.setRadius(radius);
        c.setPosition(x, y);
        window.draw(c);
    }

    void point(short x, short y, sf::RenderWindow& window)
    {
        sf::CircleShape p(30, 30);
        p.setRadius(5);
        p.setPosition(x-5, y-5);
        window.draw(p);
    }

    void connect(int indexStart, int indexEnd, std::vector<vec3>& points, sf::RenderWindow& window, Window& win)
    {
        line(points[indexStart].x + win.center.x, points[indexStart].y + win.center.y,
             points[indexEnd].x + win.center.x, points[indexEnd].y + win.center.y, window);
    }
}