#pragma once



static  char tmp_s[0xffff];
static char *HexToText(BYTE *pData, UINT nLength,UINT nRow)
{
	memset(tmp_s,0,0xffff);
	if (nLength > 0xffff)
	{
		nLength = 0xffff;
		//		sprintf(tmp_s,"���ݳ��ȣ�%ld�������趨�ĳ���10240", nLength);
		//		return tmp_s;
	}
	BYTE *pBuff = new BYTE[nLength];
	memset(pBuff, 0, nLength);
	memcpy(pBuff, pData, nLength);

	int nRetLen = (nLength / 16 + 2) * 16 * 4 + (nLength / 16 + 2) * 8 + 128;
	BYTE *pResult = new BYTE[nRetLen];
	memset(pResult, 0, nRetLen);

	BYTE *p = pBuff;
	BYTE *k = pBuff;
	BYTE *pt = pResult;
	int nLoopTimes = nLength / 16;
	if (nLength%16 > 0)
		nLoopTimes ++;

	for (int i=0;i<nLoopTimes;i++)
	{
		sprintf((char *)pt, "0x%04x ", i*nRow);
		pt += 7;
		UINT nCount = (i+1) * nRow;
		if (nCount < nLength)
			nCount = nRow;
		else
			nCount = nRow - (nCount - nLength);

		for (UINT j=0;j<nCount;j++)
		{
			int t = *p;
			t >>= 4;
			if (t >= 10)
				t += 55;
			else
				t += 0x30;
			*pt++ = t;

			t = *p;
			t &= 0x0F;
			if (t >= 10)
				t += 55;
			else
				t += 0x30;
			*pt++ = t;
			*pt++ = ' ';
			if (*p == 0)
				*p = '.';
			p++;
		}

		if (nCount < nRow)
		{
			memset(pt, 0x20, (nRow-nCount)*3);
			pt += (nRow-nCount)*3;
		}

		memcpy(pt, k, nCount);
		pt += nCount;
		k += nCount;
		memcpy(pt, "\r\n", 2);
		pt += 2;
	}
	memcpy(tmp_s, pResult, min(0xffff, nRetLen));
	delete[] pResult;
	pResult = NULL;
	delete[] pBuff;
	pBuff = NULL;
	return tmp_s;
}

//���лس�
#define TP_NewLine	"\r\n"
#define TP_NewLineWord(_p) ((*(_p)==0x0d)&&(*(_p+1)==0x0a))
#define TP_WORDPROCESSDEF int i_str_Parse=NULL,i1_str_Parse=NULL;TCHAR * p_str_Parse=NULL;TCHAR buf_str_Parse[512]={0};

//����
#define TP_ERROR_Parse(_Msg)	printf_t(_T("ERROR_Parse :"));printf_t(_Msg);printf_t(_T("\r\n"));


//ɾ���ո�
#define TP_ClearSpace(_p)	for(;*_p==0x20;){TP_EndFunc(_p);_p++;} 
//ǰ��n��
#define TP_JMPNCHAR(_p,_n)		_p+=_n;

//�Ƿ��ǿո�
#define TP_IsSpace(_p)		if(*(_p)==0x20)



//��ֹ�㷨
#define TP_EndFunc(_p) if(*(_p)==0x00){TP_ERROR_Parse(_T("EndFunc"));break;}

//�������пո�س�
#define TP_JMPALLSPACE(_p) for(;(*(_p)==0x20)||TP_NewLineWord(_p);){TP_EndFunc(_p);if(TP_NewLineWord(_p)){_p++;}_p++;}
//������һ������
#define TP_JMPNextSpace(_p) for(;*(_p)==0x20;){_p++;} for(;(*(_p)!=0x20)&&(!TP_NewLineWord(_p));){EndFunc(_p);_p++;} for(;(*(_p)==0x20)||TP_NewLineWord(_p);)\
{if (TP_NewLineWord(_p)){ _p++; }_p++; }



//������ǰ����β��
#define TP_JMPCurWordEnd(_p) for(;*(_p)!=0x20&&(!TP_NewLineWord(_p));){EndFunc(_p);_p++;}

//����N������
#define TP_JMPNSpace(_p,_n) for(i_str_Parse=0;i_str_Parse<(_n);i_str_Parse++){TP_JMPNextSpace(_p)}

//��������_n����
#define TP_JMPWORDBACK(_p,_n) p_str_Parse=strstr(_p,_n);if(p_str_Parse)\
{_p=(p_str_Parse+strlen_t(_n));}else{ERROR_Parse("JMPWORDBACK����")}

//��������_nǰ��
#define TP_JMPWORDFRONT(_p,_n) p_str_Parse=strstr(_p,_n);if(p_str_Parse)\
{_p = p_str_Parse; }else{ TP_ERROR_Parse("JMPWORDBACK����") }

//����һ��
#define	TP_JMPONELINE(_p)	for(;!TP_NewLineWord(_p);){TP_EndFunc(_p);TP_EndFunc(_p+1);_p++;};_p+=2;

//����N��
#define	TP_JMPNLINE(_p,_n) for(i_str_Parse=0;i_str_Parse<(_n);){EndFunc(_p);TP_JMPONELINE(_p);i_str_Parse++;}
//��TCHAR * p����n�����ʵ�string s
#define TP_CopyWord(_p,_s,_n)  for(i_str_Parse=0,p_str_Parse=(_p);i_str_Parse<_n;i_str_Parse++){TP_JMPCurWordEnd(p_str_Parse)} \
	memcpy(&buf_str_Parse[0],(_p),(p_str_Parse-(_p))*sizeof(TCHAR));buf_str_Parse[p_str_Parse-(_p)]=0x00;_s=&buf_str_Parse[0];

//��_p(char*)����n(int)���ַ���_s(string)
#define TP_CopyChar(_p,_s,_n)	memcpy(&buf_str_Parse[0],(_p),_n*sizeof(TCHAR));buf_str_Parse[_n]=0x00;_s=&buf_str_Parse[0];

//��_p(char*)������_n(char*)�����Ĵ���_s(string)��
#define TP_CopyCharByEndStr(_p,_s,_n)	p_str_Parse=strstr((_p),_n);\
	if(p_str_Parse){memcpy(&buf_str_Parse[0],_p,(p_str_Parse-_p)*sizeof(TCHAR));\
	buf_str_Parse[p_str_Parse-(_p)]=0x00;_s=&buf_str_Parse[0];}\
	else{ TP_ERROR_Parse("CopyCharByEndStrû���ҵ�Ŀ���ַ���") }

//����һ�е�_s
#define TP_CopyOneLine(_p,_s)	for(p_str_Parse=_p;!TP_NewLineWord(p_str_Parse);p_str_Parse++)\
{EndFunc(p_str_Parse);EndFunc(p_str_Parse+1)};memcpy(&buf_str_Parse[0],_p,p_str_Parse-(_p));\
	buf_str_Parse[p_str_Parse-(_p)]=0x00;_s=&buf_str_Parse[0];

//����һ�е�_sβ��
#define TP_CopyOneLineCat(_p,_s) for(p_str_Parse=_p;!((*(p_str_Parse)==0x0d)&&(*((p_str_Parse+1))==0x0a));p_str_Parse++)\
{EndFunc(p_str_Parse);EndFunc(p_str_Parse+1)};memcpy(&buf_str_Parse[0],_p,p_str_Parse-(_p));\
	_s+=&buf_str_Parse[0];_s+=NewLine;

//����N��
#define TP_CopyNLine(_p,_s,_n) for(i_str_Parse=0,p_str_Parse=_p;i_str_Parse<_n;i_str_Parse++){TP_CopyOneLineCat(p_str_Parse,_s);TP_JMPONELINE(p_str_Parse)}
//_p�Ƿ���Ŀ�괮_n
#define TP_IsDstStr(_p,_n)	if(!strcmp((_p),_n))

//ƥ��һ����Χ����ĸ_a---_b
#define TP_IsCharRange(_p,_a,_b) if((*(_p)>=_a)&&(*(_p)<=_b))

//ƥ��_nλ����
#define TP_IsNumber(_p,_n) for(i_str_Parse=0,p_str_Parse=_p;i_str_Parse<_n;)\
{TP_IsCharRange(p_str_Parse, '0', '9'){ i_str_Parse++; p_str_Parse++; }else{ i_str_Parse = 0; break; }}\
	if(i_str_Parse!=0)



//ƥ��һ����ĸ
#define TP_IsChar(_p,_a) if(*(_p)==_a)

//ƥ��_nλСд��ĸ
#define TP_IsSmallWord(_p,_n) for(i_str_Parse=0;i_str_Parse<_n;)\
{if((*((_p)+i_str_Parse)>='a')&&(*((_p)+i_str_Parse)<='z')){i_str_Parse++;}else{i_str_Parse=0;break;}}\
	if(i_str_Parse==0)

//ƥ��_nλ��д��ĸ
#define TP_IsBigWord(_p,_n) for(i_str_Parse=0;i_str_Parse<_n;)\
{if((*((_p)+i_str_Parse)>='A')&&(*((_p)+i_str_Parse)<='Z')){i_str_Parse++;}else{i_str_Parse=0;break;}}\
	if(i_str_Parse==0)

//ƥ��_nλ��ĸa-z A-Z
#define TP_IsWord(_p,_n) for(i_str_Parse=0;i_str_Parse<_n;)\
{if((*((_p)+i_str_Parse)&0xdf>='a')&&(*((_p)+i_str_Parse)&0xdf<='z')){i_str_Parse++;}else{i_str_Parse=0;break;}}\
	if(i_str_Parse==0)

//ƥ��_nλ��ĸ(���ֻ����ĸ)
#define TP_IsNumAndWord(_p,_n) for(i_str_Parse=0;i_str_Parse<_n;i_str_Parse++)\
	{i1_str_Parse = 1; IsCharRange(_p, '0', '9'){ i1_str_Parse = 0; }TP_IsCharRange(_p, 'a', 'z'){ i1_str_Parse = 0; }\
TP_IsCharRange(_p, 'A', 'Z'){ i1_str_Parse = 0; }if (i1_str_Parse == 1){ break; } \
	} if (i1_str_Parse == 0)


//ƥ��_nλ16������ĸ
#define IsHexNumWord(_p,_n) for(i_str_Parse=0,p_str_Parse=_p;i_str_Parse<_n;i_str_Parse++,p_str_Parse++)\
	{i1_str_Parse = 1; TP_IsCharRange(p_str_Parse, '0', '9'){ i1_str_Parse = 0; }IsCharRange(p_str_Parse, 'a', 'f'){ i1_str_Parse = 0; }\
TP_IsCharRange(p_str_Parse, 'A', 'F'){ i1_str_Parse = 0; }if (i1_str_Parse == 1){ break; }} if (i1_str_Parse == 0)

//��_p�е�_n��16�����ַ�ת����int _o
#define HexStrToI(_p,_n,_o)	for(_o=0,i_str_Parse=0;i_str_Parse<_n;i_str_Parse++)\
	{_o = (_o << 4) & 0xfffffff0; TP_IsCharRange(&_p[i_str_Parse], '0', '9'){ _o += (_p[i_str_Parse] - '0'); } TP_IsCharRange(&_p[i_str_Parse], 'A', 'F'){ _o += (_p[i_str_Parse] - 'A' + 10); }\
	TP_IsCharRange(&_p[i_str_Parse], 'a', 'f'){ _o += ((_p[i_str_Parse] - 'a' + 10)); }}

//�õ�1�ֽ�16������
#define TP_HexStrToC(_p,_o)	for(_o=0,i_str_Parse=0;i_str_Parse<2;i_str_Parse++)\
	{_o = (_o << 4) & 0xf0; TP_IsCharRange(&_p[i_str_Parse], '0', '9'){ _o += (_p[i_str_Parse] - '0'); } TP_IsCharRange(&_p[i_str_Parse], 'A', 'F'){ _o += (_p[i_str_Parse] - 'A' + 10); }\
	TP_IsCharRange(&_p[i_str_Parse], 'a', 'f'){ _o += ((_p[i_str_Parse] - 'a' + 10)); }}

static BOOL HEXStringToBuf(char * pInbuf,char * pOutBuf)
{
	TP_WORDPROCESSDEF
	if(strlen(pInbuf)%2==0)
	{

	}
	else
	{
		return FALSE;
	}
	for(int i=0;pInbuf[2*i]!=0;i++)
	{
		TP_HexStrToC((pInbuf + 2 * i), *(pOutBuf + i));
	}
	return TRUE;
}

