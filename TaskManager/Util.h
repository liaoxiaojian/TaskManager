#pragma once
//π§æﬂ¿‡
#ifndef Util_h
#define Util_h

class Util
{
public:
	Util();
	~Util();
	
	CString static IntToCString(int a);
	int static CStringToInt(CString str);
};

#endif

