#pragma once
#include "resource.h"

// CEvent_LoadMusic �Ի���

class CEvent_LoadMusic : public CDialogEx
{
	DECLARE_DYNAMIC(CEvent_LoadMusic)

public:
	CEvent_LoadMusic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEvent_LoadMusic();

// �Ի�������
	enum { IDD = IDD_EVENT_LOADMUSIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// ������ţ���¼ѡ����combobox�ؼ���λ��
	int m_MusicSequence;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
