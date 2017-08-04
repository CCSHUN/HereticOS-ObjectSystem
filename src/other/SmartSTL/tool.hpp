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
#include "MetaProgram.h"
#define IN
#define OUT

#define YSS_ASSERT(c) if((c)) {*(int *)0=0;}


//模板类型参数重邦定
#define RebindT1(Type,Template) Type::rebind<Template>::other
#define DefRebindT1(MyType) \
	template<class _Other> \
struct rebind \
{	\
	typedef MyType<_Other> other;\
};\


#define RebindT2(Type,Template,Template1) Type::rebind<Template,Template1>::other
#define DefRebindT2(MyType) \
	template<class _Other,class _Other1> \
struct rebind \
{	\
	typedef MyType<_Other,_Other1> other;\
};\


#define RebindT3(Type,Template,Template1,Template2) Type::rebind<Template,Template1,Template2>::other
#define DefRebindT3(MyType) \
	template<class _Other,class _Other1,class _Other2> \
struct rebind \
{	\
	typedef MyType<_Other> other;\
};\


