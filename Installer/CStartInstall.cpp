// CStartInstall.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "CStartInstall.h"
#include "afxdialogex.h"
#include "CSelectFilePath.h"
#include "CProcess.h"


// CStartInstall 对话框

IMPLEMENT_DYNAMIC(CStartInstall, CDialogEx)

CStartInstall::CStartInstall(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG2, pParent)
{

}

CStartInstall::~CStartInstall()
{
}

void CStartInstall::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartInstall, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CStartInstall::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CStartInstall::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CStartInstall::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CStartInstall 消息处理程序


BOOL CStartInstall::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();
	SetDlgItemText(IDC_S_TIELE, "安装程序现在准备开始安装 保密检查客户端到您的计算机中。");
	SetDlgItemText(IDC_S_Content, "点击\"安装\"开始安装。如果您想复查或更改您的安装设置，点击\"上一步(&B)\".\n点击\"取消\"退出向导。");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CStartInstall::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CStartInstall::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelectFilePath *parent = (CSelectFilePath*)GetParent();
	parent->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}


void CStartInstall::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CProcess *cp = new CProcess;
	cp->selectpath = selectpath;
	cp->Create(IDD_INSTALLER_DIALOG3, this);
	cp->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
	
}


void CStartInstall::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}


void CStartInstall::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	if (MessageBox("你确定要取消保密检查客户端安装吗?", "提示", MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		exit(0);
	}
}
