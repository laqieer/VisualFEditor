#pragma once
#include "afxcmn.h"
#include "afxwin.h"


#define S_EVENT L"�¼�"
#define S_EVENT_BLANK L"�հ��¼�"
#define S_EVENT_0 L"0�¼�"
#define S_UNIT L"��������"
#define S_TEXT L"���ֶԻ�"
#define S_MAP  L"��ͼ�ļ�"
// CNewSlutionWizad �Ի���

class CNewSlutionWizad : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSlutionWizad)

public:
	CNewSlutionWizad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewSlutionWizad();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEWSLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeSluType;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnInitDialog();

	CString m_sFileName;
	CString m_sTip;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	int m_iFileType;
};
