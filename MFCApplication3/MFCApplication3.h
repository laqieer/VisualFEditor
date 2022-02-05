
// MFCApplication3.h : MFCApplication3 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "NewSlutionWizad.h"
#include "MainFrm.h"
#include "NewSlu.h"

#define ID_普通剧情 1
#define ID_开始剧情 2
#define ID_结束剧情 3

#define ID_角色事件 5
#define ID_回合事件 6
#define ID_地图事件 7
#define ID_Misc事件 8

#define ID_战场配置 11
#define ID_文字修改 12

// CMFCApplication3App:
// 有关此类的实现，请参阅 MFCApplication3.cpp
//

class CMFCApplication3App : public CWinAppEx
{
private:
	bool IsSluOpened;
public:
	CMFCApplication3App();

// 重写
public:

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void SetComboxContent(int iType);
// 实现
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
	CString Path开始剧情;
	CString Path结束剧情;
	CString Path角色事件;
	CString Path回合事件;
	CString Path地图事件;
	CString PathMisc事件;
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
