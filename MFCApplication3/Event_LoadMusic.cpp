// Event_LoadMusic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Event_LoadMusic.h"
#include "afxdialogex.h"

// CEvent_LoadMusic �Ի���

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


// CEvent_LoadMusic ��Ϣ�������


void CEvent_LoadMusic::OnBnClickedOk()
{
	m_MusicSequence = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL CEvent_LoadMusic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);//��ѡ�����ڵ�һ��ѡ����

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
