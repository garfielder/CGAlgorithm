
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"

namespace Drawing
{
	class Circle: public Graphics
	{
	public:
		Circle(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
	//	virtual SUBMODE GetCurState();
		virtual void Transform(Matrix<float>& M){};
	
		virtual void Draw();
		virtual void DDACircle();
		virtual void BreshamCircle() const;
	protected:
		//--起点，终点-----------
		enum STATE{ONE, TWO} sState;  //指示当前已经拾取到了几个点，一个点仅有圆心，
										//两个即可计算半径
		CPoint pCen;  //圆心
		int iRadius;	//半径
		
		

	};
};