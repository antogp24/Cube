#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "math3D.h"
#include "settings.h"

int main()
{
    FrameTimer ft;
    Window win;
    sf::ContextSettings settings(0, 0, ANTIALIASING, 2, 0);
    sf::RenderWindow window(sf::VideoMode(win.x, win.y), "3D Rotating Cube", sf::Style::Default, settings);

    std::vector<Vector> points;
    points.reserve(8);

    // First Face
    points.emplace_back(-SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH); // Top Left      #0
    points.emplace_back(+SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH); // Top Right     #1
    points.emplace_back(+SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH); // Bottom Right  #2
    points.emplace_back(-SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH); // Bottom Left   #3

    // Second Face
    points.emplace_back(-SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH); // Top Left      #4
    points.emplace_back(+SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH); // Top Right     #5
    points.emplace_back(+SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH); // Bottom Right  #6
    points.emplace_back(-SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH); // Bottom Left   #7

    // Game Loop
    // ------------------------------------------------------------------------- //
    while (window.isOpen())
    {
        float dt = ft.Mark();

        //rvX += 0.1f * dt;
        //rvY += 0.1f * dt;
        //rvZ += 0.1f * dt;
        matrices::init(rvX * dt, rvY * dt, rvZ * dt);

        // Logic (Every Frame)
        // ------------------------------------------------------------------------- //

        for (Vector& v : points)
        {
            /// Transformations

            Vector rotated = matrices::matmul(matrices::rotationX, v);

            rotated = matrices::matmul(matrices::rotationY, rotated);

            rotated = matrices::matmul(matrices::rotationZ, rotated);

            // Proyecting Points

            Vector projected = matrices::matmul(matrices::projectionOrthographic, rotated);
            v.x = projected.x;
            v.y = projected.y;
            v.z = rotated.z;
        }

        // Input
        // ------------------------------------------------------------------------- //
        sf::Event event;
        for (;window.pollEvent(event);)
        {
            using sf::Event;
            using sf::Keyboard;

            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Escape:
                    window.close();
                    break;

                case Keyboard::Left:
                    rvX *= -1;
                    break;

                case Keyboard::Right:
                    rvY *= -1;
                    break;

                case Keyboard::Up:
                    rvZ *= -1;
                    break;
                }
            }

        }
        // Rendering
        // ------------------------------------------------------------------------- //
        window.clear(sf::Color::Black);
        for (Vector& v : points)
        {
            shapes::point(v.x + win.center.x, v.y + win.center.y, window);
        }
        // Algorith to draw the edges
        for (int i = 0; i < 4; i++)
        {
            // FACE #1
            shapes::connect(i, (i + 1) % 4, points, window, win);
            // FACE #2
            shapes::connect(i + 4, ((i + 1) % 4) + 4, points, window, win);
            // BETWEEN FACES
            shapes::connect(i, i + 4, points, window, win);
        }
        window.display();

    }
    return 0;
}