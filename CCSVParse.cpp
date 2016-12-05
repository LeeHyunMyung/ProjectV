#include "CCSVParse.h"

using namespace cocos2d;

CCSVParse::CCSVParse(void)
{
	//CCFileUtils::sharedFileUtils()->
}


CCSVParse::~CCSVParse(void)
{
	
}

void CCSVParse::StringSplit(const string& str, vector<string>& tokens, const char& delimiters)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void CCSVParse::split(vector<string>& field, string line)
{
	string fld;
	unsigned int i, j = 0;

	if (line.length() == 0)
		return;
	i = 0;

	do
	{
		if (j<line.length() && line[i] == '"')
			j = advquoted(line, fld, ++i);
		else
			j = advplain(line, fld, i);

		field.push_back(fld);
		i = j + 1;

	} while (j<line.length());
}

int CCSVParse::advplain(const string& s, string& fld, int i)
{
	unsigned int j;
	j = s.find_first_of(fieldsep, i);
	if (j>s.length())
		j = s.length();
	fld = string(s, i, j - i);
	return j;
}

int CCSVParse::advquoted(const string& s, string& fld, int i)
{
	unsigned int j;
	fld = "";
	for (j = i; j<s.length(); ++j)
	{
		if (s[j] == '"' && s[++j] != '"')
		{
			unsigned int k = s.find_first_of(fieldsep, j);
			if (k>s.length())
				k = s.length();
			for (k -= j; k-->0;)
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

//解析 CVS 文件
bool CCSVParse::openFile(const char* fileName)
{
	string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	unsigned char* pBuffer = nullptr;
	ssize_t bufferSize = 0;
	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", &bufferSize);
	string s = (char*)pBuffer;
	string str = s.substr(0, bufferSize);
	SaveData = s.substr(0, bufferSize);
	vector<string> line;
	StringSplit(str, line, '\n');
	for (unsigned int i = 0; i<line.size(); ++i)
	{
		vector<string> field;
		split(field, line[i]);
		data.push_back(field);
		cols = max(cols, (int)field.size());
	}

	return true;
}

//获取指定行列的数据
const char* CCSVParse::getData(unsigned int rows, unsigned int cols)
{
	if (rows<0 || rows >= data.size() || cols<0 || cols >= data[rows].size())
	{
		return "";
	}
	return data[rows][cols].c_str();
}

//获取指定数据的列下标
int CCSVParse::findColsData(int cols, const char* value)
{
	for (unsigned int i = 0; i<data.size(); ++i)
	{
		if (strcmp(getData(i, cols), value) == 0)
			return i;
	}
	return -1;
}

void CCSVParse::ParseData(string *outData,CCSVParse* csvFile,string Name)
{
	for (int i = 0; i < csvFile->getRows(); ++i)
	{
		string strLine = "";
		for (int j = 0; j < csvFile->getCols(); ++j)
		{
			strLine += csvFile->getData(i, j);
		}

		int LineCount = 0;
		int OutPutCount = 0;
		string Copystr = "";
		while (1)
		{

			if (strLine[LineCount] != '\r')
			{
				if (strLine[LineCount] != ',')
				{
					Copystr += strLine[LineCount];
				}
				else if (Name == Copystr)
				{

					Copystr = "";
					while (true)
					{
						LineCount++;
						if (strLine[LineCount] != '\r')
						{
							if (strLine[LineCount] != ',')
							{
								Copystr += strLine[LineCount];
							}
							else
							{
								outData[OutPutCount] = Copystr;
								OutPutCount++;
								Copystr = "";
							}
						}
						else
						{
							outData[OutPutCount] = Copystr;
							return;
						}
					}
				}
				if (strLine[LineCount] != '\r')
					LineCount++;
			}
			else
			{
				break;
			}
		}
	}
}

string CCSVParse::getSaveData()
{
	return SaveData;
}

void CCSVParse::SetSaveData(string Data)
{
	SaveData = Data;
}

void CCSVParse::SaveDataBase(const char* fileName)
{
	CCFileUtils::sharedFileUtils()->writeStringToFile(SaveData,fileName);
}