#include "stdafx.h"
#include "Line.h"
#include "../myhead.h"
#include "./Vector3.h"
namespace Drawing
{
	Line::Line(CView* p): Graphics(p)
	{
		pb.x=pb.y=pe.x=pe.y=0;
		sState = TWO;
		subMode = DDA;
	}

	void Line::Draw()
	{
		DispHintInfo();
		if(sState == TWO)  //仅当一条线的两个端点都接受到以后才画线
			switch (subMode)
			{
			case DDA:
				DDALine();break;
			case BRESHAM:
				BreshamLine();break;
			}

	}

	void Line::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)	
		{
		case WM_LBUTTONDOWN:
			
			if(sState == ONE)
			{
				pe = msg.pt;
				SetHintInfo("点击鼠标输入新直线的起点");
				 this->Draw();
				 sState = TWO;
	
			}
			else if(sState == TWO)
			{	
				pb = msg.pt;
				 SetHintInfo("请输入第二点");
				this->Draw();
				sState = ONE;
			//	DispHintInfo("点击鼠标输入新直线的起点");
				
			}
			
			break;
		case IDC_SUB_SELECT:
			this->SetSubMode(static_cast<enum SUBMODE>(msg.wParam));
			break;
		}
	
		
	};
		
	void Line::DDALine()
	{
		CDC* p = this->pView->GetDC();
		float x,y;
		float L=max(abs(pe.x-pb.x),abs(pe.y-pb.y));
		float deltax=(pe.x-pb.x)/L;
		float  deltay=(pe.y-pb.y)/L;
		x=(float)pb.x;
		y=(float)pb.y;

		for(int i=0;i<L;i++)
		{
			x+=deltax;
			y+=deltay;
			p->SetPixel(x,y, RENDERCOLOR);
		}
	};
	void Line::BreshamLine() const  //防止pe， pb在程序中被修改
	{
			CDC* pDC = this->pView->GetDC();

			//判断斜率
			float k;
			CPoint p1,p2;
			CPoint pbegin = this->pb;
			CPoint pend   =this->pe;

			if(pend.x<pbegin.x)	//保证dx>0
			{
				CPoint temp=pb;
				pbegin=pend;
				pend=temp;
			}

			k=(float)(pend.y-pbegin.y)/(pend.x-pbegin.x);

			if(k>=0&&k<=1)
			{
				p1=pbegin;
				p2=pend;
			}
			else if(k>1)		//交换
			{
				p1.x=pbegin.y;
				p1.y=pbegin.x;
				p2.x=pend.y;
				p2.y=pend.x;
			}
			else if(k>-1&&k<0)
			{
				p1.x=pbegin.x;
				p1.y=-pbegin.y;
				p2.x=pend.x;
				p2.y=-pend.y;

			}
			else
			{
				p1.x=pbegin.y;
				p1.y=-pbegin.x;
				p2.x=pend.y;
				p2.y=-pend.x;

			}


			if(p2.x<p1.x)	//保证dx>0
			{
				CPoint temp=p1;
				p1=p2;
				p2=temp;
			}



			int dx=p2.x-p1.x;
			int dy=p2.y-p1.y;


			CPoint p=p1;
			int e=-dx;

			for(int i=0;i<dx;i++)
			{
				e=e+2*dy;
				p.x++;
				if(e>0)
				{
					p.y++;
					e-=2*dx;
				}
				//	pDC->SetPixel(p,0);
				{
					if(k>=0&&k<=1)
					{
						pDC->SetPixel(p, RENDERCOLOR);
					}
					else if(k>1)		//交换
					{
						pDC->SetPixel(p.y,p.x, RENDERCOLOR);

					}
					else if(k>-1&&k<0)
					{
						pDC->SetPixel(p.x,-p.y, RENDERCOLOR);			
					}
					else
					{
						pDC->SetPixel(-p.y,p.x, RENDERCOLOR);

					}

				}
			}

	};

	void Line::Transform(Matrix<float>& M)
	{
		Vector3 p(pb.x, pb.y, 0);
		p.Transform(M);
		pb.x = p.x;
		pb.y = p.y;

		p.x = pe.x;
		p.y = pe.y;
		p.z = 0;

		p.Transform(M);
		pe.x = p.x;
		pe.y = p.y;

	}

	void Line::OnChar(UINT ch){};
	void Line::OnLeftBtnDown(CPoint p){};
	void Line::OnRightBtnDown(CPoint p){};
	void Line::OnCmdBtnDown(UINT ID){};
	//SUBMODE Line::GetCurState(){return 0;};
}