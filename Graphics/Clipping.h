
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"


#include "Polygon.h"
#include "line.h"


namespace Drawing
{


	class Clip: public Graphics
	{
	public:
		enum STATE{INIT, CLIPPING, LINNING} sState;  // 当前状态




	public:
		Clip(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		//	virtual SUBMODE GetCurState();

		virtual void Draw();
		virtual void ClipLine();

		virtual void Transform(Matrix<float>& M);
	protected:
		virtual CodeStruct CodePoint(CPoint p);


		

		~Clip();

	protected:
		//--起点，终点-----------

		CButton* pButton;  // 注意不要把CButton定义成CButton button,而用指针*pButton,否则
							//销毁对象会出问题的
	
		
		int xleft,xright, ytop, ybottom;

		CPoint pb, pe;
		CPoint newpb, newpe; //裁减后的

		Polygon* pPoly;
		Line*	pLine;
        
	};
};