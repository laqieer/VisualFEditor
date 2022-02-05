#pragma once
#include "resource.h"
#include "afxwin.h"
// CNewSlu 对话框

class CNewSlu : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSlu)

public:
	CNewSlu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewSlu();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_SLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	CString m_sluPath;
	CString m_sluName;
	virtual BOOL OnInitDialog();
};
