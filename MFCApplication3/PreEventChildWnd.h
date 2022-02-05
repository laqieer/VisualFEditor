#pragma once


// CPreEventChildWnd

class CPreEventChildWnd : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CPreEventChildWnd)

public:
	CPreEventChildWnd();
	virtual ~CPreEventChildWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};


