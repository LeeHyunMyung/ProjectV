//////////////////////////
#ifndef __C_UNIT__
#define __C_UNIT__


#include <iostream>
#include <time.h>


using namespace std;


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

class Unit
{
public:
	Unit();
	int* GetParameters();
	void DoSkill();

private:

	int mParameters[10] = {};	

};

#endif








