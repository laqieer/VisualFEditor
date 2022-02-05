
// MFCApplication3View.cpp : CMFCApplication3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: 在此处添加构造代码

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 绘制

void CMFCApplication3View::OnDraw(CDC* pDC)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOutW(50,2,pDoc->GetTitle());
	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication3View 打印


void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 消息处理程序
