// PersonalGiftSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PersonalGiftSystem.h"
#include "PersonalGiftSystemDlg.h"
#include "afxdialogex.h"
#include"Person.h"
#include <fstream>
#include <map>
#include"CNewPersonDlg.h"
#include<atlenc.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

map<CString, Person*>m_PersonData;
CFile mhtFile;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPersonalGiftSystemDlg 对话框



CPersonalGiftSystemDlg::CPersonalGiftSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONALGIFTSYSTEM_DIALOG, pParent)
	, key(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPersonalGiftSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_LIST, m_PersonList);
	DDX_Text(pDX, IDC_EDIT_KEY, key);
}

BEGIN_MESSAGE_MAP(CPersonalGiftSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPersonalGiftSystemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonalGiftSystemDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CPersonalGiftSystemDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_ADD, &CPersonalGiftSystemDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CPersonalGiftSystemDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CPersonalGiftSystemDlg::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// CPersonalGiftSystemDlg 消息处理程序

BOOL CPersonalGiftSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString tmp[4] = { L"姓名",L"性别",L"序号",L"礼金" };
	for (int i = 0; i < 4; i++)
	{
		m_PersonList.InsertColumn(i, (LPCTSTR)tmp[i], LVCFMT_CENTER);//在报告模式下插入一列
		m_PersonList.SetColumnWidth(i, 120);
	}
	DWORD dwStyle = m_PersonList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_PersonList.SetExtendedStyle(dwStyle); //设置扩展风格
	//needSave = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPersonalGiftSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPersonalGiftSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPersonalGiftSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPersonalGiftSystemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CPersonalGiftSystemDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CPersonalGiftSystemDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if (dlg.DoModal() == IDOK)
	{

	fileName = dlg.GetPathName();
	ifstream in(fileName);
	char s[3][100];
	CString st[3];
	m_PersonData.clear();
	m_PersonList.DeleteAllItems();
	int index = 0;
	while (in >> s[0])
	{
		for (int i = 1; i < 3; i++)
		{
			in >> s[i];
		}
		//转成宽字节，解决中文乱码
		for (int i = 0; i < 3; i++)
		{
			int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, s[i], strlen(s[i]), NULL, 0);
			wchar_t* wszMultiByte = new wchar_t[wcsLen + 1];
			MultiByteToWideChar(CP_UTF8, NULL, s[i], strlen(s[i]), wszMultiByte, wcsLen);
			wszMultiByte[wcsLen] = '\0';
			st[i] = wszMultiByte;
		}
		long money;
		in >> money;
		Person *p = new Person(st[0], st[1],st[2], money);
		m_PersonList.InsertItem(index, st[0]);
		m_PersonList.SetItemText(index, 1, st[1]);
		m_PersonList.SetItemText(index, 2, st[2]);
		CString sMoney;
		sMoney.Format(L"%ld", money);
		m_PersonList.SetItemText(index, 3, sMoney);
	    }
	    //needSave = false;
	    UpdateData(FALSE);
    }

}


void CPersonalGiftSystemDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CNewPersonDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (m_PersonData.find(dlg.sid) != m_PersonData.end())
		{
			MessageBox(L"错误，该客人已经添加!");
			return;
		}
		Person *p = new Person(dlg.name, dlg.gender, dlg.sid,dlg.money);
		m_PersonData[dlg.sid] = p;
		int index = m_PersonList.GetItemCount();
		m_PersonList.InsertItem(index, dlg.name);
		m_PersonList.SetItemText(index, 1, dlg.gender);
		m_PersonList.SetItemText(index, 2, dlg.sid);
		CString sMoney;
		sMoney.Format(L"%d", dlg.money);
		m_PersonList.SetItemText(index, 3, sMoney);
		UpdateData(FALSE);
		//needSave = true;
	}

}

void f_unicode_utf8(CFile &mhtFile, CString a, int flag)
{
	int nSrcLen = (int)wcslen(a);//content为要写入的文本
	CStringA utf8String(a);
	int nBufLen = (nSrcLen + 1) * 6;
	LPSTR buffer = utf8String.GetBufferSetLength(nBufLen);
	int nLen = AtlUnicodeToUTF8(a, nSrcLen, buffer, nBufLen);
	//上面的函数AtlUnicodeToUTF8()需头文件：<atlenc.h>
	//功能：将unicode转换成utf-8
	buffer[nLen] = 0;
	utf8String.ReleaseBuffer();
	mhtFile.SeekToEnd();
	//将转码后的内容写入mht文件
	mhtFile.Write(utf8String.GetBuffer(), nLen);
	if (flag == 0)
		mhtFile.Write("\r\n", 2);
}

void CPersonalGiftSystemDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
/*	if(needSave==false)
	{
		return;
	}*/
	if (fileName.GetLength() == 0)
	{
		if (dlg.DoModal() == IDOK)
			fileName = dlg.GetPathName();
		else
			return;
	}
	//ofstream out(fileName);
	map<CString, Person*>::iterator it;
	//添加
	CFile mhtFile;
	string f = "D:\\data2.txt";
	CString cstr(f.c_str());
	mhtFile.Open(fileName, CFile::modeCreate | CFile::modeWrite);
	//mhtFile为CFile类型，filePath为文件路径CString类型
	//-------以下是将Unicode字符转为utf-8字符，这样才能正常显示中文
	DWORD dwFileLen = mhtFile.GetLength();
	if (0 == dwFileLen)
	{
		const unsigned char LeadBytes[] = { 0xEF, 0xBB, 0xBF };
		mhtFile.Write(LeadBytes, sizeof(LeadBytes));
	}
	for (it = m_PersonData.begin(); it != m_PersonData.end(); it++)
	{
		Person *p = it->second;
		f_unicode_utf8(mhtFile, p->name, 0);
		f_unicode_utf8(mhtFile, p->gender, 0);
		f_unicode_utf8(mhtFile, p->sid, 0);
		//int成员变量需要先转成CString
		CString str;
		str.Format(_T("%d"), p->money);
		f_unicode_utf8(mhtFile, str, 0);
	}
	mhtFile.Close();

}



void CPersonalGiftSystemDlg::OnBnClickedBtnSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString strItem;
	for (int row = 0; row < m_PersonList.GetItemCount(); row++)
	{
		m_PersonList.SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
		for (int col = 0; col < m_PersonList.GetHeaderCtrl()->GetItemCount(); col++)
		{
			strItem = m_PersonList.GetItemText(row, col);
			if (strItem.Find(key) >= 0)
			{
				m_PersonList.SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			}
		}
	}
	m_PersonList.SetFocus();
}
