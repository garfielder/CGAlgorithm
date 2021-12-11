
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"

namespace Drawing
{
	class Line: public Graphics
	{
	public:
				enum STATE{ONE = 1, TWO = 2} sState;  //指示当前已经拾取到了几个点
	public:
		Line(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		virtual STATE GetCurState(){return sState;};
	
		virtual void Draw();
		virtual void DDALine();
		virtual void BreshamLine() const;

		CPoint GetPe(){return pe;};
		CPoint GetPb(){return pb;}
		
		virtual void Transform(Matrix<float>& M);

		
		
	protected:
		//--起点，终点-----------

		CPoint pb, pe; 
		
		

	};
};