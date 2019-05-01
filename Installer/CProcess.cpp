// CProcess.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "CProcess.h"
#include "afxdialogex.h"
#include "CFinshedDialog.h"

DWORD WINAPI DeleteAllFiles(LPVOID lparam);

// CProcess 对话框

IMPLEMENT_DYNAMIC(CProcess, CDialogEx)

CProcess::CProcess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG3, pParent)
{

}

CProcess::~CProcess()
{
}

void CProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_process);
}


BEGIN_MESSAGE_MAP(CProcess, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CProcess::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CProcess::OnBnClickedButton1)
END_MESSAGE_MAP()


// CProcess 消息处理程序


void CProcess::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		TerminateThread(m_thread, 0);
		CloseHandle(m_thread);
		CF *cf = new CF;
		cf->m_instance = this;
		HANDLE d_handle = CreateThread(0, 0, DeleteAllFiles, cf, 0, 0);
		WaitForSingleObject(d_handle, INFINITE);
		CloseHandle(d_handle);
		exit(0);
	}
}


void CProcess::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	OnBnClickedButton3();
}


void CProcess::FindAndDelete(CString Path)
{
	CFileFind m_find;
	
	CString tmp_strDir = Path;
	if (tmp_strDir.Right(1) != "\\")
		tmp_strDir += "\\";
	tmp_strDir += "*.*";

	BOOL ret = m_find.FindFile(tmp_strDir);
	while (ret)
	{
		ret = m_find.FindNextFile();
		if (m_find.IsDots())
		{
			continue;
		}
		else if (m_find.IsDirectory())
		{
			FindAndDelete(m_find.GetFilePath());
		}
		else
		{
			CString FileName = m_find.GetFilePath();
			DeleteFile(FileName);
		}
	}
	m_find.Close();
	RemoveDirectory(Path);
}

void CProcess::CopyFileToPath(HRSRC &hrFile, CString filename)
{
	//HRSRC       hrFile = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL1), "DLL"); //后面这连个参数很重要   

	if (hrFile == NULL)
	{
		AfxMessageBox("没有找到资源 ");
	}
	HGLOBAL       hgFile = LoadResource(NULL, hrFile);
	if (hgFile == NULL)
	{
		AfxMessageBox("加载资源失败 ");
	}
	LPVOID       pvFile = LockResource(hgFile);
	if (pvFile == NULL)
	{
		MessageBox("不能加载内存 ");
	}
	CString tmpselectpath = selectpath;
	if (tmpselectpath.Right(1) != "\\")
		tmpselectpath += "\\";
	tmpselectpath += filename;
	HANDLE       hfFile = CreateFile(tmpselectpath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD       nFileLength = SizeofResource(NULL, hrFile);
	DWORD       nWriteLength;
	WriteFile(hfFile, pvFile, nFileLength, &nWriteLength, NULL);
	CloseHandle(hfFile);
	FreeResource(hrFile);
	//这样就会在c: / 下面生成一个amn.exe, 这个就是当时包含进去的那个exe文件
}

void CProcess::CopyEveryFile(HRSRC hrFile, CString filename, int Pos)
{
	CopyFileToPath(hrFile, filename);
	m_process.SetPos(Pos);
}

void CProcess::CreateFindshedDialog()
{
	CFinshedDialog *cf = new CFinshedDialog;
	cf->selectpath = selectpath;
	cf->Create(IDD_INSTALLER_DIALOG4, this);
	cf->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}

DWORD WINAPI CopyFile(LPVOID lparam)
{
	CF *m_cf = (CF*)lparam;
	HRSRC       hrFile[11];
	hrFile[0] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL1), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[0], "msvcr120.dll", 10);
	Sleep(300);

	hrFile[1] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL2), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[1], "libssl-1_1.dll", 20);

	hrFile[2] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL3), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[2], "libcrypto-1_1.dll", 40);


	hrFile[3] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL4), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[3], "all2txt\\a2t.key", 42);
	m_cf->m_instance->SetDlgItemText(IDC_S_STATUE, "状态...正在复制a2t.key");
	Sleep(300);

	hrFile[4] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL5), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[4], "all2txt\\a2thlp.dll", 45);


	hrFile[5] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL6), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[5], "all2txt\\a2thlp.dll", 47);
	Sleep(300);
	m_cf->m_instance->SetDlgItemText(IDC_S_STATUE, "状态..正在复制a2thlp.dll");

	hrFile[6] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL7), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[6], "all2txt\\a2tpdf.dll", 49);

	hrFile[7] = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL8), "DLL"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[7], "all2txt\\a2trtf.dll", 60);
	Sleep(300);

	hrFile[10] = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE2), "exe"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[10], "all2txt\\a2tcmd.exe", 67);

	hrFile[8] = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE3), "exe"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[8], "userUI.exe", 75);
	m_cf->m_instance->SetDlgItemText(IDC_S_STATUE, "状态.正在复制userUI.exe");

	hrFile[9] = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE1), "exe"); //后面这连个参数很重要   
	m_cf->m_instance->CopyEveryFile(hrFile[9], "MainClient.exe", 100);
	m_cf->m_instance->SetDlgItemText(IDC_S_STATUE, "状态...已完成");
	//m_cf->m_instance->CreateFindshedDialog();
	m_cf->m_instance->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	return 0;
}

DWORD WINAPI DeleteAllFiles(LPVOID lparam)
{
	CF *m_cf = (CF*)lparam;
	m_cf->m_instance->FindAndDelete(m_cf->m_instance->selectpath);
	return 0;
}

BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();
	//MessageBox(selectpath);
	CreateDirectory(selectpath, NULL);
	CreateDirectory(selectpath + "\\all2txt", NULL);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	CF *m_cf = new CF;
	m_cf->m_instance = this;

	m_thread = CreateThread(0, 0, CopyFile, (LPVOID)m_cf, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}






void CProcess::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateFindshedDialog();
}
