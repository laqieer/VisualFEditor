#pragma once
#include "PreEventView.h"
// CPreEventDoc �ĵ�

class CPreEventDoc : public CDocument
{
	DECLARE_DYNCREATE(CPreEventDoc)

public:
	CPreEventDoc();
	virtual ~CPreEventDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTextDoc;
	CString m_strProperty;
	CString m_strInfo;
	CString m_strCode;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
