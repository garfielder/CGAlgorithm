// CGAlgorithmView.cpp : CCGAlgorithmView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCGAlgorithmView ����/����

CCGAlgorithmView::CCGAlgorithmView()
{
	// TODO: �ڴ˴���ӹ������

}

CCGAlgorithmView::~CCGAlgorithmView()
{
}

BOOL CCGAlgorithmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CCGAlgorithmView ����

void CCGAlgorithmView::OnDraw(CDC* /*pDC*/)
{
	CCGAlgorithmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCGAlgorithmView ��ӡ

BOOL CCGAlgorithmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCGAlgorithmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CCGAlgorithmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CCGAlgorithmView ���

#ifdef _DEBUG
void CCGAlgorithmView::AssertValid() const
{
	CView::AssertValid();
}

void CCGAlgorithmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGAlgorithmDoc* CCGAlgorithmView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgorithmDoc)));
	return (CCGAlgorithmDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGAlgorithmView ��Ϣ�������
