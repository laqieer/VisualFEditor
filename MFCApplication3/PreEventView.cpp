// PreEventView.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "PreEventView.h"


// CPreEventView

IMPLEMENT_DYNCREATE(CPreEventView, CFormView)

CPreEventDoc *pDoc;
extern int Split(CString source, CString ch, CStringArray &strarr);

CPreEventView::CPreEventView()
	: CFormView(CPreEventView::IDD)
	, m_loca_edit_x(0)
	, m_loca_edit_y(0)
	, m_turn_edit_0(0)
	, m_turn_edit_1(0)
	, m_misc_edut_x(0)
	, m_misc_edut_y(0)
	, m_misc_edut_w(0)
	, m_misc_edut_h(0)
{

	m_strTextView = _T("");
}

CPreEventView::~CPreEventView()
{
}

void CPreEventView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRE_CODE, m_ListCode);
	DDX_Control(pDX, IDC_LIST_PRE_INFO, m_ListInfo);
	DDX_Text(pDX, IDC_EDIT1, m_loca_edit_x);
	DDV_MinMaxInt(pDX, m_loca_edit_x, 0, 50);
	DDX_Text(pDX, IDC_EDIT2, m_loca_edit_y);
	DDV_MinMaxInt(pDX, m_loca_edit_y, 0, 50);
	DDX_Text(pDX, IDC_EDIT4, m_turn_edit_0);
	DDV_MinMaxInt(pDX, m_turn_edit_0, 0, 50);
	DDX_Text(pDX, IDC_EDIT5, m_turn_edit_1);
	DDV_MinMaxInt(pDX, m_turn_edit_1, 0, 50);
	DDX_Text(pDX, IDC_EDIT8, m_misc_edut_x);
	DDV_MinMaxInt(pDX, m_misc_edut_x, 0, 50);
	DDX_Text(pDX, IDC_EDIT9, m_misc_edut_y);
	DDV_MinMaxInt(pDX, m_misc_edut_y, 0, 50);
	DDX_Text(pDX, IDC_EDIT10, m_misc_edut_w);
	DDV_MinMaxInt(pDX, m_misc_edut_w, 0, 50);
	DDX_Text(pDX, IDC_EDIT11, m_misc_edut_h);
	DDV_MinMaxInt(pDX, m_misc_edut_h, 0, 50);
}

BEGIN_MESSAGE_MAP(CPreEventView, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST_PRE_INFO, &CPreEventView::OnLbnSelchangeListPreInfo)
	ON_LBN_SELCHANGE(IDC_LIST_PRE_CODE, &CPreEventView::OnLbnSelchangeListPreCode)
	ON_BN_CLICKED(IDC_BUTTON1, &CPreEventView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_GROUP_MISC2, &CPreEventView::OnBnClickedGroupMisc2)
//	ON_WM_CHAR()
//ON_EN_UPDATE(IDC_EDIT1, &CPreEventView::OnEnUpdateEdit1)
ON_EN_UPDATE(IDC_EDIT1, &CPreEventView::OnEnUpdateEdit1)
ON_EN_UPDATE(IDC_EDIT2, &CPreEventView::OnEnUpdateEdit2)
ON_EN_UPDATE(IDC_EDIT4, &CPreEventView::OnEnUpdateEdit4)
ON_EN_UPDATE(IDC_EDIT5, &CPreEventView::OnEnUpdateEdit5)
ON_EN_UPDATE(IDC_EDIT8, &CPreEventView::OnEnUpdateEdit8)
ON_EN_UPDATE(IDC_EDIT9, &CPreEventView::OnEnUpdateEdit9)
ON_EN_UPDATE(IDC_EDIT10, &CPreEventView::OnEnUpdateEdit10)
ON_EN_UPDATE(IDC_EDIT11, &CPreEventView::OnEnUpdateEdit11)
ON_BN_CLICKED(IDC_BUTTON2, &CPreEventView::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPreEventView 诊断

#ifdef _DEBUG
void CPreEventView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreEventView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreEventView 消息处理程序


void CPreEventView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	pDoc = (CPreEventDoc*)GetDocument();//获取文档指针 //获取文档指针
	m_strTextView = pDoc->m_strTextDoc; //获取文档数据
	CString sDocType= pDoc->GetTitle();

	if (sDocType == L"角色事件启动子.peve")
	{
		GetDlgItem(IDC_GROUP_CHAR)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW); 
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(0);

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW); 
	}

	if (sDocType == L"地图事件启动子.peve")
	{
		GetDlgItem(IDC_GROUP_LOCA)->ShowWindow(SW_SHOW);

		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(true);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC12)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_COMBO4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO7)->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(0);

		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
	}

	if (sDocType == L"回合事件启动子.peve")
	{
		GetDlgItem(IDC_GROUP_TURN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GROUP_TURN2)->ShowWindow(SW_SHOW);

		((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(true);
		GetDlgItem(IDC_RADIO7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO9)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC14)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_COMBO8)->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(0);

		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	}

	if (sDocType == L"Misc事件启动子.peve")
	{
		GetDlgItem(IDC_GROUP_MISC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GROUP_MISC2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC17)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC18)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC19)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC21)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC22)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC23)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC24)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC25)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT11)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_COMBO9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO11)->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO9))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO10))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO11))->SetCurSel(0);

		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);
	}
	//pDoc->SetModifiedFlag(); //提示关闭文档时保存文件修改

	UpdateData(FALSE); //初始化自定义数据
	// TODO:  在此添加专用代码和/或调用基类
}

void CPreEventView::ViewListToDoc() //将listbox中的内容链接到文档中
{
	pDoc = (CPreEventDoc*)GetDocument();
	pDoc->m_strInfo.Empty();
	pDoc->m_strCode.Empty();
	for (int i = 0; i < m_ListInfo.GetCount(); i++)
	{
		CString s;
		m_ListInfo.GetText(i, s);
		pDoc->m_strInfo += (s + L"*");
		/////////////////////////////
		m_ListCode.GetText(i, s);
		pDoc->m_strCode += (s + L"*");
	}
}
void CPreEventView::DocToViewList()//将文档内容链接到listbox中
{
	OnInitialUpdate();
	pDoc = (CPreEventDoc*)GetDocument();
	CStringArray saInfo;
	CStringArray saCode;
	int m = Split(pDoc->m_strInfo, L"*", saInfo);
	int n = Split(pDoc->m_strCode, L"*", saCode);
	if (n != m)
	{
		AfxMessageBox(L"文档以损坏，打开失败！！！");
		return;
	}
	for (int i = 0; i < m - 1; i++)
	{
		m_ListInfo.AddString(saInfo.GetAt(i));
		m_ListCode.AddString(saCode.GetAt(i));
	}
}

void CPreEventView::OnLbnSelchangeListPreInfo()
{
	m_ListCode.SetCurSel(m_ListInfo.GetCurSel());
}


void CPreEventView::OnLbnSelchangeListPreCode()
{
	m_ListInfo.SetCurSel(m_ListCode.GetCurSel());
}

void CPreEventView::manipulateList(CString sInfo, CString sCode)
{
	m_ListInfo.InsertString(m_ListInfo.GetCurSel() + 1, sInfo);
	m_ListInfo.SetCurSel(m_ListInfo.GetCount() - 1);
	pDoc->SetModifiedFlag();
	m_ListCode.InsertString(m_ListCode.GetCurSel() + 1, sCode);
	m_ListCode.SetCurSel(m_ListCode.GetCount() - 1);
}

void CPreEventView::OnBnClickedButton1()
{	/*if (textBox21.TextLength < 7) { MessageBox.Show(null, "请输入一个有效的七位数指针，地址在1000000之后", null, MessageBoxButtons.OK, MessageBoxIcon.Information); return; }
	Int32 a = Convert.ToInt32(numericUpDown43.Value);
	Int32 b = Convert.ToInt32(numericUpDown42.Value);
	string x = a.ToString("X2");
	string y = b.ToString("X2");
	string a1 = textBox21.Text.Substring(5, 2);
	string a2 = textBox21.Text.Substring(3, 2);
	string a3 = textBox21.Text.Substring(1, 2);
	string p = a1 + " " + a2 + " " + a3 + " 09 ";     //实际写入地址
	listcode.Items.Insert(listinfo.SelectedIndex + 1, "03 00 " + EventID++.ToString("X2") + " 00 " + p + x + " " + y + " 00 00 00 00 00 00 ");
	listinfo.Items.Insert(listinfo.SelectedIndex + 1, "人物" + a + "对人物" + b + "有话要说" + textBox21.Text);
	listinfo.SelectedIndex = listinfo.Items.Count - 1;
	listcode.SelectedIndex = listinfo.Items.Count - 1;*/
	UpdateData();
	CString sAdress,s0,s1, s2;
	((CComboBox*)GetDlgItem(IDC_COMBO3))->GetWindowTextW(sAdress);
	if (sAdress.GetLength() < 7)
	{
		AfxMessageBox(L"输入的地址有误");
		return;
	}
	s0.Format(L"%s %s %s 09 ", sAdress.Mid(5, 2), sAdress.Mid(3, 2), sAdress.Mid(1, 2));
	int role1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel()+1;
	int role2 = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel()+1;
	int EventID = 18;
	s1.Format(L"人物%d对人物%d有话要说%s",role1,role2,sAdress);
	s2.Format(L"03 00 %.2X 00 %s %.2X %.2X 00 00 00 00 00 00 ",EventID,s0,role1,role2);
	manipulateList(s1, s2);
}


void CPreEventView::OnBnClickedGroupMisc2()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CPreEventView::OnEnUpdateEdit1()
{
	UpdateData();
	if (m_loca_edit_x> 50)
		m_loca_edit_x /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit2()
{
	UpdateData();
	if (m_loca_edit_y> 50)
		m_loca_edit_y /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit4()
{
	UpdateData();
	if (m_turn_edit_0> 50)
		m_turn_edit_0 /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit5()
{
	UpdateData();
	if (m_turn_edit_1> 50)
		m_turn_edit_1 /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit8()
{
	UpdateData();
	if (m_misc_edut_x> 50)
		m_misc_edut_x /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit9()
{
	UpdateData();
	if (m_misc_edut_y> 50)
		m_misc_edut_y /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit10()
{
	UpdateData();
	if (m_misc_edut_w> 50)
		m_misc_edut_w /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnEnUpdateEdit11()
{
	UpdateData();
	if (m_misc_edut_h> 50)
		m_misc_edut_h /= 10;
	UpdateData(FALSE);
}


void CPreEventView::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
}
