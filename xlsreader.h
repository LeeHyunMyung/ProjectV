#pragma once


#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <Windows.h>

#include <SDKDDKVer.h>

#define SAFE_RELEASE(x) if(x) { x.Release(); }

#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

class BAdoAutoInit
{
public:
	BAdoAutoInit();
	~BAdoAutoInit();
};

class BAdoExcel
{
private:
	char m_szConn[256];
	char m_szQuery[256];
	HRESULT m_hrLast;
	std::vector<std::vector<std::string> > m_datas;

public:
	int m_row;
	int m_col;

public:
	BAdoExcel();
	bool Open(LPCSTR path, LPCSTR sheet);
	const char* GetValue(int row, int col);
};


