// NewSlutionWizad.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "NewSlutionWizad.h"
#include "afxdialogex.h"

// CNewSlutionWizad 对话框

IMPLEMENT_DYNAMIC(CNewSlutionWizad, CDialogEx)

CNewSlutionWizad::CNewSlutionWizad(CWnd* pParent /*=NULL*/)
: CDialogEx(CNewSlutionWizad::IDD, pParent)
, m_sFileName(_T(""))
, m_sTip(_T(""))
{

	m_iFileType = 0;
}

CNewSlutionWizad::~CNewSlutionWizad()
{
}

void CNewSlutionWizad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeSluType);
	DDX_Text(pDX, IDC_EDIT1, m_sFileName);
	DDV_MaxChars(pDX, m_sFileName, 50);
	DDX_Text(pDX, IDC_EDIT2, m_sTip);
	DDV_MaxChars(pDX, m_sTip, 255);
	//  DDX_LBString(pDX, IDC_LIST1, m_ListString);
}


BEGIN_MESSAGE_MAP(CNewSlutionWizad, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CNewSlutionWizad::OnTvnSelchangedTree1)
	//	ON_WM_CREATE()
	//	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDCANCEL, &CNewSlutionWizad::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNewSlutionWizad::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewSlutionWizad 消息处理程序


void CNewSlutionWizad::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	HTREEITEM hItem = m_treeSluType.GetSelectedItem();
	if (hItem != NULL)//如果点击的位置是在节点位置上面
	{
		DWORD  nDat = m_treeSluType.GetItemData(hItem);
		//然后根据不同的节点，你完成不同的动作即可
		switch (nDat)
		{
		case -1:
		{
				   m_sFileName = L"";//AfxMessageBox(L"请选择对应的事件！");
				   break;
		}
		case -2:
		{
				  m_sFileName = L"";//AfxMessageBox(L"请选择对应的模板！"); 
				  break;
		}
		case 1:
		{
				  m_sFileName = S_EVENT_BLANK ;
				  break;
		}
		case 2:
		{
				  m_sFileName = S_TEXT;
				  break;
		}
		case 3:
		{
				  m_sFileName = S_UNIT;
				  break;
		}
		case 4:
		{
				  m_sFileName = S_MAP;
				  break;
		}	
		}
		if (m_sFileName != L"")
			m_sFileName += L"-";
	}

	UpdateData(FALSE);
}


BOOL CNewSlutionWizad::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(L"新建项目");
	HTREEITEM hItem = m_treeSluType.InsertItem(S_EVENT, NULL, NULL);///root就是节点的标题 
	HTREEITEM hItem0 = m_treeSluType.InsertItem(S_EVENT_BLANK, NULL, NULL, hItem);
	HTREEITEM hItem1 = m_treeSluType.InsertItem(L"模板事件", NULL, NULL, hItem);
	HTREEITEM hItem1_0 = m_treeSluType.InsertItem(L"0事件", NULL, NULL, hItem1);
	HTREEITEM hItem1_1 = m_treeSluType.InsertItem(L"1事件", NULL, NULL, hItem1);
	HTREEITEM hItem1_2 = m_treeSluType.InsertItem(L"2事件", NULL, NULL, hItem1);
	HTREEITEM hItem1_3 = m_treeSluType.InsertItem(L"4事件", NULL, NULL, hItem1);
	HTREEITEM hItem2 = m_treeSluType.InsertItem(S_TEXT, NULL, NULL, NULL);
	HTREEITEM hItem3 = m_treeSluType.InsertItem(S_UNIT, NULL, NULL, NULL);
	HTREEITEM hItem4 = m_treeSluType.InsertItem(S_MAP, NULL, NULL, NULL);

	m_treeSluType.SetItemData(hItem, -1);
	m_treeSluType.SetItemData(hItem1, -2);

	m_treeSluType.SetItemData(hItem0, 1);
	m_treeSluType.SetItemData(hItem2, 2);
	m_treeSluType.SetItemData(hItem3, 3);
	m_treeSluType.SetItemData(hItem4, 4);

	m_treeSluType.SetItemData(hItem1_0, 10);
	m_treeSluType.SetItemData(hItem1_1, 11);
	m_treeSluType.SetItemData(hItem1_2, 12);
	m_treeSluType.SetItemData(hItem1_3, 13);

	m_treeSluType.Expand(hItem, TVE_EXPAND);
	m_treeSluType.Expand(hItem1, TVE_EXPAND);
	return true;

}


void CNewSlutionWizad::OnBnClickedOk()
{
	UpdateData();
	if (m_sFileName.IsEmpty())
	{
		MessageBox(L"请输入项目的名称", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}
	if (m_sFileName.FindOneOf(L"!\\*%|+/.,") != -1)
	{
		MessageBox(L"项目名称中不能包含以下特殊字符：\"!%*/|\"\n项目名称中不能包含\".\",\",\"", L"Visual FEdit", MB_ICONERROR | MB_OK);
		return;
	}
	HTREEITEM hItem = m_treeSluType.GetSelectedItem();
	if (hItem != NULL)
	{
		 m_iFileType = m_treeSluType.GetItemData(hItem);
	}
	if (m_iFileType>0)
		CDialogEx::OnOK();
	}

	void CNewSlutionWizad::OnBnClickedCancel()
	{
		CDialogEx::OnCancel();
	}
