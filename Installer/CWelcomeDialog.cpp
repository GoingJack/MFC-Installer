// CWelcomeDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Installer.h"
#include "CWelcomeDialog.h"
#include "afxdialogex.h"


// CWelcomeDialog 对话框

IMPLEMENT_DYNAMIC(CWelcomeDialog, CDialogEx)

CWelcomeDialog::CWelcomeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTALLER_DIALOG, pParent)
{

}

CWelcomeDialog::~CWelcomeDialog()
{
}

void CWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialogEx)
END_MESSAGE_MAP()


// CWelcomeDialog 消息处理程序
