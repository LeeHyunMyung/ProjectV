//////////////////////////
#ifndef __C_UNIT__
#define __C_UNIT__


#include <iostream>

using namespace std;


class Unit
{
public:
	Unit();
	int* GetParameters();

private:

	int mParameters[10] = {};	
};

#endif








