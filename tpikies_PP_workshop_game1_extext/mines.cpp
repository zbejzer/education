#include "mines.h"

#include "constants.h"

unsigned int getFreeMineIndex(Mine _mines[])
{
    for (int i = 0; i < MAX_MINE_COUNT; i++)
    {
        if (_mines[i].pos == 0)
        {
            return i;
        }
    }

    return 0;
}

int getMineBonusMove(Mine _mines[], unsigned int _position)
{
    for (int i = 0; i < MAX_MINE_COUNT; i++)
    {
        if (_mines[i].pos == _position)
        {
            return _mines[i].bonusMove;
        }
        else if (_mines[i].pos == 0)
        {
            return 0;
        }
    }

    return 0;
}

void addMine(Mine _mines[], unsigned int _position, int _bonusMove)
{
    unsigned int freeIndex = getFreeMineIndex(_mines);

    _mines[freeIndex].pos = _position;
    _mines[freeIndex].bonusMove = _bonusMove;
}
