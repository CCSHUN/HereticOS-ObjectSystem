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
//RotationalFlowers.h
//
//1. �������Ĵ���ģʽ  �ʺ���Ҫ��ʱ����ҵ�����ݵĳ���
//   ��ģʽ������Clientע���ע�Լ������Updata�¼���
//	 �����߷��û����һ��ָ��Client�Ļ����ʱ����Client�յ�Updata�¼���ȡ������ȴ�������󽫻�����뻷����һ���û��Ļ���ۣ���һ���û�ѭ���˲���
//
//2. ��ѯ���´���ģʽ  �ʺϲ���Ҫ��ʱ����ҵ�����ݳ���
//   ��ģʽ������Client����ע������¼���
//   ����û��ӵ�л���Client ���ڲ�ѯ������һ���û��Ļ���ۣ����ӵ�л�����ȡ�������Լ��Ļ���ۡ�
//   Client�յ��Լ������Updata�¼���˵��ӵ���˻��䡣
//
//3  ����Ա�����¼�
//   ����Clientע����ܹ���Ա������ȫ����Ϣ�����Updata�¼�������ԱUpdata���øö���ʱ�㲥�����пͻ��ˡ�
//   ����ȫ��֪ͨ�������رյȡ�
//   ����Ա�����ʼ���û�����ۺͻ�,���ṩNeedNewSlot����ӿ�Ϊ��½�û�����һ������ۡ�
//
//4	 �����ƹ㲥
//   ������Ϸ�û���ע�����ƣ������û����ݵȴ�ʱ���ǹ���Ա��̬���á�
//

#include "RotationalFlowersDataMode.h"

typedef TransportMini::TransportMiniUDPServer<Transport::Server<LocalObjectServerT>, 8485, 'game'> GameServerTransportT;
typedef Transport::Client<TransportMini::TransportMiniUDPClient<8485, 'game'>> GameClientTransportT;
typedef CObjectSystem_Client<GameClientTransportT, 1> GameClientT;

#define Address_BulletinBoard _T("Share\\BulletinBoard")
#define Address_ManagerMsg _T("Master\\BroadcastMsg")
#define Address_NeedNewSlot _T("Master\\NeedNewSlot")
#define LOOP_TIMEOUT_TICK			50
#define LOOP_TIMEOUT_KEEPALIVED		6*LOOP_TIMEOUT_TICK
#define LOOP_TIMEOUT_GAME_UPDATA	LOOP_TIMEOUT_TICK
enum eUserType
{
	User_PublishSubscribe,
	User_Poll,
	User_Master,
};

TCHAR * pManagerMsgType[] = {_T(""),_T("���"), _T("��ʼ"), _T("��ͣ"), _T("����"), NULL};

template<typename ClientT>
class GameUserBase
{
public:
	_tagBulletinBoard m_bb;
	_tagMangerBroadcast m_LastMangerMsg;
	MangerMsgType m_LastCtlState;
	int m_nSlot;
	int m_nInitStep;
	BOOL m_bGetFlower;
	DWORD m_nFlowerTickCount;
	GameUserBase() { m_bGetFlower = FALSE; m_nFlowerTickCount = ::GetTickCount(); m_nInitStep = 0; };
	~GameUserBase() {};
	BOOL init()
	{
		if(m_nInitStep == 4)  return TRUE ;
		//��ȡһ��Slot
		if (m_nInitStep == 0)
		{
			tstring szNeedNewSlotAddr = GetNewSlotAddr();
			_tagNeedSlotRet_Wrap<ClientT> CreateNewSlot(szNeedNewSlotAddr);
			CreateNewSlot.UpDataObject();
			_tagNeedSlotRet_Wrap<ClientT> NewSlotCallBack(szNeedNewSlotAddr, ObjectEvent_Updata, [this](ObjectSystemEvent & Event) {

				_tagNeedSlotRet_Wrap<ClientT> NewSlot(Event.szObjectAddress);
				if (NewSlot.GetObject())
				{
					m_nSlot = NewSlot.nNewSlot;
					printf_t(_T("�õ�����(Slot-%d)\n"), m_nSlot);
					m_nInitStep = 3;
				}
			});
			m_nInitStep = 1;
			
		}
		if (m_nInitStep==1)
		{
			//����һ��NewSlot
			_tagNeedSlot_Wrap<ClientT> NewSlot(Address_NeedNewSlot);
			NewSlot.szUserSession = GetNewSlotAddr();
			if (NewSlot.UpDataObject())
			{
				if (NewSlot.NeedNewObject())
				{
					printf_t(_T("��%s���������һ������\n"), NewSlot.szUserSession.c_str());
					m_nInitStep=2;
				}
			}
		}

		if (m_nInitStep == 3)
		{
			//��ע����Ա����
			
			_tagMangerBroadcast_Wrap<ClientT> Msg(Address_ManagerMsg, ObjectEvent_Updata, [this](ObjectSystemEvent & Event) {

				_tagMangerBroadcast_Wrap<ClientT> Msg(Event.szObjectAddress);
				if (Msg.GetObject(m_LastMangerMsg))
				{
					printf_t(_T("�յ�����Ա��Ϣ(%s)\n"), pManagerMsgType[m_LastMangerMsg.nMsgType]);
					if (m_LastMangerMsg.nMsgType == MangerMsgType_Horn)
					{
						printf_t(_T("\n========================================================================\n\n%s\n\n========================================================================\n\n"),
							m_LastMangerMsg.szMsg.c_str());
					}
					else
					{
						m_LastCtlState = (MangerMsgType)m_LastMangerMsg.nMsgType;
					}
					if (m_LastCtlState == MangerMsgType_Over)
					{
						for (int s=5;s>0;s--)
						{
							printf_t(_T("��Ϸ����,%ds���˳�...\n"),s);
							Sleep(1000);
						}
						
						::ExitProcess(0);
					}
				}
			});

			Msg.GetObject(m_LastMangerMsg);
			m_LastCtlState = (MangerMsgType)m_LastMangerMsg.nMsgType;
			
			//��ע������Ϣ��

			_tagBulletinBoard_Wrap<ClientT> _bb(Address_BulletinBoard, ObjectEvent_Updata, [this](ObjectSystemEvent & Event) {

				_tagBulletinBoard_Wrap<ClientT> bb(Event.szObjectAddress);
				if (bb.GetObject())
				{
					m_bb = bb;
					printf_t(_T("�����Ƹ�����\n"));
				}
			});
			_bb.GetObject(m_bb);
			m_nInitStep=4;
		}
		

		return m_nInitStep==4?TRUE:FALSE;
	}
	static void GetSlotAddr(tstring & OutAddr, int nSlot)
	{
		OutAddr = _T("Slot");
		OutAddr += (tstring)CAutoVal(nSlot);
		OutAddr += _T("\\FlowerSlot");
		
	}
	void GetSlotAddr(tstring & OutAddr)
	{
		OutAddr = _T("Slot");
		OutAddr += (tstring)CAutoVal(m_nSlot);
		OutAddr += _T("\\FlowerSlot");

	}
	tstring GetSlotAddr()
	{
		tstring  OutAddr;
		OutAddr = _T("Slot");
		OutAddr += (tstring)CAutoVal(m_nSlot);
		OutAddr += _T("\\FlowerSlot");
		return OutAddr;

	}
	static tstring GetNewSlotAddr(tstring & szSession)
	{
		tstring OutAddr=_T("Session\\Session-");
		OutAddr += szSession;
		OutAddr += _T("\\NeedNewSlotRet");
		return OutAddr;

	}
	tstring GetNewSlotAddr()
	{
		tstring OutAddr=_T("Session\\Session-");
		OutAddr += ClientT::GetInstance().GetSession();
		OutAddr += _T("\\NeedNewSlotRet");
		return OutAddr;
	}

private:

};
//��������ģʽ
template<typename ClientT>
class Game_PublishSubscribe :public GameUserBase<ClientT>
{
public:
	BOOL m_bInit;
	_tagFlowerSlot_Wrap<ClientT> m_ToFlowerSlot;
	Game_PublishSubscribe() { 
		m_bInit = FALSE;
	};
	~Game_PublishSubscribe() {};
	typedef Game_PublishSubscribe<ClientT> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	BOOL init()
	{
		BOOL bRet=GameUserBase<ClientT>::init();
		if (bRet == FALSE) return bRet;

		if (m_bInit) return m_bInit;
		//��ע�Լ������Updata
		tstring szSlotAddr;
		GetSlotAddr(szSlotAddr);

		tstring szNextAddr;
		GetSlotAddr(szNextAddr, ((m_nSlot + 1) % m_bb.nMaxFlowerSlotCount));
		m_ToFlowerSlot.m_szAddr = szNextAddr;

		m_ToFlowerSlot.szLastLog = _T("Sender:Slot-");
		m_ToFlowerSlot.szLastLog += (tstring)CAutoVal(m_nSlot);
		m_ToFlowerSlot.szLastLog += _T("  To:Slot-");
		m_ToFlowerSlot.szLastLog += (tstring)CAutoVal((m_nSlot + 1) % m_bb.nMaxFlowerSlotCount);

		_tagFlowerSlot_Wrap<ClientT> Slot(szSlotAddr, ObjectEvent_Updata, [this](ObjectSystemEvent & Event) {
			
				_tagFlowerSlot_Wrap<ClientT> FlowerSlot(Event.szObjectAddress);
				if (FlowerSlot.GetObject())
				{
					printf_t(_T("�յ�����(���ݴ���%d ������Ϣ-%s)��ʱ(%d)\n"),
						FlowerSlot.nFlowerTransportCount, FlowerSlot.szLastLog.c_str(),::GetTickCount()- m_nFlowerTickCount);
					
					m_ToFlowerSlot.nFlowerTransportCount = FlowerSlot.nFlowerTransportCount;

					m_ToFlowerSlot.nFlowerTransportCount++;
					
					//Sleep(m_bb.nTransportWaitTime);
					m_nFlowerTickCount = ::GetTickCount();
					m_bGetFlower = TRUE;
					
				}
		});

		m_bInit = TRUE;
		return m_bInit;
	}
	void Loop()
	{
		if (m_LastCtlState == MangerMsgType_Start)
		{
			if (m_bGetFlower)
			{
				if ((::GetTickCount() - m_nFlowerTickCount) > m_bb.nTransportWaitTime)
				{
					
					if (m_ToFlowerSlot.UpDataObject())
					{
						printf_t(_T("���û��䵽(%s)(���ݴ���%d ������Ϣ-%s)\n"), m_ToFlowerSlot.m_szAddr.c_str(),
							m_ToFlowerSlot.nFlowerTransportCount, m_ToFlowerSlot.szLastLog.c_str());
						m_bGetFlower = FALSE;
					}
					
				}
			}
		}
	}
private:

};

//��ѯģʽ
template<typename ClientT>
class Game_Poll :public GameUserBase<ClientT>
{
public:
	BOOL m_bInit;
	int m_nPrevSlot;
	_tagFlowerSlot_Wrap<ClientT> m_PrevSlot;
	_tagFlowerSlot_Wrap<ClientT> m_SelfSlot;
	DWORD m_nLastPollTickCount;
	int m_nStep;
	Game_Poll() {
		m_bInit = FALSE;
		m_nStep= 0;
	};
	~Game_Poll() {};
	typedef Game_Poll<ClientT> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	BOOL init()
	{
		BOOL bRet = GameUserBase<ClientT>::init();
		if (bRet == FALSE) return bRet;
		if (m_bInit) return m_bInit;
		
		m_nPrevSlot = (m_nSlot - 1)>=0 ? (m_nSlot - 1) : (m_bb.nMaxFlowerSlotCount - 1);
		tstring szPrevSlotAddr;
		GetSlotAddr(szPrevSlotAddr, m_nPrevSlot);
		m_PrevSlot.m_szAddr = szPrevSlotAddr;
		m_SelfSlot.m_szAddr = GetSlotAddr();
		m_bInit = TRUE;
		m_nLastPollTickCount = ::GetTickCount();
		return m_bInit;
	}
	void Loop()
	{
		if (m_LastCtlState == MangerMsgType_Start)
		{
			if ((::GetTickCount() - m_nLastPollTickCount) > m_bb.nTransportWaitTime)
			{
				if (m_nStep == 0)
				{
					if (m_PrevSlot.GetObject())
					{
						m_nStep = 1;
					}
				}
				if (m_nStep == 1)
				{
					if (m_PrevSlot.bOwn)
					{
						m_nStep = 2;
						m_PrevSlot.bOwn = FALSE;
						m_SelfSlot.bOwn = TRUE;
						m_SelfSlot.nFlowerTransportCount = (m_PrevSlot.nFlowerTransportCount + 1);
						m_SelfSlot.szLastLog = _T("Slot-");
						m_SelfSlot.szLastLog += (tstring)CAutoVal(m_nSlot);
						m_SelfSlot.szLastLog = _T("pick form: Slot-");
						m_SelfSlot.szLastLog += (tstring)CAutoVal(m_nPrevSlot);
						printf_t(_T("����(Slot-%d)����(���ݴ���%d ������Ϣ-%s)��ʱ(%dms)\n"), m_nPrevSlot,
							m_PrevSlot.nFlowerTransportCount, m_PrevSlot.szLastLog.c_str(), ::GetTickCount() - m_nFlowerTickCount);
					}else{
						printf_t(_T("δ����(Slot-%d)ӵ�л��䣬�ѵȴ�(%dms)\n"), m_nPrevSlot,
							::GetTickCount() - m_nFlowerTickCount);

						m_nLastPollTickCount = ::GetTickCount();
						m_nStep = 0;
					}
				}
				if (m_nStep == 2)
				{
					if (m_PrevSlot.UpDataObject())
					{
						m_nStep = 3;
					}
				}

				if (m_nStep == 3)
				{
					if (m_SelfSlot.UpDataObject())
					{
						m_nStep = 4;
						printf_t(_T("�����Լ�����(���ݴ���%d ������Ϣ-%s)\n"), 
							m_SelfSlot.nFlowerTransportCount, m_SelfSlot.szLastLog.c_str());
						m_nFlowerTickCount = ::GetTickCount();
					}
				}

				if (m_nStep == 4) {
					m_nLastPollTickCount = ::GetTickCount();
					m_nStep = 0;
				}
			}
		}
	}
private:

};

template<typename ClientT>
class Game_Master
{
public:
	int m_nNewSlot;
	BOOL m_bInit;
	Game_Master() {
		m_bInit = FALSE;
		m_nNewSlot = 0;
	};
	~Game_Master() {};
	typedef Game_Master<ClientT> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	_tagBulletinBoard m_bb;
	HANDLE m_hConsoleThread;
	void ConsoleLoop()
	{
		_tagMangerBroadcast_Wrap<ClientT> mb(Address_ManagerMsg);
	begin:
		system("cls");
		int i = 0;
		printf("��ѡ�����������\n1.�������\n2.��ʼ\n3.��ͣ\n4.����\n5.�Ż�\n6.���ô��ݵȴ�ʱ��\n7.������Ϸ\n");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
		{
			TCHAR szMsg[512];
			printf("��������ʣ�\n");
			scanf_t(_T("%s"), &szMsg[0]);
			mb.szMsg = szMsg;
			mb.nMsgType = MangerMsgType_Horn;
			mb.UpDataObject();
		}
		break;
		case 2:
			mb.nMsgType = MangerMsgType_Start;
			mb.UpDataObject();
			break;
		case 3:
			mb.nMsgType = MangerMsgType_Stop;
			mb.UpDataObject();
			break;
		case 4:
			mb.nMsgType = MangerMsgType_Over;
			mb.UpDataObject();
			break;
		case 5:
		{
			printf("��������õĲۺ�(С�����ۺ�):\n");
			scanf("%d", &i);
			tstring szSlotAddr;
			GameUserBase<ClientT>::GetSlotAddr(szSlotAddr, i);
			_tagFlowerSlot_Wrap<ClientT> Slot(szSlotAddr);
			Slot.bOwn = TRUE;
			Slot.nFlowerTransportCount = 0;
			Slot.szLastLog = _T("Manager inited");
			Slot.UpDataObject();
		}

		break;
		case 6:
		{
			_tagBulletinBoard_Wrap<ClientT> bb(Address_BulletinBoard);
		SelectWaitTime:
			printf("�����ô����ȴ�ʱ��:\n");
			scanf("%d", &i);
			if (i < 0) goto SelectWaitTime;

			m_bb.nTransportWaitTime = i;
			bb.UpDataObject(m_bb);
		}

		break;
		case 7 :
			mb.nMsgType = MangerMsgType_Over;
			mb.UpDataObject();
			MakeRoom();
			break;
		default:
			goto begin;
			break;
		}

	}
	static DWORD WINAPI ConsoleCtlThread(LPVOID lpParameter)
	{
		_Myt * pCtl = (_Myt*)lpParameter;
		for (;;)
		{
			pCtl->ConsoleLoop();
		}
		
	}
	void MakePar()
	{
		int i = 0;
		printf("�����뻨�ۻ�������:\n");
		scanf("%d", &i);
		m_bb.nMaxFlowerSlotCount = i;

	SelectMode:

		printf("�����û��Ĵ���ģʽ:\n1.��������ģʽ\n2.��ѯ��ȡģʽ\n");
		scanf("%d", &i);
		if (i > 2 || i < 1) goto SelectMode;

		m_bb.nGameMode = i;
	SelectWaitTime:

		printf("�����ô����ȴ�ʱ��:\n");
		scanf("%d", &i);
		if (i < 0) goto SelectWaitTime;

		m_bb.nTransportWaitTime = i;
	}
	void MakeRoom()
	{
		_tagBulletinBoard_Wrap<ClientT> bb(Address_BulletinBoard);

	SelectMode:
		int i = 0;
		printf("1.����ԱĬ�ϲ�������(3���ۣ���������ģʽ��3000ms���ݵȴ�):\n2.����ԱĬ�ϲ�������(3���ۣ���ѯģʽ��3000ms���ݵȴ�):\n3.����Ա��ģʽ\n");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			m_bb.nTransportWaitTime = 3000;
			m_bb.nGameMode = GameMode_Publish_Subscribe;
			m_bb.nMaxFlowerSlotCount = 3;
			break;
		case 2:
			m_bb.nTransportWaitTime = 3000;
			m_bb.nGameMode = GameMode_Poll_Event;
			m_bb.nMaxFlowerSlotCount = 3;
			break;
		case 3:
			MakePar();
			break;
		default:
			goto SelectMode;
			break;
		}
		bb.UpDataObject(m_bb);

		//��������
		for (int s = 0; s < m_bb.nMaxFlowerSlotCount; s++)
		{
			tstring szSlotAddr;
			GameUserBase<ClientT>::GetSlotAddr(szSlotAddr, s);
			_tagFlowerSlot_Wrap<ClientT> Slot(szSlotAddr);
			Slot.bOwn = FALSE;
			Slot.nFlowerTransportCount = 0;
			Slot.szLastLog = _T("init");
			Slot.UpDataObject();

		}
		m_nNewSlot = 0;
	}
	BOOL init()
	{
		//ע��Slotע��ӿ�
		
		//��ʼ��������
		if (m_bInit) return m_bInit;

		MakeRoom();
		_tagNeedSlot_Wrap<ClientT> Service_NewSlot(Address_NeedNewSlot, ObjectEvent_NeedNew, [this](ObjectSystemEvent & Event) {

			_tagNeedSlot_Wrap<ClientT> NewSlotReq(Event.szObjectAddress);
			if (NewSlotReq.GetObject())
			{
				TCHAR szMsg[512];
				if (m_bb.nMaxFlowerSlotCount > m_nNewSlot){
					sprintf_t(szMsg,_T("����һ�����ٻ���(%d)��(%s)\n"), m_nNewSlot, NewSlotReq.szUserSession.c_str());
					_tagNeedSlotRet_Wrap<ClientT> NewSlot(NewSlotReq.szUserSession);
					NewSlot.nNewSlot = m_nNewSlot++;
					NewSlot.UpDataObject();
				}else{
					sprintf_t(szMsg,_T("���仨��ʧ��(Session=%s)\n"), NewSlotReq.szUserSession.c_str());
				}
				printf_t(szMsg);
				//OutputDebugString(szMsg);
				
			}
		});
		Service_NewSlot.UpDataObject();


		do
		{

			m_hConsoleThread = CreateThread(NULL, 0, ConsoleCtlThread, this, 0, NULL);
			if (NULL == m_hConsoleThread) {
				printf_t(_T("Master CreateThread fail %x....\n"), GetLastError());
				break;
			}

		} while (FALSE);
		m_bInit = TRUE;
		return m_bInit;
	}
	void Loop()
	{
		//printf_t(_T("Master Alived  ....\n"));
		//fflush(stdout);
	}
	
private:

};

template <typename ClientT>
void GameLoop()
{
	//ObjectSystemTestInit();
	DWORD nLastKeepAlived, nLastGameUpData, nCurTick;
	
	for (int s=0;s<10;s++)
	{
		if (ClientT::GetInstance().init()) break;
		Sleep(500);
		GameClientTransportT::GetInstance().Loop(KEEPALIVED_MODE);
	}

	if (ClientT::GetInstance().init())
	{
		nLastKeepAlived = nLastGameUpData = nCurTick = ::GetTickCount();
		for (int i = 0;; i++)
		{
			nCurTick = ::GetTickCount();
			if (nCurTick- nLastKeepAlived>LOOP_TIMEOUT_KEEPALIVED)
			{
				//�����������¼�
				GameClientTransportT::GetInstance().Loop(KEEPALIVED_MODE);
				nLastKeepAlived = nCurTick;
			}
			if (nCurTick - nLastGameUpData > LOOP_TIMEOUT_KEEPALIVED)
			{
				ClientT::GetInstance().Loop();
				//�����¼�
				GameClientTransportT::GetInstance().Loop();
				nLastGameUpData = nCurTick;
			}
			Sleep(LOOP_TIMEOUT_TICK);
		}
	}
	else
	{
		printf_t(_T("��Ϸ��ʼ��ʧ��....\n"));
	}
	
}
TCHAR * pGameModeInfo[] = {
	_T(""),_T("��������ģʽ"),_T("��ѯģʽ"),NULL
};

void UserSelect()
{
	int i = 0;
	_tagBulletinBoard_Wrap<GameClientT> bb(Address_BulletinBoard);
	if (bb.GetObject())
	{
		printf_t(_T("��ǰ��Ϸ�ܻ������Ϊ:%d\n��ϷģʽΪ:(%s)\n���ݵȴ�ʱ��:(%dms)\n"),
			bb.nMaxFlowerSlotCount, pGameModeInfo[bb.nGameMode],bb.nTransportWaitTime);
	}

	switch (bb.nGameMode)
	{
	case GameMode_Publish_Subscribe:
		//Game_PublishSubscribe<GameClientT>::GetInstance().m_nSlot = i;
		Game_PublishSubscribe<GameClientT>::GetInstance().m_bb = bb;
		GameLoop<Game_PublishSubscribe<GameClientT>>();
		break;
	case GameMode_Poll_Event:
		//Game_Poll<GameClientT>::GetInstance().m_nSlot = i;
		GameLoop<Game_Poll<GameClientT>>();
		break;
	default:
		break;
	}
}

void GameServerEntry()
{
	GameServerTransportT::GetInstance().init();
	
}

void GameEntry(BOOL bMaster=FALSE)
{
	unsigned int i = 0;
	/*[3].string map yss_allocator StaticGC*/
	if (GameClientTransportT::TransportMiniT::GetInstance().init()){
		SYSTEMERROR error;
		if (GameClientT::GetInstance().LogonInSystem(tstring(bMaster ? _T("Master") :_T("User")), tstring(_T("123")), &error)){
			if (bMaster){
				GameLoop<Game_Master<GameClientT>>();
			}else{
				UserSelect();
			}
		}else{
			printf("��½ʧ��\n");
		}
		
	}else{
		printf("ϵͳ��ʼ��ʧ��\n");
	}
}