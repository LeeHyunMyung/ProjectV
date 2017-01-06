//////////////////////////
#ifndef __C_UNIT__
#define __C_UNIT__


#include <iostream>
#include <time.h>
#include <cocos2d.h>

using namespace std;
USING_NS_CC;

#define UNIT_TYPE			0
#define LEVEL				1
#define KILL				2
#define HP					3
#define POWER				4
#define DEF					5
#define DEX					6
#define SKILL_TYPE1			7
#define SKILL_TYPE2			8
#define FIX_COUNT			9



class Unit : Sprite
{
public:
	Unit();
	void SetImage(const char* FileName);
	void ChangeImage(const char* FileName);
	int* GetParameters();
	Sprite* GetSprite();
	void Release();

private:

	int mParameters[10] = {};	
	Sprite* mSprite;

};

#endif








