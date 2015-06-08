// ListViewCurrentPro.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "ListViewCurrentPro.h"
#include "afxdialogex.h"


// ListViewCurrentPro 对话框

IMPLEMENT_DYNAMIC(ListViewCurrentPro, CDialogEx)

ListViewCurrentPro::ListViewCurrentPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(ListViewCurrentPro::IDD, pParent)
{

}

ListViewCurrentPro::~ListViewCurrentPro()
{
}

void ListViewCurrentPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ListViewCurrentPro, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, List_Current_Pro, &ListViewCurrentPro::OnLvnItemchangedCurrentPro)
END_MESSAGE_MAP()


// ListViewCurrentPro 消息处理程序
void ListViewCurrentPro::OnLvnItemchangedCurrentPro(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

