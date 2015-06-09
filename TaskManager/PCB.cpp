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
