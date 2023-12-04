#include "walls.h"

#include "constants.h"

unsigned int getFreeWallIndex(Wall _walls[])
{
    for (int i = 0; i < MAX_WALL_COUNT; i++)
    {
        if (_walls[i].pos == 0)
        {
            return i;
        }
    }

    return 0;
}

unsigned int getWallHeight(Wall _walls[], unsigned int _position)
{
    for (int i = 0; i < MAX_WALL_COUNT; i++)
    {
        if (_walls[i].pos == _position)
        {
            return _walls[i].height;
        }
        else if (_walls[i].pos == 0)
        {
            return 0;
        }
    }

    return 0;
}

void addWall(Wall _walls[], unsigned int _position, unsigned int _height)
{
    unsigned int freeIndex = getFreeWallIndex(_walls);

    _walls[freeIndex].pos = _position;
    _walls[freeIndex].height = _height;
}