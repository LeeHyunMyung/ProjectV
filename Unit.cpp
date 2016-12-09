#pragma once

#include "Unit.h"


Unit::Unit()
{	
	srand(time(NULL));

	for (int Count = 0; Count < 10; Count++)
	{
		mParameters[Count] = rand() % 5;
	}

	
}

int* Unit::GetParameters()
{
	return mParameters;
}

void Unit::DoSkill()
{
	
}

