#pragma once


// CNewPersonDlg 对话框

class CNewPersonDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewPersonDlg)

public:
	CNewPersonDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNewPersonDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPERSON_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString name;
	CString gender;
	CString sid;
	long money;
	
};
