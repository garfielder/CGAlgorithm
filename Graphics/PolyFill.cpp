#include "stdafx.h"
#include "PolyFill.h"
#include "../CGAlgorithmDoc.h"
#include "../RightView.h"
#include "stdlib.h"
#include <stack>

#include "../myhead.h"
namespace Drawing
{
	PolyFill::PolyFill(CView* p): Graphics(p)
	{

		sState = POLY;
		subMode = SEED_FILL;
		pPoly = new  Polygon(pView);
		
		CCGAlgorithmDoc* pDoc1 = ((CRightView*)pView)->GetDocument();
		CCGAlgorithmDoc* pDoc = (CCGAlgorithmDoc*)pDoc1;
		CView* pLeftView = pDoc->GetLeftView();
		
		pButton = new CButton;
		pButton->Create("填充", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(10 , 210, 100, 240), pLeftView, IDC_BTN_FILL);
	}

	void PolyFill::Draw()
	{
		DispHintInfo();
		CDC* pDC = pView->GetDC();

		if(sState == FILLED)
		{	
			pPoly->Draw();
			switch(subMode)
			{
			case SEED_FILL:
				SeedFill(pDC, pSeed.x, pSeed.y);break;
			case BETTER_SEED_FILL:
				SeedFillOptimized(pDC, pSeed.x, pSeed.y);
				break;
			case SCAN_LINE:
				ScanLine();
			}
		}
		else
		{

			pPoly->Draw();
		} 



	}

	void PolyFill::ReceiveMsg(MSG& msg)
	{
		switch(msg.message)
		{
		case IDC_BTN_FILL:
			OnCmdBtnDown(msg.message);
			break;
		case WM_LBUTTONDOWN:
			if(sState == WTFORSEED || sState == FILLED)
				OnLeftBtnDown(msg.pt);
			else
				pPoly->ReceiveMsg(msg);
			break;
		case IDC_SUB_SELECT:
			this->SetSubMode(static_cast<enum SUBMODE>(msg.wParam));
			break;
		default: 
				pPoly->ReceiveMsg(msg);
		}
		

	};



	void PolyFill::OnChar(UINT ch){};
	void PolyFill::OnLeftBtnDown(CPoint p)
	{
		if(sState == WTFORSEED)
		{ 
			sState = FILLED;
			pSeed = p;
			SetHintInfo("点击左试图返回填充模式");
		}

     };

	void PolyFill::OnRightBtnDown(CPoint p)
	{

	}
	void PolyFill::OnCmdBtnDown(UINT ID)
	{
		if (subMode == SCAN_LINE)
		{
			if(sState == POLY)
				sState = FILLED;
			else if (sState == FILLED)
			{
				sState = POLY;
			}
			return;
		}

		if (ID == IDC_BTN_FILL)
		{
			if(sState == POLY)
			{
				sState = WTFORSEED;

				pButton->SetWindowText("返回");
				SetHintInfo("请用点击鼠标左键拾取种子点");
				pView->UpdateWindow();
			}
			else if(sState == FILLED)
			{
				sState = POLY;
				pButton->SetWindowText("填充");
			
			}
		}

	};


	//Drawing function 
	void PolyFill::FillArea()
	{
		pView->GetDC()->TextOut(100,100,"在裁减模式");
		
	}

	void PolyFill::SeedFill(CDC* pDC, int x, int y)
	{  
		static int  iFillCnt;
		iFillCnt++;

		if(pDC->GetPixel(x,y) != RENDERCOLOR && iFillCnt < 12000)
		{
			pDC->SetPixel(x,y, RENDERCOLOR);
			SeedFill(pDC,x,y+1);
			SeedFill(pDC,x,y-1);
			SeedFill(pDC,x-1,y);
			SeedFill(pDC,x+1,y);
		}
		if (iFillCnt >=12000)
		{
			AfxMessageBox("种子填充算法中函数递归次数太多，堆栈溢出，换用其他填充算法可以解决问题");
			exit(0);
		}
	
		

	};
	
	void PolyFill::SeedFillOptimized(CDC* pDC, int x, int y)
	{
		stack<CPoint> s;
		CPoint p(x,y),temp;
	
		//AfxMessageBox("in optimized");

		s.push(p);

		long iThreshold=0;//控制循环次数，以防死循环
		while(!s.empty())
		{
			iThreshold++;
			if(iThreshold>0x40000)
			{
				AfxMessageBox("出现死循环，种子超出边界？");
				exit(0);
			}
			p=s.top();
			s.pop();

			if(pDC->GetPixel(p) != RENDERCOLOR)
			{
				pDC->SetPixel(p,RENDERCOLOR);
				temp.x=p.x;temp.y=p.y+1;
				s.push(temp);
				temp.x=p.x;temp.y=p.y-1;
				s.push(temp);

				temp.x=p.x+1;temp.y=p.y;
				s.push(temp);
				temp.x=p.x-1;temp.y=p.y;
				s.push(temp);
			}
		}

	}


	PolyFill::~PolyFill()
	{
		delete pButton;
		delete pPoly;
	};




	void PolyFill::ScanLine()
	{

		CDC* pDC = pView->GetDC();
		EdgeElem *pTemp;

		this->CreateET();

		for(int y=ytop;y<=ybottom;y++)  //开始填充
		{
			this->MergeList(ET[y],AET,pTemp);
			AET = pTemp;

			//--利用xstart，xend，以及finish实现扫描线上点的两两组合
			int xstart,xend;
			bool finish=false;  
			while(pTemp)
			{
				if(!finish)
				{
					xstart=pTemp->xmin;
					finish=!finish;
				}
				else
				{
					xend=pTemp->xmin;

					pDC->MoveTo(xstart,y);
					pDC->LineTo(xend,y);

					line(pDC, xstart, y, xend, y);
					finish=!finish;
				}
				pTemp = pTemp->next;
			}


			pTemp = AET;
			while(pTemp!=NULL)
			{


				if(y >= (int)(pTemp->ymax))
				{
					this->Remove(AET,pTemp);
					continue; //必不可少
				}
				else				
				{
					pTemp->xmin += pTemp->delta;
					if(pTemp)
						pTemp = pTemp->next;
				}
			}
			SortList(AET);
		}
	}
	bool PolyFill::CreateET()
	{
		//-----初始化边表ET与活动边表AET为空----
		for(int i=0;i<768;i++)
		{
			ET[i] = NULL;
		}
		AET=NULL;

		//----寻找y的最大值与最小值-----
		int eIndex=0;

		Vector3 temp = pPoly->V(eIndex,0);  //返回局部变量注意
		
		ytop = ybottom = temp.y;
		for(int i=0;i < pPoly->EdgeCnt(eIndex); i++)
		{

			if( pPoly->V(eIndex,i).y < ytop) ytop = pPoly->V(eIndex,i).y ;
			if( pPoly->V(eIndex,i).y > ybottom) ybottom = pPoly->V(eIndex,i).y;
		}


		//---根据第eIndex个多边形中的所有边建立边表-----
		for(int i = 0;i < pPoly->EdgeCnt(eIndex);i++)
		{
			//---yi当前边的y值，yiPre前一条边的y值，（不要直接用V(eIndex, i).y，因为他们是函数中的局部变量，易出问题） 
			int yi = pPoly->V(eIndex, i).y,		xi=pPoly->V(eIndex, i).x;
			int yiPre = pPoly->V(eIndex, i-1).y,	xiPre = pPoly->V(eIndex, i-1).x;
			int yiNext = pPoly->V(eIndex, i+1).y,	xiNext = pPoly->V(eIndex, i+1).x;


			EdgeElem  temp,*p;
			temp.next = NULL;
			p = &temp;

			//----特殊情况：平行边不考虑
			if(yi == yiPre)
				continue;

			//--产生多边形信息单元---
			p=new EdgeElem;
			p->xmin = yi<yiPre?xi:xiPre;
			p->ymax = max(yi,yiPre);
			float a=(float)xi -  (float)xiPre; //注意，float一个都不能少
			float  b=(float)yi - (float)yiPre;
			//p->delta = ( V(eIndex,i).x -  V(eIndex,i-1).x) / ( V(eIndex,i).y - V(eIndex,i-1).y);
			p->delta = a/b;
			p->next = NULL;



			if(yi>yiPre)
			{
				if(yi<yiNext)
					p->ymax-- ;
			}else if(yi<yiPre)
			{
				if(yi>yiNext)

				{
					yi++;
					p->xmin += p->delta;
				}
			}

		//if(yi>yiPre&&yi<yiNext)
			//	p->ymax--;
			//else if(yi<yiPre&&yi>yiNext)
			//{
			//	yi++;
			//	p->xmin += p->delta;
			//}

			//ET[min(yiPre,yi)] = temp.next;
			if(ET[min(yiPre,yi)] ==	NULL)
				ET[min(yiPre,yi)] = p;
			else 
			{
				p->next = ET[min(yiPre,yi)];
				ET[min(yiPre,yi)] = p;
			}
		}
		//对新建立的边表进行排序
		for(int y=ytop;y<=ybottom;y++)
			this->SortList(ET[y]);
		return true; 
	}
	void  PolyFill::MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL)  //保证合并后按xmin递增排序
	{	
		EdgeElem temp,*k;
		k = &temp;

		while(p&&q)
		{
			if(p->xmin < q->xmin)
			{
				k->next = p;
				p = p->next;
			}
			else 
			{
				k->next =  q;
				q=q->next;
			}
			k = k->next;
		}
		if(p) 
			k->next = p;
		else 
			k->next = q;

		pL=temp.next;

	}
	void PolyFill::SortList(EdgeElem * p)
	{
		//use select sorting
		EdgeElem *q,*pRec; //p points to the leftmost element of an array left to sorted
		// q Vector3 to the current element being checked 
		//prec Vector3 to the min element checked by q
		EdgeElem temp;	

		if(p==NULL) return ;

		while(p->next)
		{
			q =  p->next;
			pRec=p;
			while(q != NULL)
			{
				if(q->xmin < pRec->xmin) 
					pRec = q;
				q=q->next;
			}


			this->exchange(p->xmin,pRec->xmin);
			this->exchange(p->delta,pRec->delta);
			this->exchange(p->ymax,pRec->ymax);
			p=p->next;

		}

		//EdgeElem * pPre, *q, *pCur, *pNext, *pHead,head;	//记录用于和第一个元素交换的节点指针 
		//if(!p || !p->next) return ;  //空链表或单元素链表不用排序
		//
		//head.next = p;
		//pHead = &head;

		//while(p->next)
		//{
		//	pPre = NULL;
		//	pCur = p;
		//	for( q = p; q->next; q = q->next)
		//		if(q->next->xmin < pCur->xmin)
		//		{
		//			pPre = q;
		//			pCur = q->next;
		//		}
	 //    			
		//	if(!pPre) //不用交换
		//	{
		//		p = p->next; 
		//		pHead = pHead->next;
		//	}
		//	else 
		//	{
		//		pNext = pCur->next;
		//
		//		if(pPre == p)
		//		{
		//			pPre->next = pNext;
		//			pCur->next = pPre;
		//		}else
		//		{
		//			pCur->next = p->next;
		//			pPre->next = p;
		//			p->next = pNext;
		//		}	
		//	
		//		pHead->next = pCur;
		//		pHead= pHead->next ;

		//		p = pCur->next;
		//	}
		//}
		//p= head.next;
	}
	void PolyFill::Remove(EdgeElem* &pHead,EdgeElem* &q)
	{

		if(pHead==q)
		{	
			pHead = pHead->next;
			delete q;
			q = pHead;

		}
		else		
		{
			EdgeElem* p=pHead;
			while(p->next!=q&&p->next!=NULL)
			{
				p=p->next;
			}
			if(p->next)
			{
				p->next=q->next;
				delete q;
				q = p->next;
			}
		}


	}




	//SUBMODE PolyFill::GetCurState(){return 0;};
}