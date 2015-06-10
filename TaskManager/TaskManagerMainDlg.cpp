
// TaskManagerMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskManager.h"
#include "TaskManagerMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// TaskManagerMainDlg 对话框
TaskManagerMainDlg::TaskManagerMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TaskManagerMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//初始化参数
	CPURunTime = 0;
	mDialogCurrenPro.continueRunTimeSlots = continueRunTimeSlots;
	mDialogCurrenPro.tmp = continueRunTimeSlots;

}

void TaskManagerMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Tab_Current_Pro, tabControl);
	DDX_Control(pDX, Main_Button_New_Task, buttonNewTask);
	DDX_Control(pDX, Main_Text_Cpu_Info, CPURunTimeTextCtrl);
	DDX_Control(pDX, Main_Button_Stop_CPU, buttonCPUCtrl);
	DDX_Control(pDX, Main_Button_Step_In, buttonStepInCtrl);
}

BEGIN_MESSAGE_MAP(TaskManagerMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, Tab_Current_Pro, &TaskManagerMainDlg::OnTcnSelchange)
	ON_BN_CLICKED(Main_Button_Settings, &TaskManagerMainDlg::OnBnClickedButtonSettings)
	ON_BN_CLICKED(Main_Button_New_Task, &TaskManagerMainDlg::OnBnClickedButtonNewTask)
	ON_BN_CLICKED(Main_Button_Stop_CPU, &TaskManagerMainDlg::OnBnClickedButtonStopCpu)
	ON_BN_CLICKED(Main_Button_Step_In, &TaskManagerMainDlg::OnBnClickedButtonStepIn)
END_MESSAGE_MAP()

// TaskManagerMainDlg 消息处理程序
BOOL TaskManagerMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	CRect tabRect;//

	//添加Tab选项
	tabControl.InsertItem(Dialog_Current_Pro, _T("当前进程"));
	tabControl.InsertItem(Dialog_Finished_Pro, _T("已结束"));
	//创建
	mDialogCurrenPro.Create(Dialog_Current_Pro, &tabControl);
	mDialogFinishedPro.Create(Dialog_Finished_Pro, &tabControl);
	//调整tabRect，使其覆盖范围适合放置标签页
	tabControl.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//设置显示
	mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	SetTimer(PERIOD_TASK, timeSlot, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void TaskManagerMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//最小化按钮
void TaskManagerMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示
HCURSOR TaskManagerMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Tab切换事件处理
void TaskManagerMainDlg::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;//
	tabControl.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//切换
	switch (tabControl.GetCurSel())
	{
	case 0:
		mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		mDialogCurrenPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		mDialogFinishedPro.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}

//设置按钮点击后
void TaskManagerMainDlg::OnBnClickedButtonSettings()
{
	int nRet = mDialogSettings.DoModal();
	if (nRet == IDOK)
	{
		//更改相应的参数
		timeSlot = Util::CStringToInt(mDialogSettings.mSNum);
		continueRunTimeSlots = Util::CStringToInt(mDialogSettings.continueRunTimeSlots);
		decPriority = Util::CStringToInt(mDialogSettings.decPriority);
		incPriority = Util::CStringToInt(mDialogSettings.incPriority);
		mDialogCurrenPro.continueRunTimeSlots = continueRunTimeSlots;
		mDialogCurrenPro.tmp = continueRunTimeSlots;

		KillTimer(PERIOD_TASK);
		SetTimer(PERIOD_TASK, timeSlot, NULL);
	}
}

//新建任务按钮被点击后
void TaskManagerMainDlg::OnBnClickedButtonNewTask()
{
	INT_PTR nRet = mDialogNewTask.DoModal();
	if (nRet == IDOK){
		int size = mDialogNewTask.newTaskList.size();
		for (int i = 0; i < size; i++){
			//数据传递，新任务进入就绪队列等待
			mDialogNewTask.newTaskList.get(0)->enterTime = CPURunTime;
			mDialogCurrenPro.mReadyProcess.add(mDialogNewTask.newTaskList.shift());
		}
	}
	//更新数据信息，并初始化一些变量
	mDialogNewTask.ClearAll();
	mDialogCurrenPro.NotifyDataSetChange();
}

//周期性函数
void TaskManagerMainDlg::OnTimer(UINT_PTR nIDEvent){
	if (nIDEvent == PERIOD_TASK){
		Execute();
	}
}

//cpu运转控制
void TaskManagerMainDlg::OnBnClickedButtonStopCpu()
{
	if (++clickTimes % 2 == 1)//终止运行
	{
		buttonCPUCtrl.SetWindowTextW(_T("启动CPU"));
		buttonStepInCtrl.EnableWindow(TRUE);
		KillTimer(PERIOD_TASK);
	}
	else
	{
		buttonCPUCtrl.SetWindowTextW(_T("终止CPU"));
		buttonStepInCtrl.EnableWindow(FALSE);
		SetTimer(PERIOD_TASK, timeSlot, NULL);
	}
}

//步进按钮点击
void TaskManagerMainDlg::OnBnClickedButtonStepIn()
{
	if (clickTimes % 2 == 1){
		Execute();
	}
}

void TaskManagerMainDlg::Execute(){
	CString str;
	str.Format(_T("CPU已连续运行%d个时间片"), CPURunTime++);
	CPURunTimeTextCtrl.SetWindowTextW(str);
	PCB * finishedPCB;
	finishedPCB = mDialogCurrenPro.Execute(decPriority, incPriority, CPURunTime);
	if (finishedPCB != NULL){
		finishedPCB->endTime = CPURunTime;
		finishedPCB->calRightTime();
		mDialogFinishedPro.mFinishedProcess.add(finishedPCB);
		mDialogFinishedPro.NotifyDataSetChange();
	}
}
