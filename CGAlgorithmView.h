// CGAlgorithmView.h : CCGAlgorithmView ��Ľӿ�
//


#pragma once


class CCGAlgorithmView : public CView
{
protected: // �������л�����
	CCGAlgorithmView();
	DECLARE_DYNCREATE(CCGAlgorithmView)

// ����
public:
	CCGAlgorithmDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCGAlgorithmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CGAlgorithmView.cpp �ĵ��԰汾
inline CCGAlgorithmDoc* CCGAlgorithmView::GetDocument() const
   { return reinterpret_cast<CCGAlgorithmDoc*>(m_pDocument); }
#endif

