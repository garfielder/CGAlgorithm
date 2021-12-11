#include "stdafx.h"
#include "Clipping.h"
#include "../CGAlgorithmDoc.h"
#include "../RightView.h"
#include "stdlib.h"
#include <stack>

#include "../myhead.h"
#include "../Graphics/ClipPoly.h"
namespace Drawing
{
	ClipPoly::ClipPoly(CView* p): Graphics(p)
	{

		sState = INIT;
		subMode = SUTHURLAND;

		//初始化窗口
		xleft = 100;
		xright = 500;
		ybottom = 100;
		ytop	= 500;
	
		pPoly = new  Polygon(pView);
	
		CCGAlgorithmDoc* pDoc1 = ((CRightView*)pView)->GetDocument();
		CCGAlgorithmDoc* pDoc = (CCGAlgorithmDoc*)pDoc1;
		CView* pLeftView = pDoc->GetLeftView();

		pButton = new CButton;
		pButton->Create("裁减", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(10 , 210, 100, 240), pLeftView, IDC_BTN_FILL);
	}

	void ClipPoly::Draw()
	{
		DispHintInfo();
		CDC* pDC = pView->GetDC();

		line(pDC, xleft, ytop, xright, ytop);
		line(pDC, xleft, ytop, xleft, ybottom);
		line(pDC, xleft, ybottom, xright, ybottom);
		line(pDC, xright, ytop, xright, ybottom);
		
		pPoly->Draw();	

		if(sState == CLIPPING)
			BeginClipPoly();


	

	}

	void ClipPoly::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)
		{
		case WM_LBUTTONDOWN:
			pPoly->ReceiveMsg(msg);
			break;
		case WM_RBUTTONDOWN:
			pPoly->ReceiveMsg(msg);
			break;
		case IDC_BTN_FILL:
			OnCmdBtnDown(IDC_BTN_FILL);
			break;

		case IDC_SUB_SELECT:
			SetSubMode(static_cast<enum SUBMODE>(msg.wParam));

         }
	};



	void ClipPoly::OnChar(UINT ch){};
	void ClipPoly::OnLeftBtnDown(CPoint p){};
	void ClipPoly::OnRightBtnDown(CPoint p){};

	void ClipPoly::OnCmdBtnDown(UINT ID)
	{
		if (sState == INIT)
			sState = CLIPPING;
		else if (sState == CLIPPING)
		{
			sState = INIT;
		}
	};

	void ClipPoly::BeginClipPoly()
	{
		ASSERT(pPoly->GetSurfaceCnt() >= 1);
		InputList.clear();
		OutputList.clear();


		int nVertexCnt = pPoly->EdgeCnt(0); //取第0个多边形的顶点数
		for (int i=0; i< nVertexCnt; i++)   //生成inputlist
			InputList.push_back(pPoly->V(0, i));

		int n = 0 ;
		//int m = 1;
		Vector3 B = InputList[0];

		//逐边裁减
	for (int  tag = 0; tag< 4; tag++)
	{ 
		int input_size = InputList.size();
		for(int i= 0;  i< input_size; i++)
		{
			B = InputList[i]; 
			if(IsInWindow(B, static_cast<enum WinTag>(tag)))
				OutputList.push_back(B);

			Vector3 E = InputList[(i+1)%input_size];

			// if(IsCross(B, E)) //求交
			
			GetCrossPoint(B, E, static_cast<enum WinTag>(tag));

		
		}

		//InputList.clear();

		//int temp_c = InputList.size();
		//for(int i=0; i<OutputList.size(); i++)
		//InputList.push_back(OutputList[i]);
		InputList = OutputList;
	
		//int temp_c = InputList.size();
		 	OutputList.clear();
	}
	//上裁减
		//B = InputList[0];
		//for(int i= 0; i< nVertexCnt; i++)
		//{
		//	B = InputList[i]; 
		//	if(B.y > ybottom)
		//		OutputList.push_back(B);

		//	Vector3 E = InputList[i+1];

		//	if(E.y < ybottom && B.y > ybottom|| E.y > ybottom && B.y < ybottom) //求交
		//	{					
		//		float t = ((float)ybottom - (float)B.y)/((float)E.y - (float)B.y);
		//		int x = (float)B.x + ((float)E.x - (float)B.x)*t;	
		//		OutputList.push_back(Vector3(x, ybottom, 0));
		//	}

		//}
	for(int i=0; i<InputList.size(); i++)
		OutputList.push_back(InputList[i]);
		int a = OutputList.size();
			CDC* pDC = pView->GetDC();
			
			if (OutputList.size()>0)
			{	pDC->MoveTo(OutputList[0].x, OutputList[0].y);
				for(int i= 0; i< OutputList.size(); i++)
				{
					pDC->LineTo(OutputList[i].x, OutputList[i].y);
				}
			}
			pDC->LineTo(OutputList[0].x, OutputList[0].y);

			

	}

	bool ClipPoly::IsInWindow(Vector3 p, WinTag tag)
	{	
		switch(tag)
		{
		case LEFT:
			return p.x >= xleft;break;
		case RIGHT:
			return p.x <= xright;break;
		case BOTTOM:
			return p.y >= ybottom; break;
		case TOP:
			return	p.y <= ytop; break;

		}

	}

	bool ClipPoly::IsCross(Vector3 p1, Vector3 p2)
	{
		
		//return (IsInWindow(p1) && !IsInWindow(p2)) || (!IsInWindow(p1) && IsInWindow(p2));
		return true;

	}

	Vector3 ClipPoly::GetCrossPoint(Vector3 p1, Vector3 p2, WinTag edge)
	{
		//
		switch(edge)
		{
		case LEFT:
			if(p1.x > xleft && p2.x < xleft || p1.x < xleft && p2.x > xleft)
			{
				float t = ((float)xleft - (float)p1.x) / ((float)p2.x - (float)p1.x);
				int y = (float)p1.y + ((float)p2.y - (float)p1.y) * t;

				OutputList.push_back(Vector3(xleft, y, 0));
			}
			break;
		case RIGHT:
			if(p1.x > xright && p2.x < xright || p1.x < xright && p2.x > xright)
			{
				float t = ((float)xright - (float)p1.x) / ((float)p2.x - (float)p1.x);
				int y = (float)p1.y + ((float)p2.y - (float)p1.y) * t;

				OutputList.push_back(Vector3(xright, y, 0));
				return Vector3(xright, y, 0);

			}
			break;
		case BOTTOM:
			if(p1.y > ybottom && p2.y < ybottom ||p1.y < ybottom && p2.y > ybottom)
			{
				float t = ((float)ybottom - (float)p1.y) / ((float)p2.y - (float)p1.y);
				int x = (float)p1.x + ((float)p2.x - (float)p1.x) * t; 
				
				OutputList.push_back(Vector3(x, ybottom, 0));
				return Vector3(x, ybottom, 0);				
			}
			break;
		case TOP: 
			if(p1.y > ytop && p2.y < ytop ||p1.y < ytop && p2.y > ytop)
			{
				float t = ((float)ytop - (float)p1.y) / ((float)p2.y - (float)p1.y);
				int x = (float)p1.x + ((float)p2.x - (float)p1.x) * t; 
				
				OutputList.push_back(Vector3(x, ytop, 0));
				return Vector3(x, ytop, 0);
	
			};
			break;

		}

	
		return Vector3(0,0,0);
	}

	CodeStruct  ClipPoly::CodePoint(CPoint p)
	{
		CodeStruct code;


	 	if(p.x >= xleft)		code.xl = 0;	else code.xl = 1;
		if(p.x <= xright)		code.xr = 0;	else code.xr = 1;
		if(p.y >= ybottom)		code.yb = 0;	else code.yb = 1;
		if(p.y <= ytop)			code.yt = 0;	else code.yt = 1;
		
		return code; 
	}

	
	void ClipPoly::Transform(Matrix<float>& M)
	{
		pPoly->Transform(M);
	}



	ClipPoly::~ClipPoly()
	{
	//	pButton->DestroyWindow();

	
		delete pButton;
		delete pPoly;

	};

}