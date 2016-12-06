#pragma once

#include "Unit.h"

Unit::Unit()
{	
	for (int Count = 0; Count < 10; Count++)
	{
		mParameters[Count] = rand() % 100;
	}
}

int* Unit::GetParameters()
{
	return mParameters;
}