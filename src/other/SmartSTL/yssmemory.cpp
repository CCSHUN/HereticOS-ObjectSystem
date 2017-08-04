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
#include "yssmemory.hpp"

/*
#define MEMMGR_TYPE_DEF			0
#define MEMMGR_TYPE_1			1
#define MEMMGR_TYPE_STATICGC	2
#define MEMMGR_TYPE_OS			3*/
unsigned int g_hTlsForHeap=::TlsAlloc();

MemoryMgr<PointInterfaceForMemoryMgr<IndexType> > g_MemoryMgrDef;
MemoryMgr_OS<PointInterfaceForMemoryMgr<IndexType>,0> g_MemoryMgrOS;
MemoryMgr_OS_VirtualMem<PointInterfaceForMemoryMgr<IndexType>, 0> g_MemoryMgrOSVm;
//MemoryMgr_StaticGC<PointInterfaceForMemoryMgr<IndexType>,MEMMGR_TYPE_OS,4*1024*1024,256>	g_StaticGC;
//MemoryMgr_StaticGC<PointInterfaceForMemoryMgr<IndexType>, MEMMGR_TYPE_OS, 4 * 1024 * 1024, 512>	g_StaticGC_Tmp;
//MemoryMgr_BitMap<PointInterfaceForMemoryMgr<IndexType>, MEMMGR_TYPE_OS_VM, 6, 12,2, 2> g_BitMapMgr;
#ifndef intel_cpp
//MemoryMgr_BitMap<PointInterfaceForMemoryMgr<IndexType>, MEMMGR_TYPE_OS_VM, 6, 1, 1, 2> g_BitMapMgr;
#endif 

//cache 32*4096   16²ã×î´ó64k*32
//MemoryMgr_FreeList<PointInterfaceForMemoryMgr<IndexType>, MEMMGR_TYPE_OS, 16, 6, 4096> g_FreeListMgr;

MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >* g_pMemoryMgr[] = { 
	static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_MemoryMgrDef),
	static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_MemoryMgrDef),
	//static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_StaticGC),
	//static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_StaticGC_Tmp),
	static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_MemoryMgrOS) ,
	static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_MemoryMgrOSVm),
#ifdef intel_cpp
	static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_FreeListMgr),
#else
	//static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_BitMapMgr),
#endif
	
	//static_cast<MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*>(&g_FreeListMgr)
};
/*
int initPoolSystem()
{

	g_MemoryMgrInterface[MEMMGR_TYPE_DEF] =( MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> > *)&g_MemoryMgrDef;
	g_MemoryMgrInterface[MEMMGR_TYPE_1] = (MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*)&g_MemoryMgrDef;
	g_MemoryMgrInterface[MEMMGR_TYPE_STATICGC] = (MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*)&g_StaticGC;
	g_MemoryMgrInterface[MEMMGR_TYPE_OS] = (MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> >*)&g_MemoryMgrOS;
	return 0;
}

int s=initPoolSystem();*/


//MemoryMgrInterface<PointInterfaceForMemoryMgr<IndexType> > * g_pMemoryMgr = &g_MemoryMgrInterface[0];