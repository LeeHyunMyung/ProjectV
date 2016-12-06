#ifndef __C_CSV_PARSE__
#define __C_CSV_PARSE__

#include "cocos2d.h"
#include <vector>
using namespace std;


#define MAXUNIT_SZIE			100
#define PARAMETER_SIZE			12 

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
	string			    fieldsep;
	
	int				    cols;
	vector<string>		PreParseDbData;

	void StringSplit(const string& str, vector<string>& tokens, const char& delimiters);
	void split(vector<string>& field, string line);
	int advplain(const string& line, string& fld, int);
	int advquoted(const string& line, string& fld, int);

public:
	bool openFile(const char* fileName, string DbData[][PARAMETER_SIZE]);
	const char* getData(unsigned int rows, unsigned int cols);
	int findColsData(int cols, const char* value);
	void ParseData(string *outData, CCSVParse* csvFile, string Name);
	void ParseDbData(string DbData[][PARAMETER_SIZE]);
	void SaveDataBase(const char* fileName, string DbData[][PARAMETER_SIZE]);

	inline int getCols() { return cols; }
	inline int getRows() { return data.size(); };
};

#endif //__C_CSV_PARSE__