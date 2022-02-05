
#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 构造
private: 
	CString sTreeParents[7];
	HTREEITEM hRoot, hEventHead, hEvent, hPreEvent, hUnit, hText, hMap;
public:
	CFileView();

	HTREEITEM GetTreeItem(int i=1);
	void AdjustLayout();
	void OnChangeVisualStyle();
	void AddString(CString sFileName, int pos = 1);
	CString GetAllString(int pos);
	void SetAllString(CString sEvent, CString sText, CString sUnit, CString sMap);//返回当前列表中的所有文件
	void ClearFileView();

protected:

	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnEditRemove();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	HTREEITEM GetSelAndSelParent(CString &sSel, CString &sSelParent);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPopupExplorerCreatnewfile();
};

