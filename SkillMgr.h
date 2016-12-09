#pragma once

#ifndef __C_SKILL_MGR__
#define __C_SKILL_MGR__

#include <iostream>
#include "cocos2d.h"

#define SKILL_1			0
#define SKILL_2			1
#define SKILL_3			2
#define SKILL_4			3
#define SKILL_5			4
#define SKILL_6			5
#define SKILL_7			6
#define SKILL_8			7
#define SKILL_9			8
#define SKILL_10		9
#define SKILL_11		10
#define SKILL_12		11
#define SKILL_13		12
#define SKILL_14		13
#define SKILL_15		14
#define SKILL_16		15
#define SKILL_17		16
#define SKILL_18		17
#define SKILL_19		18
#define SKILL_20		19
#define SKILL_21		20
#define SKILL_22		21
#define SKILL_23		22
#define SKILL_24		23
#define SKILL_25		24
#define SKILL_26		25
#define SKILL_27		26
#define SKILL_28		27
#define SKILL_29		28
#define SKILL_30		29

USING_NS_CC;

using namespace std;

void SKILL1()
{
	int k = 0;
	CCLOG("1");
}
void SKILL2()
{
	int k = 0;
	CCLOG("2");
}
void SKILL3()
{
	int k = 0;
	CCLOG("3");
}
void SKILL4()
{
	int k = 0;
	CCLOG("4");
}
void SKILL5()
{
	int k = 0;
	CCLOG("5");
}


class CSkillMgr
{
private:

	CSkillMgr()
	{
		CSkill[0] = SKILL1;
		CSkill[1] = SKILL2;
		CSkill[2] = SKILL3;
		CSkill[3] = SKILL4;
		CSkill[4] = SKILL5;
	};
	CSkillMgr(const CSkillMgr& other);

	static CSkillMgr*	instance;
	void(*CSkill[30])();


public:

	static CSkillMgr* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CSkillMgr();
		}
		return instance;
	}


	void ExcuteSkill(int SkillNum)
	{
		CSkill[SkillNum]();
	}


};

CSkillMgr* CSkillMgr::instance = nullptr;


#endif


