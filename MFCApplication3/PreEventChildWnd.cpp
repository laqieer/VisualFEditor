// PreEventChildWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PreEventChildWnd.h"
#include "PreEventDoc.h"

// CPreEventChildWnd

IMPLEMENT_DYNCREATE(CPreEventChildWnd, CMDIChildWndEx)

CPreEventChildWnd::CPreEventChildWnd()
{

}

CPreEventChildWnd::~CPreEventChildWnd()
{
}


BEGIN_MESSAGE_MAP(CPreEventChildWnd, CMDIChildWndEx)
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()



// CPreEventChildWnd ��Ϣ�������




void CPreEventChildWnd::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}
