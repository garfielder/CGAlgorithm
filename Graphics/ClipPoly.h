
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"
#include "Polygon.h"
#include "line.h"


namespace Drawing
{


	class ClipPoly: public Graphics
	{
	public:
		enum STATE{INIT, CLIPPING, LINNING} sState;  // 当前状态
		enum WinTag{LEFT, RIGHT, BOTTOM, TOP};



	public:
		ClipPoly(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		//	virtual SUBMODE GetCurState();

		virtual void Draw();
		virtual void BeginClipPoly();
	protected:
		virtual CodeStruct CodePoint(CPoint p);
		
		bool	IsInWindow(Vector3 p, WinTag tag);
		bool	IsCross(Vector3 p1, Vector3 p2);
		Vector3	GetCrossPoint(Vector3 p1, Vector3 p2, WinTag tag);

		virtual void Transform(Matrix<float>& M);

		~ClipPoly();

	protected:
		//--起点，终点-----------

		CButton* pButton;  // 注意不要把CButton定义成CButton button,而用指针*pButton,否则
							//销毁对象会出问题的
	
		
		int xleft,xright, ytop, ybottom;


		Polygon* pPoly;

		vector<Vector3> InputList;
		vector<Vector3> OutputList;

        
	};
};