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
	currentProHead = PCB::GetCurrentProInfoHead();
	readyProHead = PCB::GetReadyProInfoHead();

	file.Open(strTime+".txt", CFile::modeCreate | CFile::modeReadWrite);
	unsigned short int feff = 0xfeff;
	file.Write(&feff, sizeof(short int));//写入文件头
	file.Write(_T("任务管理日志:\r\n"), 18);
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
	ListProQCtrl.SetRedraw(FALSE);
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
	ListProQCtrl.SetRedraw(TRUE);
	ListProQCtrl.Invalidate();
	ListProQCtrl.UpdateWindow();
}

// CPU开始模拟进程调度算法
PCB* DialogCurrentPro::Execute(int decPriority,int incPriority,int cpuRunTime)
{
	PCB *finishedPCB = NULL;
	if (ListCurrentProCtrl.GetItemCount() == 0){//若CPU空闲,选择优先级最高的进程执行
		int position = GetCandidatePos();
		if (mReadyProcess.get(0) == NULL || position < 0)  {
			tmp = continueRunTimeSlots;
			return finishedPCB;//就绪列表为空，当前无运行任务
		}
		mCurrentProcess = mReadyProcess.remove(position);
		mCurrentProcess->state = RUNNING;
	}

	if (tmp-- > 0){//连续执行时间片没用完,继续执行下个时间片
		finishedPCB = UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		//更新视图
		UpdateListCPRO();
		UpdateListReady();
	}
	else//连续时间片用完，则需要选择新进程运行 
	{
		tmp = continueRunTimeSlots-1;
		if (mCurrentProcess == NULL) return finishedPCB;
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
			mCurrentProcess->runTime = 0;//连续运行时间清0
			mCurrentProcess->readyTime = 0;//就绪时间清0
		}
		finishedPCB =UpdateCurrentPro(decPriority);
		UpdateReadyPro(incPriority);
		//更新视图
		UpdateListCPRO();
		UpdateListReady();
	}

	//文件读写
	if (mCurrentProcess != NULL){
		WriteCurrentProToFile(cpuRunTime);
		file.Write(_T("\r\n"), 4);
		WriteReadyProToFile();
		file.Write(_T("\r\n"), 4);
		file.Flush();
	}
	
	return finishedPCB;
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

// 更新当前进程,返回完成的进场，若无，则返回NULL
PCB* DialogCurrentPro::UpdateCurrentPro(int decPriority)
{
	PCB* pcb = NULL;
	if (mCurrentProcess == NULL) return pcb;
	if (--mCurrentProcess->allTime <= 0)//运行完成
	{
		mCurrentProcess->usedTime++;//已运行时间增加 
		mCurrentProcess->runTime++;//连续运行时间
		mCurrentProcess->state = FINISHED;

		pcb = mCurrentProcess;

		//选择下一个进程
		int pos = GetCandidatePos();
		mCurrentProcess = mReadyProcess.remove(pos);
		if (mCurrentProcess == NULL) return pcb;
		mCurrentProcess->state = RUNNING;
	}
	else//未运行完成,更新进程信息
	{
		if (mCurrentProcess->priority - decPriority < 0)
		{
			mCurrentProcess->priority = 0;//优先级不能低于0
		}
		else
		{
			mCurrentProcess->priority -= decPriority;//正在运行进程优先级减少
		}
		mCurrentProcess->usedTime++;//已运行时间增加 
		mCurrentProcess->runTime++;//连续运行时间
	}
	return pcb;
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
	ListCurrentProCtrl.SetRedraw(FALSE);
	//更新内容
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
	ListCurrentProCtrl.SetRedraw(TRUE);
	ListCurrentProCtrl.Invalidate();
	ListCurrentProCtrl.UpdateWindow();
}


// 更新就绪列表
void DialogCurrentPro::UpdateListReady()
{
	NotifyDataSetChange();
}

void DialogCurrentPro::WriteCurrentProToFile(int cpuRunTime){
	CString cpuState;
	cpuState.Format(_T("第%d个时间片:\r\n"), cpuRunTime);
	file.Write(cpuState, cpuState.GetLength() << 1);
	file.Write(_T("CPU进程:\r\n"), 16);
	file.Write(currentProHead, currentProHead.GetLength() << 1);
	int position = file.GetLength();//获取每一行的开头位置
	int length = currentProHead.GetLength();
	//file.Write(currentProHead, currentProHead.GetLength() << 1);
	for (int i = 0; i <length; i++){
		file.Write(_T(" "), 2);
	}
	//写pid
	position += 4 << 1;
	file.Seek(position, CFile::begin);
	CString pid = mCurrentProcess->GetFormatPid();
	file.Write(pid, pid.GetLength() << 1);
	//写进程名
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString id = mCurrentProcess->GetFormatId();
	file.Write(id, id.GetLength() << 1);
	//写用户名
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString userName = mCurrentProcess->GetFormatUserName();
	file.Write(userName, userName.GetLength() << 1);
	//写优先级
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString priority = mCurrentProcess->GetFormatPriority();
	file.Write(priority, priority.GetLength() << 1);
	//写进入时间
	position += 6 << 1;
	file.Seek(position, CFile::begin);
	CString enterTime = mCurrentProcess->GetFormatEnterTime();
	file.Write(enterTime, enterTime.GetLength() << 1);
	//写所需时间
	position += 7 << 1;
	file.Seek(position, CFile::begin);
	CString allTime = mCurrentProcess->GetFormatAllTime();
	file.Write(allTime, allTime.GetLength() << 1);
	//写已运行时间
	position += 7 << 1;
	file.Seek(position, CFile::begin);
	CString usedTime = mCurrentProcess->GetFormatUsedTime();
	file.Write(usedTime, usedTime.GetLength() << 1);
	//写连续运行时间
	position += 8 << 1;
	file.Seek(position, CFile::begin);
	CString runTime = mCurrentProcess->GetFormatRunTime();
	file.Write(runTime, runTime.GetLength() << 1);
}

void DialogCurrentPro::WriteReadyProToFile(){
	CString head = _T("等待进程:\r\n");
	int b = file.GetLength();
	file.Write(head,head.GetLength()<<1);
	file.Write(readyProHead, readyProHead.GetLength() << 1);
	int length = readyProHead.GetLength();
	int size = mReadyProcess.size();
	for (int i = 0; i < size; i++){
		PCB* readyPro = mReadyProcess.get(i);
		int position = file.GetLength();//获取每一行的开头位置
		for (int j = 0; j<length; j++){
			file.Write(_T(" "), 2);
		}
		//写pid
		position += 4 << 1;
		file.Seek(position, CFile::begin);
		CString pid = readyPro->GetFormatPid();
		file.Write(pid, pid.GetLength() << 1);
		//写进程名
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString id = readyPro->GetFormatId();
		file.Write(id, id.GetLength() << 1);
		//写用户名
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString userName = readyPro->GetFormatUserName();
		file.Write(userName, userName.GetLength() << 1);
		//写优先级
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString priority = readyPro->GetFormatPriority();
		file.Write(priority, priority.GetLength() << 1);
		//写进入时间
		position += 6 << 1;
		file.Seek(position, CFile::begin);
		CString enterTime = readyPro->GetFormatEnterTime();
		file.Write(enterTime, enterTime.GetLength() << 1);
		//写所需时间
		position += 7 << 1;
		file.Seek(position, CFile::begin);
		CString allTime = readyPro->GetFormatAllTime();
		file.Write(allTime, allTime.GetLength() << 1);
		//写已运行时间
		position += 7 << 1;
		file.Seek(position, CFile::begin);
		CString usedTime = readyPro->GetFormatUsedTime();
		file.Write(usedTime, usedTime.GetLength() << 1);
		//写连续等待时间
		position += 8 << 1;
		file.Seek(position, CFile::begin);
		CString readyTime = readyPro->GetFormatReadyTime();
		file.Write(readyTime, readyTime.GetLength() << 1);

		CString end = _T("\r\n");
		file.Write(end,end.GetLength()<<1);
	}
}


BOOL DialogCurrentPro::DestroyWindow()
{
	file.Close();
	return CDialogEx::DestroyWindow();
}

