
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MFCApplication3.h"

#include "ChildFrm.h"
#define  IDC_MYBUTTON1 10001
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  IDC_MYLISTBOX1 1601
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_MYBUTTON1,OnButton1Click)
	ON_LBN_DBLCLK(IDC_MYLISTBOX1,OnListBox1DoubleClick)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	CButton *p_MyButton1 = new CButton();
	p_MyButton1->Create(L"��̬", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 10, 80, 40), this, IDC_MYBUTTON1);
	CListBox *p_MyListBox1 = new CListBox();
	CRect rect(180, 180, 600, 600);
	p_MyListBox1->Create(WS_CHILD | WS_VISIBLE | LBS_STANDARD, rect, this, IDC_MYLISTBOX1);
	p_MyListBox1->AddString(L"45");
		return 0;
}

void CChildFrame::OnButton1Click()
{
	AfxMessageBox(L"button1click");
}

void CChildFrame::OnListBox1DoubleClick()
{
	AfxMessageBox(L"listbox1dbclick");
}

