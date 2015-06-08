#pragma once

#include "ListViewCurrentPro.h"
// DialogCurrentPro 对话框

class DialogCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCurrentPro)

public:
	DialogCurrentPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCurrentPro();

// 对话框数据
	enum { IDD = Dialog_Finished_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	// 初始化正在运行的进程
	void IninListCurrentPro(CRect crect);
	// 初始化进程队列
	void InitListProQ(CRect crect);

	CListCtrl ListCurrentProCtrl;
	CListCtrl ListProQCtrl;
};
