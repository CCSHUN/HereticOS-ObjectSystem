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


//#include "windows.h"
#define _DebugOutput printf_t
#define _DebugOutputLogA 
#define _DebugOutputErrorA printf_t


#include <unordered_map>
#include <vector>
#include "TransportProtocol.h"
//#include <mswsock.h>



namespace TransportMini
{

//#define IOC_IN  0x80000000
//#define IOC_VENDOR  0x18000000
//#define SIO_UDP_CONNRESET (IOC_IN | IOC_VENDOR | 12)

#define MAX_TRANSPORT_LEN 1024*1024			//会话最大尺寸。
#define MAX_TRANSPORT_PACKET_LEN  32*1024	//分包尺寸，如果太大会导致IP 64K buffer不够用。
#define MAX_TRANSPORT_SESSION_COUNT 128		//最大session数量

#define MAX_SERVER_TRANSPORT_BUFFER 128*1024   //1M 如果太小则会丢包
#define MAX_CLIENT_TIMEOUT		10*1000			//Client 传输超时
#define SERVER_SELECT_TIMEOUT	1*1000			//1ms
#define CLIENT_SELECT_TIMEOUT	1*1000			//1ms
	inline  auto _sHash(unsigned char *_First, size_t _Count)
	{	// FNV-1a hash function for bytes in [_First, _First + _Count)
		//#ifdef __amd64
		//static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
		const size_t _FNV_offset_basis = 14695981039346656037ULL;
		const size_t _FNV_prime = 1099511628211ULL;


		size_t _Val = _FNV_offset_basis;
		for (size_t _Next = 0; _Next < _Count; ++_Next)
		{	// fold in another byte
			_Val ^= (size_t)_First[_Next];
			_Val *= _FNV_prime;
		}
		return _Val;
	}

	template<typename _Type>
	inline auto Hash(const _Type & Val)
	{
		return _sHash((unsigned char *)&Val, sizeof(_Type));
	}

	struct TransportUDPRequestHead
	{
		unsigned int nMagicCode;
		unsigned int nErrorType;
		unsigned int nChannelNo;
		unsigned int nPacketLen;
		unsigned int nCheckSum;
	};
	BOOL UDPSend(SOCKET socket, const u_char * pSendBuffer, size_t nLen, sockaddr_in * from, int  & fromlen)
	{
		int nSendedLen = 0;
		int nIoRetLen = 0;
		for (;;)
		{
			int nSendLen = min((nLen - nSendedLen), MAX_TRANSPORT_PACKET_LEN);
			nIoRetLen = sendto(socket, (char *)&pSendBuffer[nSendedLen], nSendLen, 0, (sockaddr*)from, fromlen);
			if (nIoRetLen != SOCKET_ERROR)
			{
				nSendedLen += nIoRetLen;
				if (nSendedLen == nLen) break;
			}
			else
			{
				_DebugOutput(_T("UDPSend fail %d len=%d SendedLen=%d\n"), WSAGetLastError(), nIoRetLen, nSendedLen);
				return FALSE;
			}
		}
		return TRUE;
	}
	
	BOOL UDPRecv(SOCKET socket, const u_char* pRecvBuffer, size_t nLen, sockaddr_in * from, int  & fromlen)
	{
		BOOL bRet = FALSE;
		int nRecvedLen = 0;
		int nIoRetLen = 0;
		for (;;)
		{
			int nRecvLen= min(nLen - nRecvedLen, MAX_TRANSPORT_PACKET_LEN);
			nIoRetLen = recvfrom(socket, (char *)&pRecvBuffer[nRecvedLen], nRecvLen, 0, (struct sockaddr*)from, &fromlen);
			if (nIoRetLen != SOCKET_ERROR)
			{
				nRecvedLen += nIoRetLen;
				if (nLen == nRecvedLen)
				{
					//RecvBuffer[RecvBuffer.size() - 1] = 0;
					//RecvBuffer[RecvBuffer.size() - 2] = 0;
					//_DebugOutput(_T("Client-%d Sendto server confirm OK (%d)\n"), nName, ResponseHead.nPacketLen);
					bRet = TRUE;
					break;
				}
			}
			else
			{
				_DebugOutput(_T("UDPRecv fail %d len=%d\n"), WSAGetLastError(), nIoRetLen);
				break;
			}
		}
		return bRet;
	}
	BOOL UDPSend(SOCKET socket, std::vector<u_char> & SendBuffer, sockaddr_in * from, int  & fromlen)
	{
		return UDPSend(socket, &SendBuffer[0], SendBuffer.size(), from, fromlen);
	}
	BOOL UDPRecv(SOCKET socket, std::vector<u_char> & RecvBuffer, sockaddr_in * from, int  & fromlen)
	{
		return UDPRecv(socket, &RecvBuffer[0], RecvBuffer.size(), from, fromlen);
	}
	template<unsigned int _nMagicCode>
	BOOL UDPSendMsg(SOCKET socket, const u_char * pSendBuffer, size_t nLen, sockaddr_in * from, int  & fromlen, SYSTEMERROR & error,unsigned int nChannelNo=0)
	{
		BOOL bRet = FALSE;
		TransportUDPRequestHead MsgHead;
		MsgHead.nMagicCode = _nMagicCode;
		MsgHead.nErrorType = error;
		MsgHead.nChannelNo = nChannelNo;
		MsgHead.nPacketLen = nLen + sizeof(TransportUDPRequestHead);

		int nSendLen = 0;
		int nIoRetLen = 0;
		nIoRetLen = sendto(socket, (char *)&MsgHead, sizeof(MsgHead), 0, (sockaddr*)from, fromlen);
		if (nIoRetLen == sizeof(MsgHead))
		{
			if (UDPSend(socket, pSendBuffer, nLen, from, fromlen))
			{
				bRet= TRUE;
			}
		}
		return bRet;
	}
	template<unsigned int _nMagicCode, unsigned int nName, typename ContainerT>
	BOOL UDPRecvMsg(SOCKET socket, ContainerT & RecvBuffer, sockaddr_in * from, int  & fromlen, SYSTEMERROR & error, unsigned int * nChannelNo = NULL)
	{
		BOOL bRet = FALSE;
		size_t nRecvLen = 0;
		TransportUDPRequestHead ResponseHead;
		do
		{
			int nIoRetLen = recvfrom(socket, (char *)&ResponseHead, sizeof(ResponseHead), 0, (sockaddr *)from, &fromlen);
			if (nIoRetLen == sizeof(ResponseHead))
			{
				//std::vector<u_char> ResponseBuffer;
				if ((ResponseHead.nMagicCode != _nMagicCode) || (ResponseHead.nPacketLen > MAX_TRANSPORT_LEN))
				{
					error = Error_Sys_Transport_Fail;
					_DebugOutput(_T("Client-%d  recv head data error %x\n"), nName, ResponseHead.nMagicCode);
					break;
				}
				if (nChannelNo) *nChannelNo = ResponseHead.nChannelNo;
				nRecvLen += sizeof(TransportUDPRequestHead);
				RecvBuffer.resize(ResponseHead.nPacketLen - sizeof(TransportUDPRequestHead));
				//ResponseBuffer.resize(ResponseHead.nPacketLen - sizeof(TransportUDPRequestHead));
				if (UDPRecv(socket, (const u_char*)&RecvBuffer[0], ResponseHead.nPacketLen - sizeof(TransportUDPRequestHead), from, fromlen))
				{
					bRet = TRUE;
					return bRet;
				}


			}
			else
			{
				_DebugOutput(_T("Client-%d  recv head fail %d %d\n"), nName, WSAGetLastError(), nIoRetLen);
			}

		} while (false);
		
		return bRet;
	}

	template<typename _TransportServerT,  typename ContainerT, int nUDPPort = 8484, unsigned int _nMagicCode = 'yssy'>
	class TransportMiniUDPServer :public CSystemContainerObjectBase<TransportMiniUDPServer<_TransportServerT, ContainerT, nUDPPort, _nMagicCode>, ContainerT>
	{
	public:
		HANDLE m_hServerThread;
		SOCKET m_hSocket;
		volatile BOOL m_bClose;
		u_short m_nPort;
		typedef TransportMiniUDPServer<_TransportServerT, ContainerT, nUDPPort, _nMagicCode> _Myt;

		TransportMiniUDPServer() {
			m_nPort = nUDPPort;
			m_bClose = FALSE;
			m_hSocket = INVALID_SOCKET;
		};
		~TransportMiniUDPServer() {};
		/*
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		*/
		struct IpSessionKey_Client
		{
			unsigned int	src_addr;		//源地址,32位
											//unsigned int	des_addr;		//目标地址,32位
			unsigned short	src_port;		//发送端端口号,16位
											//unsigned short	des_port;		//接收端端口号,16位
			size_t m_hash;
			void Hash()
			{
				//m_hash=Hash(x.m_Key[0]) ^ Hash(x.m_Key[1])
				m_hash = std::hash<int>()(src_addr) ^ std::hash<int>()(src_port);
			}
		};
		struct IpSessionKey_Client_Compare {
			inline bool operator()(const IpSessionKey_Client & a, const IpSessionKey_Client & b) const {

				if (likely(((a.src_addr == b.src_addr) &&
					(a.src_port == b.src_port) //&&
											   //	(a.des_addr == b.des_addr) &&
											   //	(a.des_port == b.des_port)
					)))
				{
					return true;
				}
				return false;

			}
		};

		struct IpSessionKey_Client_hash {
			size_t operator()(const IpSessionKey_Client &x) const {
				//return Hash(x.m_Key[0]) ^ Hash(x.m_Key[1]) ^ Hash(x.m_Key[2]);
				return x.m_hash;
			}
		};

		struct ClientSession
		{
			sockaddr_in from;
			int fromlen;
			BOOL bNeedNewBuildSession;
			unsigned int nChannelNo;
			std::vector<u_char> m_SessionBuffer;
		};

		typedef std::unordered_map<IpSessionKey_Client, ClientSession, IpSessionKey_Client_hash, IpSessionKey_Client_Compare> IpSessionClientT;
		IpSessionClientT m_ClientSessionMap;
		BOOL ProcessRequest(ClientSession & Session,sockaddr_in * from,int  & fromlen)
		{
			TransportUDPRequestHead* pReqHead = (TransportUDPRequestHead*)&Session.m_SessionBuffer[0];
			if ((pReqHead->nMagicCode != _nMagicCode) || (pReqHead->nPacketLen > MAX_TRANSPORT_LEN)||(pReqHead->nPacketLen < Session.m_SessionBuffer.size()))
			{
				return FALSE;
			}
			if (pReqHead->nPacketLen == Session.m_SessionBuffer.size())
			{
				tstring szInPar,szOutPar;
				szInPar = (TCHAR *)&Session.m_SessionBuffer[sizeof(TransportUDPRequestHead)];
				Session.nChannelNo = pReqHead->nChannelNo;
				//_tagstrParameter Par;
				//Par.szData = szInPar;
				//SerObjectToXmlBuffer(_tagstrParameter, Par, szInPar);
				//SerTCHARXmlBufferToObject(_tagstrParameter, Par, (szInPar.c_str()));

				SYSTEMERROR error;
				Transport::TransportHandle hHandle = Session.bNeedNewBuildSession ? &Session : NULL;
				if (_TransportServerT::GetInstance().CallInterfaceStr<_Myt>(hHandle,szInPar, szOutPar, error))
				{
					if (hHandle) Session.bNeedNewBuildSession = FALSE;
					if (!UDPSendMsg<_nMagicCode>(m_hSocket, (const u_char*)szOutPar.c_str(), (szOutPar.size() + 1) * sizeof(TCHAR),from, fromlen, error, pReqHead->nChannelNo))
					{
						return FALSE;
					}

				}
				

				Session.m_SessionBuffer.clear();
			}


			return TRUE;
		}
		fd_set m_RecvFD;
		fd_set m_SendFD;
		timeval m_SelectTimeOut;
		BOOL CanRecv(BOOL & bTransoprt)
		{
			FD_ZERO(&m_RecvFD); FD_SET(m_hSocket, &m_RecvFD);
			if (SOCKET_ERROR != select(0, &m_RecvFD, 0, 0, &m_SelectTimeOut))
			{
				bTransoprt = FD_ISSET(m_hSocket, &m_RecvFD) ? TRUE : FALSE;
				return TRUE;
			}
			return FALSE;
		}
		
		BOOL CanSend(BOOL & bTransoprt)
		{
			FD_ZERO(&m_SendFD); FD_SET(m_hSocket, &m_SendFD);
			if (SOCKET_ERROR != select(0, 0, &m_SendFD, 0, &m_SelectTimeOut))
			{
				bTransoprt = FD_ISSET(m_hSocket, &m_SendFD) ? TRUE : FALSE;
				return TRUE;
			}
			return FALSE;
		}
		void ClearSession(Transport::TransportHandle  hHandle)
		{
			if (hHandle)
			{
				ClientSession * pSession = (ClientSession *)hHandle;
				IpSessionKey_Client ClientKey;
				ClientKey.src_addr = pSession->from.sin_addr.S_un.S_addr;
				ClientKey.src_port = pSession->from.sin_port;
				IpSessionClientT::iterator itClient = m_ClientSessionMap.find(ClientKey);
				if (itClient != m_ClientSessionMap.end())
				{
					m_ClientSessionMap.erase(itClient);
				}
			}
		}
		void ClearAllSession()
		{
			IpSessionClientT::iterator itClient = m_ClientSessionMap.begin();
			for (; itClient!= m_ClientSessionMap.end(); itClient++)
			{
				itClient->second.bNeedNewBuildSession = TRUE;
			}
		}
		BOOL CanPush(Transport::TransportHandle & hTransport)
		{
			BOOL bRet = FALSE;
			if (hTransport)
			{
				ClientSession * pSession = (ClientSession *)hTransport;
				if ((!pSession->bNeedNewBuildSession))
				{
					BOOL bCanSend = FALSE;
					if (CanSend(bCanSend)&& bCanSend)
					{
						bRet = TRUE;
					}
					
				}
			}
			
			return bRet;
		}
		static DWORD WINAPI ServerUDPThread(LPVOID lpParameter)
		{
			_Myt * pCtl = (_Myt *)lpParameter;
			_DebugOutput(_T("Server-%d ServerUDPThread entry....\n"), ContainerT::nContainerName);
			std::vector<char> RecvMsg;
			RecvMsg.resize(512*1024);
			int nIoRetLen = 0;

			for (; pCtl->m_bClose == false;)
			{
				BOOL bCanRecv;
				if (pCtl->CanRecv(bCanRecv))
				{
					if (bCanRecv)
					{
						sockaddr_in from;
						int fromlen = sizeof(from);
						//_DebugOutput(_T("Wait for recv message"));
						nIoRetLen = recvfrom(pCtl->m_hSocket, (char *)&RecvMsg[0], RecvMsg.size(), 0, (struct sockaddr*)&from, &fromlen);
						IpSessionKey_Client ClientKey;
						ClientKey.src_addr = from.sin_addr.S_un.S_addr;
						ClientKey.src_port = from.sin_port;
						IpSessionClientT::iterator itClient = pCtl->m_ClientSessionMap.find(ClientKey);
						if (nIoRetLen != SOCKET_ERROR)
						{
							_DebugOutputLogA("Server-%d Received message from ip=%s port=%d len=%d\n", ContainerT::nContainerName, inet_ntoa(from.sin_addr), ntohs(from.sin_port), nIoRetLen);
							
							
							if (itClient == pCtl->m_ClientSessionMap.end()) {
								if (pCtl->m_ClientSessionMap.size() >= MAX_TRANSPORT_SESSION_COUNT)
								{
									_DebugOutputErrorA("Server-%d Received message Session Too much from ip=%s port=%d len=%d \n", ContainerT::nContainerName, inet_ntoa(from.sin_addr), ntohs(from.sin_port), fromlen);
									continue;
								}
								pCtl->m_ClientSessionMap[ClientKey] = ClientSession();
								itClient = pCtl->m_ClientSessionMap.find(ClientKey);
								itClient->second.from = from;
								itClient->second.fromlen = fromlen;
								itClient->second.bNeedNewBuildSession = TRUE;
								
							}
							itClient->second.m_SessionBuffer.insert(itClient->second.m_SessionBuffer.end(), RecvMsg.begin(), RecvMsg.begin() + nIoRetLen);
							if (pCtl->ProcessRequest(itClient->second, &from, nIoRetLen) == FALSE)
							{
								_DebugOutputErrorA("Server-%d ProcessRequest Fail from ip=%s port=%d len=%d \n", ContainerT::nContainerName, inet_ntoa(from.sin_addr), ntohs(from.sin_port), fromlen);
								//pCtl->m_ClientSessionMap.erase(itClient);
								itClient->second.bNeedNewBuildSession = TRUE;
							}

						}
						else
						{
							DWORD nError = WSAGetLastError();
							_DebugOutputErrorA(_T("Server-%d Received message error from ip=%s port=%d err=%d\n"), ContainerT::nContainerName, inet_ntoa(from.sin_addr), ntohs(from.sin_port), nError);
							//break;
							if (nError == WSAECONNRESET)
							{
								//清除链接
								if (itClient != pCtl->m_ClientSessionMap.end()) {
									itClient->second.bNeedNewBuildSession = TRUE;
								}
							}
							else
							{
								pCtl->ClearAllSession();
								Sleep(5000);
								closesocket(pCtl->m_hSocket);
								pCtl->reinit();
							}
							
						}
					}
					else
					{
						pCtl->Loop();
					}
				}
				
			}
			_DebugOutput(_T("Server-%d ServerUDPThread leave...."), ContainerT::nContainerName);
			return 0;
		}
		BOOL reinit()
		{
			BOOL bRet = FALSE;
			WSADATA wsaData;
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				//printf("WSAStartup failed: %d\n", iResult);
				_DebugOutput(_T("WSAStartup Fail %u..."), ::WSAGetLastError());
				return FALSE;
			}
			m_SelectTimeOut.tv_sec = 0;
			m_SelectTimeOut.tv_usec = SERVER_SELECT_TIMEOUT;

			do
			{
				SOCKADDR_IN LocalAddr;

				LocalAddr.sin_family = AF_INET;
				LocalAddr.sin_port = htons(m_nPort);
				LocalAddr.sin_addr.s_addr = INADDR_ANY;
				

				m_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

				if (m_hSocket == INVALID_SOCKET)
				{
					_DebugOutput(_T("Server-%d socket Fail %u..."), ContainerT::nContainerName, ::WSAGetLastError());
					break;
				}
				if (::bind(m_hSocket, (sockaddr*)&LocalAddr, sizeof(LocalAddr)) == -1)
				{
					_DebugOutput(_T("Server-%d bind socket Fail %u..."), ContainerT::nContainerName, ::WSAGetLastError());
					break;
				}

				int nRecvBuf = MAX_SERVER_TRANSPORT_BUFFER;
				setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
				//发送缓冲区
				int nSendBuf = MAX_SERVER_TRANSPORT_BUFFER;
				setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
				
				//u_long ul = 1;
				//ioctlsocket(m_hSocket, FIONBIO, &ul);

				DWORD dwBytesReturned = 0;
				BOOL bNewBehavior = FALSE;
				DWORD status;

				// disable  new behavior using  
				// IOCTL: SIO_UDP_CONNRESET 

				status = ::WSAIoctl(m_hSocket, SIO_UDP_CONNRESET,
					&bNewBehavior, sizeof(bNewBehavior),
					NULL, 0, &dwBytesReturned,
					NULL, NULL);


				FD_ZERO(&m_RecvFD);
				FD_SET(m_hSocket, &m_RecvFD);
				FD_ZERO(&m_SendFD);
				FD_SET(m_hSocket, &m_SendFD);

				

				bRet = TRUE;
				
			} while (FALSE);

			_DebugOutput(_T("UDPServer reinit %s %d\n"), (bRet ? _T("ok..."):_T("fail...")), WSAGetLastError());
			return bRet;
		}
		BOOL init(const char * pszIP = NULL, u_short nPort = 0)
		{
			BOOL bRet = FALSE;
			if (nPort) m_nPort = nPort;
			if (reinit())
			{
				do
				{

					m_hServerThread = CreateThread(NULL, 0, ServerUDPThread, this, 0, NULL);
					if (NULL == m_hServerThread) {
						_DebugOutput(_T("Server-%d CreateThread fail %x....\n"), ContainerT::nContainerName, GetLastError());
						break;
					}
					bRet = TRUE;

				} while (FALSE);
			}
			GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().RegistManager(MEMGC_SERVER_LEVEL);
			return bRet;

		}
		
		BOOL SendMsg(Transport::TransportHandle & hHandle, const u_char * pSendBuffer, size_t nLen, SYSTEMERROR & error,unsigned int nChannelNoOffset)
		{
			BOOL bRet = FALSE;
			ClientSession * pSession = (ClientSession *)hHandle;
			if (pSession)
			{
				if (pSession->bNeedNewBuildSession == FALSE)
				{
					bRet = UDPSendMsg<_nMagicCode>(m_hSocket, pSendBuffer, nLen, &pSession->from, pSession->fromlen, error, pSession->nChannelNo + nChannelNoOffset);
					if (!bRet)
					{
						_DebugOutputErrorA("Server-%d SendMsg Fail from ip=%s port=%d err=%d \n", ContainerT::nContainerName, inet_ntoa(pSession->from.sin_addr), ntohs(pSession->from.sin_port), WSAGetLastError());
						pSession->bNeedNewBuildSession = TRUE;
					}
				}
				else
				{
					ClearSession(hHandle);
					hHandle = NULL;
				}
				
			}
			return bRet;
		}
		void Loop()
		{
			//推送消息
			_TransportServerT::GetInstance().Loop(this);
		}

	private:

	};

	template<typename ContainerT,int nUDPPort = 8484, unsigned int _nMagicCode = 'yssy'>
	class TransportMiniUDPClient :public CSystemContainerObjectBase<TransportMiniUDPClient<ContainerT, nUDPPort, _nMagicCode>, ContainerT>
	{
	public:
		BOOL m_bInitOk;
		SOCKADDR_IN m_ServerAddr;
		SOCKET m_hSocket;
		string m_szIp;
		u_short m_nPort;
		unsigned int m_nChannel;
		typedef std::queue<tstring> MsgQueueT;
		typedef std::map<unsigned int, MsgQueueT, less<unsigned int>> MsgQueueMapT;
		MsgQueueMapT m_ChannelMsgQueue;
		TransportMiniUDPClient() {
			m_bInitOk = FALSE;
			m_hSocket = INVALID_SOCKET;
			m_nPort = nUDPPort;
			m_szIp = "127.0.0.1";
			m_nChannel = ContainerT::nContainerName<< PRE_TRANSOPRT_CHANNEL_COUNT_LOG2;
			for (int i=0;i<(1<< PRE_TRANSOPRT_CHANNEL_COUNT_LOG2);i++)
			{
				m_ChannelMsgQueue[m_nChannel + i] = MsgQueueT();
			}
		};
		~TransportMiniUDPClient() {};
		typedef TransportMiniUDPClient<ContainerT,nUDPPort, _nMagicCode> _Myt;
		/*
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		*/

		fd_set m_RecvFD;
		fd_set m_SendFD;
		timeval m_SelectTimeOut;
		BOOL CanRecv(BOOL & bTransoprt)
		{
			FD_ZERO(&m_RecvFD); FD_SET(m_hSocket, &m_RecvFD);
			if (SOCKET_ERROR != select(0, &m_RecvFD, 0, 0, &m_SelectTimeOut))
			{
				bTransoprt = FD_ISSET(m_hSocket, &m_RecvFD) ? TRUE : FALSE;
				return TRUE;
			}
			return FALSE;
		}
		BOOL CanSend(BOOL & bTransoprt)
		{
			FD_ZERO(&m_SendFD); FD_SET(m_hSocket, &m_SendFD);
			if (SOCKET_ERROR != select(0, 0, &m_SendFD, 0, &m_SelectTimeOut))
			{
				bTransoprt = FD_ISSET(m_hSocket, &m_SendFD) ? TRUE : FALSE;
				return TRUE;
			}
			return FALSE;
		}
		BOOL RecvAllMsg(BOOL bBlock=FALSE)
		{
			BOOL bRet = FALSE;
			SYSTEMERROR error;
			int len = sizeof(m_ServerAddr);
			BOOL  bRecv, bSend;
			BOOL bOutRecved = FALSE;
			tstring szRecvPar;
			for (;;)
			{
				if ((bBlock)||(CanRecv(bRecv) && bRecv))
				{
					unsigned int nRecvChannel = 0;

					if (UDPRecvMsg<_nMagicCode, ContainerT::nContainerName, tstring>(m_hSocket, szRecvPar, &m_ServerAddr, len, error, &nRecvChannel))
					{
						if (nRecvChannel<(m_nChannel + PRE_TRANSOPRT_CHANNEL_COUNT))
						{
							m_ChannelMsgQueue[nRecvChannel].push(szRecvPar);
							bRet = TRUE;
						}
						else
						{
							break;
						}
						
					}
					else
					{
						break;
					}

				}
				else
				{
					break;
				}
			}
			return bRet;
		}
		BOOL RecvMsg(unsigned int nChannelNoOffset, tstring & szOutPar, BOOL bRecvNew = FALSE;)
		{
			BOOL bRet = FALSE;
			
			
			if(bRecvNew) RecvAllMsg();
			MsgQueueMapT::iterator itQueue = m_ChannelMsgQueue.find(m_nChannel + nChannelNoOffset);
			if (itQueue->second.size())
			{
				szOutPar = itQueue->second.front();
				itQueue->second.pop();
				bRet = TRUE;
			}
			
			return bRet;
		}

		BOOL reinit()
		{
			if (m_hSocket != INVALID_SOCKET) closesocket(m_hSocket);

			m_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			if (m_hSocket == INVALID_SOCKET)
			{
				_DebugOutput(_T("Client-%d socket Fail %u...\n"), ContainerT::nContainerName, ::WSAGetLastError());
				return FALSE;
			}

			int nRecvBuf = 256 * 1024;//设置为32K
			setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
			//发送缓冲区
			int nSendBuf = 256 * 1024;//设置为32K
			setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

			timeval tv = { MAX_CLIENT_TIMEOUT, 0 };
			setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));

			m_SelectTimeOut.tv_sec = 0;
			m_SelectTimeOut.tv_usec = CLIENT_SELECT_TIMEOUT;

			m_ServerAddr.sin_family = AF_INET;
			m_ServerAddr.sin_port = htons(m_nPort);
			m_ServerAddr.sin_addr.s_addr = inet_addr(m_szIp.c_str());

			DWORD dwBytesReturned = 0;
			BOOL bNewBehavior = FALSE;
			DWORD status;

			// disable  new behavior using  
			// IOCTL: SIO_UDP_CONNRESET 
			
			status = ::WSAIoctl(m_hSocket, SIO_UDP_CONNRESET,
				&bNewBehavior, sizeof(bNewBehavior),
				NULL, 0, &dwBytesReturned,
				NULL, NULL);
			
			ContainerT::SystemContainerMgrT::GetInstance().PrintInfo();
			_DebugOutput(_T("Client-%d reint...\n"), ContainerT::nContainerName);
			m_bInitOk = TRUE;
			return m_bInitOk;
		}
		BOOL init(const char * pszIP = NULL, u_short nPort = 0)
		{
			WSADATA wsaData;
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				//printf("WSAStartup failed: %d\n", iResult);
				_DebugOutput(_T("WSAStartup Fail %u..."), ::WSAGetLastError());
				return FALSE;
			}
			if (pszIP) m_szIp = pszIP;
			if (nPort) m_nPort = nPort;

			GCContainer<MemoryMgr__StaticGC_Tmp>::GetInstance().RegistManager(MEMGC_CLIENT_LEVEL);

			return reinit();
		}
		BOOL CallInterfacePar(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter, SYSTEMERROR & error)
		{
			return FALSE;
		}
		BOOL CallInterfaceStr(tstring & szInPar, tstring & szOutPar, SYSTEMERROR & error)
		{
			BOOL bRet = FALSE;
			int len = sizeof(m_ServerAddr);
			int nIoRetLen = 0;
			do
			{
				//m_nCurSessionNo += (m_nCurSessionNo + 1) ? 1 : 2;
				if (UDPSendMsg<_nMagicCode>(m_hSocket, (const u_char *)szInPar.c_str(), (szInPar.size() + 1) * sizeof(TCHAR), &m_ServerAddr, len, error, m_nChannel))
				{
					for (;;)
					{
						unsigned int nRecvChannel = 0;
						if (UDPRecvMsg<_nMagicCode, ContainerT::nContainerName, tstring>(m_hSocket, szOutPar, &m_ServerAddr, len, error, &nRecvChannel))
						{
							if (nRecvChannel == m_nChannel)
							{
								bRet = TRUE;
								break;
							}
							else if(nRecvChannel<(m_nChannel+(1<<PRE_TRANSOPRT_CHANNEL_COUNT_LOG2)))
							{
								m_ChannelMsgQueue[nRecvChannel].push(szOutPar);
							}
						}
						else
						{
							_DebugOutput(_T("CallInterfaceStr Recv Error Channel(%d)\n"), nRecvChannel);
							bRet = FALSE;
							break;
						}
					}
					
				}
			} while (false);
			if (!bRet)
			{
				reinit();
			}
			return bRet;
		}

		
	private:

	};


}


#undef _DebugOutput