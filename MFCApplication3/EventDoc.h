#pragma once
#include "EventView.h"
// CEventDoc 文档

class CEventDoc : public CDocument
{
	DECLARE_DYNCREATE(CEventDoc)

public:
	CEventDoc();
	virtual ~CEventDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
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
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	CString m_strTextDoc;
	CFile m_fileDoc;
	CString m_strProperty;
	CString m_strInfo;
	CString m_strCode;
	virtual void OnCloseDocument();
};
