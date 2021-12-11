#include "stdafx.h"
#include "LineCulling.h"
#include "../myhead.h"
namespace Drawing
{
	LineCulling::LineCulling(CView* p): Graphics(p)
	{
		f = ::fun;
		xBoundLeft = 0;
		xBoundRight = 50;

	}

	void LineCulling::Draw()
	{
		DispHintInfo();

		CDC* pDC = pView->GetDC();

		Cull();

	}

	void LineCulling::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)	
		{

		case IDC_SUB_SELECT:
			this->SetSubMode(static_cast<enum SUBMODE>(msg.wParam));
			break;
		}
	
		
	};
		
	void LineCulling::Cull()
	{
		CDC* pDC = pView->GetDC();
			
		//Init
		for (int i = 0; i < 1024; i++)
		{
			HUP[i] = 0;
			HLW[i] = 1024;
		}

		float x, y, z, deltax, deltaz;
		
		x = -1.0; z = -1.0; deltaz = 0.05; deltax = 0.01;
	
		for (z = -2.0; z < 2.0; z += deltaz)
		{
			for (x = -2.0; x < 4.0; x += deltax)
			{
				y = f(x, z);
				
				int Y = DoubleToInt(y);
				int X = DoubleToInt(x);
				if( Y > HUP[X] || Y < HLW[X])
					pDC->SetPixel(X, Y, RENDERCOLOR);
			}
		}

	}

	void LineCulling::OnChar(UINT ch){};
	void LineCulling::OnLeftBtnDown(CPoint p){};
	void LineCulling::OnRightBtnDown(CPoint p){};
	void LineCulling::OnCmdBtnDown(UINT ID){};
	//SUBMODE LineCulling::GetCurState(){return 0;};
}