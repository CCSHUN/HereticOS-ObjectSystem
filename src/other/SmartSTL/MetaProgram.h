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
//2008.3.7 叶树深 编译期编程


//模板工具
#ifndef _LINUX_
namespace TTL
{

	//斐波拉契
	template<int N>
	struct Fib
	{
		enum { nRet = Fib<N - 1>::nRet + Fib<N - 2>::nRet };
	};

	// 完全特化版
	template <>
	struct Fib<1>
	{
		enum { nRet = 1 };
	};


	// 完全特化版
	template <>
	struct Fib<0>
	{
		enum { nRet = 0 };
	};

	//求幂 x的a次方
	template<int x, int a>
	struct power
	{
		enum{ nRet = x*power<x, a - 1>::nRet };
	};

	template<int x>
	struct power<x, 0>
	{
		enum{ nRet = 1 };
	};

	//求对数 loga(x)
	template<int x, int a>
	struct log
	{
		enum{ nRet = log<x / a, a>::nRet + 1 };
	};

	template<int a>
	struct log<0, a>
	{
		enum{ nRet = -1 };
	};

	//
	//递归求和 x-0的所有通项式之和 Func是通项式


	

	//杨辉三角形每层数量通项式
	template<int nDepth, int nBitTreeNodeLog2>
	struct DepthTreeNodeCount
	{
		template<int nRebindDepth>
		struct rebind
		{
			typedef DepthTreeNodeCount<nRebindDepth, nBitTreeNodeLog2> other;
		};
		enum{ nRet = power<power<2, nBitTreeNodeLog2>::nRet, nDepth>::nRet };
	};

	

	//标记位生成
	template<unsigned int  nNum, unsigned int nBitSize, size_t nBitVal>
	struct MakeBitMask
	{
		enum : size_t{ nRet = ((MakeBitMask<nNum - 1, nBitSize, nBitVal>::nRet << nBitSize) | nBitVal) };
	};

	template<unsigned int nBitSize, size_t nBitVal>
	struct MakeBitMask<1, nBitSize, nBitVal>
	{
		enum{ nRet = nBitVal };
	};

#ifndef  intel_cpp

	//编译时条件运行
#define _default -1
	struct _NullCase
	{
		typedef  _NullCase _Next;
	};

	template<unsigned int nCaseVal, typename CodeTypeT, typename NextCase>
	struct _Case
	{
		enum{ CaseVal = nCaseVal };
		typedef   NextCase _Next;
		typedef   CodeTypeT CodeType;
	};

	template<typename CodeTypeT>
	struct _Case<_default, CodeTypeT, _NullCase>
	{
		enum{ CaseVal = _default };
		typedef   _NullCase _Next;
		typedef   CodeTypeT CodeType;
	};

	template<bool ConditionT, typename CodeTypeT, typename CodeType1T>
	struct _IF
	{
		//typedef CodeTypeT CodeType;
	};
	template< typename CodeTypeT, typename CodeType1T>
	struct _IF<true, CodeTypeT, CodeType1T>
	{
		typedef  CodeTypeT CodeType;
	};
	template< typename CodeTypeT, typename CodeType1T>
	struct _IF<false, CodeTypeT, CodeType1T>
	{
		typedef  CodeType1T CodeType;
	};

	template<unsigned int nVal, typename CaseExpT>
	struct _Switch
	{
		enum : bool{ found = ((CaseExpT::CaseVal == nVal) || (CaseExpT::CaseVal == _default)) };
		typedef typename _IF<found, typename CaseExpT::CodeType, typename _Switch<nVal, typename CaseExpT::_Next>::RetType >::CodeType RetType;
	};
	template<unsigned int nVal>
	struct _Switch<nVal, _NullCase>
	{
		typedef  _NullCase RetType;
	};


	template<int x, typename Func>
	struct Sum
	{
		enum{ nRet = Func::rebind<x>::other::nRet + Sum<x - 1, Func>::nRet };
	};

	template<typename Func>
	struct Sum<0, Func>
	{
		enum{ nRet = Func::rebind<0>::other::nRet };
	};
	//         a
	//       /   \
	//      b     c           nDepth=1  nBitTreeNodeLog2=1
	//     / \   / \
	//    d   e f   g         nDepth=2
	template<int nDepth, int nTreeNodeLog2>
	struct TotalTreeNodeCount
	{
		enum{ nRet = Sum<nDepth, DepthTreeNodeCount<nDepth, nTreeNodeLog2>>::nRet };
	};

#endif 
}

#endif

namespace TTL_CEXP
{
	//求幂 x的a次方

	constexpr  int  power(int x, int a)
	{
		return a == 0 ? 1 : x*power(x, a - 1);
	};
	
	template<int nDepth, int nBitTreeNodeLog2>
	struct DepthTreeNodeCount
	{
		constexpr  int rebind(int nRebindDepth)
		{
			return power(power(2, nBitTreeNodeLog2), nRebindDepth);
		};

	};
	


	template<typename FuncT>
	constexpr int Sum(int s, FuncT func)
	{
		return s == 0 ? func.rebind(s) : func.rebind(s) + Sum(s - 1, func);
	}
	//         a
	//       /   \
	//      b     c           nDepth=1  nBitTreeNodeLog2=1
	//     / \   / \
	//    d   e f   g         nDepth=2


	
	template<int nDepth, int nTreeNodeLog2>
	constexpr int TotalTreeNodeCount()
	{
		return  Sum(nDepth, DepthTreeNodeCount<nDepth, nTreeNodeLog2>());
	};
	/*
	
	struct TotalTreeNodeCount
	{
		enum { nRet = Sum(nDepth, DepthTreeNodeCount<nDepth, nTreeNodeLog2>()) };
	};
	*/
}


