// CFinshedDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "CFinshedDialog.h"
#include "afxdialogex.h"


// CFinshedDialog 对话框

IMPLEMENT_DYNAMIC(CFinshedDialog, CDialogEx)

CFinshedDialog::CFinshedDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG4, pParent)
{

}

CFinshedDialog::~CFinshedDialog()
{
}

void CFinshedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_check);
}


BEGIN_MESSAGE_MAP(CFinshedDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFinshedDialog::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFinshedDialog 消息处理程序


void CFinshedDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_check.GetCheck() == 1)
	{
		STARTUPINFO stStartUpInfo;
		::memset(&stStartUpInfo, 0, sizeof(stStartUpInfo));
		stStartUpInfo.cb = sizeof(stStartUpInfo);

		PROCESS_INFORMATION stProcessInfo;
		::memset(&stProcessInfo, 0, sizeof(stProcessInfo));

		//TCHAR szPath[] = _T("c:\\program files\\internet explorer\\iexplore.exe");
		//TCHAR szCmd[] = _T(" http://community.csdn.net/");   //lpCommandLine的内容中开头需要一个空格，不然就和lpApplicationName连在一起去了

		//设置当前工作路径为安装目录
		SetCurentPath();

		//ShellExecute(NULL, _T("open"), selectpath + "MainClient.exe", NULL, NULL, SW_SHOW);
		bool bRet = ::CreateProcess(
			selectpath + "MainClient.exe",
			NULL,
			NULL,
			NULL,
			false,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&stStartUpInfo,
			&stProcessInfo);


		SetAutoStart();
	}
	exit(0);
}


BOOL CFinshedDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();
	m_check.SetCheck(BST_CHECKED);


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

	CEdit *m_welcome = (CEdit*)GetDlgItem(IDC_S_BLUE);

	m_welcome->SetFont(&font, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFinshedDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


HBRUSH CFinshedDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_S_BLUE)
	{

		pDC->SetTextColor(RGB(0, 0, 250));

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CFinshedDialog::SetAutoStart()
{
	SetCurentPath();
	/*1，网上说这种方法报毒*/
	//TCHAR StartUpPath[MAX_PATH];
	//SHGetSpecialFolderPath(this->GetSafeHwnd(), StartUpPath, CSIDL_STARTUP, 0);

	//CString TmpStartUpPath = (CString)StartUpPath;
	//if (TmpStartUpPath.Right(1) != "\\")
	//	TmpStartUpPath += "\\";

	//CString PathLink = TmpStartUpPath + "MainClient.lnk";
	//CoInitialize(NULL);
	//HRESULT hres;
	//IShellLink *psl;

	//hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	//if (SUCCEEDED(hres))
	//{
	//	IPersistFile* ppf;
	//	//设置快捷方式的目标路径，添加描述  
	//	psl->SetPath(selectpath + "MainClient.exe");
	//	//描述：就是备注
	//	psl->SetDescription(_T("link of MainClient"));
	//	//生成快捷方式
	//	hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
	//	if (SUCCEEDED(hres))
	//	{
	//		WCHAR wsz[MAX_PATH];
	//		// Ensure that the string is Unicode.  
	//		MultiByteToWideChar(CP_ACP, 0, PathLink, -1, wsz, MAX_PATH);
	//		// TODO: Check return value from MultiByteWideChar to ensure  
	//		// Save the link by calling IPersistFile::Save.  
	//		hres = ppf->Save(wsz, TRUE);
	//		ppf->Release();
	//	}
	//	psl->Release();
	//}
	//CoUninitialize();


	TCHAR StartUpPath[MAX_PATH];
	SHGetSpecialFolderPath(this->GetSafeHwnd(), StartUpPath, CSIDL_STARTUP, 0);

	CString TmpStartUpPath = (CString)StartUpPath;
	if (TmpStartUpPath.Right(1) != "\\")
		TmpStartUpPath += "\\";

	CString PathLink = TmpStartUpPath + "MainClient.lnk";


	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		hr = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;
			pisl->SetPath(selectpath + "MainClient.exe");
			pisl->SetWorkingDirectory(selectpath);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{
				//CString csStartPath;
				//SHGetSpecialFolderPath(NULL, (LPWSTR)(LPCTSTR)csStartPath, CSIDL_DESKTOP, 0);
				CString csLnkPath;
				//csLnkPath.Format(_T("%s\\%s"), csStartPath, lnk_fname);
				//csLnkPath.Format(_T("%s"), PathLink);
				USES_CONVERSION;
				LPCOLESTR lpOleStr = A2W(PathLink);
				pIPF->Save(lpOleStr, FALSE);
				pIPF->Release();
			}
			pisl->Release();
		}
		CoUninitialize();
	}
}

void CFinshedDialog::SetCurentPath()
{
	TCHAR strExeFullDir[MAX_PATH];
	GetModuleFileName(NULL, strExeFullDir, MAX_PATH);
	PathRemoveFileSpec(strExeFullDir);
	SetCurrentDirectory(selectpath);
}
