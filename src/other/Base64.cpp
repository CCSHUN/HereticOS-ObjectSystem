// Base64.cpp: implementation of the Base64 class.
//
//////////////////////////////////////////////////////////////////////
template<typename CharT>
Base64<CharT>::Base64()
{
 Init( );
}
template<typename CharT>
int Base64<CharT>::find(char ch)
{
	 int i;
	 /*
	 for(i=0;i<64;i++)
		 if(EncodeTable[i]==ch)
			 break;
			 */
	 i = DecodeTable[ch];
	 return i;
}
template<typename CharT>
void  Base64<CharT>::Base64EnCode(unsigned char * src, int ssize, CharT * dst,int & dsize)
{
	 int poss,posd,padding;
	 union Data D;
	 
	 poss=0;posd=0,padding=0;
	 for( ;poss<ssize; )
	 {
	  if((ssize-poss)>=3) /*处理多于等于3个的*/
	  {D.B3.a=src[poss++];
	   D.B3.b=src[poss++];
	   D.B3.c=src[poss++];
	  }
	  else   /*处理还剩字符少与3个的(末尾)*/
	  {
		if(ssize-poss>0)/*还有可输入字符*/
		{
		D.B3.a=src[poss++];
		D.B3.b=D.B3.c=0;
		padding=2;        }
		if(ssize-poss>0)
			 {
			 D.B3.b=src[poss++];
			 padding=1;
			 }
	   }

	  dst[posd++]=EncodeTable[D.B4.a];
	  dst[posd++]=EncodeTable[D.B4.b];
	  dst[posd++]=EncodeTable[D.B4.c];
	  dst[posd++]=EncodeTable[D.B4.d];
	 }

	 for( ;padding>0;padding--)
	   dst[posd++]='=';
	 dsize=posd;
	 dst[posd]=0;

}
template<typename CharT>
void  Base64<CharT>::Base64DeCode(const CharT * src, int ssize,unsigned char *dst,int & dsize)
{
	 int count=0,i;
	 int poss,posd;
	 union Data D;
		 for(i=ssize-1;i>0;i--)
			 if(src[i]=='=')
				 count++;
			 else
				 break;

	 poss=0;posd=0;

	 for( ;ssize-poss-count>=4; )
	 {/*读入原串*/
	  D.B4.a=find(src[poss++]);
	  D.B4.b=find(src[poss++]);
	  D.B4.c=find(src[poss++]);
	  D.B4.d=find(src[poss++]);
	  /*映射*/
	  dst[posd++]=D.B3.a;
	  dst[posd++]=D.B3.b;
	  dst[posd++]=D.B3.c;
	 }
	 dsize=posd-count;

}

template<typename CharT>
void Base64<CharT>::Init()
{
	char Table[64]={
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
	'O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b',
	'c','d','e','f','g','h','i','j','k','l','m','n','o','p',
	'q','r','s','t','u','v','w','x','y','z','0','1','2','3',
	'4','5','6','7','8','9','+','/'};
	for (int i = 0; i < 64; i++)
	{
		EncodeTable[i] = Table[i];
		DecodeTable[Table[i]] = i;
	}
	 
}
