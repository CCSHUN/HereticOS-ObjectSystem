#include "stdafx.h"
#include "TextIoSystem.h"
#include "HeapAnslyze.h"


void GetHeapMemInfo1(HANDLE hHeap, PROCESS_HEAP_ENTRY & CurHeap)
{
	ErrorPrinter_OutputDebugString error;
	error(_T("==================MemBegin=================\r\n"));
	if ((CurHeap.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0) {

		error(_T("BUSY Block(p=%p size=%u cbdata=%u 0x%x)"), CurHeap.lpData, HeapSize(hHeap, 0, CurHeap.lpData), CurHeap.cbData, CurHeap.cbData);

		if ((CurHeap.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0) {

			error(_T("MOVEABLE(%p)"), CurHeap.Block.hMem);

		}

		if ((CurHeap.wFlags & PROCESS_HEAP_ENTRY_DDESHARE) != 0) {

			error(_T(", DDESHARE"));

		}

	}
	else if ((CurHeap.wFlags & PROCESS_HEAP_REGION) != 0) {

		error(_T("Region(index=%u cbdata=%u 0x%x)\r\n  %d bytes committed\r\n")
			_T("  %d bytes uncommitted\r\n  First block address: %#p\r\n")
			_T("  Last block address: %#p\r\n"), 
			CurHeap.iRegionIndex, CurHeap.cbData, CurHeap.cbData,
			CurHeap.Region.dwCommittedSize,
			CurHeap.Region.dwUnCommittedSize,
			CurHeap.Region.lpFirstBlock,
			CurHeap.Region.lpLastBlock);

	}
	else if ((CurHeap.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0) {

		error(_T("Uncommitted range (lpData=%p,cbData=%u 0x%x)\r\n"), CurHeap.lpData, CurHeap.cbData, CurHeap.cbData);

	}
	else {
		DWORD nSize = 0; 
		
		error(_T("Block(%p size=%u cbdata=%u 0x%x)\r\n"), CurHeap.lpData, nSize, CurHeap.cbData, CurHeap.cbData);

	}

	error(_T("==================MemEnd=================\r\n"));
}


void GetHeapMemInfo(HANDLE hHeap, PROCESS_HEAP_ENTRY & CurHeap, _tagHeapInfoSet & HeapInfo)
{
	ErrorPrinter_OutputDebugString error;
	//error(_T("==================MemBegin=================\r\n"));
	if ((CurHeap.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0) {

		//error(_T("BUSY Block(p=%p size=%u cbdata=%u 0x%x)"), CurHeap.lpData, HeapSize(hHeap, 0, CurHeap.lpData), CurHeap.cbData, CurHeap.cbData);

		HeapInfo.nTotalSize += CurHeap.cbData;
		HeapInfo.nTotalHeadSize += CurHeap.cbOverhead;

		HeapInfo.nUseBlockCount++;
		HeapInfo.nUseBlockSize += CurHeap.cbData;
		if (HeapInfo.meminfo.find(CurHeap.cbData) == HeapInfo.meminfo.end()) HeapInfo.meminfo[CurHeap.cbData]=0;
		
		HeapInfo.meminfo[CurHeap.cbData]++;
	}
	else if ((CurHeap.wFlags & PROCESS_HEAP_REGION) != 0) {

		/*error(_T("Region(index=%u cbdata=%u 0x%x)\r\n  %d bytes committed\r\n")
			_T("  %d bytes uncommitted\r\n  First block address: %#p\r\n")
			_T("  Last block address: %#p\r\n"),
			CurHeap.iRegionIndex, CurHeap.cbData, CurHeap.cbData,
			CurHeap.Region.dwCommittedSize,
			CurHeap.Region.dwUnCommittedSize,
			CurHeap.Region.lpFirstBlock,
			CurHeap.Region.lpLastBlock);*/
		HeapInfo.nTotalSize += CurHeap.cbData;
		HeapInfo.nTotalHeadSize += CurHeap.cbOverhead;
		HeapInfo.nRangeSize += CurHeap.Region.dwCommittedSize;
		HeapInfo.nNotCommittedSize += CurHeap.Region.dwUnCommittedSize;
		HeapInfo.nRangeCount++;
	}
	else if ((CurHeap.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0) {

		//error(_T("Uncommitted range (lpData=%p,cbData=%u 0x%x)\r\n"), CurHeap.lpData, CurHeap.cbData, CurHeap.cbData);
		HeapInfo.nTotalSize += CurHeap.cbData;
		HeapInfo.nNotCommittedSize += CurHeap.cbData;
		HeapInfo.nRangeUnUsedCount++;
	}
	else {
		DWORD nSize = 0;
		HeapInfo.nTotalSize += CurHeap.cbData;
		HeapInfo.nNotUsedSize += CurHeap.cbData;
		HeapInfo.nNotUsedCount++;
		//error(_T("Block(%p size=%u cbdata=%u 0x%x)\r\n"), CurHeap.lpData, nSize, CurHeap.cbData, CurHeap.cbData);

	}

	//error(_T("==================MemEnd=================\r\n"));
}

void GetHeapInfo(bool bCompact, bool bCheck, bool bBufferInfo)
{
	_tagHeapInfo HeapInfoMap;
	

	HANDLE HeapArray[4096];

	tstring szTmp;
	DWORD nTotal = GetProcessHeaps(4096, &HeapArray[0]);
	DWORD i = 0;
	ErrorPrinter_OutputDebugString error;
	

	for (i = 0; i < nTotal; i++)
	{
		PROCESS_HEAP_ENTRY CurHeap;
		_tagHeapInfoSet HeapInfo;
		ULONG info = 0xff;
		SIZE_T RetLen = sizeof(ULONG);
		HeapQueryInformation(HeapArray[i], HeapCompatibilityInformation, &info, RetLen, &RetLen);

		//error.cat(szTmp, _T("%u %p(%u %u) \r\n"), i, HeapArray[i], info, HeapSize(HeapArray[i], 0, HeapArray[i]));
		HeapInfo.hHeap = HeapArray[i];
		HeapInfo.nHeapType = info;
		if (bCompact)
		{
			HeapLock(HeapArray[i]);
			HeapCompact(HeapArray[i], 0);
			HeapUnlock(HeapArray[i]);
		}

		CurHeap.lpData = 0;
		//error(_T("==================================HeapBegin(%p)==================================\r\n"), HeapArray[i]);
		if (bBufferInfo || bCheck)
		{
			do
			{
				BOOL bOk = FALSE;

				if (HeapLock(HeapArray[i]))
				{

					bOk = HeapWalk(HeapArray[i], &CurHeap);
					HeapUnlock(HeapArray[i]);
				}
				if (bOk)
				{
					if (bCheck && (CurHeap.wFlags & PROCESS_HEAP_ENTRY_BUSY))
					{
						if (HeapValidate(HeapArray[i], 0, CurHeap.lpData) == FALSE)
						{
							error(_T("HeapError (%p) \r\n"), HeapArray[i]);
						}
					}
					if (bBufferInfo)
					{
						GetHeapMemInfo(HeapArray[i], CurHeap, HeapInfo);

					}
				}
				else
				{
					break;
				}

			} while (true);
		}
		
		HeapInfoMap.heapinfo[HeapArray[i]] = HeapInfo;
		//error(_T("==================================HeapEnd(%p)==================================\r\n\r\n\r\n"), HeapArray[i]);

	}

	//打印堆使用信息
	error(_T("==================HeapInfoBegin(Count=%u ProcessHeap(%p) HeapAnslyzeHeap(%p) bCompact=%d bCheck=%d bBufferInfo=%d )=================\r\n"), 
		HeapInfoMap.heapinfo.size(), GetProcessHeap(), NULL,/*HeapInfoMap.heapinfo.m_Heap,*/ bCompact, bCheck, bBufferInfo);
	_tagHeapInfo::HeapInfoMapT::iterator itHeap=HeapInfoMap.heapinfo.begin();
	for (i=0; itHeap != HeapInfoMap.heapinfo.end();itHeap++)
	{
		error(_T("%u %p(%u) info(datasize=%u ctlsize=%u) used(c=%u,s=%u) unuse(c=%u,s=%u) commit(c=%u,s=%u) uncommit(c=%u,s=%u) "),i,itHeap->first,
			itHeap->second.nHeapType, itHeap->second.nTotalSize, itHeap->second.nTotalHeadSize,
			itHeap->second.nUseBlockCount, itHeap->second.nUseBlockSize,
			itHeap->second.nNotUsedCount, itHeap->second.nNotUsedSize,
			itHeap->second.nRangeCount,itHeap->second.nRangeSize,
			itHeap->second.nRangeUnUsedCount,itHeap->second.nNotCommittedSize
			);
		i++;
	}
	error(_T("==================HeapInfoEnd(Count=%u ProcessHeap(%p))=================\r\n"), HeapInfoMap.heapinfo.size(), GetProcessHeap());
}

void GetHeapInfo1(bool bCompact,bool bCheck,bool bBufferInfo)
{
	HANDLE HeapArray[4096];
	
	tstring szTmp;
	DWORD nTotal = ::GetProcessHeaps(4096, &HeapArray[0]);
	DWORD i = 0;
	ErrorPrinter_OutputDebugString error;
	error(_T("==================HeapInfoBegin(Count=%u ProcessHeap(%p))=================\r\n"), nTotal, GetProcessHeap());
	for (i = 0; i < nTotal; i++)
	{
		//if (i % 4 == 0) error.cat(szTmp, _T("\r\n%u "), (i / 4));
		ULONG info=0xff;
		SIZE_T RetLen=sizeof(ULONG);
		::HeapQueryInformation(HeapArray[i], HeapCompatibilityInformation, &info, RetLen, &RetLen);
		
		error.cat(szTmp, _T("%u %p(%u %u) \r\n"), i, HeapArray[i], info, HeapSize(HeapArray[i], 0, HeapArray[i]));
		if (bCompact)
		{
			HeapCompact(HeapArray[i], 0);
		}
	}

	error(szTmp);
	error(_T("\r\n==================HeapInfoEnd=================\r\n"));

	for (i=0;i<nTotal;i++)
	{
		PROCESS_HEAP_ENTRY CurHeap;
		CurHeap.lpData = 0;
		error(_T("==================================HeapBegin(%p)==================================\r\n"), HeapArray[i]);
		do
		{
			BOOL bOk = FALSE;

			if (::HeapLock(HeapArray[i]))
			{

				bOk = ::HeapWalk(HeapArray[i], &CurHeap);
				::HeapUnlock(HeapArray[i]);
			}
			if (bOk)
			{
				if (bCheck && (CurHeap.wFlags & PROCESS_HEAP_ENTRY_BUSY))
				{
					if (::HeapValidate(HeapArray[i], 0, CurHeap.lpData) == FALSE)
					{
						error(_T("HeapError (%p) \r\n"), HeapArray[i]);
					}
				}
				if (bBufferInfo)
				{
					GetHeapMemInfo1(HeapArray[i], CurHeap);
				}
			}
			else
			{
				break;
			}

		} while (true);
		error(_T("==================================HeapEnd(%p)==================================\r\n\r\n\r\n"), HeapArray[i]);
		
	}
}


inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | 
		_CRTDBG_LEAK_CHECK_DF 
		//_CRTDBG_CHECK_ALWAYS_DF|
		//_CRTDBG_ALLOC_MEM_DF|
		//_CRTDBG_DELAY_FREE_MEM_DF
		//_CRTDBG_CHECK_CRT_DF
		);
}
