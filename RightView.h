#pragma once

#include "CGAlgorithmDoc.h"
// CRightView ��ͼ


class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRightView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
	CCGAlgorithmDoc* GetDocument() const;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Vector3);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint Vector3);
	afx_msg void OnMouseMove(UINT nFlags, CPoint Vector3);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);  //ע��ֻ�е����ͼ������ͼʱ�������ã�
																	//�����������Ӧ�÷ŵ�Doc���е�
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

//#ifndef _DEBUG  // CGAlgorithmView.cpp �ĵ��԰汾
//inline CCGAlgorithmDoc* CCGAlgorithmView::GetDocument() const
//   { return reinterpret_cast<CCGAlgorithmDoc*>(m_pDocument); }
//#endif

