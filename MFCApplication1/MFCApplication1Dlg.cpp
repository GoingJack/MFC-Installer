
// MFCApplication1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include "CCild.h"

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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_result);
	DDX_Control(pDX, IDC_PROGRESS1, m_process);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	int a = 20;
	FatherData.Format(_T("%d"), a);
	m_result.SetWindowText(FatherData);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CCild *dlg = new CCild;
	dlg->Create(IDD_DIALOG1,this);
	dlg->SetBackgroundColor(RGB(255, 155, 0));
	//dlg.DoModal();
	dlg->SetDlgItemText(IDC_EDIT1, FatherData);
	dlg->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CCild *dlg = new CCild;
	//CString FarherData;
	m_result.GetWindowText(FatherData);//获取当前对话框中的文本框内容
	dlg->Create(IDD_DIALOG1, this);
	dlg->SetBackgroundColor(RGB(255, 155, 0));
	dlg->ChildData = FatherData;
	dlg->ShowWindow(SW_SHOW);      //设置子对话框背景颜色黄色 CDiologEx中	
}

int times = 0;
CCild *dlg;
void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (times == 0)
	{
		dlg = new CCild;
		dlg->Create(IDD_DIALOG1, this);
		dlg->ShowWindow(SW_SHOW);
		this->ShowWindow(SW_HIDE);
	}
	else
	{
		dlg->ShowWindow(SW_SHOW);
		this->ShowWindow(SW_HIDE);
	}
}

typedef struct MMM
{
	CMFCApplication1Dlg *m_Instance;

}MMM;
DWORD WINAPI CopyFile(LPVOID lparam)
{
	MMM *sf = (MMM*)lparam;
	for (int i = 10; i < 100; i++)
	{
		
		if (sf->m_Instance->isend == 0)
		{
			break;
		}
		sf->m_Instance->m_process.SetPos(i);
		Sleep(300);
	}
	return 0;
}
void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_process.SetRange(0, 100);
	m_process.SetPos(10);
	MMM *sf = new MMM;
	sf->m_Instance = this;
	isend = 1;
	mythread = CreateThread(0, 0, CopyFile, (LPVOID)sf, 0, 0);
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateThread(mythread, 0);
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR MyDir[MAX_PATH];
	SHGetSpecialFolderPath(this->GetSafeHwnd(), MyDir, CSIDL_STARTUP, 0);
	MessageBox(MyDir);


	CString PathLink = "D:\\file.lnk";
	CoInitialize(NULL);
	HRESULT hres;
	IShellLink *psl;

	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		//设置快捷方式的目标路径，添加描述  
		psl->SetPath(_T("C:\\BaiduNetdiskDownload\\ideaIU-2018.1.5.win\\build.txt"));
		//描述：就是备注
		psl->SetDescription(_T("link of file"));
		//生成快捷方式
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres))
		{
			WCHAR wsz[MAX_PATH];
			// Ensure that the string is Unicode.  
			MultiByteToWideChar(CP_ACP, 0, PathLink, -1, wsz, MAX_PATH);
			// TODO: Check return value from MultiByteWideChar to ensure  
			// Save the link by calling IPersistFile::Save.  
			hres = ppf->Save(wsz, TRUE);
			ppf->Release();
		}
		psl->Release();
	}
	CoUninitialize();
}
