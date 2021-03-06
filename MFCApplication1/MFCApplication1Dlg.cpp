
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
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
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




#define myHeapAlloc(x) (HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,x))

typedef BOOL(WINAPI *SetSecurityDescriptorControlFnPtr)(
	IN PSECURITY_DESCRIPTOR pSecurityDescriptor,
	IN SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
	IN SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet);

typedef BOOL(WINAPI *AddAccessAllowedAceExFnPtr)(
	PACL pAcl,
	DWORD dwAceRevision,
	DWORD AceFlags,
	DWORD AccessMask,
	PSID pSid
	);
BOOL AddRights(TCHAR* lpFileName, TCHAR* lpAccountName, DWORD dw)
{
	//lookupAccountName相关变量
	PSID pUserID = NULL;
	DWORD dUserID = 0;
	TCHAR* pDomainName = NULL;
	DWORD dDomainName = 0;
	SID_NAME_USE snuType;

	//第一步，取得传入的用户或用户组的SID
	BOOL check1 = LookupAccountName(NULL, lpAccountName, pUserID, &dUserID, pDomainName, &dDomainName, &snuType);
	pUserID = (PSID)myHeapAlloc(dUserID);
	pDomainName = (TCHAR*)myHeapAlloc(dDomainName * sizeof(TCHAR));
	check1 = LookupAccountName(NULL, lpAccountName, pUserID, &dUserID, pDomainName, &dDomainName, &snuType);

	//第二步，取得文件的安全描述符(SD)
	PSECURITY_DESCRIPTOR pFileSD = NULL;
	DWORD dFileSD = 0;
	SECURITY_INFORMATION secInfo = DACL_SECURITY_INFORMATION;

	check1 = GetFileSecurity(lpFileName, secInfo, pFileSD, 0, &dFileSD);
	pFileSD = (PSECURITY_DESCRIPTOR)myHeapAlloc(dFileSD);
	check1 = GetFileSecurity(lpFileName, secInfo, pFileSD, dFileSD, &dFileSD);

	//第三步，初始一个新的SD
	SECURITY_DESCRIPTOR newSD;
	InitializeSecurityDescriptor(&newSD, SECURITY_DESCRIPTOR_REVISION);

	//第四步，从SD中取出DACL
	BOOL bPresent;
	BOOL bDaclDefault;
	PACL pACL = NULL;
	GetSecurityDescriptorDacl(pFileSD, &bPresent, &pACL, &bDaclDefault);

	//第五步，取DACL的内存大小
	ACL_SIZE_INFORMATION aclInfo;
	aclInfo.AceCount = 0;
	aclInfo.AclBytesFree = 0;
	aclInfo.AclBytesInUse = sizeof(ACL);

	// 如果DACL不为空，则取其信息
	if (bPresent) {
		GetAclInformation(pACL, &aclInfo, sizeof(ACL_SIZE_INFORMATION), AclSizeInformation);
	}

	//第六步，计算新的ACL的size
	DWORD dNewAcl = aclInfo.AclBytesInUse + sizeof(ACL_SIZE_INFORMATION) + GetLengthSid(pUserID) - 2;

	//第七步，为新ACL分配内存
	PACL pNewAcl = (PACL)myHeapAlloc(dNewAcl);

	//第八步，初始化新的acl
	InitializeAcl(pNewAcl, dNewAcl, ACL_REVISION2);

	//第九步，如果文件（目录）的DACL有数据则拷贝数据到新的DACL
	UINT newAclIndex = 0;
	UINT curAclIndex = 0;
	LPVOID pTempAce = NULL;
	if (bPresent&&aclInfo.AceCount)
	{
		for (curAclIndex = 0; curAclIndex != aclInfo.AceCount; curAclIndex++)
		{
			GetAce(pACL, curAclIndex, &pTempAce);
			if (((ACCESS_ALLOWED_ACE*)pTempAce)->Header.AceFlags == INHERITED_ACE)
				break;

			if (EqualSid(pUserID, &(((ACCESS_ALLOWED_ACE*)pTempAce)->SidStart)))
			{
				printf("suc");
				continue;
			}

			AddAce(pNewAcl, ACL_REVISION, MAXDWORD, pTempAce, ((PACE_HEADER)pTempAce)->AceSize);
			newAclIndex++;
		}
	}

	SetSecurityDescriptorControlFnPtr _SetSecurityDescriptorControl = NULL;
	AddAccessAllowedAceExFnPtr _AddAccessAllowedAceEx = NULL;
	//动态装载函数
	_AddAccessAllowedAceEx = (AddAccessAllowedAceExFnPtr)
		GetProcAddress(GetModuleHandle(TEXT("advapi32.dll")),
			"AddAccessAllowedAceEx");
	_AddAccessAllowedAceEx(pNewAcl, ACL_REVISION2,
		CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE,
		dw, pUserID);

	//拷贝继承的ACE
	if (bPresent&&aclInfo.AceCount)
	{
		for (; curAclIndex != aclInfo.AceCount; curAclIndex++)
		{
			GetAce(pACL, curAclIndex, &pTempAce);
			AddAce(pNewAcl, ACL_REVISION, MAXDWORD, pTempAce, ((PACE_HEADER)pTempAce)->AceSize);
		}
	}

	//把新的acl设置到新的sd中
	check1 = SetSecurityDescriptorDacl(&newSD, TRUE, pNewAcl, FALSE);
	check1 = SetFileSecurity(lpFileName, secInfo, &newSD);
	DWORD err = GetLastError();

	return TRUE;
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL ret = AddRights("C:\\Program Files\\SafeCheck", "Everyone", GENERIC_ALL);
	if (ret == TRUE)
	{
		MessageBox("设置成功");
	}
	else
	{
		MessageBox("设置失败");
	}
}
