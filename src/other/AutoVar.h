#pragma once
#include "BaseFunctionTool.h"
//#include "SerIni.h"

#include "MacroTool.h"

#include "Sexp.h"

//#define AutoValParameter(par) CAutoVal(par)
//#define AutoValParameter(par,par1) AutoValParameter(par),AutoValParameter(par1)


//自动参数列表



#define TemplateParameterBase(_t) typename _t
#define FunctionParameterBase(_t) _t _t##par
#define CodeParameterRender(_t)	par.push_back(_t##par);



/*
#define DefineTemplateParameter(_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)\
	template<AddCodeN(TemplateParameterBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)>\
	vector<CAutoVal> operator()(\
	AddCodeN(FunctionParameterBase,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20))\
	{\
	vector<CAutoVal>   par;\
	par.clear();\
	Code(CodeParameterRender,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20) \
	return par;\
};\



#define DefineTemplateParameter(_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60 )\
	template<AddCodeN(TemplateParameterBase,_FieldNum,\
	_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60 )>\
	vector<CAutoVal> operator()(\
	AddCodeN(FunctionParameterBase,_FieldNum,\
	_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60 ))\
	{\
	vector<CAutoVal>   par;\
	par.clear();\
	Code(CodeParameterRender,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60 ) \
	return par;\
};\

*/


#define DefineTemplateParameter(_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60, \
	_Field61,_Field62,_Field63,_Field64,_Field65,_Field66,_Field67,_Field68,_Field69,_Field70,_Field71,_Field72,_Field73,_Field74,_Field75,_Field76,_Field77,_Field78,_Field79,_Field80, \
	_Field81,_Field82,_Field83,_Field84,_Field85,_Field86,_Field87,_Field88,_Field89,_Field90,_Field91,_Field92,_Field93,_Field94,_Field95,_Field96,_Field97,_Field98,_Field99,_Field100, \
	_Field101,_Field102,_Field103,_Field104,_Field105,_Field106,_Field107,_Field108,_Field109,_Field110,_Field111,_Field112,_Field113,_Field114,_Field115,_Field116,_Field117,_Field118,_Field119,_Field120)\
	template<AddCodeN(TemplateParameterBase,_FieldNum,\
	_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60, \
	_Field61,_Field62,_Field63,_Field64,_Field65,_Field66,_Field67,_Field68,_Field69,_Field70,_Field71,_Field72,_Field73,_Field74,_Field75,_Field76,_Field77,_Field78,_Field79,_Field80, \
	_Field81,_Field82,_Field83,_Field84,_Field85,_Field86,_Field87,_Field88,_Field89,_Field90,_Field91,_Field92,_Field93,_Field94,_Field95,_Field96,_Field97,_Field98,_Field99,_Field100, \
	_Field101,_Field102,_Field103,_Field104,_Field105,_Field106,_Field107,_Field108,_Field109,_Field110,_Field111,_Field112,_Field113,_Field114,_Field115,_Field116,_Field117,_Field118,_Field119,_Field120)>\
	vector<CAutoVal> operator()(\
	AddCodeN(FunctionParameterBase,_FieldNum,\
	_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
	_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
	_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60, \
	_Field61,_Field62,_Field63,_Field64,_Field65,_Field66,_Field67,_Field68,_Field69,_Field70,_Field71,_Field72,_Field73,_Field74,_Field75,_Field76,_Field77,_Field78,_Field79,_Field80, \
	_Field81,_Field82,_Field83,_Field84,_Field85,_Field86,_Field87,_Field88,_Field89,_Field90,_Field91,_Field92,_Field93,_Field94,_Field95,_Field96,_Field97,_Field98,_Field99,_Field100, \
	_Field101,_Field102,_Field103,_Field104,_Field105,_Field106,_Field107,_Field108,_Field109,_Field110,_Field111,_Field112,_Field113,_Field114,_Field115,_Field116,_Field117,_Field118,_Field119,_Field120))\
	{\
		ContainerT   par;\
		par.clear();\
		Code(CodeParameterRender,_FieldNum,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20, \
		_Field21,_Field22,_Field23,_Field24,_Field25,_Field26,_Field27,_Field28,_Field29,_Field30,_Field31,_Field32,_Field33,_Field34,_Field35,_Field36,_Field37,_Field38,_Field39,_Field40, \
		_Field41,_Field42,_Field43,_Field44,_Field45,_Field46,_Field47,_Field48,_Field49,_Field50,_Field51,_Field52,_Field53,_Field54,_Field55,_Field56,_Field57,_Field58,_Field59,_Field60, \
		_Field61,_Field62,_Field63,_Field64,_Field65,_Field66,_Field67,_Field68,_Field69,_Field70,_Field71,_Field72,_Field73,_Field74,_Field75,_Field76,_Field77,_Field78,_Field79,_Field80, \
		_Field81,_Field82,_Field83,_Field84,_Field85,_Field86,_Field87,_Field88,_Field89,_Field90,_Field91,_Field92,_Field93,_Field94,_Field95,_Field96,_Field97,_Field98,_Field99,_Field100, \
		_Field101,_Field102,_Field103,_Field104,_Field105,_Field106,_Field107,_Field108,_Field109,_Field110,_Field111,_Field112,_Field113,_Field114,_Field115,_Field116,_Field117,_Field118,_Field119,_Field120 ) \
		return par;\
	};\



#define AutoParameter(...) CAutoParameter()(__VA_ARGS__)
#define Sexp(...) CAutoParameter()(__VA_ARGS__)
#define DefParameter(Name,...) CAutoParameter::ContainerT Name=CAutoParameter()(__VA_ARGS__)

class CAutoVal;

class CAutoParameter
{
public:
	CAutoParameter(){};
	~CAutoParameter(){};
	typedef vector<CAutoVal> ContainerT;
	/*
	template<AddCodeN(TemplateParameterBase,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)>
	void AutoValParameter(list<CAutoVal>  & par,
		AddCodeN(FunctionParameterBase,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20))
	{
		par.clear();
		Code(CodeParameterRender,16,_Field1,_Field2,_Field3,_Field4,_Field5,_Field6,_Field7,_Field8,_Field9,_Field10,_Field11,_Field12,_Field13,_Field14,_Field15,_Field16,_Field17,_Field18,_Field19,_Field20)
	}
	*/
	//DefineTemplateParameter(1,T1);

	DefineTemplateParameterList;
	/*
	DefineTemplateParameter(1,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(2,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(3,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(4,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(5,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);

	DefineTemplateParameter(6,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(7,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(8,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(9,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(10,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);


	DefineTemplateParameter(11,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(12,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(13,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(14,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(15,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);


	DefineTemplateParameter(16,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(17,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(18,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(19,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	DefineTemplateParameter(20,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20);
	*/
	
	
	/*DefineTemplateParameter(1,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(2,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(3,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(4,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(5,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);

	DefineTemplateParameter(6,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(7,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(8,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(9,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(10,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);


	DefineTemplateParameter(11,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(12,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(13,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(14,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(15,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);


	DefineTemplateParameter(16,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(17,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(18,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(19,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(20,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);

	DefineTemplateParameter(21,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(22,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(23,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(24,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(25,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);


	DefineTemplateParameter(26,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(27,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(28,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(29,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);
	DefineTemplateParameter(30,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30);*/
	

/*
	template<typename T1,typename T2>
	list<CAutoVal> operator()(T1 t1,T2 t2)
	{
		list<CAutoVal>   par;
		par.push_back(t1);
		par.push_back(t2);
		return par;
	}
	*/
protected:

private:
};


//自动变量


enum ValType
{
	typeError=0,
	typeANSIString,
	typeUnicodeString,
	typeInt,
	typeUint,
	typeLong,
	typeUlong,

	typeLL,
	typeInt64,
	typeChar,
	typeUchar,
	typeFloat,
	typeDouble,
	typeShort,
	typeUshort,
	typeBOOL,
	typeboolen,
	typeDWORD,
	typeContainer,	//容器
};
//CMyString;
//VARTYPE
//类型转换向量表
typedef struct _tagTypeTransform
{
	ValType SrcValueType;

}TypeTransform;


//class CAutoParameter;

class CAutoVal
{
public:
	ValType m_ValType;
	union UnionVal
	{
		int iVal;
		unsigned int uiVal;
		long lVal;
		unsigned long ulVal;
		__int64 i64Val;
		float fVal;
		double lfVal;
		char cVal;
		unsigned char ucVal;
		short sVal;
		unsigned short usVal;
		bool bVal;
#ifdef WIN32
		LONGLONG llVal;
		BOOL BVal;
		DWORD dwVal;
#endif
	}m_Val;

	typedef CAutoParameter::ContainerT ContainerT;
	ContainerT m_ContainerVal;
	//vector
	//UnioVal m_Val;

	wstring_tmp m_UnicodeString;
	string_tmp m_ANSIString;

	CAutoVal(){m_ValType=typeError;};

	~CAutoVal(){};
	//拷贝构造
	template<typename tVal>
	CAutoVal(ValType & ValT,tVal & val)
	{
		m_ValType=ValT;
		if(m_ValType==typeBOOL)
		{
			m_Val.BVal=val;
		}else if(m_ValType==typeboolen)
		{
			m_Val.bVal=val;
		}else if(m_ValType==typeContainer)
		{
			m_ContainerVal=val;
		}else
		{
			//m_Val.bVal=val;
			memcpy((unsigned char *)&m_Val,(unsigned char *)&val,sizeof(UnionVal));
		}
	}

	template<typename PoolT>
	CAutoVal(tstring_pool<PoolT,wchar_t> & Val)
	{
		m_UnicodeString=Val.c_str();
		m_ValType=typeUnicodeString;
	}

	template<typename PoolT>
	CAutoVal(tstring_pool<PoolT, char> & Val)
	{
		m_ANSIString=Val.c_str();
		m_ValType=typeANSIString;
	}
	

	CAutoVal(const WCHAR * Val)
	{
		m_UnicodeString=Val;
		m_ValType=typeUnicodeString;
	}
	CAutoVal(const char * Val)
	{
		m_ANSIString=Val;
		m_ValType=typeANSIString;
	}
	
	
	CAutoVal(const unsigned int & Val)
	{
		m_Val.uiVal=Val;
		m_ValType=typeUint;
	}

	CAutoVal(const long & Val)
	{
		m_Val.lVal=Val;
		m_ValType=typeLong;
	}

	
	CAutoVal(const float & Val)
	{
		m_Val.fVal=Val;
		m_ValType=typeFloat;
	}
	CAutoVal(const double & Val)
	{
		m_Val.lfVal=Val;
		m_ValType=typeDouble;
	}
	CAutoVal(const bool & Val)
	{
		m_Val.bVal=Val;
		m_ValType=typeboolen;
	}

	CAutoVal(const unsigned long & Val)
	{
		m_Val.ulVal=Val;
		m_ValType=typeUlong;
	}
	CAutoVal(const int & Val)
	{
		m_Val.iVal=Val;
		m_ValType=typeInt;
	}
	CAutoVal(CAutoParameter::ContainerT & Container)
	{
		m_ContainerVal=Container;
		m_ValType=typeContainer;
	}


#ifdef WIN32
	/*CAutoVal(BOOL * Val)
	{
		m_Val.BVal=*Val;
		m_ValType=typeBOOL;
	}
	CAutoVal(DWORD * Val)
	{
		m_Val.dwVal=*Val;
		m_ValType=typeDWORD;
	}*/
	CAutoVal(const LONGLONG & Val)
	{
		m_Val.llVal=Val;
		m_ValType=typeLL;
	}

	CAutoVal(LPSTR Val)
	{
		m_ANSIString=Val;
		m_ValType=typeANSIString;
	}
	CAutoVal(LPWSTR Val)
	{
		m_UnicodeString=Val;
		m_ValType=typeUnicodeString;
	}
#else


#endif
	//类型转换
	operator string_tmp &()
	{
		
#define CASE_VAL(AutoType,Val,fmt) case AutoType: \
	sprintf_s(szVal,63,fmt,m_Val.Val);\
	m_ANSIString=szVal;\
		return m_ANSIString;\
		break;\


		char szVal[64]={0};

		switch (m_ValType)
		{
		case typeUnicodeString:
			return m_ANSIString;
			break;
		case typeANSIString:
			m_ANSIString=(char *)CMyString((WCHAR *)m_UnicodeString.c_str(),m_UnicodeString.length()*sizeof(WCHAR));
			return m_ANSIString;
		CASE_VAL(typeInt,iVal,"%d");
		CASE_VAL(typeUint,uiVal,"%u");
		CASE_VAL(typeLong,lVal,"%ld");
		CASE_VAL(typeUlong,ulVal,"%lu");


		CASE_VAL(typeInt64,i64Val,"%I64d");
		CASE_VAL(typeFloat,fVal,"%f");
		CASE_VAL(typeDouble,lfVal,"%lf");
		CASE_VAL(typeChar,cVal,"%c");
		CASE_VAL(typeUchar,ucVal,"%c");

		CASE_VAL(typeShort,sVal,"%hd");
		CASE_VAL(typeUshort,usVal,"%hu");
		CASE_VAL(typeLL,llVal,"%lld");
		//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
		CASE_VAL(typeDWORD,ucVal,"%lu");
		case typeboolen:
			{
				sprintf_s(szVal,63,"%s",m_Val.bVal==false?"false":"true");
			}
			break;
		case typeBOOL:
			{
				sprintf_s(szVal,63,"%s",m_Val.BVal==FALSE?"FALSE":"TRUE");
			}
			break;
		case typeContainer:
			{
				m_ANSIString="(";
				CAutoParameter::ContainerT::iterator itPos=m_ContainerVal.begin();
				for(unsigned int i=0;itPos!=m_ContainerVal.end();itPos++,i++)
				{
					string_tmp tmp=(string_tmp)*itPos;
					m_ANSIString+=tmp;
					if(i!=(m_ContainerVal.size()-1))
					{
						m_ANSIString+=" ";
					}
				}
				m_ANSIString+=")";
				return m_ANSIString;
			}
			break;
		default:
			break;
		}
		m_ANSIString=szVal;
		return m_ANSIString;
	}

	operator wstring_tmp & ()
	{
#define WCASE_VAL(AutoType,Val,fmt) case AutoType: \
	swprintf_s(szVal,63,L##fmt,m_Val.Val);\
	m_UnicodeString=szVal; \
	return m_UnicodeString;\
	break;\


		WCHAR szVal[64]={0};

		switch (m_ValType)
		{
		case typeUnicodeString:
			return m_UnicodeString;
			break;
		case typeANSIString:
			m_UnicodeString=(WCHAR *)CMyString((char *)m_ANSIString.c_str(),m_ANSIString.length());
			return m_UnicodeString;
			break;
			WCASE_VAL(typeInt,iVal,"%d");
			WCASE_VAL(typeUint,uiVal,"%u");
			WCASE_VAL(typeLong,lVal,"%ld");
			WCASE_VAL(typeUlong,ulVal,"%lu");


			WCASE_VAL(typeInt64,i64Val,"%I64d");
			WCASE_VAL(typeFloat,fVal,"%f");
			WCASE_VAL(typeDouble,lfVal,"%lf");
			WCASE_VAL(typeChar,cVal,"%c");
			WCASE_VAL(typeUchar,ucVal,"%c");

			WCASE_VAL(typeShort,sVal,"%hd");
			WCASE_VAL(typeUshort,usVal,"%hu");
			WCASE_VAL(typeLL,llVal,"%lld");
			//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
			WCASE_VAL(typeDWORD,ucVal,"%lu");
		case typeboolen:
			{
				swprintf_s(szVal,63,L"%s",m_Val.bVal==false?L"false":L"true");
			}
			break;
		case typeBOOL:
			{
				swprintf_s(szVal,63,L"%s",m_Val.BVal==FALSE?L"FALSE":L"TRUE");
			}
			break;
		case typeContainer:
			{
				m_UnicodeString=L"(";
				CAutoParameter::ContainerT::iterator itPos=m_ContainerVal.begin();
				for(unsigned int i=0;itPos!=m_ContainerVal.end();itPos++,i++)
				{
					wstring_tmp tmp=(wstring_tmp&)*itPos;
					m_UnicodeString+=tmp;
					if(i!=(m_ContainerVal.size()-1))
					{
						m_UnicodeString+=L" ";
					}
				}
				m_UnicodeString+=L")";
				return m_UnicodeString;
			}
			break;
		default:
			break;
		}
		m_UnicodeString=szVal;
		return m_UnicodeString;
	}
	operator const char *()
	{
		return ((string_tmp&)*this).c_str();
	}
	operator const wchar_t *()
	{
		return ((wstring_tmp&)*this).c_str();
	}

#define COMMON_TRANS(DstType,AutoType,Val,szFmt) \
	operator DstType () \
	{\
		if (m_ValType==AutoType)\
		{\
			return m_Val.Val;\
		}else if (m_ValType==typeANSIString)\
		{\
			sscanf_s(m_ANSIString.c_str(),szFmt,&m_Val.Val);\
		}else if (m_ValType==typeUnicodeString)\
		{\
			swscanf_s(m_UnicodeString.c_str(),L##szFmt,&m_Val.Val);\
		}else\
		{\
			CAutoVal tmp=(tstring_tmp&)*this;\
			*this=tmp;\
			return (DstType)*this;\
		}\
		return m_Val.Val;\
	};\

	/*
	int iVal;
	unsigned int uiVal;
	long lVal;
	unsigned long ulVal;
	__int64 i64Val;
	float fVal;
	double eVal;
	char cVal;
	unsigned char ucVal;

	short sVal;
	unsigned short usVal;
	bool bVal;
	#ifdef WIN32
	LONGLONG llVal;
	BOOL BVal;
	DWORD dwVal;
	*/
	COMMON_TRANS(int,typeInt,iVal,"%d");
	COMMON_TRANS(unsigned int,typeUint,uiVal,"%u");
	COMMON_TRANS(long,typeLong,lVal,"%ld");
	COMMON_TRANS(unsigned long,typeUlong,ulVal,"%lu");


	COMMON_TRANS(__int64,typeInt64,i64Val,"%I64d");

	COMMON_TRANS(float,typeFloat,fVal,"%f");
	COMMON_TRANS(double,typeDouble,lfVal,"%lf");
	COMMON_TRANS(char,typeChar,cVal,"%c");
	COMMON_TRANS(unsigned char,typeUchar,ucVal,"%c");

	COMMON_TRANS(short,typeShort,sVal,"%hd");
	COMMON_TRANS(unsigned short,typeUshort,usVal,"%hu");
	//COMMON_TRANS(bool,typeDouble,"%lf");
	operator bool () 
	{
		if (m_ValType==typeboolen)
		{
			return m_Val.bVal;
		}else if (m_ValType==typeUnicodeString)
		{
			//sscanf(m_ANSIString,szFmt,&m_Val.Val);
			if(wstring_tmp(L"false")==m_UnicodeString)
			{
				return false;
			}else if(wstring_tmp(L"true")==m_UnicodeString)
			{
				return true;
			}
		}else if (m_ValType==typeANSIString)
		{
			if(string_tmp("false")==m_ANSIString)
			{
				return false;
			}else if(string_tmp("true")==m_ANSIString)
			{
				return true;
			}
		}
		*(unsigned int *)0=0;
		
		return false;
	};
	operator CAutoParameter::ContainerT ()
	{
		if (m_ValType==typeContainer)
		{
			return m_ContainerVal;
		}else if (m_ValType==typeUnicodeString)
		{
			m_ContainerVal=CSexp<ContainerT>(m_UnicodeString);
		}else if (m_ValType==typeANSIString)
		{
			m_ContainerVal=CSexp<ContainerT>(m_ANSIString);
		}else
		{
			*(unsigned int *)0=0;
		}
		
		return m_ContainerVal;
	}

	

#ifdef WIN32
	//COMMON_TRANS(LONGLONG,typeLL,llVal,"%ll");
	//COMMON_TRANS(BOOL,typeBOOL,ucVal,"%c");
	//COMMON_TRANS(DWORD,typeDWORD,dwVal,"%lu");

	/*operator BOOL () 
	{
		if (m_ValType==typeboolen)
		{
			return m_Val.bVal;
		}else if (m_ValType==typeUnicodeString)
		{
			//sscanf(m_ANSIString,szFmt,&m_Val.Val);
			if(wstring(L"FALSE")==m_UnicodeString)
			{
				return FALSE;
			}else if(wstring(L"TRUE")==m_UnicodeString)
			{
				return TRUE;
			}
		}else if (m_ValType==typeANSIString)
		{
			if(string("FALSE")==m_ANSIString)
			{
				return FALSE;
			}else if(string("TRUE")==m_ANSIString)
			{
				return TRUE;
			}
		}
		*(unsigned int *)0=0;

		return FALSE;
	};*/

#endif


protected:

	
private:
};



