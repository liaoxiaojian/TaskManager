#pragma once

#include "ListViewCurrentPro.h"
#include "Util.h"
#include "LinkedList.h"
#include "PCB.h"
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	// 初始化正在运行的进程
	void IninListCurrentPro(CRect crect);
	// 初始化进程队列
	void InitListProQ(CRect crect);

	CListCtrl ListCurrentProCtrl;
	CListCtrl ListProQCtrl;

	//数据刷新
	void NotifyDataSetChange();
	
	// CPU开始模拟进程调度算法
	void Execute(int decPriority,int incPriority,int runTimeSlots);
	// 获取从就绪队列进入运行队列的候选任务位置
	int GetCandidatePos();
	// 更新当前进程
	void UpdateCurrentPro(int decPriority);
	// 更新就绪队列
	void UpdateReadyPro(int incPriority);
	// 更新当前进程列表
	void UpdateListCPRO();
	// 更新就绪列表
	void UpdateListReady();
};