#pragma once
#include "resource.h"
#include "afxwin.h"
// CNewSlu �Ի���

class CNewSlu : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSlu)

public:
	CNewSlu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewSlu();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_SLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	CString m_sluPath;
	CString m_sluName;
	virtual BOOL OnInitDialog();
};
