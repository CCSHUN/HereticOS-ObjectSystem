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

#pragma once


#define APPDATA_HEAD(_name) SERHEAD(./AppProtocol/,_name)
// �û������
// SlotN\\FlowerSlot
typedef struct _tagFlowerSlot
{
	BOOL bOwn;
	unsigned int nFlowerTransportCount;
	tstring szLastLog;
}FlowerSlot, *PFlowerSlot;

enum GameMode
{
	GameMode_Publish_Subscribe=1,
	GameMode_Poll_Event=2,
};
//������ Client��ѯģʽ
// Share\\BulletinBoard
typedef struct _tagBulletinBoard
{
	//���ۻ�����
	unsigned int nMaxFlowerSlotCount;
	//��ǰ��Ϸ
	unsigned int nGameMode;
	//���ݵȴ�ʱ�� ms
	unsigned int nTransportWaitTime;
}BulletinBoard,*PBulletinBoard;

enum MangerMsgType
{
	MangerMsgType_Horn=1,	//���
	MangerMsgType_Start=2,	//����
	MangerMsgType_Stop = 3,	//����
	MangerMsgType_Over=4	//����
};

//����Ա�㲥
//Master\\BroadcastMsg
typedef struct _tagMangerBroadcast
{
	unsigned int nMsgType;
	tstring szMsg;
}MangerBroadcast,*PMangerBroadcast;

//����Ա ����Slot�ӿ�
//Master\\NeedNewSlot
typedef struct _tagNeedSlot
{
	tstring szUserSession;
}NeedSlot,*PNeedSlot;

//����Ա ����Slot�ӿ�
//UserSession\\NeedNewSlotRet
typedef struct _tagNeedSlotRet
{
	int nNewSlot;
}NeedSlotRet,*PNeedSlotRet;

#include APPDATA_HEAD(_tagFlowerSlot)
//#include "./AppProtocol/_tagFlowerSlot_StructInfo.h"
MAKESTRUCTINFO(_tagFlowerSlot)

//#include "./AppProtocol/_tagBulletinBoard_StructInfo.h"
#include APPDATA_HEAD(_tagBulletinBoard)
MAKESTRUCTINFO(_tagBulletinBoard)

//#include "./AppProtocol/_tagMangerBroadcast_StructInfo.h"
#include APPDATA_HEAD(_tagMangerBroadcast)
MAKESTRUCTINFO(_tagMangerBroadcast)

#include APPDATA_HEAD(_tagNeedSlotRet)
MAKESTRUCTINFO(_tagNeedSlotRet)

#include APPDATA_HEAD(_tagNeedSlot)
MAKESTRUCTINFO(_tagNeedSlot)