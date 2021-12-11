// CGAlgorithmView.cpp : CCGAlgorithmView 类的实现
//

#include "stdafx.h"
#include "CGAlgorithm.h"

#include "CGAlgorithmDoc.h"
#include "CGAlgorithmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGAlgorithmView

IMPLEMENT_DYNCREATE(CCGAlgorithmView, CView)

BEGIN_MESSAGE_MAP(CCGAlgorithmView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCGAlgorithmView 构造/析构

CCGAlgorithmView::CCGAlgorithmView()
{
	// TODO: 在此处添加构造代码

}

CCGAlgorithmView::~CCGAlgorithmView()
{
}

BOOL CCGAlgorithmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CCGAlgorithmView 绘制

void CCGAlgorithmView::OnDraw(CDC* /*pDC*/)
{
	CCGAlgorithmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCGAlgorithmView 打印

BOOL CCGAlgorithmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCGAlgorithmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CCGAlgorithmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CCGAlgorithmView 诊断

#ifdef _DEBUG
void CCGAlgorithmView::AssertValid() const
{
	CView::AssertValid();
}

void CCGAlgorithmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGAlgorithmDoc* CCGAlgorithmView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgorithmDoc)));
	return (CCGAlgorithmDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGAlgorithmView 消息处理程序
