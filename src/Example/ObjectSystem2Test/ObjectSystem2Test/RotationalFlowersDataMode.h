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
// 用户花朵槽
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
//公告牌 Client轮询模式
// Share\\BulletinBoard
typedef struct _tagBulletinBoard
{
	//花槽环槽数
	unsigned int nMaxFlowerSlotCount;
	//当前游戏
	unsigned int nGameMode;
	//传递等待时间 ms
	unsigned int nTransportWaitTime;
}BulletinBoard,*PBulletinBoard;

enum MangerMsgType
{
	MangerMsgType_Horn=1,	//广告
	MangerMsgType_Start=2,	//启动
	MangerMsgType_Stop = 3,	//结束
	MangerMsgType_Over=4	//结束
};

//管理员广播
//Master\\BroadcastMsg
typedef struct _tagMangerBroadcast
{
	unsigned int nMsgType;
	tstring szMsg;
}MangerBroadcast,*PMangerBroadcast;

//管理员 申请Slot接口
//Master\\NeedNewSlot
typedef struct _tagNeedSlot
{
	tstring szUserSession;
}NeedSlot,*PNeedSlot;

//管理员 申请Slot接口
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