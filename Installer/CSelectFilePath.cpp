// CSelectFilePath.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "CSelectFilePath.h"
#include "afxdialogex.h"
#include "InstallerDlg.h"
#include "CStartInstall.h"

// CSelectFilePath 对话框

IMPLEMENT_DYNAMIC(CSelectFilePath, CDialogEx)

CSelectFilePath::CSelectFilePath(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG1, pParent)
{

}

CSelectFilePath::~CSelectFilePath()
{
}

void CSelectFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_selectpath);
}


BEGIN_MESSAGE_MAP(CSelectFilePath, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CSelectFilePath::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &CSelectFilePath::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CSelectFilePath::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSelectFilePath 消息处理程序


HBRUSH CSelectFilePath::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_S_BLUE)
	{
		pDC->SetTextColor(RGB(0, 0, 250));
	}
	return hbr;
}


void CSelectFilePath::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CInstallerDlg *parent = (CInstallerDlg*)GetParent();
	parent->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}


BOOL CSelectFilePath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();
	SetDlgItemText(IDC_S_Content, "安装程序将被安装到下列文件夹中，点击\"下一步(N)\"继续，要选择不同的位置，\n请在下面输入或点击放大镜图标按钮更改现有的文件夹.");
	m_selectpath.SetWindowText("C:\\Program Files\\SafeCheck\\");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSelectFilePath::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}


void CSelectFilePath::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}


void CSelectFilePath::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CStartInstall *dlg = new CStartInstall;
	dlg->Create(IDD_INSTALLER_DIALOG2, this);
	GetDlgItemText(IDC_MFCEDITBROWSE1, dlg->selectpath);
	dlg->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}
