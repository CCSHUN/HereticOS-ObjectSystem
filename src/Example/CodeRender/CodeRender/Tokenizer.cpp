///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CTokenizer::IsAbsolutePath(const char * pFilePath)
{
	if ((('z' >= pFilePath[0] && 'a' <= pFilePath[0]) || ('Z' >= pFilePath[0] && 'A' <= pFilePath[0])))
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CTokenizer::FilePathToDirPath(string & szPath)
{
	size_t nPos1 = szPath.rfind('\\');
	size_t nPos2 = szPath.rfind('/');
	size_t nPos = nPos1 == string::npos ? 0 : nPos1;
	nPos = nPos2 == string::npos ? nPos : (max(nPos, nPos2));
	if (nPos)
	{
		szPath[nPos + 1] = 0;
		return TRUE;
	}
	return FALSE;
}

CTokenizer::CTokenizer(string &string)
{
	m_bPushedBack = FALSE;
	m_bEolIsSignificant = TRUE;
	m_bSlSlComments = TRUE;
	m_bSlStComments = TRUE;
	m_bForceLower = FALSE;	// case sensitive
	m_iLineNo = 1;			// the first line
	m_iChar = 0;
	m_peekc = ' ';
	m_sString = string;
	m_tType=TT_EOF;
	setlocale( LC_ALL, "" );
	//m_sString.GetBuffer()[m_sString.GetLength()] = -1;
}

CTokenizer::~CTokenizer()
{
}


void CTokenizer::PushBack()
{
	m_bPushedBack = TRUE;
}

// Specifies that EOL is significant or not
void CTokenizer::EolIsSignificant(BOOL bFlag)
{
	m_bEolIsSignificant = bFlag;
}

// Enable C Style comments
void CTokenizer::SlStComments(BOOL bFlag)
{
	m_bSlStComments = bFlag;
}

// Enable C++ Style comments
void CTokenizer::SlSlComments(BOOL bFlag)
{
	m_bSlSlComments = bFlag;
}

// Enable / disable case sensitivity
void CTokenizer::LowerCaseMode(BOOL bFlag)
{
	m_bForceLower = bFlag;
}
//ANSI多字符
BOOL CTokenizer::IsAnsiMulString(char * pStr,string & StrRst,int &len)
{
	BOOL bFind=FALSE;
	int i=0;
	for(i=0;(pStr[i]!=0)&&(pStr[i]&0x80);i+=2)
	{
		if(pStr[i+1]==0) return FALSE;
		bFind=TRUE;
	}
	if(bFind==FALSE) return FALSE;
	char tmp=pStr[i];
	pStr[i]=0;
	StrRst+=pStr;
	pStr[i]=tmp;
	len=i;
	return bFind;
}
// gives the next Token, returns the token type
int CTokenizer::NextToken()
{
	

	if( m_bPushedBack ) {
		m_bPushedBack = FALSE;
		return m_tType;
	}
	int len=0;
	int c = m_peekc;
	m_sVal = _T("");
	BOOL bFindAnsiMul=FALSE;
	
	if ( c == EOF ) return m_tType = TT_EOF;
	
	// is this a space 
	while( ::isspace( c ) ) {
		if( c == '\r' ) {
			m_iLineNo++;
			c = GetChar();
			if( c == '\n' ) c = GetChar();
			if( m_bEolIsSignificant ) {
				m_peekc = c;
				return m_tType = TT_EOL;
			}
		} else {
			if( c == '\n' ) {
				m_iLineNo++;
				if( m_bEolIsSignificant ) {
					m_peekc = ' ';
					return m_tType = TT_EOL;
				}
			}
			c = GetChar();
		}

		if ( c == EOF ) return m_tType = TT_EOF;
	}
	//十六进制整型
	if(c=='0')
	{
		m_dVal=0.0;
		ULONGLONG nRet=0;
		c = GetChar();
		if((c=='x')||(c=='X'))
		{
			for(;;)
			{
				c = GetChar();
				if( ((c|0x20)>='a')&&((c|0x20)<='f') )
				{
					nRet=nRet<<4;
					nRet|=(c|0x20)-'a'+10;
				}
				else if( (c>='0')&&(c<='9'))
				{
					nRet=nRet<<4;
					nRet|=c-'0';
				}else
				{
					m_iChar--;
					break;
				}
			}
			
		}
		else
		{
			m_iChar--;
		}
		m_dVal=nRet;
		return m_tType = TT_INTEGER;
	}
	// is this a number
	if( ::isdigit( c ) || c == '.' || c == '-' ) {
		BOOL neg = FALSE;
		if( c == '-' )	{
			c = GetChar();
			if( c != '.' && !::isdigit( c ) ) {
				m_peekc = c;
				return  m_tType = '-';
			}
			neg = TRUE;
		}
		double v = 0;
		int decexp = 0;
		int seendot = 0;
		while( true ) {
			if (c == '.' && seendot == 0)
				seendot = 1;
			else if ( ::isdigit( c ) ) {
				v = v* 10 + (c - '0');
				decexp += seendot;
			} else
				break;
			c = GetChar();
		}
		
		m_peekc = c;
		if( decexp != 0 ) {
			double denom = 10;
			decexp--;
			while( decexp > 0 ) {
				denom *= 10;
				decexp --;
			}
			v = v / denom;
		} else if( seendot == 1 ) {
			if(c==EOF)
			{
				return m_tType = '.';
			}
			m_iChar --;
			m_peekc = ' ';
			return m_tType = '.';
		}
		m_dVal = neg ? -v : v;
		if( seendot == 0 )
			return m_tType = TT_INTEGER;
		else
			return m_tType = TT_REAL;
	}
	
	// is this a word
	do 
	{
		if( ::isalpha( c ) || c == '_' ) {
			int i = 0;
			m_sVal = _T("");
			do {
				m_sVal+=c;
				c = GetChar();
			} while ( ::isalnum( c ) || c == '_' );
			m_peekc = c;
			if( m_bForceLower )
			{
				_strlwr((char *)m_sVal.c_str());
			}
			//return 
			m_tType = TT_WORD;
			bFindAnsiMul=TRUE;
		}else if(IsAnsiMulString(&m_sString[m_iChar-1],m_sVal,len))
		{
			m_iChar+=(len-1);
			c = GetChar();
			if(::isalnum( c ) || c == '_')
			{
				do {
					m_sVal+=c;
					c = GetChar();
				} while ( ::isalnum( c ) || c == '_' );
			}
			m_tType=TT_WORD;
			m_peekc = c;
			bFindAnsiMul=TRUE;
		}else
		{
			if(bFindAnsiMul) return m_tType;
			break;
		}
	} while (true);
	

	// now the char & string
	if( c == '\'' || c == '"' ) {
		m_sVal = _T("");
		m_tType = c;
		m_peekc = ' ';
		int i = 0, c2;
		while( (c = GetChar()) != EOF && c != m_tType && c != '\n' && c != '\r' ) {
			if( c == '\\' )// escape
				switch( c = GetChar() ) {
				case 'a': c = 0x7;  break;
				case 'b': c = '\b'; break;
				case 'f': c = 0xC;  break;
				case 'n': c = '\n'; break;
				case 'r': c = '\r'; break;
				case 't': c = '\t'; break;
				case 'v': c = 0xb;  break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
					c = c - '0';
					c2 = GetChar();
					if( c2 == m_tType ) {
						m_sVal += (TCHAR)c;
						return m_tType;
					}
					if( '0' <= c2 && c2 <= '7' ) {// octal
						c = (c<<3) + (c2 - '0');
						c2 = GetChar();
						if( c2 == m_tType ) {
							m_sVal += (TCHAR)c;
							return m_tType;
						}
						if( '0' <= c2 && c2 <= '7')
							c = (c<<3) + (c2 - '0');
						else {
							m_sVal += (TCHAR)c;
							c = c2;
						}
					} else {
						m_sVal += (TCHAR)c;
						c = c2;
					}
					break;
				default:
					// warning: 'c' : unrecognized character escape sequence
					//OutputErrMsg( "warning in line %d: '%c': unrecognized character escape sequence",
						//m_iLineNo, c );
					break;
				}
			m_sVal += (TCHAR)c;
		}
		if( c == EOF ) {
			// error msg: syntax error in line %d: missing '"'
			//OutputErrMsg( "error in line %d: syntax error, missing '\"'", m_iLineNo );
		} else if( c == '\r' || c == '\n' ) {
			// error msg: syntax error in line %d: new line in constant
			//OutputErrMsg( "error in line %d: syntax error, new line in constant", m_iLineNo );
		}

		return m_tType;
	}

	// and now the comment
	// "//" or "/*...*/"
	if( c == '/' && ( m_bSlSlComments || m_bSlStComments ) ) {
		c = GetChar();
		if( c == '*' && m_bSlStComments ) {
			int prevc = 0;
			while( (c = GetChar()) != '/' || prevc != '*' ) {
				if( c == '\n' )	m_iLineNo++;
				if( c == EOF ) return m_tType = TT_EOF;
				prevc = c;
			}
			m_peekc = ' ';
			return NextToken();
		} else {
			if (c == '/' && m_bSlSlComments) {
				while ( (c = GetChar()) != '\n' && c != '\r' && c != EOF );
				m_peekc = c;
				return NextToken();
			} else {
				m_peekc = c;
				return m_tType = '/';
			}
		}
	}

	m_peekc = ' ';
	return m_tType = c;
}

int CTokenizer::LineNo()
{
	return m_iLineNo;
}

string CTokenizer::GeValueType()
{
	string szType;
	szType="结束";
	switch (m_tType)
	{
	case TT_EOF:
		szType = "结束";
		break;
	case TT_EOL:
		szType = "换行";
		break;
	case TT_WORD:
		szType = "词型";
		break;
	case TT_STRING:
		szType = "字符串型";
		break;
	case TT_INTEGER:
		szType = "整型";
		break;
	case TT_REAL:
		szType = "浮点型";
		break;
	default:
		szType = "符号型";
	}
	return string(szType);
}

BOOL CTokenizer::GetWordArray(vector<WordSet> & WordArray)
{
	if(strstr(m_sString.c_str(),"//MAKE"))
	{
		OutputDebugStringA("221321");
	}
	for(;NextToken()!=TT_EOF;)
	{
		WordSet set;
		set.WordType=GeValueType();
		set.WordVal=GetStrValue();
		if(string("换行")==set.WordType) 
			continue;

		WordArray.push_back(set);
	}
	return TRUE;
}
string CTokenizer::GetStrValue()
{
	string ret;
	char szType[128];
	switch (m_tType)
	{
	case TT_EOF:
		ret = "EOF";
		break;
	case TT_EOL:
		ret = "EOL";
		break;
	case TT_WORD:
		ret = m_sVal;
		break;
	case TT_STRING:
		ret = m_sVal;
		break;
	case TT_INTEGER:
	case TT_REAL:
		sprintf(szType,"%g",m_dVal);
		ret=szType;
		break;
	default:
		sprintf(szType,"%c",(char)m_tType) ;
		ret=szType;
	}
	return ret;
}

double CTokenizer::GetDoubleNumValue()
{
	return m_dVal;
}

int CTokenizer::GetIntNumValue()
{
	return (int)m_dVal;
}