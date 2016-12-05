// xlsreader.cpp : Defines the entry point for the console application.
//

#include "xlsreader.h"




BAdoAutoInit::BAdoAutoInit()
{
	 CoInitialize(NULL);
}

BAdoAutoInit::~BAdoAutoInit()
{
	 CoUninitialize();
}


BAdoExcel::BAdoExcel()
{
	m_row = 0;
	m_col = 0;
	memset(m_szConn, 0, sizeof(m_szConn));
	memset(m_szQuery, 0, sizeof(m_szQuery));
	m_hrLast = S_OK;
}

bool BAdoExcel::Open(LPCSTR path, LPCSTR sheet)
{
	_snprintf_s(m_szConn, _countof(m_szConn), _TRUNCATE, "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=%s;Extended Properties=\"Excel 12.0;HDR=Yes;\";", path);
	_bstr_t strCnn = m_szConn;
	_RecordsetPtr pRstAuthors;

	m_hrLast = pRstAuthors.CreateInstance(__uuidof(Recordset));
	if(FAILED(m_hrLast))
	{
		SAFE_RELEASE(pRstAuthors);
		return false;
	}

	_snprintf_s(m_szQuery, _countof(m_szQuery), _TRUNCATE, "SELECT * FROM [%s$]", sheet);	
	m_hrLast = pRstAuthors->Open(m_szQuery, strCnn, adOpenStatic, adLockReadOnly,adCmdText);
	if(FAILED(m_hrLast))
	{
		SAFE_RELEASE(pRstAuthors);
		return false;
	}

	//pRstAuthors->MoveFirst();

	m_row = 0;
	m_col = 0;
	m_datas.clear();

	long r = 0;
	long c = 0;

	for(r=0; !pRstAuthors->EndOfFile; pRstAuthors->MoveNext(), r++)
	{
		std::vector<std::string> row;
		for(c=0; c<pRstAuthors->Fields->Count; c++)
		{
			FieldPtr field = pRstAuthors->Fields->GetItem(c);
			_variant_t val = field->Value;
			if(VT_NULL == val.vt)
			{
				row.push_back("");
				continue;
			}
			else
			{
				_bstr_t str = val;
				const char* sz = str;
				row.push_back(sz);
			}
		}

		m_datas.push_back(row);
	}

	m_row = r;
	m_col = c;

	SAFE_RELEASE(pRstAuthors);

	return true;
}

const char* BAdoExcel::GetValue(int row, int col)
{
	if(row >= 0 && row < m_row)
	{
		if(col >= 0 && col < m_col)
		{
			return m_datas[row][col].c_str();
		}
	}

	return "";
}


int _tmain(int argc, _TCHAR* argv[])
{
	BAdoAutoInit autoinit;

	/*
	//------------------------------------------------
	// lua_tinker bind code
	//------------------------------------------------
	lua_State* L = lua_open();
	luaopen_base(L);
	luaopen_string(L);

	lua_tinker::class_add<BAdoExcel>(L, "Excel");
	lua_tinker::class_con<BAdoExcel>(L, lua_tinker::constructor<>());
	lua_tinker::class_def<BAdoExcel>(L, "Open", &BAdoExcel::Open);
	lua_tinker::class_def<BAdoExcel>(L, "Val", &BAdoExcel::GetValue);
	lua_tinker::class_mem<BAdoExcel>(L, "row", &BAdoExcel::m_row);
	lua_tinker::class_mem<BAdoExcel>(L, "col", &BAdoExcel::m_col);

	//------------------------------------------------
	// lua code
	//------------------------------------------------
	e = Excel()
	e:Open("d:\\project\\csv2cs\\gamedata.xls", "Sheet1");
	print("row:" .. e.row);
	print("col:" .. e.col);

	for r=0, e.row-1, 1 do
		for c=0, e.col-1, 1 do
		   print("[" .. r .. "][" .. c .. "][" .. e:Val(r,c) .. "]");
		end
	end
	*/

	BAdoExcel excel;
	excel.Open("sample.xlsx", "Sheet1");
	for(int r=0; r<excel.m_row; r++)
	{
		for(int c=0; c<excel.m_col; c++)
		{
			printf_s("%d,%d = %s\n", r, c, excel.GetValue(r, c));
		}
	}

	return 0;
}

