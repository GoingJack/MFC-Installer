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

	{
		//TCHAR *        szDomain = NULL;
		//DWORD          cbDomain = 0;
		//LPVOID         pUserSID = NULL;
		//DWORD          cbUserSID = 0;
		//TCHAR *lpszAccountName;

		//LookupAccountName(NULL, lpszAccountName,
		//	pUserSID, &cbUserSID, szDomain, &cbDomain, &snuType)
		//	InitializeSecurityDescriptor(newSD, SECURITY_DESCRIPTOR_REVISION)  //初始化一个新的SD
		//	BOOL che = SetSecurityDescriptorOwner(newSD, pUserSID, FALSE);  //设置文件所有者为前面获得的SID，返回值是TRUE，应该也没问题
		//che = IsValidSecurityDescriptor(newSD);  //特意做了下判断，是有效的
		//SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, TRUE);
		//SetFileSecurity(filename, (SECURITY_INFORMATION)(OWNER_SECURITY_INFORMATION),
		//	newSD)
	}

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

BOOL AddRights(TCHAR* lpFileName, TCHAR* lpAccountName, DWORD dw);

BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();
	CStringA tmp = selectpath;

	CreateDirectory(selectpath, NULL);
	AddRights(tmp.GetBuffer(), "Everyone", GENERIC_ALL);
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


//设置文件夹的权限
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
