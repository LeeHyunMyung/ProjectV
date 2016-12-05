#ifndef __C_CSV_PARSE__
#define __C_CSV_PARSE__

#include "cocos2d.h"
#include <vector>
using namespace std;

class CCSVParse
{

public:
	CCSVParse(void);
	~CCSVParse(void);

	//CCSVParse(istream& fin = cin, string sep = ",") :fieldsep(sep),cols(0)
	//{

	//}

	std::vector<std::vector<std::string>> data;

private:
	string        fieldsep;
	string        SaveData;
	int            cols;

	void StringSplit(const string& str, vector<string>& tokens, const char& delimiters);
	void split(vector<string>& field, string line);
	int advplain(const string& line, string& fld, int);
	int advquoted(const string& line, string& fld, int);

public:
	bool openFile(const char* fileName);
	const char* getData(unsigned int rows, unsigned int cols);
	int findColsData(int cols, const char* value);
	void ParseData(string *outData, CCSVParse* csvFile, string Name);
	string getSaveData();
	void SetSaveData(string Data);
	void SaveDataBase(const char* fileName);

	inline int getCols() { return cols; }
	inline int getRows() { return data.size(); };
};

#endif //__C_CSV_PARSE__