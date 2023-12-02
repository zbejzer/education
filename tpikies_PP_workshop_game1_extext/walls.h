#pragma once

struct Wall
{
    int height;
    unsigned int pos;
};

unsigned int getFreeWallIndex(Wall _walls[]);
int getWallHeight(Wall _walls[], unsigned int _position);
void addWall(Wall _walls[], unsigned int _position, int _height);