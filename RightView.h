#pragma once

#include "CGAlgorithmDoc.h"
// CRightView 视图


class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制此视图
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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);  //注意只有当活动视图是右视图时才有作用，
																	//本来这个函数应该放到Doc类中的
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

//#ifndef _DEBUG  // CGAlgorithmView.cpp 的调试版本
//inline CCGAlgorithmDoc* CCGAlgorithmView::GetDocument() const
//   { return reinterpret_cast<CCGAlgorithmDoc*>(m_pDocument); }
//#endif

