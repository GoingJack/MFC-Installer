#pragma once


// CSelectFilePath 对话框

class CSelectFilePath : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectFilePath)

public:
	CSelectFilePath(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSelectFilePath();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALLER_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CMFCEditBrowseCtrl m_selectpath;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
};
