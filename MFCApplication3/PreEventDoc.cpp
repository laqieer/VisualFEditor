// PreEventDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "PreEventDoc.h"


// CPreEventDoc

IMPLEMENT_DYNCREATE(CPreEventDoc, CDocument)

CPreEventDoc::CPreEventDoc()
{
	m_strTextDoc = _T("");
	m_strProperty = _T("");
	m_strInfo = _T("");
	m_strCode = _T("");
}

BOOL CPreEventDoc::OnNewDocument()
{
	m_strProperty = m_strInfo = m_strCode = L"";
	return true;
}

CPreEventDoc::~CPreEventDoc()
{
}


BEGIN_MESSAGE_MAP(CPreEventDoc, CDocument)
END_MESSAGE_MAP()


// CPreEventDoc 诊断

#ifdef _DEBUG
void CPreEventDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPreEventDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CPreEventDoc 序列化

void CPreEventDoc::Serialize(CArchive& ar)
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


// CPreEventDoc 命令


BOOL CPreEventDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	POSITION pos = GetFirstViewPosition();// 获得第一个视类对象在对象列表中的位置
	CPreEventView *pView = (CPreEventView*)GetNextView(pos);
	pView->DocToViewList();

	return TRUE;
}


void CPreEventDoc::OnCloseDocument()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDocument::OnCloseDocument();
}


BOOL CPreEventDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();// 获得第一个视类对象在对象列表中的位置 

	CPreEventView *pView = (CPreEventView*)GetNextView(pos);
	pView->ViewListToDoc();

	return CDocument::OnSaveDocument(lpszPathName);
}
