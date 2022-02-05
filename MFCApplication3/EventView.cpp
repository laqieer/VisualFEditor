// EventView.cpp : 实现文件
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
	* 函数介绍： 从原字符串里按照指定的分隔字符串进行分割,将分隔的结果存放到字符串数组里
	* 输入参数：
	source -- 原字符串
	ch -- 指定的分隔字符串
	strarr -- 外部引用的一个字符串数组
	* 输出参数：
	* 返回值 ：总共分隔了多少段字符串.
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
	while (findn != -1)//有发现
	{
		findn = source.Find(ch, findi);
		if (findn != -1)
		{
			TmpStr = source.Mid(findi, findn - findi);
			//TmpStr.Trim();//去除头尾空格
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


// CEventView 诊断

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


// CEventView 消息处理程序


void CEventView::OnBnClickedButton1() //载入音乐按钮
{
	CEvent_LoadMusic diaLM = new CEvent_LoadMusic();
	if (diaLM.DoModal() == IDOK)
	{
		CString s1, s2;
		s1.Format(L"载入第%d首音乐", diaLM.m_MusicSequence + 1);
		s2.Format(L"20 12 %.2X 00 ", diaLM.m_MusicSequence + 1);
		manipulateList(s1, s2);
	}
	delete diaLM;
}


void CEventView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	pDoc = (CEventDoc*)GetDocument();//获取文档指针 //获取文档指针
	//pDoc->SetModifiedFlag(); //提示关闭文档时保存文件修改
	m_strTextView = pDoc->m_strTextDoc; //获取文档数据

	UpdateData(FALSE); //初始化自定义数据
}
void CEventView::ViewListToDoc() //将listbox中的内容链接到文档中
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
void CEventView::DocToViewList()//将文档内容链接到listbox中
{
	OnInitialUpdate();
	pDoc = (CEventDoc*)GetDocument();
	CStringArray saInfo;
	CStringArray saCode;
	int m=Split(pDoc->m_strInfo, L"*", saInfo);
	int n = Split(pDoc->m_strCode, L"*", saCode);
	if (n != m)
	{
		AfxMessageBox(L"文档以损坏，打开失败！！！");
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

/*	void 载入音乐(int 音乐编号)
	{
	CString s1, s2;
	s1.Format(L"载入第%d首音乐", 音乐编号);
	s2.Format(L"20 12 %X2 00 ", s2);
	manipulateList(s1, s2);
	}

	void 移动屏幕(int 人物序号)
	{
	CString s1, s2;
	s1.Format(L"屏幕转至人物%d中心处",人物序号);
	s2.Format(L"29 26 %d 00 ", s2);
	manipulateList(s1, s2);
	};
	移动屏幕(int X坐标, int Y坐标)
	{
	CEventView::manipulateList(L"屏幕移动到坐标 X:" + X坐标 + " Y:" + Y坐标 + "处", "20 26 " + X坐标.ToString("X2") + " " + Y坐标.ToString("X2") + " ";
	}
	void 载入人物(string 地址)
	{
	Info = "在" + 地址 + "处载入人物";
	Code = "40 2C 01 00 " + returnpoint(地址) + "20 30 00 00 ";
	}
	void 载入人物2(string 地址)
	{
	Info = "在" + 地址 + "处载入人物";
	Code = "40 05 02 00 " + returnpoint(地址) + "40 0A 00 00 AC 03 A6 08 22 0E 1E 00 ";
	}
	void 结束()
	{
	Info = "结束";
	Code = "28 02 07 00 20 01 00 00 ";
	}
	void 清除屏幕()
	{
	Info = "清除屏幕上所有的人物";
	Code = "2A 34 00 00 2B 34 00 00 2C 34 00 00 20 02 02 00 ";
	}
	void 准备画面()
	{
	Info = "进入准备画面";
	Code = "40 0A 00 00 BC 9D 5B 08 ";
	}
	void 载入地图(int 地图编号)
	{
	Info = "载入第" + 地图编号 + "个地图";
	Code = "20 25 " + 地图编号.ToString("X2") + " 00 ";
	}
	void 进入章节(int 章节编号)
	{
	Info = "进入第" + 章节编号 + "章节";
	Code = "21 2A " + 章节编号.ToString("X2") + " 00 ";
	}
	void 画面淡入(int 淡入时间)
	{
	Info = " 画面以" + 淡入时间 + "的速度淡入";
	Code = "21 17 " + 淡入时间.ToString("X2") + " 00 ";
	}
	void 画面淡出(int 淡出时间)
	{
	Info = " 画面以" + 淡出时间 + "的速度淡入";
	Code = "20 17 " + 淡出时间.ToString("X2") + " 00 ";
	}
	void 光标(int X坐标, int Y坐标)
	{
	Info = "光标放置到坐标 X:" + X坐标 + " Y:" + Y坐标 + "处";
	Code = "20 3B " + X坐标.ToString("X2") + " " + Y坐标.ToString("X2") + " 20 0E 3C 00 22 3B 00 00 ";
	}
	void 光标(int 人物序号)
	{
	Info = "光标放到人物" + 人物序号 + "上";;
	Code = "21 3B " + 人物序号.ToString("X2") + " 00 20 0E 3C 00 22 3B 00 00 ";
	}
	void 移动(int 移动的人物, int x坐标, int y坐标)
	{
	L"移动人物 " + 移动的人物 + " 至坐标  X: " + x坐标 + "   Y: " + y坐标;
	Code = L"40 2F 00 00 " + To16(移动的人物) + " 00 " + To16(x坐标) + " " + To16(y坐标) + " 20 30 00 00 ";
	}
	void 移动(int 移动的人物, int 移动至此人处)
	{
	Info = "移动人物 " + 移动的人物 + " 到人物 " + 移动至此人处 + " 上";
	Code = "41 2F 00 00 " + 移动的人物.ToString("X2") + " 00 " + 移动至此人处.ToString("X2") + " 00 20 30 00 00 ";
	}
	void 对话(int 文字序号, int 背景序号)
	{
	Info = "载入序号为" + 背景序号 + "的背景和序号为" + 文字序号 + "的对话";
	Code = "40 05 02 00 " + 背景序号.ToString("X2") + " 00 00 00 40 05 03 00 " + returntextindex(文字序号) + "00 00 40 0A 00 00 48 04 A6 08 ";
	}
	void 对话(int 文字序号)
	{
	Info = "载入序号为" + 文字序号 + "的对话(无背景图片)";
	Code = "20 1A 00 00 20 1B " + returntextindex(文字序号) + " 20 1D 00 00 22 1B 00 00 ";
	}
	void 人物消失(int 人物序号)
	{
	Info = "人物" + 人物序号 + "在地图上消失";
	Code = "2F 34 " + 人物序号.ToString("X2") + " 00 ";
	}
	void 人物死亡(int 人物序号)
	{
	Info = "人物" + 人物序号 + "在地图上死亡";
	Code = "2D 34 " + 人物序号.ToString("X2") + " 00 ";
	}
	void 成为敌方(int 人物序号)
	{
	Info = "人物" + 人物序号 + "成为敌人";
	Code = "24 34 " + 人物序号.ToString("X2") + " 00 ";
	}
	void 成为我方(int 人物序号)
	{
	Info = "人物" + 人物序号 + "成为我方";
	Code = "22 34 " + 人物序号.ToString("X2") + " 00 ";
	}
	void 成为NPC(int 人物序号)
	{
	Info = "人物" + 人物序号 + "成为NPC";
	Code = "23 34 " + 人物序号.ToString("X2") + " 00 ";
	}
	void 得到物品(int 人物序号, int 物品序号)
	{
	if (人物序号 == 255)
	{
	Info = "当前人物得到物品" + 物品序号;
	Code = "40 05 03 00 " + 人物序号 + " 00 00 00 20 37 FF FF ";
	}
	else
	{
	Info = "人物" + 人物序号 + "得到物品" + 物品序号;
	Code = "40 05 03 00 " + 人物序号.ToString("X2") + " 00 00 00 20 37 " + 物品序号.ToString("X2") + " 00 ";
	}
	}
	void 得到金钱(int 金钱数额)
	{
	string i = 金钱数额.ToString("x6");
	string i1 = i.Substring(4, 2);
	string i2 = i.Substring(2, 2);
	string i3 = i.Substring(0, 2);
	i = i1 + " " + i2 + " " + i3;
	Info = "得到金钱" + 金钱数额;
	Code = "40 05 03 00 " + i + " 00 21 37 00 00 ";
	}
	void 音量降低()
	{
	Info = "降低音量大小";
	Code = "20 15 00 00 ";
	}
	void 音量还原()
	{
	Info = "还原原音量";
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
