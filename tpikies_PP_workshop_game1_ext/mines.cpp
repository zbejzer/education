#include "mines.h"

#include "constans.h"

void addMine(Mine _mines[], unsigned int _position, int _bonusMove)
{
    unsigned int freeIndex = 0;

    while ((freeIndex < MAX_MINE_COUNT) && (_mines[freeIndex].pos != 0))
    {
        freeIndex++;
    }

    _mines[freeIndex].pos = _position;
    _mines[freeIndex].bonusMove = _bonusMove;
}

int getMineBonusMove(Mine _mines[], unsigned int _position)
{
    for (int i = 0; i < MAX_MINE_COUNT; i++)
    {
        if (_mines[i].pos == _position)
        {
            return _mines[i].bonusMove;
        }
    }

    return 0;
}