#pragma once
#include "windows.h"
#define _DebugOutput printf_t
//#define _DebugOutputA printf
//#define _DebugOutput
#define _DebugOutputA 
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

#include <unordered_map>
#include <vector>
#include "TransportProtocol.h"
#pragma comment(lib, "ws2_32.lib")

namespace TransportMini
{


#define MAX_TRANSPORT_LEN 1024*1024			//会话最大尺寸。
#define MAX_TRANSPORT_PACKET_LEN  32*1024	//分包尺寸，如果太大会导致IP 64K buffer不够用。
#define MAX_TRANSPORT_SESSION_COUNT 64		//最大session数量

#define MAX_SERVER_TRANSPORT_BUFFER 1024*1024   //1M 如果太小则会丢包
#define MAX_CLIENT_TIMEOUT		10*1000			//Client 传输超时

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
		unsigned int nPacketLen;
		unsigned int nCheckSum;
	};

	BOOL UDPSend(SOCKET socket,std::vector<u_char> & SendBuffer, sockaddr_in * from, int  & fromlen)
	{
		int nSendedLen = 0;
		int nIoRetLen = 0;
		for (;;)
		{
			int nSendLen = min((SendBuffer.size() - nSendedLen), MAX_TRANSPORT_PACKET_LEN);
			nIoRetLen = sendto(socket, (char *)&SendBuffer[nSendedLen], nSendLen, 0, (sockaddr*)from, fromlen);
			if (nIoRetLen != SOCKET_ERROR)
			{
				nSendedLen += nIoRetLen;
				if (nSendedLen == SendBuffer.size()) break;
			}
			else
			{
				_DebugOutput(_T("UDPSend fail %d len=%d SendedLen=%d\n"), WSAGetLastError(), nIoRetLen, nSendedLen);
				return FALSE;
			}
		}
		return TRUE;
	}
	BOOL UDPRecv(SOCKET socket, std::vector<u_char> & RecvBuffer, sockaddr_in * from, int  & fromlen)
	{
		BOOL bRet = FALSE;
		int nRecvedLen = 0;
		int nIoRetLen = 0;
		for (;;)
		{
			int nRecvLen= min(RecvBuffer.size()- nRecvedLen, MAX_TRANSPORT_PACKET_LEN);
			nIoRetLen = recvfrom(socket, (char *)&RecvBuffer[nRecvedLen], nRecvLen, 0, (struct sockaddr*)from, &fromlen);
			if (nIoRetLen != SOCKET_ERROR)
			{
				nRecvedLen += nIoRetLen;
				if (RecvBuffer.size() == nRecvedLen)
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
	template<typename _TransportServerT, int nUDPPort = 8484, unsigned int _nMagicCode = 'yssy',int nName=0>
	class TransportMiniUDPServer
	{
	public:
		HANDLE m_hServerThread;
		SOCKET m_hSocket;
		volatile BOOL m_bClose;
		u_short m_nPort;
		typedef TransportMiniUDPServer<_TransportServerT, nUDPPort, _nMagicCode, nName> _Myt;

		TransportMiniUDPServer() {
			m_nPort = nUDPPort;
			m_bClose = FALSE;
			m_hSocket = INVALID_SOCKET;
		};
		~TransportMiniUDPServer() {};

		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
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
				//_tagstrParameter Par;
				//Par.szData = szInPar;
				//SerObjectToXmlBuffer(_tagstrParameter, Par, szInPar);
				//SerTCHARXmlBufferToObject(_tagstrParameter, Par, (szInPar.c_str()));

				SYSTEMERROR error;

				if (_TransportServerT::GetInstance().CallInterfaceStr(szInPar, szOutPar, error))
				{
					g_pMemoryMgr[MEMMGR_TYPE_STATICGC_TMP]->DelGc(FALSE);
					TransportUDPRequestHead ResponseHead;
					//Par.szData = szOutPar;
					//SerObjectToXmlBuffer(_tagstrParameter, Par, szOutPar);

					ResponseHead.nMagicCode = _nMagicCode;
					ResponseHead.nErrorType = error;
					ResponseHead.nPacketLen = (szOutPar.size() + 1) * sizeof(TCHAR) + sizeof(TransportUDPRequestHead);
					vector<u_char> Buffer;
					
					Buffer.resize((szOutPar.size() + 1) * sizeof(TCHAR));

					
					//memcpy(&Buffer[0], &ResponseHead, sizeof(TransportUDPRequestHead));
					memcpy(&Buffer[0], szOutPar.c_str(), (szOutPar.size() + 1) * sizeof(TCHAR));
					
					int nSendLen = 0;
					int nIoRetLen = 0;
					nIoRetLen = sendto(m_hSocket, (char *)&ResponseHead,sizeof(ResponseHead), 0, (sockaddr*)from, fromlen);
					if (nIoRetLen == sizeof(ResponseHead))
					{
						if (!UDPSend(m_hSocket, Buffer, from, fromlen))
						{
							return FALSE;
						}
					}
					

				}
				Session.m_SessionBuffer.clear();
			}


			return TRUE;
		}

		static DWORD WINAPI ServerUDPThread(LPVOID lpParameter)
		{
			_Myt * pCtl = (_Myt *)lpParameter;
			_DebugOutput(_T("Server-%d ServerUDPThread entry....\n"),nName);
			std::vector<char> RecvMsg;
			RecvMsg.resize(512*1024);
			int nIoRetLen = 0;
			for (; pCtl->m_bClose == false;)
			{

				sockaddr_in from;
				int fromlen = sizeof(from);
				//_DebugOutput(_T("Wait for recv message"));
				nIoRetLen = recvfrom(pCtl->m_hSocket, (char *)&RecvMsg[0], RecvMsg.size(), 0, (struct sockaddr*)&from, &fromlen);
				if (nIoRetLen != SOCKET_ERROR)
				{
					_DebugOutputA("Server-%d Received message from ip=%s port=%d len=%d\n",nName, inet_ntoa(from.sin_addr), from.sin_port, nIoRetLen);
					IpSessionKey_Client ClientKey;
					ClientKey.src_addr = from.sin_addr.S_un.S_addr;
					ClientKey.src_port = from.sin_port;
					IpSessionClientT::iterator itClient = pCtl->m_ClientSessionMap.find(ClientKey);
					if (itClient == pCtl->m_ClientSessionMap.end()) {
						if (pCtl->m_ClientSessionMap.size() >= MAX_TRANSPORT_SESSION_COUNT)
						{
							_DebugOutputA("Server-%d Received message Session Too much from ip=%s port=%d len=%d \n",nName, inet_ntoa(from.sin_addr), from.sin_port, fromlen);
							continue;
						}
						pCtl->m_ClientSessionMap[ClientKey] = ClientSession();
						itClient = pCtl->m_ClientSessionMap.find(ClientKey);
					}
					itClient->second.m_SessionBuffer.insert(itClient->second.m_SessionBuffer.end(), RecvMsg.begin(), RecvMsg.begin()+ nIoRetLen);
					if (pCtl->ProcessRequest(itClient->second,&from, nIoRetLen) == FALSE)
					{
						_DebugOutputA("Server-%d ProcessRequest Fail from ip=%s port=%d len=%d \n", nName, inet_ntoa(from.sin_addr), from.sin_port, fromlen);
						pCtl->m_ClientSessionMap.erase(itClient);
					}

				}
				else
				{
					_DebugOutput(_T("Server-%d Received message error %d\n"),nName, WSAGetLastError());
					//break;
					Sleep(5000);
					closesocket(pCtl->m_hSocket);
					
					pCtl->reinit();
				}
			}
			_DebugOutput(_T("Server-%d ServerUDPThread leave...."),nName);
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
			do
			{
				SOCKADDR_IN LocalAddr;

				LocalAddr.sin_family = AF_INET;
				LocalAddr.sin_port = htons(m_nPort);
				LocalAddr.sin_addr.s_addr = INADDR_ANY;
				

				m_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

				if (m_hSocket == INVALID_SOCKET)
				{
					_DebugOutput(_T("Server-%d socket Fail %u..."), nName, ::WSAGetLastError());
					break;
				}
				if (::bind(m_hSocket, (sockaddr*)&LocalAddr, sizeof(LocalAddr)) == -1)
				{
					_DebugOutput(_T("Server-%d bind socket Fail %u..."), nName, ::WSAGetLastError());
					break;
				}

				int nRecvBuf = MAX_SERVER_TRANSPORT_BUFFER;
				setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
				//发送缓冲区
				int nSendBuf = MAX_SERVER_TRANSPORT_BUFFER;
				setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

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
						_DebugOutput(_T("Server-%d CreateThread fail %x....\n"), nName, GetLastError());
						break;
					}
					bRet = TRUE;

				} while (FALSE);
			}
			
			return bRet;

		}



	private:

	};

	template<int nUDPPort = 8484, unsigned int _nMagicCode = 'yssy',int nName=0>
	class TransportMiniUDPClient
	{
	public:
		BOOL m_bInitOk;
		SOCKADDR_IN m_ServerAddr;
		SOCKET m_hSocket;
		string m_szIp;
		u_short m_nPort;
		TransportMiniUDPClient() {
			m_bInitOk = FALSE;
			m_hSocket = INVALID_SOCKET;
			m_nPort = nUDPPort;
			m_szIp = "127.0.0.1";
		};
		~TransportMiniUDPClient() {};
		typedef TransportMiniUDPClient<nUDPPort, _nMagicCode, nName> _Myt;
		static _Myt & GetInstance()
		{
			static _Myt _self;
			return _self;
		}
		

		BOOL reinit()
		{
			if (m_hSocket != INVALID_SOCKET) closesocket(m_hSocket);

			m_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			if (m_hSocket == INVALID_SOCKET)
			{
				_DebugOutput(_T("Client-%d socket Fail %u...\n"), nName, ::WSAGetLastError());
				return FALSE;
			}

			int nRecvBuf = 256 * 1024;//设置为32K
			setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
			//发送缓冲区
			int nSendBuf = 256 * 1024;//设置为32K
			setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

			timeval tv = { MAX_CLIENT_TIMEOUT, 0 };
			setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));


			m_ServerAddr.sin_family = AF_INET;
			m_ServerAddr.sin_port = htons(m_nPort);
			m_ServerAddr.sin_addr.s_addr = inet_addr(m_szIp.c_str());

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
			return reinit();
		}
		BOOL CallInterfacePar(_tagCallParameter & tagCallParameter, _tagCallParameter & RetParameter, SYSTEMERROR & error)
		{
			return FALSE;
		}
		BOOL CallInterfaceStr(tstring & szInPar, tstring & szOutPar, SYSTEMERROR & error)
		{
			BOOL bRet = FALSE;
			BOOL bSysFail = TRUE;
			int len = sizeof(m_ServerAddr);

			TransportUDPRequestHead Head;
			//_tagstrParameter Par;
			//Par.szData = szInPar;
			//tstring szInPar1;
			//SerObjectToXmlBuffer(_tagstrParameter, Par, szInPar1);

			TransportUDPRequestHead ResponseHead;
			Head.nMagicCode = _nMagicCode;
			Head.nPacketLen = (szInPar.size() + 1) * sizeof(TCHAR) + sizeof(TransportUDPRequestHead);
			vector<u_char> RequestBuffer;
			RequestBuffer.resize(Head.nPacketLen- sizeof(TransportUDPRequestHead));
			//memcpy(&Buffer[0], &Head, sizeof(TransportUDPRequestHead));
			memcpy(&RequestBuffer[0], szInPar.c_str(), (szInPar.size() + 1) * sizeof(TCHAR));
			int nIoRetLen = 0;
			nIoRetLen = sendto(m_hSocket, (const char *)&Head, sizeof(Head), 0, (struct sockaddr*)&m_ServerAddr, len);
			do
			{

				if (nIoRetLen == sizeof(Head))
				{

					if (UDPSend(m_hSocket, RequestBuffer, &m_ServerAddr, len))
					{
						size_t nRecvLen = 0;
						nIoRetLen = recvfrom(m_hSocket, (char *)&ResponseHead, sizeof(ResponseHead), 0, (struct sockaddr*)&m_ServerAddr, &len);
						if (nIoRetLen == sizeof(ResponseHead))
						{
							std::vector<u_char> ResponseBuffer;
							if ((ResponseHead.nMagicCode != _nMagicCode) || (ResponseHead.nPacketLen > MAX_TRANSPORT_LEN))
							{
								error = Error_Sys_Transport_Fail;
								break;
							}
							nRecvLen += sizeof(TransportUDPRequestHead);
							ResponseBuffer.resize(ResponseHead.nPacketLen- sizeof(TransportUDPRequestHead));
							if (UDPRecv(m_hSocket, ResponseBuffer, &m_ServerAddr, len))
							{
								bRet = TRUE;
								szOutPar = (TCHAR*)&ResponseBuffer[0];
								//_tagstrParameter Par;
								//SerTCHARXmlBufferToObject(_tagstrParameter, Par, (szOutPar.c_str()));
								//szOutPar = Par.szData;
								bSysFail = FALSE;
								return bRet;
							}
						

						}
						else
						{
							_DebugOutput(_T("Client-%d  recv head fail %d %d\n"),nName,WSAGetLastError(), nIoRetLen);
						}
					}
					else
					{
						_DebugOutput(_T("Client-%d UDPSend Fail err=%d io=%d size=%d\n"), nName, WSAGetLastError(), nIoRetLen, RequestBuffer.size());
					}
				}
				else
				{
					_DebugOutput(_T("Client-%d send head Transport Fail err=%d io=%d size=%d\n"), nName, WSAGetLastError(), nIoRetLen, RequestBuffer.size());
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