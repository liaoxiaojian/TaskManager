#pragma once
#include "afxwin.h"
#include "Util.h"


// DialogSettings 对话框
class DialogSettings : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSettings)

public:
	DialogSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogSettings();

	CString  decPriority;
	CString incPriority;
	CString continueRunTimeSlots;//连续运行的时间片的个数
	CString mSNum;

// 对话框数据
	enum { IDD = Dialog_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CEdit decPriEditCtrl;
	CEdit incPriEditCtrl;
	CEdit continueRunTimeSlotsCtrl;
	CEdit mSNumEditCtrl;

	afx_msg void OnBnClickedOk();
	
	virtual BOOL OnInitDialog();
};
