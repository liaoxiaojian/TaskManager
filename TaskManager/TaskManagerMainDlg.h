
// TaskManagerMainDlg.h : 头文件

#pragma once
#ifndef TASK_MANAGER_MAIN_DLG_H
#define TASK_MANAGER_MAIN_DLG_H

#include "DialogCurrentPro.h"
#include "afxcmn.h"
#include "DialogFinishedPro.h"
#include "DialogNewTask.h"
#include "DialogSettings.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxwin.h"

#define PERIOD_TASK  1
class DialogCurrentPro;

// TaskManagerMainDlg 对话框
class TaskManagerMainDlg : public CDialogEx
{
// 构造
public:
	TaskManagerMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TASKMANAGER_DIALOG };

	DialogCurrentPro mDialogCurrenPro;//当前进程
	DialogFinishedPro mDialogFinishedPro;//已经结束进程
	DialogNewTask mDialogNewTask;
	DialogSettings mDialogSettings;

	int CPURunTime;//CPU运行时间，以时间片为单位
	int timeSlot = 1000;//时间片
	int continueRunTimeSlots = 5;//连续运行的时间片的个数
	
	int decPriority = 3;//运行进程减少的优先数
	int incPriority = 1;//就绪进程增加的优先数

	int clickTimes = 0;//cpu控制键的点击次数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void Execute();
	void FinishTask();

	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonNewTask();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStopCpu();
	afx_msg void OnBnClickedButtonStepIn();
	afx_msg void OnBnClickedButtonFinishTask();

	//Tab栏切换控制
	CTabCtrl tabControl;
	// 新建任务按钮点击控制
	CButton buttonNewTask;
	CStatic CPURunTimeTextCtrl;
	CButton buttonCPUCtrl;
	CButton buttonStepInCtrl;
};

#endif
