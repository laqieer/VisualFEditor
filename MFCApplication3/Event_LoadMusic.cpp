// Event_LoadMusic.cpp : 实现文件
//

#include "stdafx.h"
#include "Event_LoadMusic.h"
#include "afxdialogex.h"

// CEvent_LoadMusic 对话框

IMPLEMENT_DYNAMIC(CEvent_LoadMusic, CDialogEx)

CEvent_LoadMusic::CEvent_LoadMusic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEvent_LoadMusic::IDD, pParent)
	, m_MusicSequence(0)
{

}

CEvent_LoadMusic::~CEvent_LoadMusic()
{
}

void CEvent_LoadMusic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEvent_LoadMusic, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEvent_LoadMusic::OnBnClickedOk)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CEvent_LoadMusic 消息处理程序


void CEvent_LoadMusic::OnBnClickedOk()
{
	m_MusicSequence = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CEvent_LoadMusic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);//让选择框放在第一个选项上

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
