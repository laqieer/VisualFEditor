
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
// CViewTree ��Ϣ�������

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
	// ͨ������ڿͻ����е�λ��
	GetCursorPos(&ptCurSel);
	pTreeCtrl->ScreenToClient(&ptCurSel);
	// ��ȡ��ǰѡ�������һ��
	HitTestInfo.pt = ptCurSel;
	HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);

	if (hSelect == NULL)
	{
		return;
	} 
	CString sSel = pTreeCtrl->GetItemText(hSelect);
	CString sSelParent = pTreeCtrl->GetItemText(pTreeCtrl->GetParentItem(hSelect));
	theApp.OpenDocument(sSelParent, sSel);
	//���ѡ�������ؼ��ı�
	/* ���ø���Ϊѡ��״̬
		pTreeCtrl->SelectItem(hSelect);

	//���·�����ȡ������һ�δ���ѡ��״̬�������Ƚ�����Ķ���ѡ��
	hSelect = pTreeCtrl->GetSelectedItem();
	HTREEITEM hLight = pTreeCtrl->GetDropHilightItem();
	if ((hLight != NULL) && (hSelect != hLight))
		hSelect = hLight;
	if (hSelect == NULL)
		return;
	pTreeCtrl->SelectItem(hSelect);

	//�༭��ǰѡ�ж�������
	pTreeCtrl->EditLabel(hSelect);
	if (NULL != hSelect)
	{
		CString strItem = pTreeCtrl->GetItemText(hSelect);
		if (strItem == _T("������"));
		{
			pTreeCtrl->SetItemText(hSelect, _T("�ı��Ŀ�����"));
		}
		::AfxMessageBox(strItem);
	}*/
	*pResult = 0;
}
