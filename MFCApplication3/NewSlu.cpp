// NewSlu.cpp : 实现文件
//

#include "stdafx.h"
#include "NewSlu.h"
#include "afxdialogex.h"


// CNewSlu 对话框

IMPLEMENT_DYNAMIC(CNewSlu, CDialogEx)

CNewSlu::CNewSlu(CWnd* pParent /*=NULL*/)
: CDialogEx(CNewSlu::IDD, pParent)
, m_sluPath(_T(""))
, m_sluName(_T(""))
{

}

CNewSlu::~CNewSlu()
{
}

void CNewSlu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, m_Slupath);
	DDX_Text(pDX, IDC_EDIT2, m_sluPath);
	DDX_Text(pDX, IDC_EDIT1, m_sluName);
	//  DDX_Control(pDX, IDC_EDIT1, m_edit1);
}


BEGIN_MESSAGE_MAP(CNewSlu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewSlu::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CNewSlu::OnBnClickedOk)
//	ON_WM_ENABLE()
//ON_WM_SETFOCUS()
//ON_WM_CREATE()
END_MESSAGE_MAP()


// CNewSlu 消息处理程序


void CNewSlu::OnBnClickedButton2()
{
	TCHAR  szDisplayName[255];
	BROWSEINFO bi;
	memset(&bi, 0, sizeof BROWSEINFO);
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.lpszTitle = L"请选择存放目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (!lp)return;
	SHGetPathFromIDList(lp, szDisplayName);
	SetDlgItemText(IDC_EDIT2, szDisplayName);
}


void CNewSlu::OnBnClickedOk()
{
	UpdateData();
	if (m_sluPath.IsEmpty())
	{
		MessageBox(L"请输入项目的存放位置", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}
	if (!PathFileExistsW(m_sluPath))
	{
		MessageBox(L"无效存放位置，请重新选择位置", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}

	if (m_sluPath == L"" || m_sluName == L"")
	{
		MessageBox(L"请先选定工程保存的路径", L"提示", MB_OK);
		return;
	}

	CDialogEx::OnOK();
}



BOOL CNewSlu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT1)->SetFocus();

	return FALSE;//返回false使光标能正确被设置
}
