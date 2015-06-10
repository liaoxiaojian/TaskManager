#pragma once

#ifndef DIALOG_CURRENT_PRO_H
#define DIALOG_CURRENT_PRO_H

#include "ListViewCurrentPro.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxcmn.h"
#include "afxwin.h"

// DialogCurrentPro 对话框

class DialogCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCurrentPro)

public:
	DialogCurrentPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCurrentPro();

// 对话框数据
	enum { IDD = Dialog_Finished_Pro };

	PCB* mCurrentProcess;
	LinkedList<PCB*> mReadyProcess;

	int continueRunTimeSlots;
	int tmp;//记录连续运行的时间片的个数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	// 初始化正在运行的进程
	void IninListCurrentPro(CRect crect);
	// 初始化进程队列
	void InitListProQ(CRect crect);
	virtual BOOL DestroyWindow();

	CListCtrl ListCurrentProCtrl;
	CListCtrl ListProQCtrl;

	//数据刷新
	void NotifyDataSetChange();
	
	// CPU开始模拟进程调度算法
	PCB*  Execute(int decPriority, int incPriority, int cpuRunTime);
	// 获取从就绪队列进入运行队列的候选任务位置
	int GetCandidatePos();
	// 更新当前进程
	PCB* UpdateCurrentPro(int decPriority);
	// 更新就绪队列
	void UpdateReadyPro(int incPriority);
	// 更新当前进程列表
	void UpdateListCPRO();
	// 更新就绪列表
	void UpdateListReady();
	//当前进程写入文件 
	void WriteCurrentProToFile(int cpuRunTime);
	//就绪进程写入文件
	void WriteReadyProToFile();

	// 获取当前时间并保存到curTime   
	CTime curTime = CTime::GetCurrentTime();
	// 将当前时间curTime对象格式化为字符串   
	CString strTime = curTime.Format(_T("%Y_%m_%d_%H_%M_%S"));

	CFile file;

	CString currentProHead;
	CString readyProHead;
	afx_msg void OnStnClickedAvgRightTime();
};

#endif 
