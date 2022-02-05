#pragma once
#include "afxcmn.h"
#include "afxwin.h"


#define S_EVENT L"事件"
#define S_EVENT_BLANK L"空白事件"
#define S_EVENT_0 L"0事件"
#define S_UNIT L"人物配置"
#define S_TEXT L"文字对话"
#define S_MAP  L"地图文件"
// CNewSlutionWizad 对话框

class CNewSlutionWizad : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSlutionWizad)

public:
	CNewSlutionWizad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewSlutionWizad();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEWSLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
