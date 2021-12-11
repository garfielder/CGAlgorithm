
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"

namespace Drawing
{
	class Line: public Graphics
	{
	public:
				enum STATE{ONE = 1, TWO = 2} sState;  //ָʾ��ǰ�Ѿ�ʰȡ���˼�����
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
		//--��㣬�յ�-----------

		CPoint pb, pe; 
		
		

	};
};