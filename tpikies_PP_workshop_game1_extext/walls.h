#pragma once

struct Wall
{
    unsigned int height;
    unsigned int pos;
};

unsigned int getFreeWallIndex(Wall _walls[]);
unsigned int getWallHeight(Wall _walls[], unsigned int _position);
void addWall(Wall _walls[], unsigned int _position, unsigned int _height);