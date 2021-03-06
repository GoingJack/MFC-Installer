#pragma once


// CProcess 对话框

class CProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CProcess)

public:
	CProcess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALLER_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_process;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();

	CString selectpath;
	HANDLE m_thread;

	void FindAndDelete(CString Path);

	void CopyFileToPath(HRSRC &hrFile, CString filename);

	void CopyEveryFile(HRSRC hrFile, CString filename, int Pos);

	void CreateFindshedDialog();
	afx_msg void OnBnClickedButton1();
};
typedef struct CF {
	CProcess *m_instance;
}CF;
