// EventDoc.cpp : ʵ���ļ�
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


// CEventDoc ���

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
// CEventDoc ���л�

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

// CEventDoc ����

BOOL CEventDoc::OnNewDocument()
{
	m_strProperty = m_strInfo = m_strCode = L"";
	return TRUE;
}

BOOL CEventDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	POSITION pos = GetFirstViewPosition();// ��õ�һ����������ڶ����б��е�λ��
		CEventView *pView = (CEventView*)GetNextView(pos);
		pView->DocToViewList();
	return TRUE;
}

BOOL CEventDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();// ��õ�һ����������ڶ����б��е�λ�� 

	CEventView *pView = (CEventView*)GetNextView(pos);
	pView->ViewListToDoc();

	return CDocument::OnSaveDocument(lpszPathName);
}


void CEventDoc::OnCloseDocument()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDocument::OnCloseDocument();
}
