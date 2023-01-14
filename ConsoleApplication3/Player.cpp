#include "Player.h"

player::player()
{
    name = "player";
}

void player::update() //set direction for spaceship
{
    float DEGTORAD = 0.017453f; // create movement of spaceship like it has inertia
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * 0.2;
        dy += sin(angle * DEGTORAD) * 0.2;
    }
    else
    {
        dx *= 0.99;
        dy *= 0.99;
    }

    int maxSpeed = 15;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) // not to slowdown spaceship suddenly  
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > screenWidth) x = 0; 
    if (x < 0) x = screenWidth;
    if (y > screenHeight) y = 0; 
    if (y < 0) y = screenHeight;
}
