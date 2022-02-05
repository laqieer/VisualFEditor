
#include "stdafx.h"
#include "MFCApplication3.h"
#include "ViewTree.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTreeCtrl* pTreeCtrl = this; 
	CPoint ptCurSel(0, 0);
	TVHITTESTINFO HitTestInfo;
	// 通过鼠标在客户区中的位置
	GetCursorPos(&ptCurSel);
	pTreeCtrl->ScreenToClient(&ptCurSel);
	// 获取当前选择的是哪一项
	HitTestInfo.pt = ptCurSel;
	HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);

	if (hSelect == NULL)
	{
		return;
	} 
	CString sSel = pTreeCtrl->GetItemText(hSelect);
	CString sSelParent = pTreeCtrl->GetItemText(pTreeCtrl->GetParentItem(hSelect));
	theApp.OpenDocument(sSelParent, sSel);
	//获得选定的树控件文本
	/* 设置该项为选中状态
		pTreeCtrl->SelectItem(hSelect);

	//以下方法获取的是上一次处于选中状态的项首先将点击的对象选中
	hSelect = pTreeCtrl->GetSelectedItem();
	HTREEITEM hLight = pTreeCtrl->GetDropHilightItem();
	if ((hLight != NULL) && (hSelect != hLight))
		hSelect = hLight;
	if (hSelect == NULL)
		return;
	pTreeCtrl->SelectItem(hSelect);

	//编辑当前选中对象名称
	pTreeCtrl->EditLabel(hSelect);
	if (NULL != hSelect)
	{
		CString strItem = pTreeCtrl->GetItemText(hSelect);
		if (strItem == _T("控制器"));
		{
			pTreeCtrl->SetItemText(hSelect, _T("改变后的控制器"));
		}
		::AfxMessageBox(strItem);
	}*/
	*pResult = 0;
}
