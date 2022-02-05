#pragma once
#include "resource.h"

// CEvent_LoadMusic 对话框

class CEvent_LoadMusic : public CDialogEx
{
	DECLARE_DYNAMIC(CEvent_LoadMusic)

public:
	CEvent_LoadMusic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEvent_LoadMusic();

// 对话框数据
	enum { IDD = IDD_EVENT_LOADMUSIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 音乐序号，记录选定的combobox控件的位置
	int m_MusicSequence;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
