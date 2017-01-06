#pragma once

#include "Unit.h"

USING_NS_CC;

Unit::Unit()
{	
	srand(time(NULL));

	for (int Count = 0; Count < 10; Count++)
	{
		mParameters[Count] = rand() % 5;
	}	
}

void Unit::SetImage(const char* FileName)
{
	mSprite = Sprite::create(FileName);
}

void Unit::ChangeImage(const char* FileName)
{
	mSprite->initWithFile(FileName);
}

int* Unit::GetParameters()
{
	return mParameters;
}

Sprite* Unit::GetSprite()
{
	return mSprite;
}

void Unit::Release()
{
	if (mSprite != NULL)
	{
		mSprite->removeFromParentAndCleanup(true);
		mSprite = NULL;
	}
}



