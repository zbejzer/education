#include "Entity.h"

Entity::Entity()
	: pos_x(0)
	, pos_y(0)
	, texture(nullptr)
{
}

unsigned int& Entity::getPosX()
{
	return pos_x;
}

unsigned int& Entity::getPosY()
{
	return pos_y;
}
