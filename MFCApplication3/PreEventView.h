#pragma once
#include "PreEventDoc.h"
#include "afxwin.h"
#include"Resource.h"

// CPreEventView 窗体视图

class CPreEventView : public CFormView
{
	DECLARE_DYNCREATE(CPreEventView)

protected:
	CPreEventView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPreEventView();

public:
	enum { IDD = IDD_PREEVENTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	void ViewListToDoc();
	void DocToViewList();
	void manipulateList(CString sInfo, CString sCode);
	CString m_strTextView;
	CListBox m_ListCode;
	CListBox m_ListInfo;
	afx_msg void OnLbnSelchangeListPreInfo();
	afx_msg void OnLbnSelchangeListPreCode();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedGroupMisc2();
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnEnUpdateEdit1();
	int m_loca_edit_x;
	int m_loca_edit_y;
	int m_turn_edit_0;
	int m_turn_edit_1;
	afx_msg void OnEnUpdateEdit1();
	afx_msg void OnEnUpdateEdit2();
	afx_msg void OnEnUpdateEdit4();
	afx_msg void OnEnUpdateEdit5();
	afx_msg void OnEnUpdateEdit8();
	int m_misc_edut_x;
	int m_misc_edut_y;
	int m_misc_edut_w;
	int m_misc_edut_h;
	afx_msg void OnEnUpdateEdit9();
	afx_msg void OnEnUpdateEdit10();
	afx_msg void OnEnUpdateEdit11();
	afx_msg void OnBnClickedButton2();
};


