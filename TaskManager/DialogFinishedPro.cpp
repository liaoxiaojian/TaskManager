// DialogFinishedPro.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogFinishedPro.h"
#include "afxdialogex.h"


// DialogFinishedPro 对话框

IMPLEMENT_DYNAMIC(DialogFinishedPro, CDialogEx)

DialogFinishedPro::DialogFinishedPro(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogFinishedPro::IDD, pParent)
{

}

DialogFinishedPro::~DialogFinishedPro()
{
}

void DialogFinishedPro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogFinishedPro, CDialogEx)
END_MESSAGE_MAP()


// DialogFinishedPro 消息处理程序
