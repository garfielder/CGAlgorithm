#include "stdafx.h"
#include "Circle.h"
#include "../myhead.h"
namespace Drawing
{
	Circle::Circle(CView* p): Graphics(p)  //��ʼ��Բ�ģ��뾶
	{
		this->iRadius=0;
		this->sState = TWO;
		this->pCen.x=pCen.y=0;
	}

	void Circle::Draw()
	{
		DispHintInfo();
		if(sState == TWO)  //����һ���ߵ������˵㶼���ܵ��Ժ�Ż���
			switch (subMode)
			{
			case DDA:
				DDACircle();break;
			case BRESHAM:
				BreshamCircle();break;
			}

	}

	void Circle::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)	
		{
		case WM_LBUTTONDOWN:
			
			if(sState == ONE)
			{
				CPoint p = msg.pt;
				iRadius=sqrt((float)(p.y-pCen.y)*(p.y-pCen.y)+(p.x-pCen.x)*(p.x-pCen.x));
				SetHintInfo("�����������µ�Բ��");
				this->Draw();
				sState = TWO;
	
			}
			else if(sState == TWO)
			{	


				pCen = msg.pt;
				SetHintInfo("������Բ����һ��");
				this->Draw();
				
				sState = ONE;
			//	DispHintInfo("������������ֱ�ߵ����");
				
			}
			
			break;
		case IDC_SUB_SELECT:
			this->SetSubMode(static_cast<enum SUBMODE>(msg.wParam));
			break;
		}
	
		
	};
		
	void Circle::DDACircle()
	{
		//CDC* p = this->pView->GetDC();
		
		DispHintInfo("�Բ��𣬸��㷨δʵ��");

	};
	void Circle::BreshamCircle() const
	{
		CDC* pDC = this->pView->GetDC();
		int x0=pCen.x;
		int y0=pCen.y;

		int x=0,y=iRadius;
		int d=3-2*iRadius;

		while(x<y)
		{
			{
				pDC->SetPixel(x0+x,y0+y, RENDERCOLOR);
				pDC->SetPixel(x0+y,y0+x, RENDERCOLOR);
				pDC->SetPixel(x0-x,y0+y, RENDERCOLOR);
				pDC->SetPixel(x0+y,y0-x, RENDERCOLOR);
				pDC->SetPixel(x0+x,y0-y, RENDERCOLOR);
				pDC->SetPixel(x0-y,y0+x, RENDERCOLOR);
				pDC->SetPixel(x0-x,y0-y, RENDERCOLOR);
				pDC->SetPixel(x0-y,y0-x, RENDERCOLOR);
			}

			if(d<0)
				d+=4*x+6;
			else
			{
				d+=4*(x-y)+10;
				y--;
			}
			x++;
		}

		//--�������������ĸ���

		int delta = int((float)iRadius * (float)sqrt(2.0)/2);
		pDC->SetPixel(pCen.x + delta, pCen.y +delta, RENDERCOLOR);
		pDC->SetPixel(pCen.x - delta, pCen.y +delta, RENDERCOLOR);
		pDC->SetPixel(pCen.x + delta, pCen.y -delta, RENDERCOLOR);
		pDC->SetPixel(pCen.x - delta, pCen.y -delta, RENDERCOLOR);
	
		
	}
	void Circle::OnChar(UINT ch){};
	void Circle::OnLeftBtnDown(CPoint p){};
	void Circle::OnRightBtnDown(CPoint p){};
	void Circle::OnCmdBtnDown(UINT ID){};
	//SUBMODE Circle::GetCurState(){return 0;};
}