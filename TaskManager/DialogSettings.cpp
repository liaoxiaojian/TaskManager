// DialogSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "DialogSettings.h"
#include "afxdialogex.h"


// DialogSettings 对话框

IMPLEMENT_DYNAMIC(DialogSettings, CDialogEx)

DialogSettings::DialogSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSettings::IDD, pParent)
{

}

DialogSettings::~DialogSettings()
{
}

void DialogSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Settings_Dec_Pri, decPriEditCtrl);
	DDX_Control(pDX, Settings_Inc_Pri, incPriEditCtrl);
	DDX_Control(pDX, Settings_Exist_Time_Slot, continueRunTimeSlotsCtrl);
	DDX_Control(pDX, Settings_Time_Slot_MS_Num, mSNumEditCtrl);
}


BEGIN_MESSAGE_MAP(DialogSettings, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSettings::OnBnClickedOk)
END_MESSAGE_MAP()


//确认键按下后
void DialogSettings::OnBnClickedOk()
{
	//数据保存在相应变量中
	decPriEditCtrl.GetWindowTextW(decPriority);
	incPriEditCtrl.GetWindowTextW(incPriority);
	continueRunTimeSlotsCtrl.GetWindowTextW(continueRunTimeSlots);
	mSNumEditCtrl.GetWindowTextW(mSNum);

	if (Util::CStringToInt(decPriority) < 0 || Util::CStringToInt(decPriority)>20 || Util::CStringToInt(incPriority) < 0 || Util::CStringToInt(incPriority)>20)
	{
		MessageBox(_T("增加或者减少优先数的范围是[1,20]!"), _T("提示"),0);
	}
	else if (decPriority == "" || incPriority == "" || continueRunTimeSlots == "" || mSNum == "")
	{
		MessageBox(_T("请填写完整!"), _T("提示"), 0);
	}
	else
	{
		CDialogEx::OnOK();
	}
}


BOOL DialogSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	decPriEditCtrl.SetWindowTextW(_T("3"));
	incPriEditCtrl.SetWindowTextW(_T("1"));
	continueRunTimeSlotsCtrl.SetWindowTextW(_T("5"));
	mSNumEditCtrl.SetWindowTextW(_T("1000"));

	return TRUE;
}
