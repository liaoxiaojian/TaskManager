// DialogCurrentPro.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogCurrentPro.h"
#include "afxdialogex.h"

// DialogCurrentPro 对话框

IMPLEMENT_DYNAMIC(DialogCurrentPro, CDialogEx)

DialogCurrentPro::DialogCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCurrentPro::IDD, pParent)
{

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
	// 获取编程语言列表视图控件的位置和大小   
	ListCurrentProCtrl.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	ListCurrentProCtrl.SetExtendedStyle(ListCurrentProCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
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
	// 获取编程语言列表视图控件的位置和大小   
	ListProQCtrl.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	ListProQCtrl.SetExtendedStyle(ListProQCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
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


