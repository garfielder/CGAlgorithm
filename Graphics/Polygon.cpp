#include "stdafx.h"
#include "Polygon.h"
#include "../myhead.h"
namespace Drawing
{
	Polygon::Polygon(CView* p): Graphics(p)
	{

		sState = INIT;
		subMode = SEED_FILL;
	}

	void Polygon::Draw()
	{
		DispHintInfo();
		
		CDC* pDC = pView->GetDC();

		//{ //这几句是搞测试的可以省略
		//	if(SurfaceTable.size()>1) 
		//	{
		//		//pDC->MoveTo( V(0,0).x, V(0,0).y );
		//		//pDC->LineTo( V(0,2).x, V(0,2).y );

		//		//AfxMessageBox("test V");

		//		//char temp[100];
		//		//sprintf(temp,"EdgeCnt(0) is %d", EdgeCnt(1));

		//		//AfxMessageBox(temp);
		//	}
		//				
		//}

		for(int i = 0; i< EdgeTable.size(); i++){
			int m = EdgeTable[i].start;
			int n = EdgeTable[i].end;

			//pDC->MoveTo(VertexTable[m].x, VertexTable[m].y);
			//pDC->LineTo(VertexTable[n].x, VertexTable[n].y);

			line(pDC,VertexTable[m].x, VertexTable[m].y, VertexTable[n].x, VertexTable[n].y);
		}

	}

	void Polygon::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)	
		{
		case WM_LBUTTONDOWN:
			OnLeftBtnDown(msg.pt);			
			break;
		case WM_RBUTTONDOWN:
			OnRightBtnDown(msg.pt);
			break;
        case IDC_SUB_SELECT:
			SetSubMode(static_cast<enum SUBMODE>(msg.wParam));
			break;
		}
	
		
	};
		

	
	void Polygon::OnChar(UINT ch){};
	void Polygon::OnLeftBtnDown(CPoint p)
	{
		if (sState == INIT)
		{
			VertexTable.push_back(Vector3(p.x, p.y, 0));  //z坐标默认为零
				
			int temp_a = VertexTable.size();
				
			SetHintInfo("点击鼠标输入下一点，点击右键闭合多边形");
				
			sState = ADDING;
		}
		else if(sState == ADDING)
		{
			VertexTable.push_back(Vector3(p.x, p.y, 0));

			int temp_a = VertexTable.size();
			
			int vTableTop = VertexTable.size() - 1;

			EdgeTable.push_back(Edge(vTableTop-1, vTableTop));

			int temp_b = EdgeTable.size();

			int eTableTop = EdgeTable.size() - 1;
			sElem.push_back(eTableTop);
			int temp_c = EdgeTable.size();
		}
		else if(sState == ENCLOSE)
		{
			 sState = INIT;
		}

	};
	void Polygon::OnRightBtnDown(CPoint p)
	{
		if(sState == ADDING)  //目前尚不提供检测异常，主要是仅含一个顶点的面和两个顶点的面
		{
			int stop = sElem.size() - 1;
			//1 etable.push(selem.top.end, selem.first.start)
			//	2 selem.push()
			//	3 stable.push(selem)
			//	selem.clear

			//闭合一个多边形

			int lastEdgeIndex = sElem[stop];  
			int firstEdgeIndex = sElem[0];
			
			int vStartIndex = EdgeTable[lastEdgeIndex].end;
			int vEndIndex	= EdgeTable[firstEdgeIndex].start;

			EdgeTable.push_back(Edge(vStartIndex, vEndIndex));
			sElem.push_back(EdgeTable.size() - 1);  //将前句新增的边索引放入sElem中		
			
			SurfaceTable.push_back(sElem);
			int tempc = SurfaceTable.size();
			int  temp_d = sElem.size();
				
			sElem.clear();
			

			sState = INIT;
			SetHintInfo("点击鼠标左键，开始输入一个新的多边形");
		}

	};
	void Polygon::OnCmdBtnDown(UINT ID)
	{

	};



	Vector3 &Polygon::V(int nPolyIndex,int nVertexIndex)
	{
		
		//ASSERT(0 <= -1);
		int temp_a = SurfaceTable.size()-1;
		ASSERT(nPolyIndex <= temp_a);   //不用temp_a的话可能有问题
		SurfaceElem surf = SurfaceTable[nPolyIndex];  //第 nPolyIndex个多边形
		
		//j=(j+n)%n;

		nVertexIndex = (nVertexIndex + surf.size()) % surf.size();

		int temp_b = surf.size() - 1;
		ASSERT(nVertexIndex<=surf.size()-1);
		int iEdgeIndex = surf[nVertexIndex];		//第 nPolyIndex个多边形中第nVertexIndex个边
													//的索引
			
		int iVertexIndex = EdgeTable[iEdgeIndex].start; //第 nVertexIndex条边的起点即定义为第nVertexIndex
														//个顶点，然后从顶点表中找出具体点

		return VertexTable[iVertexIndex];															//
	}


	void Polygon::Transform(Matrix<float>& M)
	{
		for (int i=0; i< VertexTable.size(); i++)
			VertexTable[i].Transform(M);
	}

	//SUBMODE Polygon::GetCurState(){return 0;};
}