// DialogFinishedPro.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogFinishedPro.h"
#include "afxdialogex.h"
#include "PCB.h"
#include "Util.h"

// DialogFinishedPro 对话框

IMPLEMENT_DYNAMIC(DialogFinishedPro, CDialogEx)

DialogFinishedPro::DialogFinishedPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogFinishedPro::IDD, pParent)
{
	//初始化链表
	mFinishedProcess = LinkedList<PCB*>();
}

DialogFinishedPro::~DialogFinishedPro()
{
}

void DialogFinishedPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, List_Finished_Pro, listFinishedProCtrl);
	DDX_Control(pDX, Text_AVG_Right_Time, textAVGRightTimeCtrl);
}

BEGIN_MESSAGE_MAP(DialogFinishedPro, CDialogEx)
END_MESSAGE_MAP()

void DialogFinishedPro::InitFinishedProList(CRect rect){
	listFinishedProCtrl.GetClientRect(&rect);
	listFinishedProCtrl.SetExtendedStyle(listFinishedProCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	listFinishedProCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 9, 0);
	listFinishedProCtrl.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, rect.Width() / 9, 1);
	listFinishedProCtrl.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect.Width() / 9, 2);
	listFinishedProCtrl.InsertColumn(3, _T("优先级"), LVCFMT_CENTER, rect.Width() / 9, 3);
	listFinishedProCtrl.InsertColumn(4, _T("进入时间"), LVCFMT_CENTER, rect.Width() / 9, 4);
	listFinishedProCtrl.InsertColumn(5, _T("运行时间"), LVCFMT_CENTER, rect.Width() / 9, 5);
	listFinishedProCtrl.InsertColumn(6, _T("结束时间"), LVCFMT_CENTER, rect.Width() / 9, 6);
	listFinishedProCtrl.InsertColumn(7, _T("带权周转时间"), LVCFMT_CENTER, rect.Width() / 9, 7);
	listFinishedProCtrl.InsertColumn(8, _T("状态"), LVCFMT_CENTER, rect.Width() / 9, 8);
}

void DialogFinishedPro::NotifyDataSetChange(){
	int size = this->mFinishedProcess.size();
	listFinishedProCtrl.SetRedraw(FALSE);
	listFinishedProCtrl.DeleteAllItems();
	for (int i = 0; i<size; i++){
		PCB *pcb = this->mFinishedProcess.get(i);
		listFinishedProCtrl.InsertItem(i, Util::IntToCString(pcb->pid));
		listFinishedProCtrl.SetItemText(i, 1, pcb->id);
		listFinishedProCtrl.SetItemText(i, 2, pcb->userName);
		listFinishedProCtrl.SetItemText(i, 3, Util::IntToCString(pcb->priority));
		listFinishedProCtrl.SetItemText(i, 4, Util::IntToCString(pcb->enterTime));
		listFinishedProCtrl.SetItemText(i, 5, Util::IntToCString(pcb->usedTime));
		listFinishedProCtrl.SetItemText(i, 6, Util::IntToCString(pcb->endTime));
		listFinishedProCtrl.SetItemText(i, 7, Util::DoubleToCString(pcb->rightTime));
		listFinishedProCtrl.SetItemText(i, 8, pcb->getState());
	}
	listFinishedProCtrl.SetRedraw(TRUE);
	listFinishedProCtrl.Invalidate();
	listFinishedProCtrl.UpdateWindow();

	CString str;
	str.Format(_T("平均代权周转时间%f"),CalAVGRightTime());
	textAVGRightTimeCtrl.SetWindowTextW(str);
	textAVGRightTimeCtrl.Invalidate();
	textAVGRightTimeCtrl.UpdateWindow();
}

double DialogFinishedPro::CalAVGRightTime(){
	int size = mFinishedProcess.size();
	double allRightTime = 0;
	for (int i = 0; i < size; i++){
		allRightTime += mFinishedProcess.get(i)->rightTime;
	}
	return allRightTime / size;
}

BOOL DialogFinishedPro::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect crect;

	InitFinishedProList(crect);

	return TRUE;  
}

