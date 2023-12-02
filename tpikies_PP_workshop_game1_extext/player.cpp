#include "player.h"

#include "constants.h"

void initPlayer(Player *_player, int _num)
{
    _player->pos = 0;
    _player->num = _num;
    _player->passedStartSeq = 0;
    _player->isInactive = 0;
    _player->isStarted = 0;
}

void checkPlayerStartSequence(Player *_player, unsigned int _gameStartSeq[], int _moveValue)
{
    if (_gameStartSeq[_player->passedStartSeq] != 0)
    {
        if (_moveValue == _gameStartSeq[_player->passedStartSeq])
        {
            _player->passedStartSeq++;
        }
        else if (_moveValue == _gameStartSeq[0])
        {
            _player->passedStartSeq = 1;
        }
        else
        {
            _player->passedStartSeq = 0;
        }
    }
}

int canPlayerStart(Player *_player, unsigned int _gameStartSeq[])
{
    if (_player->passedStartSeq >= MAX_START_SEQUENCE || _gameStartSeq[_player->passedStartSeq] == 0)
    {
        return 1;
    }
        
    return 0;
}
