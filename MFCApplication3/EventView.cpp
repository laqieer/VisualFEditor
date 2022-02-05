// EventView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "EventView.h"
#include "EventDoc.h"
#include "Event_LoadMusic.h"
// CEventView

IMPLEMENT_DYNCREATE(CEventView, CFormView)

CEventDoc*pDoc;
int Split(CString source, CString ch, CStringArray &strarr);

int Split(CString source, CString ch, CStringArray &strarr)
{
	/*---------------------------------------------------------
	* �������ܣ� ��ԭ�ַ����ﰴ��ָ���ķָ��ַ������зָ�,���ָ��Ľ����ŵ��ַ���������
	* ���������
	source -- ԭ�ַ���
	ch -- ָ���ķָ��ַ���
	strarr -- �ⲿ���õ�һ���ַ�������
	* ���������
	* ����ֵ ���ܹ��ָ��˶��ٶ��ַ���.
	-----------------------------------------------------------*/
	CString TmpStr;
	strarr.RemoveAll();
	if (source.IsEmpty() || ch.IsEmpty())
		return 0;
	int len = ch.GetLength();
	int findi = 0;
	int findn = 0;
	int sum = 0;
	findn = source.Find(ch, findi);
	if (findn != -1)
	{
		TmpStr = source.Mid(0, findn);
		//TmpStr.Trim();
		strarr.Add(TmpStr);
		findi = findn + len;
		sum++;
	}
	else
	{
		//source.Trim();
		strarr.Add(source);
		sum++;
		return sum;
	}
	while (findn != -1)//�з���
	{
		findn = source.Find(ch, findi);
		if (findn != -1)
		{
			TmpStr = source.Mid(findi, findn - findi);
			//TmpStr.Trim();//ȥ��ͷβ�ո�
			strarr.Add(TmpStr);
			findi = findn + len;
			sum++;
		}
		else
		{
			TmpStr = source.Mid(findi, source.GetLength() - findi);
			//TmpStr.Trim();
			strarr.Add(TmpStr);
			sum++;
		}
	}
	return sum;
}


CEventView::CEventView()
: CFormView(CEventView::IDD)
{
	m_strTextView = _T("");
}

CEventView::~CEventView()
{
}

void CEventView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CODE, m_ListCode);
	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
}

BEGIN_MESSAGE_MAP(CEventView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CEventView::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST_INFO, &CEventView::OnLbnSelchangeListInfo)
	ON_LBN_SELCHANGE(IDC_LIST_CODE, &CEventView::OnLbnSelchangeListCode)
//	ON_WM_ACTIVATE()
//	ON_WM_CHILDACTIVATE()
END_MESSAGE_MAP()


// CEventView ���

#ifdef _DEBUG
void CEventView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CEventView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CEventView ��Ϣ�������


void CEventView::OnBnClickedButton1() //�������ְ�ť
{
	CEvent_LoadMusic diaLM = new CEvent_LoadMusic();
	if (diaLM.DoModal() == IDOK)
	{
		CString s1, s2;
		s1.Format(L"�����%d������", diaLM.m_MusicSequence + 1);
		s2.Format(L"20 12 %.2X 00 ", diaLM.m_MusicSequence + 1);
		manipulateList(s1, s2);
	}
	delete diaLM;
}


void CEventView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	pDoc = (CEventDoc*)GetDocument();//��ȡ�ĵ�ָ�� //��ȡ�ĵ�ָ��
	//pDoc->SetModifiedFlag(); //��ʾ�ر��ĵ�ʱ�����ļ��޸�
	m_strTextView = pDoc->m_strTextDoc; //��ȡ�ĵ�����

	UpdateData(FALSE); //��ʼ���Զ�������
}
void CEventView::ViewListToDoc() //��listbox�е��������ӵ��ĵ���
{
	pDoc = (CEventDoc*)GetDocument();
	pDoc->m_strInfo.Empty();
	pDoc->m_strCode.Empty();
	for (int i = 0; i < m_ListInfo.GetCount();i++)
	{ 
		CString s;
		m_ListInfo.GetText(i, s);
		pDoc->m_strInfo += (s+L"*");
		/////////////////////////////
		m_ListCode.GetText(i, s);
		pDoc->m_strCode += (s + L"*");
	}
}
void CEventView::DocToViewList()//���ĵ��������ӵ�listbox��
{
	OnInitialUpdate();
	pDoc = (CEventDoc*)GetDocument();
	CStringArray saInfo;
	CStringArray saCode;
	int m=Split(pDoc->m_strInfo, L"*", saInfo);
	int n = Split(pDoc->m_strCode, L"*", saCode);
	if (n != m)
	{
		AfxMessageBox(L"�ĵ����𻵣���ʧ�ܣ�����");
		return;
	}
	for (int i = 0; i < m-1; i++)
	{
		m_ListInfo.AddString(saInfo.GetAt(i));
		m_ListCode.AddString(saCode.GetAt(i));
	}
}

void CEventView::manipulateList(CString sInfo, CString sCode)
{
	m_ListInfo.InsertString( m_ListInfo.GetCurSel()+1, sInfo);
	m_ListInfo.SetCurSel(m_ListInfo.GetCount() - 1);
	pDoc->SetModifiedFlag();
	m_ListCode.InsertString(m_ListCode.GetCurSel() + 1, sCode);
	m_ListCode.SetCurSel(m_ListCode.GetCount() - 1);
}

/*	void ��������(int ���ֱ��)
	{
	CString s1, s2;
	s1.Format(L"�����%d������", ���ֱ��);
	s2.Format(L"20 12 %X2 00 ", s2);
	manipulateList(s1, s2);
	}

	void �ƶ���Ļ(int �������)
	{
	CString s1, s2;
	s1.Format(L"��Ļת������%d���Ĵ�",�������);
	s2.Format(L"29 26 %d 00 ", s2);
	manipulateList(s1, s2);
	};
	�ƶ���Ļ(int X����, int Y����)
	{
	CEventView::manipulateList(L"��Ļ�ƶ������� X:" + X���� + " Y:" + Y���� + "��", "20 26 " + X����.ToString("X2") + " " + Y����.ToString("X2") + " ";
	}
	void ��������(string ��ַ)
	{
	Info = "��" + ��ַ + "����������";
	Code = "40 2C 01 00 " + returnpoint(��ַ) + "20 30 00 00 ";
	}
	void ��������2(string ��ַ)
	{
	Info = "��" + ��ַ + "����������";
	Code = "40 05 02 00 " + returnpoint(��ַ) + "40 0A 00 00 AC 03 A6 08 22 0E 1E 00 ";
	}
	void ����()
	{
	Info = "����";
	Code = "28 02 07 00 20 01 00 00 ";
	}
	void �����Ļ()
	{
	Info = "�����Ļ�����е�����";
	Code = "2A 34 00 00 2B 34 00 00 2C 34 00 00 20 02 02 00 ";
	}
	void ׼������()
	{
	Info = "����׼������";
	Code = "40 0A 00 00 BC 9D 5B 08 ";
	}
	void �����ͼ(int ��ͼ���)
	{
	Info = "�����" + ��ͼ��� + "����ͼ";
	Code = "20 25 " + ��ͼ���.ToString("X2") + " 00 ";
	}
	void �����½�(int �½ڱ��)
	{
	Info = "�����" + �½ڱ�� + "�½�";
	Code = "21 2A " + �½ڱ��.ToString("X2") + " 00 ";
	}
	void ���浭��(int ����ʱ��)
	{
	Info = " ������" + ����ʱ�� + "���ٶȵ���";
	Code = "21 17 " + ����ʱ��.ToString("X2") + " 00 ";
	}
	void ���浭��(int ����ʱ��)
	{
	Info = " ������" + ����ʱ�� + "���ٶȵ���";
	Code = "20 17 " + ����ʱ��.ToString("X2") + " 00 ";
	}
	void ���(int X����, int Y����)
	{
	Info = "�����õ����� X:" + X���� + " Y:" + Y���� + "��";
	Code = "20 3B " + X����.ToString("X2") + " " + Y����.ToString("X2") + " 20 0E 3C 00 22 3B 00 00 ";
	}
	void ���(int �������)
	{
	Info = "���ŵ�����" + ������� + "��";;
	Code = "21 3B " + �������.ToString("X2") + " 00 20 0E 3C 00 22 3B 00 00 ";
	}
	void �ƶ�(int �ƶ�������, int x����, int y����)
	{
	L"�ƶ����� " + �ƶ������� + " ������  X: " + x���� + "   Y: " + y����;
	Code = L"40 2F 00 00 " + To16(�ƶ�������) + " 00 " + To16(x����) + " " + To16(y����) + " 20 30 00 00 ";
	}
	void �ƶ�(int �ƶ�������, int �ƶ������˴�)
	{
	Info = "�ƶ����� " + �ƶ������� + " ������ " + �ƶ������˴� + " ��";
	Code = "41 2F 00 00 " + �ƶ�������.ToString("X2") + " 00 " + �ƶ������˴�.ToString("X2") + " 00 20 30 00 00 ";
	}
	void �Ի�(int �������, int �������)
	{
	Info = "�������Ϊ" + ������� + "�ı��������Ϊ" + ������� + "�ĶԻ�";
	Code = "40 05 02 00 " + �������.ToString("X2") + " 00 00 00 40 05 03 00 " + returntextindex(�������) + "00 00 40 0A 00 00 48 04 A6 08 ";
	}
	void �Ի�(int �������)
	{
	Info = "�������Ϊ" + ������� + "�ĶԻ�(�ޱ���ͼƬ)";
	Code = "20 1A 00 00 20 1B " + returntextindex(�������) + " 20 1D 00 00 22 1B 00 00 ";
	}
	void ������ʧ(int �������)
	{
	Info = "����" + ������� + "�ڵ�ͼ����ʧ";
	Code = "2F 34 " + �������.ToString("X2") + " 00 ";
	}
	void ��������(int �������)
	{
	Info = "����" + ������� + "�ڵ�ͼ������";
	Code = "2D 34 " + �������.ToString("X2") + " 00 ";
	}
	void ��Ϊ�з�(int �������)
	{
	Info = "����" + ������� + "��Ϊ����";
	Code = "24 34 " + �������.ToString("X2") + " 00 ";
	}
	void ��Ϊ�ҷ�(int �������)
	{
	Info = "����" + ������� + "��Ϊ�ҷ�";
	Code = "22 34 " + �������.ToString("X2") + " 00 ";
	}
	void ��ΪNPC(int �������)
	{
	Info = "����" + ������� + "��ΪNPC";
	Code = "23 34 " + �������.ToString("X2") + " 00 ";
	}
	void �õ���Ʒ(int �������, int ��Ʒ���)
	{
	if (������� == 255)
	{
	Info = "��ǰ����õ���Ʒ" + ��Ʒ���;
	Code = "40 05 03 00 " + ������� + " 00 00 00 20 37 FF FF ";
	}
	else
	{
	Info = "����" + ������� + "�õ���Ʒ" + ��Ʒ���;
	Code = "40 05 03 00 " + �������.ToString("X2") + " 00 00 00 20 37 " + ��Ʒ���.ToString("X2") + " 00 ";
	}
	}
	void �õ���Ǯ(int ��Ǯ����)
	{
	string i = ��Ǯ����.ToString("x6");
	string i1 = i.Substring(4, 2);
	string i2 = i.Substring(2, 2);
	string i3 = i.Substring(0, 2);
	i = i1 + " " + i2 + " " + i3;
	Info = "�õ���Ǯ" + ��Ǯ����;
	Code = "40 05 03 00 " + i + " 00 21 37 00 00 ";
	}
	void ��������()
	{
	Info = "����������С";
	Code = "20 15 00 00 ";
	}
	void ������ԭ()
	{
	Info = "��ԭԭ����";
	Code = "21 15 00 00 ";
	}
	*/

void CEventView::OnLbnSelchangeListInfo()
{
	m_ListCode.SetCurSel(m_ListInfo.GetCurSel());
}


void CEventView::OnLbnSelchangeListCode()
{
	m_ListInfo.SetCurSel(m_ListCode.GetCurSel());
}
