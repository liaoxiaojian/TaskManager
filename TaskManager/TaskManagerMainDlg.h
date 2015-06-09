
// TaskManagerMainDlg.h : 头文件

#pragma once
#include "afxcmn.h"
#include "DialogCurrentPro.h"
#include "DialogFinishedPro.h"
#include "DialogNewTask.h"
#include "DialogSettings.h"
#include "LinkedList.h"
#include "PCB.h"
#include "afxwin.h"

#define PERIOD_TASK  1

// TaskManagerMainDlg 对话框
class TaskManagerMainDlg : public CDialogEx
{
// 构造
public:
	TaskManagerMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TASKMANAGER_DIALOG };
private:

	DialogCurrentPro mDialogCurrenPro;//当前进程
	DialogFinishedPro mDialogFinishedPro;//已经结束进程
	DialogNewTask mDialogNewTask;
	DialogSettings mDialogSettings;
	
	LinkedList<PCB*> mFinishedProcess;

	int CPURunTime = 0;//CPU运行时间，以时间片为单位
	int timeSlot = 1000;//时间片
	int continueRunTimeSlots = 5;//连续运行的时间片的个数
	int tmp;//记录连续运行的时间片的个数
	int decPriority = 3;//运行进程减少的优先数
	int incPriority = 1;//就绪进程增加的优先数

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
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonNewTask();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//Tab栏切换控制
	CTabCtrl tabControl;
	// 新建任务按钮点击控制
	CButton buttonNewTask;
	CStatic CPURunTimeTextCtrl;

};
