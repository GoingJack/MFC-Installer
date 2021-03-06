
// InstallerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "InstallerDlg.h"
#include "afxdialogex.h"

#include "CSelectFilePath.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInstallerDlg 对话框



CInstallerDlg::CInstallerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstallerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInstallerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CInstallerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInstallerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInstallerDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CInstallerDlg 消息处理程序

BOOL CInstallerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//屏蔽上一步的按钮
	CEdit *button2 = (CEdit *)GetDlgItem(IDC_BUTTON2);
	button2->EnableWindow(FALSE);

	//设置字体大小
	CFont font;
	font.CreateFont(13,                                    //   字体的高度   
		0,                                          //   字体的宽度  
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("宋体"));
	
	CEdit *m_welcome = (CEdit*)GetDlgItem(IDC_S_WELCOME);
	
	m_welcome->SetFont(&font, FALSE);

	SetDlgItemText(IDC_S_Content, "安装向导将在您的计算机上安装SafeCheck。点击\n\"下一步(N)\"继续，或点击\"取消\"退出安装向导。");



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CInstallerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInstallerDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInstallerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CInstallerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (pWnd->GetDlgCtrlID() == IDC_S_WELCOME)
	{
		
		//pDC->SetTextColor(RGB(0, 0, 250));
		
	}
	return hbr;
}

//下一步的按钮函数
void CInstallerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelectFilePath *cs = new CSelectFilePath;
	//cs.DoModal();
	cs->Create(IDD_INSTALLER_DIALOG1, this);
	cs->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}

//写 n 和 b 按键的响应函数
BOOL CInstallerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'n')
	{
		OnBnClickedButton1();
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'b')
	{
		OnBnClickedButton2();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//上一步按钮
void CInstallerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

//取消按钮
void CInstallerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox("你确定要取消保密检查客户端安装吗?","提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}


void CInstallerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}
