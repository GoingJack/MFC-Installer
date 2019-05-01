// CCild.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CCild.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"


// CCild 对话框

IMPLEMENT_DYNAMIC(CCild, CDialogEx)

CCild::CCild(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CCild::~CCild()
{
}

void CCild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_result2);
}


BEGIN_MESSAGE_MAP(CCild, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCild::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCild::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &CCild::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCild::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCild 消息处理程序


BOOL CCild::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMFCApplication1Dlg *pFatherDlg = (CMFCApplication1Dlg*)GetParent();
	ChildData = pFatherDlg->FatherData;
	m_result2.SetWindowText(ChildData);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCild::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCApplication1Dlg *pFatherDlg = (CMFCApplication1Dlg*)GetParent();
	ChildData = pFatherDlg->FatherData;
	m_result2.SetWindowText(ChildData);
}


void CCild::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCApplication1Dlg * parent = (CMFCApplication1Dlg*)GetParent();
	//CString FarherData;
	this->m_result2.GetWindowText(ChildData);//获取当前子窗口编辑框中的值
	parent->m_result.SetWindowText(ChildData);//把当前编辑框中的值回传给父窗口
	this->ShowWindow(SW_HIDE);
	parent->ShowWindow(SW_SHOW);
}


void CCild::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


void CCild::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T("123");
	this->m_result2.SetWindowText(str);
}


void CCild::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCApplication1Dlg *parent = (CMFCApplication1Dlg*)GetParent();
	parent->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
}
