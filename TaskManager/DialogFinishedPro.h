#pragma once

#include "PCB.h"
#include "LinkedList.h"

class DialogFinishedPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFinishedPro)

public:
	DialogFinishedPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogFinishedPro();

// 对话框数据
	enum { IDD = Dialog_Finished_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl listFinishedProCtrl;
	CStatic textAVGRightTimeCtrl;

	LinkedList<PCB*> mFinishedProcess;

	void InitFinishedProList(CRect rect);//初始化已结束列表
	void NotifyDataSetChange();//更新列表
	double CalAVGRightTime();//计算平均带权周转时间

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};


