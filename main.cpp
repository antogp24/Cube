#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "math3D.h"

#define SIDES_LENGTH 50
#define ANTIALIASING 0

int main()
{
    Window win;
    sf::ContextSettings settings(0, 0, ANTIALIASING, 2, 0);
    sf::RenderWindow window(sf::VideoMode(win.x, win.y), "3D Rotating Cube", sf::Style::Default, settings);

    std::vector<vec3> points;
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
        // Logic (Every Frame)
        // ------------------------------------------------------------------------- //

        for (vec3& v : points)
        {
            /// Transformations

            float** rotated = matrices::matmul<3,3/*matrix*/,  3,1/*vector*/>
                             (matrices::rotationY, v.vec3ToFloat());

            rotated = matrices::matmul<3,3/*matrix*/,  3,1/*vector*/>
                     (matrices::rotationX, rotated);

            rotated = matrices::matmul<3,3/*matrix*/,  3,1/*vector*/>
                     (matrices::rotationZ, rotated);

            // Proyecting Points

            float** projected = matrices::matmul<2,3,/*matrix*/  3,1/*vector*/>
                (matrices::projectionOrthographic, rotated);
            v.x = projected[0][0];
            v.y = projected[1][0];
            v.z = rotated[2][0];

            // Deleting after they aren't needed

            ND_arrays::delete_2p<float>(projected, 2);
            ND_arrays::delete_2p<float>(rotated, 3);
        }

        // Input
        // ------------------------------------------------------------------------- //
        sf::Event event;
        for (;window.pollEvent(event);)
        {
            using sf::Event;
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                using sf::Keyboard;
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }
        }
        // Rendering
        // ------------------------------------------------------------------------- //
        window.clear(sf::Color(12, 14, 20));
        for (vec3& v : points)
        {
            shapes::point(v.x + win.center.x, v.y + win.center.y, window);
        }
        // Algorith to draw the edges
        for (int i = 0; i < 4; i++)
        {
            // FACE #1
            shapes::connect( i,    (i+1) % 4,     points, window, win);
            // FACE #2
            shapes::connect( i+4, ((i+1) % 4)+4,  points, window, win);
            // BETWEEN FACES
            shapes::connect( i,     i+4,          points, window, win);
        }
        window.display();
    }
    return 0;
}

/*

/// MANUAL WAY OF THE ALGORITH TO CONNECT THE POINTS

    /// FACE #1

    /// From top left to top right
    shapes::connect(0, 1, points, window, win);
    /// From top right to bottom right
    shapes::connect(1, 2, points, window, win);
    /// From bottom left to bottom right
    shapes::connect(2, 3, points, window, win);
    /// From top left to bottom left
    shapes::connect(3, 0, points, window, win);

    /// FACE #2

    /// From top left to top right
    shapes::connect(4, 5, points, window, win);
    /// From top right to bottom right
    shapes::connect(5, 6, points, window, win);
    /// From bottom left to bottom right
    shapes::connect(6, 7, points, window, win);
    /// From top left to bottom left
    shapes::connect(7, 4, points, window, win);

    /// BETWEEN FACES

    /// Top Left
    shapes::connect(0, 4, points, window, win);
    /// Top Right
    shapes::connect(1, 5, points, window, win);
    /// Bottom Right
    shapes::connect(2, 6, points, window, win);
    /// Bottom Left
    shapes::connect(3, 7, points, window, win);
*/