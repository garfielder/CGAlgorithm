#include "stdafx.h"
#include "Clipping.h"
#include "../CGAlgorithmDoc.h"
#include "../RightView.h"
#include "stdlib.h"
#include <stack>

#include "../myhead.h"
namespace Drawing
{
	Clip::Clip(CView* p): Graphics(p)
	{

		sState = INIT;
		subMode = SUTHURLAND;

		//初始化窗口
		xleft = 100;
		xright = 500;
		ybottom = 100;
		ytop	= 500;
	
		pPoly = new  Polygon(pView);
		pLine = new Line(pView);

		CCGAlgorithmDoc* pDoc1 = ((CRightView*)pView)->GetDocument();
		CCGAlgorithmDoc* pDoc = (CCGAlgorithmDoc*)pDoc1;
		CView* pLeftView = pDoc->GetLeftView();

		pButton = new CButton;
		pButton->Create("裁减", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(10 , 210, 100, 240), pLeftView, IDC_BTN_FILL);
	}

	void Clip::Draw()
	{
		DispHintInfo();
		CDC* pDC = pView->GetDC();

		line(pDC, xleft, ytop, xright, ytop);
		line(pDC, xleft, ytop, xleft, ybottom);
		line(pDC, xleft, ybottom, xright, ybottom);
		line(pDC, xright, ytop, xright, ybottom);
		
		pLine->Draw();	

		if(sState == CLIPPING)
			ClipLine();
	}

	void Clip::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)
		{
		case WM_LBUTTONDOWN:
			pLine->ReceiveMsg(msg);
		
			break;
		case IDC_BTN_FILL:
			OnCmdBtnDown(IDC_BTN_FILL);
			break;

		case IDC_SUB_SELECT:
			SetSubMode(static_cast<enum SUBMODE>(msg.wParam));

         }
	};



	void Clip::OnChar(UINT ch){};
	void Clip::OnLeftBtnDown(CPoint p){};
	void Clip::OnRightBtnDown(CPoint p){};

	void Clip::OnCmdBtnDown(UINT ID)
	{
		if (sState == INIT)
			sState = CLIPPING;
		else if (sState == CLIPPING)
		{
			sState = INIT;
		}
	};

	void Clip::ClipLine()
	{

		CodeStruct pb_code, pe_code;
		
	

		int a = pLine->GetCurState();
		 if(pLine->GetCurState() != 2)  return;//保证裁减时已经拾取到了两个点
		
		pb = pLine->GetPb();
		pe = pLine->GetPe();

//	AfxMessageBox("clipline");
		//初始化，定点编码
		pb_code = CodePoint(pb);
		pe_code = CodePoint(pe);

		//左边比较
		
		if (pb_code.xl == 1 && pe_code.xl == 1) return; //同在xleft左边，拒绝
		else if(pb_code.xl == 1 && pe_code.xl == 0) 
		{//分段
			float t = ((float)xleft - (float)pb.x)/((float)pe.x - (float)pb.x);
			
			int y = (float)pb.y + ((float)pe.y - (float)pb.y)*t;	
			
			pb.x = xleft;
			pb.y = y;
			pb_code = CodePoint(pb);
		}
		else if(pb_code.xl == 0 && pe_code.xl == 1) 
		{//分段
			float t = ((float)xleft - (float)pb.x)/((float)pe.x - (float)pb.x);

			int y = (float)pb.y + ((float)pe.y - (float)pb.y)*t;	

			pe.x = xleft;
			pe.y = y;
			pe_code = CodePoint(pe);
		}

		//右边比较
		if (pb_code.xr == 1 && pe_code.xr == 1) return; //同在xright右边，拒绝
		else if(pb_code.xr == 1 && pe_code.xr == 0) 
		{//分段
			float t = ((float)xright- (float)pb.x)/((float)pe.x - (float)pb.x);

			int y = (float)pb.y + ((float)pe.y - (float)pb.y)*t;	

			pb.x = xright;
			pb.y = y;
			pb_code = CodePoint(pb);
		}
		else if(pb_code.xr == 0 && pe_code.xr == 1) 
		{//分段
			float t = ((float)xright - (float)pb.x)/((float)pe.x - (float)pb.x);

			int y = (float)pb.y + ((float)pe.y - (float)pb.y)*t;	

			pe.x = xright;
			pe.y = y;
			pe_code = CodePoint(pe);
		}

		//code

		//bottom 比较
		if (pb_code.yb == 1 && pe_code.yb == 1) return; //同在ybottom上边，拒绝
		else if(pb_code.yb == 1 && pe_code.yb == 0) 
		{//分段
			float t = ((float)ybottom - (float)pb.y)/((float)pe.y - (float)pb.y);

			int x = (float)pb.x + ((float)pe.x - (float)pb.x)*t;	

			pb.x = x;
			pb.y = ybottom;
			pb_code = CodePoint(pb);
		}
		else if(pb_code.yb == 0 && pe_code.yb == 1) 
		{//分段
			float t = ((float)ybottom - (float)pb.y)/((float)pe.y - (float)pb.y);

			int x = (float)pb.x + ((float)pe.x - (float)pb.x)*t;	

			pe.x = x;
			pe.y = ybottom;
			pe_code = CodePoint(pe);
		}


		//top比较
		if (pb_code.yt == 1 && pe_code.yt == 1) return; //同在ybottom上边，拒绝
		else if(pb_code.yt == 1 && pe_code.yt == 0) 
		{//分段
			float t = ((float)ytop - (float)pb.y)/((float)pe.y - (float)pb.y);

			int x = (float)pb.x + ((float)pe.x - (float)pb.x)*t;	

			pb.x = x;
			pb.y = ytop;
			pb_code = CodePoint(pb);
		}
		else if(pb_code.yt == 0 && pe_code.yt == 1) 
		{//分段
			float t = ((float)ytop- (float)pb.y)/((float)pe.y - (float)pb.y);

			int x = (float)pb.x + ((float)pe.x - (float)pb.x)*t;	

			pe.x = x;
			pe.y = ytop;
			pe_code = CodePoint(pe);
		}



		
			CDC* pDC = pView->GetDC();

			line(pDC, pb.x, pb.y, pe.x, pe.y, 0x000000ff);

	}

	CodeStruct  Clip::CodePoint(CPoint p)
	{
		CodeStruct code;


	 	if(p.x >= xleft)		code.xl = 0;	else code.xl = 1;
		if(p.x <= xright)		code.xr = 0;	else code.xr = 1;
		if(p.y >= ybottom)		code.yb = 0;	else code.yb = 1;
		if(p.y <= ytop)			code.yt = 0;	else code.yt = 1;
		
		return code; 
	}

	//Drawing function 


	void Clip::Transform(Matrix<float>& M)
	{
		
	}
	Clip::~Clip()
	{
	//	pButton->DestroyWindow();

	
		delete pButton;
		delete pPoly;
		delete pLine;
	};
}