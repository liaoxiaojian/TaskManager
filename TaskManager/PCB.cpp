#include "stdafx.h"
#include "PCB.h"


PCB::PCB()
: id("新进程")
, userName("默认用户")
, priority(GeneratePriority())
, enterTime(0)
, allTime(GenerateNeedTime())
, usedTime(0)
, runTime(0)
, readyTime(0)
, state(READY)
, rightTime(0)
, endTime(0)
{
}

PCB::PCB(int pid ,CString id, CString userName, int priority, int enterTime, int allTime){
	this->pid = pid;
	this->id = id;
	this->userName = userName;
	this->usedTime = 0;
	this->runTime = 0;
	this->readyTime = 0;
	this->rightTime = 0;
	this->endTime = 0;
	this->state = READY;
	this->priority = priority;
	this->enterTime = enterTime;
	this->allTime = allTime;
}

PCB::~PCB()
{
}

// 随机生成优先数
int PCB::GeneratePriority()
{
	return rand() % 40;	
}

//随机生成需要时间
int PCB::GenerateNeedTime()
{
	return rand() % 40+1;
}


CString PCB::getState()
{
	switch (this->state)
	{
	case READY:
		return  _T("就绪");
	case RUNNING:
		return _T("运行");
	case FINISHED:
		return _T("结束");
	default:
		break;
	}
	return _T("未知");
}

CString PCB::GetCurrentProDetail(){
	CString str;
	str.Format(_T("    %-3d   %-6s   %-6s   %-6d   %-8d   %-8d   %-10d   %-12d\r\n"), pid, id, userName, priority, enterTime, allTime, usedTime, runTime);
	return str;
}

CString PCB::GetReadyProDetail(){
	CString str;
	str.Format(_T("    %-3d   %-6s   %-6s   %-6d   %-8d   %-8d   %-10d   %-12d\r\n"), pid, id, userName, priority, enterTime, allTime, usedTime, readyTime);
	return str;
}

void PCB::calRightTime(){
	this->rightTime = (double)(endTime - enterTime) / usedTime;
}

CString PCB::GetCurrentProInfoHead(){
	CString str;
	str = "    PID   进程名   用户名   优先级   进入时间   所需时间   已运行时间   连续运行时间\r\n";
	return str;
}

CString PCB::GetReadyProInfoHead(){
	CString str;
	str = "    PID   进程名   用户名   优先级   进入时间   所需时间   已运行时间   连续就绪时间\r\n";
	return str;
}

CString PCB::GetFormatPid(){
	CString pid;
	pid.Format(_T("%3d"), this->pid);
	return pid;
}

CString PCB::GetFormatId(){
	CString id;
	id.Format(_T("%6s"), this->id);
	return id;
}

CString PCB::GetFormatUserName(){
	CString userName;
	userName.Format(_T("%6s"), this->userName);
	return userName;
}

CString PCB::GetFormatPriority(){
	CString priority;
	priority.Format(_T("%6d"), this->priority);
	return priority;
}

CString PCB::GetFormatEnterTime(){
	CString enterTime;
	enterTime.Format(_T("%8d"), this->enterTime);
	return enterTime;
}

CString PCB::GetFormatAllTime(){
	CString allTime;
	allTime.Format(_T("%8d"), this->allTime);
	return allTime;
}

CString PCB::GetFormatRunTime(){
	CString runTime;
	runTime.Format(_T("%10d"), this->runTime);
	return runTime;
}

CString PCB::GetFormatUsedTime(){
	CString usedTime;
	usedTime.Format(_T("%12d"), this->usedTime);
	return usedTime;
}

CString PCB::GetFormatReadyTime(){
	CString readyTime;
	readyTime.Format(__T("%5d"), this->readyTime);
	return readyTime;
}

