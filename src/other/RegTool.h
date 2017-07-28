//************************************************************************ 
// 公司: 2012-2015, DM. Co., Ltd.
// 文件名: RegTool.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/12/07
// 功能描述: 遍历枚举注册表项值
// 其他备注:
// 维护历史:
//************************************************************************ 
#pragma once
#include "BaseFunctionTool.h"
#include "AutoVar.h"

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

class CRegFind
{
public:
	CRegFind(){ m_hKey = NULL; };
	~CRegFind(){};
	HKEY m_hKey;
	LONG m_nLastError;
	CRegFind(HKEY hKey, TCHAR * pPath)
	{
		m_nLastError = RegOpenKey(hKey, pPath, &m_hKey);

	}
	bool operator ()(HKEY hKey, TCHAR * pPath)
	{
		if (m_hKey != NULL) RegCloseKey(m_hKey);
		m_nLastError = RegOpenKeyEx(hKey, pPath, 0, KEY_READ , &m_hKey);
		if (m_nLastError != ERROR_SUCCESS) m_nLastError = RegOpenKeyEx(hKey, pPath, 0, KEY_READ | KEY_WOW64_64KEY, &m_hKey);
		return m_nLastError == ERROR_SUCCESS ? true : false;

	}
	CAutoVal RegValToCAutoVal(DWORD nRegValueType, void * pValueData, unsigned int nValueLan)
	{
		CAutoVal ret;
		switch (nRegValueType)
		{
		case REG_DWORD:
			ret = *(unsigned int*)pValueData;
			break;
		case REG_SZ:
		case REG_EXPAND_SZ:
			ret = wstring((WCHAR*)pValueData);
			break;
		case REG_MULTI_SZ:
			{
				TCHAR * pStringArray = (TCHAR *)pValueData;
				for (unsigned int nCurPos = 0; pStringArray[nCurPos] != 0; nCurPos++)
				{
					ret.m_ContainerVal.push_back(CAutoVal(&pStringArray[nCurPos]));
					nCurPos += strlen_t(&pStringArray[nCurPos]);
					nCurPos++;
				}
			}
			
			break;
		default:
			break;
		}
		return ret;
	}

	template<typename EnumKeyCallBackT, typename EnumValueCallBackT, typename EnumEndCallBackT>
	void QueryKey(EnumKeyCallBackT EnumKeyCallBack, EnumValueCallBackT EnumValueCallBack, EnumEndCallBackT EnumEndCallBack)
	{
		TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys = 0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		DWORD i, retCode;

		TCHAR  achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;
		if (m_hKey == NULL) return;

		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			m_hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 

		// Enumerate the subkeys, until RegEnumKeyEx fails.

		if (cSubKeys)
		{
			//printf("\nNumber of subkeys: %d\n", cSubKeys);

			for (i = 0; i < cSubKeys; i++)
			{
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(m_hKey, i,
					achKey,
					&cbName,
					NULL,
					NULL,
					NULL,
					&ftLastWriteTime);
				if (retCode == ERROR_SUCCESS)
				{
					//_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
					EnumKeyCallBack(m_hKey, achKey);
				}
			}
		}

		// Enumerate the key values. 

		if (cValues)
		{
			//printf("\nNumber of values: %d\n", cValues);

			for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
			{
				cchValue = MAX_VALUE_NAME;
				achValue[0] = '\0';
				DWORD nType = REG_NONE;
				BYTE ValueData[1024 * 8] = { 0 };
				DWORD nValueLan = 1024*8;
				retCode = RegEnumValue(m_hKey, i,
					achValue,
					&cchValue,
					NULL,
					&nType,
					&ValueData[0],
					&nValueLan);

				if (retCode == ERROR_SUCCESS)
				{
					//_tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
					CAutoVal Val = RegValToCAutoVal(nType, &ValueData[0], nValueLan);
					EnumValueCallBack(m_hKey, achValue, Val);
				}
			}
		}

		EnumEndCallBack();
	}


protected:
	
private:
};


