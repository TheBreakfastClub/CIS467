#include "location.h"

Location::Location(int x, int y) : xy(x, y)
{
	blocking = false;
	//entity = NULL;
}
/*
void Location::set_entity(Entity &e)
{
	entity = e;
}
*/
std::string Location::str()
{
	return "(" + std::to_string(xy.first) + ", " + std::to_string(xy.second) + ")";
}