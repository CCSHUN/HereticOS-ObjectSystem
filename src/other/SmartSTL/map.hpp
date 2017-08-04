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
//2005.4.16 智能指针重制map
#include "yssmemory.hpp"
#include "SmartPoint.hpp"
#include "AVLTree1.hpp"

namespace YSS
{
	template<typename KeyType, typename ValType>
	class MapSet
	{
	public:
		typedef MapSet< KeyType, ValType> _Myt;
		MapSet() {};
		~MapSet() {};
		KeyType first;
		ValType second;

	protected:

	private:
	};

	template<typename KeyType, typename ValType>
	bool operator<(const MapSet<KeyType, ValType> & lift, const MapSet<KeyType, ValType> & right)
	{
		return lift.first<right.first;
	}

	//CompareT 暂时不用，提供的类型必须支持<运算符
	template<typename KeyType, typename ValType, typename CompareT, class PointT = MemReMapPoint<MapSet<KeyType, ValType>> >
	class map :public AVLTree<MapSet<KeyType, ValType>, PointT>
	{
	public:
		typedef AVLTree<MapSet<KeyType, ValType>, PointT> _base;
		typedef MapSet<KeyType, ValType> Set;
		map() {};
		~map() {};
		ValType& operator[](const KeyType& KeyVal)
		{
			Set s; s.first = KeyVal;
			iterator itFind = _base::find(s);
			if (itFind != end())
			{
				return itFind->second;
			}
			else
			{
				iterator itOut;
				if (Insert(s, itOut))
				{
					return itOut->second;
				}
			}
			return *(ValType*)0;
		}
		iterator find(const KeyType & KeyVal)
		{
			Set s; s.first = KeyVal;
			return _base::find(s);
		}
	protected:

	private:
	};
}
