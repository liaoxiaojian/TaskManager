// DialogCurrentPro.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogCurrentPro.h"
#include "afxdialogex.h"
#include "LinkedList.h"
#include "PCB.h"

// DialogCurrentPro 对话框

IMPLEMENT_DYNAMIC(DialogCurrentPro, CDialogEx)

DialogCurrentPro::DialogCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCurrentPro::IDD, pParent)
{
	//初始化链表 
	mReadyProcess = LinkedList<PCB*>();
	
}

DialogCurrentPro::~DialogCurrentPro()
{
}

void DialogCurrentPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//此句话非常重要
	//Called by the framework to exchange and validate dialog data.大意是框架调用此函数来改写与确认对话框数据。
	DDX_Control(pDX, List_Current_Pro, ListCurrentProCtrl);
	DDX_Control(pDX, List_Pro_Queue, ListProQCtrl);
}

BEGIN_MESSAGE_MAP(DialogCurrentPro, CDialogEx)
END_MESSAGE_MAP()

void DialogCurrentPro::IninListCurrentPro(CRect rect){
	ListCurrentProCtrl.GetClientRect(&rect);
	ListCurrentProCtrl.SetExtendedStyle(ListCurrentProCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListCurrentProCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 9, 0);
	ListCurrentProCtrl.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, rect.Width() / 9, 1);
	ListCurrentProCtrl.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect.Width() / 9, 2);
	ListCurrentProCtrl.InsertColumn(3, _T("优先级"), LVCFMT_CENTER, rect.Width() / 9, 3);
	ListCurrentProCtrl.InsertColumn(4, _T("进入时间"), LVCFMT_CENTER, rect.Width() / 9, 4);
	ListCurrentProCtrl.InsertColumn(5, _T("所需时间"), LVCFMT_CENTER, rect.Width() / 9, 5);
	ListCurrentProCtrl.InsertColumn(6, _T("已运行时间"), LVCFMT_CENTER, rect.Width() / 9, 6);
	ListCurrentProCtrl.InsertColumn(7, _T("连续运行时间"), LVCFMT_CENTER, rect.Width() / 9, 7);
	ListCurrentProCtrl.InsertColumn(8, _T("状态"), LVCFMT_CENTER, rect.Width() / 9, 8);
}

void DialogCurrentPro::InitListProQ(CRect rect){
	ListProQCtrl.GetClientRect(&rect);
	ListProQCtrl.SetExtendedStyle(ListProQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListProQCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 9, 0);
	ListProQCtrl.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, rect.Width() / 9, 1);
	ListProQCtrl.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect.Width() / 9, 2);
	ListProQCtrl.InsertColumn(3, _T("优先级"), LVCFMT_CENTER, rect.Width() / 9, 3);
	ListProQCtrl.InsertColumn(4, _T("进入时间"), LVCFMT_CENTER, rect.Width() / 9, 4);
	ListProQCtrl.InsertColumn(5, _T("所需时间"), LVCFMT_CENTER, rect.Width() / 9, 5);
	ListProQCtrl.InsertColumn(6, _T("已运行时间"), LVCFMT_CENTER, rect.Width() / 9, 6);
	ListProQCtrl.InsertColumn(7, _T("连续就绪时间"), LVCFMT_CENTER, rect.Width() / 9, 7);
	ListProQCtrl.InsertColumn(8, _T("状态"), LVCFMT_CENTER, rect.Width() / 9, 8);
}
//初始化
BOOL DialogCurrentPro::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;

	IninListCurrentPro(rect);
	InitListProQ(rect);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void DialogCurrentPro::NotifyDataSetChange()
{
	int size = this->mReadyProcess.size();
	ListProQCtrl.DeleteAllItems();
	for (int i = 0;i<size ; i++){

		PCB *pcb = this->mReadyProcess.get(i);
		ListProQCtrl.InsertItem(i, Util::IntToCString(pcb->pid));
		ListProQCtrl.SetItemText(i, 1, pcb->id);
		ListProQCtrl.SetItemText(i, 2, pcb->userName);
		ListProQCtrl.SetItemText(i, 3, Util::IntToCString(pcb->priority));
		ListProQCtrl.SetItemText(i, 4,Util::IntToCString(pcb->enterTime));
		ListProQCtrl.SetItemText(i, 5, Util::IntToCString(pcb->allTime));
		ListProQCtrl.SetItemText(i, 6, Util::IntToCString(pcb->usedTime));
		ListProQCtrl.SetItemText(i, 7, Util::IntToCString(pcb->readyTime));
		ListProQCtrl.SetItemText(i, 8, pcb->getState());
	}
}

// CPU开始模拟进程调度算法
void DialogCurrentPro::Execute(int decPriority,int incPriority,int runSlots)
{
	
	if (ListCurrentProCtrl.GetItemCount() == 0){//若CPU空闲,选择优先级最高的进程执行
		int position = GetCandidatePos();
		if (mReadyProcess.get(0) == NULL||position < 0)  return;//就绪列表为空
		mCurrentProcess = mReadyProcess.remove(position);
		mCurrentProcess->state = RUNNING;
	}
	//更新视图
	UpdateListCPRO();
	UpdateListReady();

	if (runSlots >= 0){//连续执行时间片没用完
		UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		return;//继续执行下个时间片
	}
	else//连续时间片用完，则需要选择新进程运行 
	{
		if (mCurrentProcess == NULL) return;
		int tmpPid = mCurrentProcess->pid;//保存上个运行进程的pid
		
		//正在运行进程进入就绪队列
		mCurrentProcess->state = READY;
		mCurrentProcess->readyTime = 0;
		mReadyProcess.add(mCurrentProcess);

		//获取新的运行进程
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		mCurrentProcess->state = RUNNING;
		if (mCurrentProcess->pid != tmpPid)//若下个运行的进程和上个一样，则连续运行时间不变
		{
			mCurrentProcess->runTime = 0;//连续运行时间重置
			mCurrentProcess->readyTime = 0;//就绪时间请0
			UpdateCurrentPro(decPriority);
			UpdateReadyPro(incPriority);
		}
		
	}
	
}

// 获取从就绪队列进入运行队列的候选任务位置
int DialogCurrentPro::GetCandidatePos()
{
	int size = mReadyProcess.size();
	if (size == 0) return -1;
	int target = mReadyProcess.get(0)->priority;
	int returnValue = 0;
	for (int i = 1; i < size; i++){
		if (mReadyProcess.get(i)->priority>target) {
			returnValue = i;
			target = mReadyProcess.get(i)->priority;
		}
	}
	return returnValue;
}

// 更新当前进程
void DialogCurrentPro::UpdateCurrentPro(int decPriority)
{
	if (mCurrentProcess == NULL) return;
	//更新运行进程信息
	mCurrentProcess->usedTime++;//已运行时间增加 
	mCurrentProcess->runTime++;//连续运行时间
	if (--mCurrentProcess->allTime == 0)//运行完成
	{
		mCurrentProcess->state = FINISHED;
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		if (mCurrentProcess == NULL) return;
	}
	if (mCurrentProcess->priority - decPriority < 0)
	{
		mCurrentProcess->priority = 0;//优先级不能低于0
	}
	else
	{
		mCurrentProcess->priority -= decPriority;//正在运行进程优先级减少
	}
}

// 更新就绪队列
void DialogCurrentPro::UpdateReadyPro(int incPriority)
{
	int sizeA = mReadyProcess.size();
	for (int i = 0; i < sizeA; i++){
		if (mReadyProcess.get(i)->priority + incPriority>40){
			mReadyProcess.get(i)->priority = 40;//优先级增加，但不能大于40 
		}
		else
		{
			mReadyProcess.get(i)->priority += incPriority;
		}
		mReadyProcess.get(i)->readyTime++;//连续就绪时间增加
	}
}

// 更新当前进程列表
void DialogCurrentPro::UpdateListCPRO()
{
	ListCurrentProCtrl.DeleteAllItems();
	if (mCurrentProcess == NULL) return;
	ListCurrentProCtrl.InsertItem(0, Util::IntToCString(mCurrentProcess->pid));
	ListCurrentProCtrl.SetItemText(0, 1, mCurrentProcess->id);
	ListCurrentProCtrl.SetItemText(0, 2, mCurrentProcess->userName);
	ListCurrentProCtrl.SetItemText(0, 3, Util::IntToCString(mCurrentProcess->priority));
	ListCurrentProCtrl.SetItemText(0, 4, Util::IntToCString(mCurrentProcess->enterTime));
	ListCurrentProCtrl.SetItemText(0, 5, Util::IntToCString(mCurrentProcess->allTime));
	ListCurrentProCtrl.SetItemText(0, 6, Util::IntToCString(mCurrentProcess->usedTime));
	ListCurrentProCtrl.SetItemText(0, 7, Util::IntToCString(mCurrentProcess->runTime));
	ListCurrentProCtrl.SetItemText(0, 8, mCurrentProcess->getState());
}


// 更新就绪列表
void DialogCurrentPro::UpdateListReady()
{
	NotifyDataSetChange();
}
