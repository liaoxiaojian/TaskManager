// DialogNewTask.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogNewTask.h"
#include "afxdialogex.h"


// DialogNewTask 对话框

IMPLEMENT_DYNAMIC(DialogNewTask, CDialogEx)

DialogNewTask::DialogNewTask(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogNewTask::IDD, pParent)
{
	pid = 0;
	tmpPid = 0;
	newTaskList = LinkedList<PCB*>();
}

DialogNewTask::~DialogNewTask()
{
}

void DialogNewTask::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, List_New_Task_Q, listNewTaskQCtrl);
	DDX_Control(pDX, New_Task_EditText_Pro, processNameCtrl);
	DDX_Control(pDX, New_Task_EditText_User, userNameCtrl);
	DDX_Control(pDX, New_Task_EditText_Pri, priorityCtrl);
	DDX_Control(pDX, New_Task_EditText_NeedTime, allTimeCtrl);
}

BEGIN_MESSAGE_MAP(DialogNewTask, CDialogEx)
	ON_BN_CLICKED(New_Task_Button_Add_To_List, &DialogNewTask::OnBnClickedTaskButtonAddToList)
	ON_BN_CLICKED(IDOK, &DialogNewTask::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL DialogNewTask::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srand((unsigned)time(NULL));     //每次执行种子不同，生成不同的随机数
	CRect rect;
	InitListNewTaskQ(rect);
	return TRUE;  
}

// 初始化新进程队列列表选项
void DialogNewTask::InitListNewTaskQ(CRect rect)
{
	listNewTaskQCtrl.GetClientRect(&rect);
	listNewTaskQCtrl.SetExtendedStyle(listNewTaskQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	listNewTaskQCtrl.InsertColumn(0, _T("PID"), LVCFMT_CENTER, rect.Width() / 5, 0);
	listNewTaskQCtrl.InsertColumn(1, _T("进程名"), LVCFMT_CENTER, rect.Width() / 5, 1);
	listNewTaskQCtrl.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect.Width() / 5, 2);
	listNewTaskQCtrl.InsertColumn(3, _T("优先级"), LVCFMT_CENTER, rect.Width() / 5, 3);
	listNewTaskQCtrl.InsertColumn(5, _T("所需时间"), LVCFMT_CENTER, rect.Width() / 5, 4);
}

//添加到列表点击事件
void DialogNewTask::OnBnClickedTaskButtonAddToList()
{
	AddItemToList();
}

// 添加任务到列表
void DialogNewTask::AddItemToList()
{
	processNameCtrl.GetWindowTextW(id);
	userNameCtrl.GetWindowTextW(userName);
	priorityCtrl.GetWindowTextW(priority);
	allTimeCtrl.GetWindowTextW(allTime);

	//默认生成
	if (userName == "") userName = CString("用户")+Util::IntToCString(pid);
	if (id == "")  id = CString("进程")+Util::IntToCString(pid);
	if (priority == "") {
		int a = PCB::GeneratePriority();
		priority = Util::IntToCString(a);
	}
	else if (Util::CStringToInt(priority) > 40 ||Util::CStringToInt(priority) < 0){
		MessageBox(_T("优先数范围为[0,40]!"), _T("提示"));
		return;
	}
	if (allTime == ""){
		int a = PCB::GenerateNeedTime();
		allTime = Util::IntToCString(a);
	}
	
	int num = listNewTaskQCtrl.GetItemCount();

	listNewTaskQCtrl.InsertItem(num, Util::IntToCString(pid));
	listNewTaskQCtrl.SetItemText(num, 1, id);
	listNewTaskQCtrl.SetItemText(num, 2, userName);
	listNewTaskQCtrl.SetItemText(num, 3, priority);
	listNewTaskQCtrl.SetItemText(num, 4, allTime);
	
	PCB *pcb = new PCB(pid++,id, userName, Util::CStringToInt(priority), NULL, Util::CStringToInt(allTime));
	
	newTaskList.add(pcb);

}

//确认键被点击后
void DialogNewTask::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

// 释放资源，值初始化
void DialogNewTask::ClearAll()
{
	id = "";
	userName = "";
	priority = "";
	allTime = "";
	newTaskList.clear();
}

void DialogNewTask::OnCancel()
{
	id = "";
	userName = "";
	priority = "";
	allTime = "";
	//释放资源
	if (newTaskList.size() != 0){
		delete(newTaskList.shift());
	}

	CDialogEx::OnCancel();
}
