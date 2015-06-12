#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
#include <iostream>
using namespace std;

// DialogNewTask 对话框

class DialogNewTask : public CDialogEx
{
	DECLARE_DYNAMIC(DialogNewTask)

public:
	DialogNewTask(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogNewTask();

// 对话框数据
	enum { IDD = Dialog_New_Task };
//pid数据
	int pid;
//辅助pid计数
	int tmpPid;
//进程名
	CString id;
//用户名
	CString userName;
//优先级
	CString priority;
//所需时间
	CString allTime;
//新任务链表
	LinkedList<PCB*> newTaskList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	// 初始化新进程队列列表选项
	void InitListNewTaskQ(CRect c);
	// 添加任务到列表
	void AddItemToList();

	CListCtrl listNewTaskQCtrl;
	CEdit processNameCtrl;
	CEdit userNameCtrl;
	CEdit priorityCtrl;
	CEdit allTimeCtrl;
	
	afx_msg void OnBnClickedTaskButtonAddToList();
	afx_msg void OnBnClickedOk();

	// 释放资源，值初始化
	void ClearAll();
	virtual void OnCancel();
	afx_msg void OnNMRClickNewTaskQ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
};
