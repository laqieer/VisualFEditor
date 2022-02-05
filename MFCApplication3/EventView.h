#pragma once
#include "afxwin.h"
#include"Resource.h"
// CEventView 窗体视图

class CEventView : public CFormView
{
	DECLARE_DYNCREATE(CEventView)

private:
	CString m_strTextView;
	void manipulateList(CString sInfo, CString sCode);

	CString To16(int iinput)
	{
		CString s;
		s.Format(L"%x2", iinput);
		return s;
	}
	int To10(CString sinput)
	{
		return _wtoi(sinput + L"X");
	}
	CListBox m_ListCode;
	CListBox m_ListInfo;

protected:
	CEventView();           // 动态创建所使用的受保护的构造函数
	virtual ~CEventView();

public:
	enum { IDD = IDD_EVENTVIEW };
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

	void ViewListToDoc();
	void DocToViewList();

	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeListInfo();
	afx_msg void OnLbnSelchangeListCode();
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg void OnChildActivate();
};


