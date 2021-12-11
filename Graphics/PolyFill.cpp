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
		pButton->Create("���", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
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
			SetHintInfo("�������ͼ�������ģʽ");
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

				pButton->SetWindowText("����");
				SetHintInfo("���õ��������ʰȡ���ӵ�");
				pView->UpdateWindow();
			}
			else if(sState == FILLED)
			{
				sState = POLY;
				pButton->SetWindowText("���");
			
			}
		}

	};


	//Drawing function 
	void PolyFill::FillArea()
	{
		pView->GetDC()->TextOut(100,100,"�ڲü�ģʽ");
		
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
			AfxMessageBox("��������㷨�к����ݹ����̫�࣬��ջ�����������������㷨���Խ������");
			exit(0);
		}
	
		

	};
	
	void PolyFill::SeedFillOptimized(CDC* pDC, int x, int y)
	{
		stack<CPoint> s;
		CPoint p(x,y),temp;
	
		//AfxMessageBox("in optimized");

		s.push(p);

		long iThreshold=0;//����ѭ���������Է���ѭ��
		while(!s.empty())
		{
			iThreshold++;
			if(iThreshold>0x40000)
			{
				AfxMessageBox("������ѭ�������ӳ����߽磿");
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

		for(int y=ytop;y<=ybottom;y++)  //��ʼ���
		{
			this->MergeList(ET[y],AET,pTemp);
			AET = pTemp;

			//--����xstart��xend���Լ�finishʵ��ɨ�����ϵ���������
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
					continue; //�ز�����
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
		//-----��ʼ���߱�ET���߱�AETΪ��----
		for(int i=0;i<768;i++)
		{
			ET[i] = NULL;
		}
		AET=NULL;

		//----Ѱ��y�����ֵ����Сֵ-----
		int eIndex=0;

		Vector3 temp = pPoly->V(eIndex,0);  //���ؾֲ�����ע��
		
		ytop = ybottom = temp.y;
		for(int i=0;i < pPoly->EdgeCnt(eIndex); i++)
		{

			if( pPoly->V(eIndex,i).y < ytop) ytop = pPoly->V(eIndex,i).y ;
			if( pPoly->V(eIndex,i).y > ybottom) ybottom = pPoly->V(eIndex,i).y;
		}


		//---���ݵ�eIndex��������е����б߽����߱�-----
		for(int i = 0;i < pPoly->EdgeCnt(eIndex);i++)
		{
			//---yi��ǰ�ߵ�yֵ��yiPreǰһ���ߵ�yֵ������Ҫֱ����V(eIndex, i).y����Ϊ�����Ǻ����еľֲ��������׳����⣩ 
			int yi = pPoly->V(eIndex, i).y,		xi=pPoly->V(eIndex, i).x;
			int yiPre = pPoly->V(eIndex, i-1).y,	xiPre = pPoly->V(eIndex, i-1).x;
			int yiNext = pPoly->V(eIndex, i+1).y,	xiNext = pPoly->V(eIndex, i+1).x;


			EdgeElem  temp,*p;
			temp.next = NULL;
			p = &temp;

			//----���������ƽ�б߲�����
			if(yi == yiPre)
				continue;

			//--�����������Ϣ��Ԫ---
			p=new EdgeElem;
			p->xmin = yi<yiPre?xi:xiPre;
			p->ymax = max(yi,yiPre);
			float a=(float)xi -  (float)xiPre; //ע�⣬floatһ����������
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
		//���½����ı߱��������
		for(int y=ytop;y<=ybottom;y++)
			this->SortList(ET[y]);
		return true; 
	}
	void  PolyFill::MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL)  //��֤�ϲ���xmin��������
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

		//EdgeElem * pPre, *q, *pCur, *pNext, *pHead,head;	//��¼���ں͵�һ��Ԫ�ؽ����Ľڵ�ָ�� 
		//if(!p || !p->next) return ;  //�������Ԫ������������
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
		//	if(!pPre) //���ý���
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