#pragma once


// CEventChildWnd

class CEventChildWnd : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CEventChildWnd)

public:
	CEventChildWnd();
	virtual ~CEventChildWnd();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};


