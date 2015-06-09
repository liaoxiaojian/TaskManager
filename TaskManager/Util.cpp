#include "stdafx.h"
#include "Util.h"


Util::Util()
{
}


Util::~Util()
{
}


CString  Util::IntToCString(int a)
{
	CString str;
	str.Format(_T("%d"), a);
	return str;
}

int Util::CStringToInt(CString str){
	return _ttoi(str);
}
