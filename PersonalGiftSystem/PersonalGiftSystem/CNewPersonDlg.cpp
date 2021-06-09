// CNewPersonDlg.cpp: 实现文件
//

#include "pch.h"
#include "PersonalGiftSystem.h"
#include "CNewPersonDlg.h"
#include "afxdialogex.h"


// CNewPersonDlg 对话框

IMPLEMENT_DYNAMIC(CNewPersonDlg, CDialog)

CNewPersonDlg::CNewPersonDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NEWPERSON_DLG, pParent)
	, name(_T(""))
	, gender(_T(""))
	, money(0)
	, sid(_T(""))
{

}

CNewPersonDlg::~CNewPersonDlg()
{
}

void CNewPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Text(pDX, IDC_EDIT_GENDER, gender);
	DDX_Text(pDX, IDC_EDIT_MONEY, money);
	DDX_Text(pDX, IDC_EDIT_SID, sid);
}


BEGIN_MESSAGE_MAP(CNewPersonDlg, CDialog)
END_MESSAGE_MAP()


// CNewPersonDlg 消息处理程序
