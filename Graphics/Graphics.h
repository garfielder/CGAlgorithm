#pragma once
#include "../stdafx.h"
#include "../myhead.h"
#include "./Matrix.h"

namespace Drawing
{
	class Graphics
	{
		//state �ŵ���������ʵ��

	public:
		Graphics(CView* p):pView(p){};
		
		virtual ~Graphics(){};
		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
	
		 virtual void SetSubMode(SUBMODE S){subMode = S;};
		virtual void Draw();
		virtual void SetHintInfo(CString info){HintInfo = info;};
		virtual void DispHintInfo(CString info = "");

		virtual void Transform(Matrix<float>& M){};

		protected:
		CView*	pView;//ͼ�λ������ڵĴ���
		SUBMODE subMode;
		CString HintInfo;

		int     sState;


	};
};  // end of namespace scope