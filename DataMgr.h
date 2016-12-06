
#ifndef __C_DATA_MGR__
#define __C_DATA_MGR__

#include <iostream>
#include "CCSVParse.h"
#include "Unit.h"



using namespace std;

class DataMgr
{
private:
	CCSVParse * mData;	
	DataMgr() 
	{
		mData = new CCSVParse();
		mData->openFile("Book1.csv",DbData);
	};
	DataMgr(const DataMgr& other);

	static DataMgr*		instance;
	string              DbData[MAXUNIT_SZIE][PARAMETER_SIZE];

public:
	static DataMgr* GetInstance()
	{
		if (instance == 0)
		{
			instance = new DataMgr();
		}
		return instance;
	}

	void SaveData(Unit* unit)
	{
		for (int unitszie = 0; unitszie < MAXUNIT_SZIE; unitszie++)
		{

			if (DbData[unitszie][0] == "Empty")
			{
				for (int parametersize = 0; parametersize < PARAMETER_SIZE - 2; parametersize++)
				{
					DbData[unitszie][parametersize] = IntToString(unit->GetParameters()[parametersize]);
				}
				DbData[unitszie][PARAMETER_SIZE - 1] = '\n';
				DbData[unitszie][PARAMETER_SIZE - 2] = '\r';
				break;
			}
		}

		mData->SaveDataBase("Book1.csv", DbData);
	};
	
	void SaveData()
	{
		mData->SaveDataBase("Book1.csv",DbData);
	};


	string IntToString(int number)
	{
		std::ostringstream convStream;
		convStream << number;
		return convStream.str();
	};

	int StringToInt(string ctr)
	{
		return stoi(ctr);
	};

};

DataMgr* DataMgr::instance = nullptr;

#endif


