#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "h/screen.h"
#include "h/v_math.h"
#include <numeric>
#include <math.h>

void line(screen& s, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);

    for (float a = 0; a < length; a++)
    {
        s.pixel(
            x1 + std::cos(angle) * a,
            y1 + std::sin(angle) * a
        );
    }
}


int main()
{
    int i, j, k;
    std::cout << "hello, g++!\nhello, SDL!" << std::endl;

    screen s;

    std::vector<vec3> points {
        {100,100,100},
        {200,100,100},
        {200,200,100},
        {100,200,100},

        {100,100,200},
        {200,100,200},
        {200,200,200},
        {100,200,200}
    };

    std::vector<connection> connections
    {
        {0,4},
        {1,5},
        {2,6},
        {3,7},

        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4},
    };

    vec3 c{0,0,0};
    for (auto& p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }
    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    while (true)
    {
        SDL_RenderSetScale(s.r,2,2);
        for (auto& p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            rotate(p,0.003,0.002,0.004);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
            s.pixel(p.x,p.y);
        }
        for (auto& conn : connections)
        {
            line(s,points[conn.a].x,points[conn.a].y,points[conn.b].x,points[conn.b].y);
        }

        s.show();
        s.clear();
        s.input();
        SDL_Delay(30);
    }

    return 0;
}
