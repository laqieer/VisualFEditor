// EventChildWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EventChildWnd.h"
#include "EventDoc.h"

// CEventChildWnd

IMPLEMENT_DYNCREATE(CEventChildWnd, CMDIChildWndEx)

CEventChildWnd::CEventChildWnd()
{

}

CEventChildWnd::~CEventChildWnd()
{
}


BEGIN_MESSAGE_MAP(CEventChildWnd, CMDIChildWndEx)
	ON_WM_MDIACTIVATE()
//	ON_WM_ACTIVATE()
END_MESSAGE_MAP()



// CEventChildWnd ��Ϣ�������




BOOL CEventChildWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}


void CEventChildWnd::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

