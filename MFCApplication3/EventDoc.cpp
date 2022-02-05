// EventDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "EventDoc.h"


// CEventDoc

IMPLEMENT_DYNCREATE(CEventDoc, CDocument)

CEventDoc::CEventDoc()
{
	m_strTextDoc = _T("");
}

CEventDoc::~CEventDoc()
{
}


BEGIN_MESSAGE_MAP(CEventDoc, CDocument)
END_MESSAGE_MAP()


// CEventDoc 诊断

#ifdef _DEBUG
void CEventDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CEventDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CEventDoc 序列化

void CEventDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strProperty << m_strInfo << m_strCode;
	}
	else
	{
		ar >> m_strProperty >> m_strInfo >> m_strCode;
	}
}
#endif

// CEventDoc 命令

BOOL CEventDoc::OnNewDocument()
{
	m_strProperty = m_strInfo = m_strCode = L"";
	return TRUE;
}

BOOL CEventDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	POSITION pos = GetFirstViewPosition();// 获得第一个视类对象在对象列表中的位置
		CEventView *pView = (CEventView*)GetNextView(pos);
		pView->DocToViewList();
	return TRUE;
}

BOOL CEventDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();// 获得第一个视类对象在对象列表中的位置 

	CEventView *pView = (CEventView*)GetNextView(pos);
	pView->ViewListToDoc();

	return CDocument::OnSaveDocument(lpszPathName);
}


void CEventDoc::OnCloseDocument()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDocument::OnCloseDocument();
}
