#pragma once


// DialogFinishedPro 对话框

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
};
