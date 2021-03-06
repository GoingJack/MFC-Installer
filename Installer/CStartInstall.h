#pragma once


// CStartInstall 对话框

class CStartInstall : public CDialogEx
{
	DECLARE_DYNAMIC(CStartInstall)

public:
	CStartInstall(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStartInstall();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALLER_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();

	CString selectpath;
};
