#pragma once
#include "afxcmn.h"

// ListViewCurrentPro 对话框

class ListViewCurrentPro : public CDialogEx
{
	DECLARE_DYNAMIC(ListViewCurrentPro)

public:
	ListViewCurrentPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ListViewCurrentPro();

// 对话框数据
	enum { IDD = Dialog_Current_Pro };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedCurrentPro(NMHDR *pNMHDR, LRESULT *pResult);
};
