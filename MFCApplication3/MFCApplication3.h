
// MFCApplication3.h : MFCApplication3 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "NewSlutionWizad.h"
#include "MainFrm.h"
#include "NewSlu.h"

#define ID_��ͨ���� 1
#define ID_��ʼ���� 2
#define ID_�������� 3

#define ID_��ɫ�¼� 5
#define ID_�غ��¼� 6
#define ID_��ͼ�¼� 7
#define ID_Misc�¼� 8

#define ID_ս������ 11
#define ID_�����޸� 12

// CMFCApplication3App:
// �йش����ʵ�֣������ MFCApplication3.cpp
//

class CMFCApplication3App : public CWinAppEx
{
private:
	bool IsSluOpened;
public:
	CMFCApplication3App();

// ��д
public:

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void SetComboxContent(int iType);
// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	int iCreateFileType;
	CString ROMName;

	CString SlutionPath;
	CString SlutionName;
	CString SlutionDictionary;
	CString SlutionLocalDir;

	CString SlutionEventFileList;
	CString SlutionTextFileList;
	CString SlutionUnitFileList;
	CString SlutionMapFileList;

	CString DicList[5];
	CString Path��ʼ����;
	CString Path��������;
	CString Path��ɫ�¼�;
	CString Path�غ��¼�;
	CString Path��ͼ�¼�;
	CString PathMisc�¼�;
public:
	CMultiDocTemplate* pDocTemplate1;
	CMultiDocTemplate* pDocTemplate2;
	void SetOLEVisible(bool bVisible =TRUE);

	bool OpenDocument(CString sSelectParent, CString sSelect);
	bool DeleteDocument(CString sSelectParent, CString sSelect);

	void SetCreateFileType(int iType);
	int GetCreateFileType();

	CString To16(int iinput);
	int To10(CString sinput);
	static CString GetCXY(int X, int Y);
	void  setPath();

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnSluNew();
	afx_msg void OnSluOpen();
	afx_msg void OnSluSave();
	afx_msg void OnSluClose();

	afx_msg void OnFileNew();
	afx_msg void OnFileAdd();
	afx_msg void OnFileSave();
	afx_msg void OnFileClose();
	DECLARE_MESSAGE_MAP()
};

 
extern CMFCApplication3App theApp;
