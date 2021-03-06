#pragma once


// CCild 对话框

class CCild : public CDialogEx
{
	DECLARE_DYNAMIC(CCild)

public:
	CCild(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCild();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString ChildData;
	CEdit m_result2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
