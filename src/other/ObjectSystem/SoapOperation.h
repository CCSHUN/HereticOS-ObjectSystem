#pragma once

class CSoapOperation
{
public:
	CSoapOperation(void);
	~CSoapOperation(void);
	BOOL CallInterface(tstring & szUserName,tstring & szConversation,int nOpCode,_tagCallParameter & tagCallParameter,_tagCallParameter & RetParameter);
};
