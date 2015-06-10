#pragma once
//工具类
#ifndef Util_h
#define Util_h

class Util
{
public:
	static CString strTime;//时间形式保存文件名

	Util();
	~Util();
	
	CString static IntToCString(int a);
	int static CStringToInt(CString str);
	CString static DoubleToCString(double a);
};

#endif

