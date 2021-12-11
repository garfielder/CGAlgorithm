// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "CGAlgorithm.h"
#include "CGAlgorithmDoc.h"
#include "RightView.h"
#include ".\rightview.h"



// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{
}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CRightView 绘图

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();


	/*CPoint ptCenter;
	CRect  rect		;	
	pDC->GetClipBox(&rect);

	ptCenter.x = (rect.left + rect.right)/2;
	ptCenter.y = (rect.bottom + rect.top)/2;

	pDC->MoveTo(rect.left, ptCenter.y);		pDC->LineTo(rect.right, ptCenter.y);
	pDC->MoveTo(ptCenter.x, rect.bottom);	pDC->LineTo(ptCenter.x, rect.top);*/

	// TODO: 在此添加绘制代码
	if(GetDocument()->pGraph)
		GetDocument()->pGraph->Draw();

	


}


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG


// CRightView 消息处理程序

void CRightView::OnLButtonDown(UINT nFlags, CPoint Vector3)
{
	CCGAlgorithmDoc* pDoc = GetDocument();

	MSG msg;
	msg.hwnd = *this;
	msg.message = WM_LBUTTONDOWN;
	msg.pt		= Vector3;

	pDoc->ReceiveMSG(msg);

	//t
	CView::OnLButtonDown(nFlags, Vector3);
}

CCGAlgorithmDoc* CRightView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgorithmDoc)));
	return (CCGAlgorithmDoc*)m_pDocument;
}
void CRightView::OnRButtonDown(UINT nFlags, CPoint Vector3)
{
	CCGAlgorithmDoc* pDoc = GetDocument();

	MSG msg;
	msg.hwnd = *this;
	msg.message = WM_RBUTTONDOWN;
	msg.pt		= Vector3;

	pDoc->ReceiveMSG(msg);


	//float arr[] = 
	//{
	//		cos(0.2), -sin(0.2),	0,	0,
	//		sin(0.2),	cos(0.2),	0,	0,
	//		0,			0,			1,	0,
	//		0,			0,			0,	1	
	//};
	//Matrix<float> M(4, 4, arr);

	//pDoc->pGraph->Transform(M);
	//
	CView::OnRButtonDown(nFlags, Vector3);
}

void CRightView::OnMouseMove(UINT nFlags, CPoint Vector3)
{

	//char  str[10];
	//sprintf(str, "%d \n %d", Vector3.x, Vector3.y);
	//this->Invalidate(1);
	//GetDC()->TextOut(Vector3.x, Vector3.y, str);
	
	//this->InvalidateRect(Vector3.x-, Vector3.y, Vector3.x, Vector3.y;)
	

	//CView::OnMouseMove(nFlags, Vector3);
}

void CRightView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)  
{

	CCGAlgorithmDoc* pDoc = GetDocument();

	MSG msg;
	msg.hwnd = *this;
	msg.message = WM_CHAR;
	msg.lParam	= nChar;

	pDoc->ReceiveMSG(msg);

	CView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CRightView::OnEraseBkgnd(CDC* pDC)
{
	CBrush backBrush(RGB(100,100,100));
	CBrush *pOldBrush = pDC->SelectObject(&backBrush);
	
	CRect rect;
	pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top,  rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return true;
}
