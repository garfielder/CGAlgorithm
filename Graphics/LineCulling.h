
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"

namespace Drawing
{
	class LineCulling: public Graphics
	{

	public:
			LineCulling(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);

		//virtual void Transform();
	
		virtual void Draw();

		virtual void Cull();

		virtual void Transform(Matrix<float>& M){};

		inline float	IntToDouble(int n)		{ return (n - 400.0)/300.0;}
		inline int		DoubleToInt(float f)	{ return  (100.0 * f) + 200; }	
		
	protected:
		//--Æðµã£¬ÖÕµã-----------
		float (*f)(float, float);
		
		int xBoundLeft, xBoundRight;
		int zBound;

		int HUP[1024];
		int HLW[1024];
	};
};