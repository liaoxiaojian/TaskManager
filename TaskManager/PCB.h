#pragma once
#ifndef PCB_H
#define PCB_H

#define READY 0//就绪
#define RUNNING 1//运行
#define FINISHED 2//结束

class PCB
{
public:
	PCB();
	PCB(int pid ,CString id,CString userName, int priority, int enterTime, int allTime);
	~PCB();
	int pid;//进场id
	// 进程的标识
	CString id;
	//用户名
	CString userName;
	// 优先数 范围[0,40]
	int priority;
	// 到达时间
	int enterTime;
	// 进程余下运行时间
	int allTime;
	// 已使用CPU的时间
	int usedTime;
	// 连续运行时间
	int runTime;
	// 连续就绪时间
	int readyTime;
	// 进程状态
	int state;
	// 代权周转时间
	double rightTime;
	//结束时间
	int endTime;

	// 随机生成优先数
	int static GeneratePriority();
	//随机生成所需运行时间
	int static GenerateNeedTime();
	//运行结束后计算带权周转时间
	void calRightTime();
	
	CString getState();
	//将信息头输出
	CString static GetCurrentProInfoHead();
	CString static GetReadyProInfoHead();

	//获取格式化输出数据
	CString GetCurrentProDetail();
	CString GetReadyProDetail();
};

#endif
