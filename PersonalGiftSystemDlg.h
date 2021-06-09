// PersonalGiftSystemDlg.h: 头文件
//

#pragma once


// CPersonalGiftSystemDlg 对话框
class CPersonalGiftSystemDlg : public CDialogEx
{
// 构造
public:
	CPersonalGiftSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString fileName;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONALGIFTSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_PersonList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSave();
	CString key;
	afx_msg void OnBnClickedBtnSearch();
};
