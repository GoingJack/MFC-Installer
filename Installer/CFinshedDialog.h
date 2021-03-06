#pragma once


// CFinshedDialog 对话框

class CFinshedDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFinshedDialog)

public:
	CFinshedDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFinshedDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALLER_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString selectpath;
	CButton m_check;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//设置开机自启
	void SetAutoStart();

	//设置安装目录为启动目录
	void SetCurentPath();
};
