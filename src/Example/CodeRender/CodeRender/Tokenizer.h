#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tokenizer.h : header file
//
#include <string>
#include <list>
#include <vector>
using namespace std;
// now should be defined the token types
#define TT_EOL		'\n'
#define TT_EOF		-1
#define TT_INTEGER	-2
#define TT_REAL		-3
#define TT_WORD		-4
#define TT_STRING	'"'
#define TT_CHAR		'\''

//´ÊÊý×é
typedef struct _tagWordSet
{
	string  WordType;
	string	WordVal;
}WordSet,*PWordSet;

class CTokenizer : public CObject
{
public:
	static BOOL FilePathToDirPath(string & szPath);
	static BOOL IsAbsolutePath(const char * pFilePath);
	CTokenizer(string& string);	
	virtual ~CTokenizer();		    

private:
	
	BOOL IsAnsiMulString(char * pStr,string & StrRst,int &len);
	inline char GetChar() 
	{ 
		if(m_iChar>=m_sString.length())
		{
			return EOF;
		}
		return m_sString[m_iChar++]; 
	}

private:
	string m_sString;			

	BOOL m_bSlSlComments;		
	BOOL m_bSlStComments;		
	BOOL m_bEolIsSignificant;	
	BOOL m_bForceLower;			
	BOOL m_bPushedBack;			

	int	 m_peekc;
	int  m_iLineNo;
	int  m_tType;				
	
protected:
	string	m_sVal;				
	double	m_dVal;
	int		m_iChar;			

public:
	double GetDoubleNumValue();
	int	GetIntNumValue();	
	virtual string GetStrValue();

	int  LineNo();
	void PushBack();
	int  NextToken();			
	string GeValueType();
	BOOL GetWordArray(vector<WordSet> & WordArray);

	void LowerCaseMode(BOOL bFlag);		
	void SlSlComments(BOOL bFlag);		
	void SlStComments(BOOL bFlag);		
	void EolIsSignificant(BOOL bFlag);	 
};

#endif
