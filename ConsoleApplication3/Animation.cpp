#include "Animation.h"

Animation::Animation(Texture& t, int x, int y, int w, int h, int count, float Speed) // create objects and animation
{
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    
}

void Animation::update() // update animation and object to draw
{
    Frame += speed;
    int n = frames.size();
    if (Frame >= n) Frame -= n; //because Frame may be higher than amount of pixel in the picture (set animation speed)
    sprite.setTextureRect(frames[int(Frame)]);
}

bool Animation::isEnd() //Delete explosions
{
    return Frame + speed >= frames.size();
}
