// NewSlu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewSlu.h"
#include "afxdialogex.h"


// CNewSlu �Ի���

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


// CNewSlu ��Ϣ�������


void CNewSlu::OnBnClickedButton2()
{
	TCHAR  szDisplayName[255];
	BROWSEINFO bi;
	memset(&bi, 0, sizeof BROWSEINFO);
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.lpszTitle = L"��ѡ����Ŀ¼��";
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
		MessageBox(L"��������Ŀ�Ĵ��λ��", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}
	if (!PathFileExistsW(m_sluPath))
	{
		MessageBox(L"��Ч���λ�ã�������ѡ��λ��", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}

	if (m_sluPath == L"" || m_sluName == L"")
	{
		MessageBox(L"����ѡ�����̱����·��", L"��ʾ", MB_OK);
		return;
	}

	CDialogEx::OnOK();
}



BOOL CNewSlu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT1)->SetFocus();

	return FALSE;//����falseʹ�������ȷ������
}
