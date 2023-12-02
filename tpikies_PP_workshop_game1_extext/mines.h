#pragma once

struct Mine
{
    int bonusMove;
    unsigned int pos;
};

unsigned int getFreeMineIndex(Mine _mines[]);
int getMineBonusMove(Mine _mines[], unsigned int _position);
void addMine(Mine _mines[], unsigned int _position, int _bonusMove);
