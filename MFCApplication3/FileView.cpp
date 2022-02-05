
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "MFCApplication3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

extern int Split(CString source, CString ch, CStringArray &strarr);
/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
	sTreeParents[0] = L"������";
	sTreeParents[1] = L"���¼�";
	sTreeParents[2] = L"�������¼�";
	sTreeParents[3] = L"�¼��ļ�";
	sTreeParents[4] = L"��������";
	sTreeParents[5] = L"���ֶԻ�";
	sTreeParents[6] = L"��ͼ";
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_REMOVE, OnEditRemove)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_POPUP_EXPLORER_CREATNEWFILE, &CFileView::OnPopupExplorerCreatnewfile) //�˵���ť����Ҫ�����Ϣӳ�䣬����ť�ǻҵ�
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������
HTREEITEM  CFileView::GetTreeItem(int i)
{
	switch (i)
	{
	case 1:return hEvent; break;
	case 2:return hText; break;
	case 3:return hUnit; break;
	case 4:return hMap; break;
	default:
		return NULL;
		break;
	}
}
void CFileView::AddString(CString sFileName, int pos)
{
	HTREEITEM h;
	switch (pos)
	{
	case 1:h = hEvent; break;
	case 2:h = hText; break;
	case 3:h = hUnit; break;
	case 4:h = hMap; break;
	default:
		return;
		break;
	}
	m_wndFileView.InsertItem(sFileName, pos, pos, h);
}

void CFileView::ClearFileView()
{
	m_wndFileView.DeleteAllItems();
}

CString CFileView::GetAllString(int pos)//���ص�ǰ�б��е������ļ�
{
	HTREEITEM hItem;
	switch (pos)
	{
	case 1:hItem = hEvent; break;
	case 2:hItem = hText; break;
	case 3:hItem = hUnit; break;
	case 4:hItem = hMap; break;
	default:
		return NULL;
		break;
	}
	int i = 0;
	CString m_strInfo = L"";
	HTREEITEM h = m_wndFileView.GetChildItem(hItem);
	if (h == NULL)return m_strInfo;
	while (h != NULL)
	{
		m_strInfo += (m_wndFileView.GetItemText(h) + L"*");
		i++;
		h = m_wndFileView.GetNextItem(h, TVGN_NEXT);
	}
	return m_strInfo;
}

void CFileView::SetAllString(CString sEvent, CString sText, CString sUnit, CString sMap)//���ص�ǰ�б��е������ļ�
{
	m_wndFileView.DeleteAllItems();
	hRoot = m_wndFileView.InsertItem(sTreeParents[0], 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	////////////////////////////////////////////////////////
	hEventHead = m_wndFileView.InsertItem(sTreeParents[1], 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("��ʼ����"), 1, 1, hEventHead);
	m_wndFileView.InsertItem(_T("��������"), 1, 1, hEventHead);

	hEvent = m_wndFileView.InsertItem(sTreeParents[3], 0, 0, hEventHead);

	hPreEvent = m_wndFileView.InsertItem(sTreeParents[2], 0, 0, hEventHead);
	m_wndFileView.InsertItem(_T("��ɫ�¼�"), 2, 2, hPreEvent);
	m_wndFileView.InsertItem(_T("��ͼ�¼�"), 2, 2, hPreEvent);
	m_wndFileView.InsertItem(_T("�غ��¼�"), 2, 2, hPreEvent);
	m_wndFileView.InsertItem(_T("Misc�¼�"), 2, 2, hPreEvent);


	//m_wndFileView.InsertItem(_T("��ʼ����"), 1, 1, hEvent);
	//�˴����ڴ����ͨ�¼�


	////////////////////////////////////////////////////////
	hUnit = m_wndFileView.InsertItem(sTreeParents[4], 0, 0, hRoot);
	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hUnit);


	hText = m_wndFileView.InsertItem(sTreeParents[5], 0, 0, hRoot);
	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hUnit);

	hMap = m_wndFileView.InsertItem(sTreeParents[6], 0, 0, hRoot);
	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hUnit);
	//////////////////////////////////////////////////////////
	CStringArray saEvent, saText, saUnit, saMap;
	int m1, m2, m3, m4;
	///////////////////////////
	m1 = Split(sEvent, L"*", saEvent);
	for (int i = 0; i < m1 - 1; i++)
	{
		m_wndFileView.InsertItem(saEvent.GetAt(i), 1, 1, hEvent);
	}
	///////////////////////////
	m2 = Split(sText, L"*", saText);
	for (int i = 0; i < m2 - 1; i++)
	{
		m_wndFileView.InsertItem(saText.GetAt(i), 1, 1, hText);
	}
	///////////////////////////
	m3 = Split(sUnit, L"*", saUnit);
	for (int i = 0; i < m3 - 1; i++)
	{
		m_wndFileView.InsertItem(saUnit.GetAt(i), 1, 1, hUnit);
	}
	///////////////////////////
	m4 = Split(sMap, L"*", saMap);
	for (int i = 0; i < m4 - 1; i++)
	{
		m_wndFileView.InsertItem(saMap.GetAt(i), 1, 1, hMap);
	}

	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hEventHead, TVE_EXPAND);
	m_wndFileView.Expand(hEvent, TVE_EXPAND);
	m_wndFileView.Expand(hPreEvent, TVE_EXPAND);
	m_wndFileView.Expand(hUnit, TVE_EXPAND);
}

HTREEITEM CFileView::GetSelAndSelParent(CString &sSel, CString &sSelParent)
{
	HTREEITEM hSelect = m_wndFileView.GetSelectedItem();
	sSel = m_wndFileView.GetItemText(hSelect);
	sSelParent = m_wndFileView.GetItemText(m_wndFileView.GetParentItem(hSelect));
	return hSelect;
}


int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndFileView;
	CString sItemText;

	ASSERT_VALID(pWndTree);
	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;

		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			sItemText = m_wndFileView.GetItemText(hTreeItem);
			pWndTree->SelectItem(hTreeItem);
		}
	}
	pWndTree->SetFocus();
	if (sItemText == L"")return;
	int iFlag = 0;
	for (int i = 0; i < 7; i++)
	{
		if (sItemText == sTreeParents[i])
			iFlag = 1;
	}
	if (iFlag == 0) //���������˷��ļ���
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
	else //�һ��ļ�
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER1, point.x, point.y, this, TRUE);
	}
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("����...."));

}

void CFileView::OnFileOpen()
{
	CString sSel, sSelParent;

	GetSelAndSelParent(sSel, sSelParent);
	theApp.OpenDocument(sSelParent, sSel);
}

void CFileView::OnFileOpenWith()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnDummyCompile()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditPaste()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditCopy()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditRemove()
{
	int i = AfxMessageBox(L"������ǡ����Ƴ�����ɾ�����ļ����������\n��ֱ��ɾ�����ļ������ȡ��������ò���", MB_ICONINFORMATION | MB_YESNOCANCEL);
	if (i == IDCANCEL)return;

	CString sSel, sSelParent;
	HTREEITEM hSelect = GetSelAndSelParent(sSel, sSelParent);

	if (i == IDNO)
		theApp.DeleteDocument(sSel, sSelParent);

	m_wndFileView.DeleteItem(hSelect);
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void CFileView::OnPopupExplorerCreatnewfile()
{
	AfxMessageBox(L"�½�һ���ļ�");
}
