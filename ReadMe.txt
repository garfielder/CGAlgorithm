================================================================================
    MICROSOFT ������⣺ CGAlgorithm ��Ŀ����
===============================================================================

Ӧ�ó�������Ϊ�������˴� CGAlgorithm Ӧ�ó��򡣴�Ӧ�ó���
����������ʹ�� Microsoft ������Ļ���֪ʶ��
�����Ǳ�дӦ�ó������㡣

���ļ�������� CGAlgorithm Ӧ�ó����ÿ���ļ�������ժҪ��

CGAlgorithm.vcproj
    ����ʹ�á�Ӧ�ó����򵼡����ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
    �������й������ļ��� Visual C++ �汾����Ϣ���Լ�
    �й��á�Ӧ�ó����򵼡���ѡ���ƽ̨�����ú�
    ��Ŀ���ܵ���Ϣ��

CGAlgorithm.h
    ����Ӧ�ó������ͷ�ļ���  ����������
    ��Ŀ�ض���ͷ�ļ������� Resource.h����������
    CCGAlgorithmApp Ӧ�ó����ࡣ

CGAlgorithm.cpp
    ���ǰ���Ӧ�ó���
    �� CCGAlgorithmApp ����Ӧ�ó���Դ�ļ���

CGAlgorithm.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ
    ���б�  �������洢�� RES ��Ŀ¼��
    ��ͼ�ꡢλͼ�͹�ꡣ  ��ֱ���� Microsoft 
    Visual C++ �б༭���ļ��� ��Ŀ��Դ������ 2052 �С�

res\CGAlgorithm.ico
    ����һ��ͼ���ļ�������Ӧ�ó����ͼ�ꡣ  ��
    ͼ�����������Դ�ļ� CGAlgorithm.rc �С�

res\CGAlgorithm.rc2
    ���ļ��������� Microsoft 
    Visual C++ �༭����Դ�� Ӧ�����в�����
    ��Դ�༭���༭����Դ���ڴ��ļ��С�
/////////////////////////////////////////////////////////////////////////////

��������ܴ��ڣ�
    ��Ŀ��������׼�� MFC ���档
MainFrm.h, MainFrm.cpp
    ��Щ�ļ���������� CMainFrame������������
    CFrameWnd ���������е� SDI ��ܹ��ܡ�
res\Toolbar.bmp
    ��λͼ�ļ����ڴ�����������ƽ��ͼ��
    ��ʼ��������״̬���� CMainFrame 
    ���й��졣 ʹ����Դ�༭���༭�˹�����λͼ����
    ���� CGAlgorithm.rc �е� IDR_MAINFRAME TOOLBAR ���������
    ��������ť��
/////////////////////////////////////////////////////////////////////////////

Ӧ�ó����򵼽�����һ���ĵ����ͺ�һ����ͼ��

CGAlgorithmDoc.h��CGAlgorithmDoc.cpp - �ĵ�
    ��Щ�ļ����� CCGAlgorithmDoc �ࡣ  �༭��Щ�ļ�
    �����������ĵ����ݲ�ʵ���ļ��ı���ͼ���
    ��ͨ�� CCGAlgorithmDoc::Serialize����
CGAlgorithmView.h��CGAlgorithmView.cpp - �ĵ���ͼ
    ��Щ�ļ����� CCGAlgorithmView �ࡣ
    CCGAlgorithmView �������ڲ鿴 CCGAlgorithmDoc ����
/////////////////////////////////////////////////////////////////////////////

�������ܣ�

ActiveX �ؼ�
    Ӧ�ó���֧��ʹ�� ActiveX �ؼ���

��ӡ֧�ֺʹ�ӡԤ��֧��
    Ӧ�ó�������������һЩ���룬ͨ���� MFC ����� CView ���еĳ�Ա������
    �����ӡ����ӡ���úʹ�ӡԤ�����
/////////////////////////////////////////////////////////////////////////////

������׼�ļ���

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ CGAlgorithm.pch ��Ԥ����ͷ�ļ� (PCH)
    ����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    ���Ǳ�׼ͷ�ļ�������������Դ ID��
    Microsoft Visual C++ ����ȡ�����´��ļ���

/////////////////////////////////////////////////////////////////////////////

����˵����

Ӧ�ó�����ʹ�á�TODO:�� ��ָʾ
Ӧ��ӻ��Զ����Դ���벿�֡�

���Ӧ�ó����ڹ��� DLL ��ʹ�� MFC����Ӧ�ó���ʹ�õ����Բ���
����ϵͳ�ĵ�ǰ���ԣ�����Ҫ�� Microsoft Visual C++ ������ 
Win\System Ŀ¼�½���Ӧ�ı��ػ���Դ MFC70XXX.DLL 
���Ƶ�������� system �� system32 Ŀ¼�£�
������������Ϊ MFCLOC.DLL��  ����XXX������
������д��  ���磬MFC70DEU.DLL ���������
�������Դ����  �������������Ӧ�ó����ĳЩ UI Ԫ��
������Ϊ����ϵͳ�����ԡ�

/////////////////////////////////////////////////////////////////////////////

//back 2006 ���³�һ

#include "stdafx.h"
#include "./3DLoader.h"
#include "../CGAlgorithmDoc.h"
#include "../RightView.h"

namespace Drawing
{

	Model::Model(CView *p):Graphics(p)
	{
		bFileLoaded = false;

		//��ȡpLeftViewָ��
		CCGAlgorithmDoc* pDoc1 = ((CRightView*)pView)->GetDocument();
		CCGAlgorithmDoc* pDoc = (CCGAlgorithmDoc*)pDoc1;
		CView* pLeftView = pDoc->GetLeftView();

		pButton = new CButton;
		pButton->Create("��3D�ļ�", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(10 , 210, 100, 240), pLeftView, IDC_3D_OPEN);
		InitList();
		//��ʼ��ET��AET
		
		for(int i=0;i<768;i++)
		{
			ET[i] = NULL;
		}
		AET=NULL;
	}
	
	Model::~Model()
	{
		delete pButton;
	}

	bool	Model::GetPolyParam(Poly &poly)
	{
		if (poly.VertexIndex.size() < 3) 
			return false;
		
		int i1 = poly.VertexIndex[0];	Point p1 = VtxListTemp[i1];
		int i2 = poly.VertexIndex[1];	Point p2 = VtxListTemp[i2];
		int i3 = poly.VertexIndex[2];	Point p3 = VtxListTemp[i3];

		poly.A = (p2.y-p1.y) * (p3.z -p1.z) - (p2.z-p1.z) * (p3.y-p1.y);
		poly.B = -(p2.x-p1.x) * (p3.z -p1.z) + (p2.z-p1.z) * (p3.x-p1.x);
		poly.C = (p2.x-p1.x) * (p3.y-p1.y) - (p2.y-p1.y) * (p3.x-p1.x);
		poly.D = -(poly.A * p1.x + poly.B * p1.y + poly.C * p1.z);

		poly.Inside = false;
//		Lighting realted 
		//Point vec = light.Dir;
		//float cos_theta = (poly.A*vec.x + poly.B*vec.y + poly.C*vec.z)/
		//	(sqrt(poly.A*poly.A + poly.B*poly.B + poly.C*poly.C) * sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
		//float color = light.Kd * light.Il * cos_theta;

		//poly.g = poly.b = poly.r = 256.0 * color;
	}
	
	bool	Model::ReadObjFile(char* FileName){
		FILE *dataFile;
		char inputLine[256];

		InitList();

		dataFile = fopen(FileName, "r");
		if (dataFile == NULL)
		{
			char strmsg[30];
			sprintf(strmsg, "�޷����ļ�%s", FileName);
			AfxMessageBox(strmsg);
			exit(0);
		}

		for(;;) {

			if (fgets(inputLine, 500, dataFile) == NULL)
				break;			//end of file

			//get the length of the input line
			int ilLen = strlen(inputLine);
			while ((ilLen > 0) && ((inputLine[ilLen - 1] == ' ') ||
				(inputLine[ilLen - 1] == '\n')))
				ilLen--;

			if(inputLine[0] == 'v') 
			{
				if (inputLine[1] == ' ')  //Read a vertex, save it to vertex list
				{
					float x, y, z;
					int count;

					count = sscanf(inputLine, "v %f %f %f", &x, &y, &z);
					if (count != 3)
						continue;
					
					VertexList.push_back(Point((float)(int)x, (float)(int)y, (float)(int)z));
					VtxListTemp.push_back(Point((float)(int)x  , (float)(int)y   , (float)(int)z  ));
		
					//VertexList.push_back( Point(x, y ,  z ));
				}//end of if (inputLine[1] == ' ') 

				if(inputLine[1] == 'n')  //��������ķ���
				{	
					float x, y, z;
					int count;

					count = sscanf(inputLine, "vn %f %f %f", &x, &y, &z);
					if (count != 3)
						continue;

					VnList.push_back(Vector3(  x,  y,  z));
				}
			} //end of if(inputLine[0] == 'v')
			else if (inputLine[0] == 'f') {
				//Read a surface to the PolygenList
				int  fvCount = 0;
				int linePos = 2;
				int		lp, tempIndex, temp;
				Poly tempPoly;

				while (linePos < ilLen) {
					//�����һ����
					sscanf(&inputLine[linePos], "%d%n", &tempIndex, &lp);
					tempPoly.VertexIndex.push_back(tempIndex);

					if (inputLine[linePos + lp] == '/') {
						{
							if(inputLine[linePos + lp+1] != '/')
							{
								int temp,temp2;
								sscanf(&inputLine[linePos + lp +1], "%d%n", &temp2, &temp);
								lp += temp;
							}
						}
						linePos += lp + 2;
						sscanf(&inputLine[linePos], "%d%n", &temp, 
							&lp);
					}
					fvCount++;
					linePos += lp + 1;
				}
				//GetColor(tempPoly);
				GetPolyParam(tempPoly);
				PolyList.push_back(tempPoly);
			}//end of if(inputLine[0] == 'v')
		}//end of for(;;)
		bFileLoaded = true;

				//{//temp
				//		float trans[]=
				//		{
				//			1,	0,	0,	250,
				//			0,	1,	0,	250 ,
				//			0,	0,	1,	250 ,
				//			0,	0,	0,	1
				//		};
				//		Matrix<float>   Mtrans(4, 4, trans);
				//		Transform(Mtrans);
				//} 
	return true;

	}

	void	Model::TestDraw()
	{

		CDC* pDC = pView->GetDC();
		Poly mine;

		if(!bFileLoaded)
			return ;

		UpdateTempVertex();
		//ReadObjFile("teaport.obj");

		for (int j = 1; j<PolyList.size(); j++)  //for every polygen in the model
		{
			mine = PolyList[j];
			for(int i=0; i<mine.VertexIndex.size()-1; i++)  // draw every edge of the polygen
			{
				CDC* pDC = pView->GetDC();
				
				int i1 = mine.VertexIndex[i];
				int i2 = mine.VertexIndex[i+1];

		 		line(pDC, (int)VtxListTemp[i1].x, (int)VtxListTemp[i1].y, (int)VtxListTemp[i2].x, (int)VtxListTemp[i2].y, RENDERCOLOR);

				//	char dbginfo[30];
				//sprintf(dbginfo, "line(%f, %f, %f, %f)\n",VtxListTemp[i].x, VtxListTemp[i].y, VtxListTemp[i+1].x, VtxListTemp[i+1].y);
				//OutputDebugString(dbginfo);
			}
			
			//connect poly's head and tail

			int i1 = mine.VertexIndex[mine.VertexIndex.size()-1];
			int i2 = mine.VertexIndex[0];
		 	line(pDC, (int)VtxListTemp[i1].x, (int)VtxListTemp[i1].y, (int)VtxListTemp[i2].x, (int)VtxListTemp[i2].y, RENDERCOLOR);
		}
		//test createET
		CreateET();
		char str[50];
		sprintf(str, "ymin : %d  ymax: %d\n", ymin, ymax);
		pDC->TextOut(300,100, str);
	}
	void	Model::Draw()
	{	

		//ReadObjFile("plane.obj");

		switch (sState)
		{
		case WIRE_FRAME:
			TestDraw();
			break;
		case SOLID:
			FillArea();
			break;
		default:
			FillArea();
		}
		//	TestDraw();
	}

	
	bool	Model::CreateET()
	{
		//-----��ʼ���߱�ET���߱�AETΪ��----
		
		if(!bFileLoaded) return false;

		Point p1= VertexList[1];

		this->UpdateTempVertex();
		
		//----Ѱ��y�����ֵ����Сֵ-----
		ymin = ymax = VtxListTemp[1].y;
		for (int i = 1; i < VtxListTemp.size(); i++)
		{
			if(VtxListTemp[i].y < ymin) ymin = VtxListTemp[i].y;
			if(VtxListTemp[i].y > ymax) ymax = VtxListTemp[i].y;
		}
		
		//����ET 
		/*for(int i = ymin; i <= ymax; i++)*/
		for(int i = 1; i < 768; i++)
			ET[i] = NULL;
	
		//for (int i = 1; i < PolyList.size(); i++)  //����ÿһ�������
		//{
		//	int VertexjndexSize = PolyList[i].VertexIndex.size();
		//	vector<int> vIndexList = PolyList[i].VertexIndex;
		//	for(int j = 0; j < VertexjndexSize; j++)
		//	{
		//		//---yj��ǰ�ߵ�yֵ��yjPreǰһ���ߵ�yֵ������Ҫֱ����V(eIndex, i).y����Ϊ�����Ǻ����еľֲ��������׳����⣩ 
		//		int yj = VtxListTemp[vIndexList[j]].y,	xj =VtxListTemp[vIndexList[j]].x;
		//		int yjPre = VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].y,	xjPre =VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].x;
		//		int yjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].y,	xjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].x;

		//		EdgeElem  temp,*p;
		//		temp.next = NULL;
		//		p = &temp;
	
		//		//----���������ƽ�б߲�����
		//		if(yj == yjPre)
		//			continue;
		//		//--�����������Ϣ��Ԫ---
		//		p=new EdgeElem;
		//		p->ID = i;
		//		p->xmin = yj<yjPre?xj:xjPre;
		//		p->ymax = max(yj,yjPre);
		//		float a=(float)xj -  (float)xjPre; //ע�⣬floatһ����������
		//		float  b=(float)yj - (float)yjPre;
		//		//p->delta = ( V(eIndex,i).x -  V(eIndex,i-1).x) / ( V(eIndex,i).y - V(eIndex,i-1).y);
		//		p->delta = a/b;
		//		p->next = NULL;

		//		if(yj>yjPre)
		//		{
		//			if(yj<yjNext)
		//				p->ymax-- ;
		//		}else if(yj<yjPre)
		//		{
		//			if(yj>yjNext)
		//			{
		//				yj++;
		//				p->xmin += p->delta;
		//			}
		//		}

		//		if(ET[min(yjPre,yj)] ==	NULL)
		//			ET[min(yjPre,yj)] = p;
		//		else 
		//		{
		//			p->next = ET[min(yjPre,yj)];
		//			ET[min(yjPre,yj)] = p;
		//		}
		//	}
		//}
				
		for (int i = 1; i < PolyList.size(); i++)  //����ÿһ�������
		{
			int VertexjndexSize = PolyList[i].VertexIndex.size();
			vector<int> vIndexList = PolyList[i].VertexIndex;
			for(int j = 0; j < VertexjndexSize; j++)
			{
				//---yj��ǰ�ߵ�yֵ��yjPreǰһ���ߵ�yֵ������Ҫֱ����V(eIndex, i).y����Ϊ�����Ǻ����еľֲ��������׳����⣩ 
				int yj = VtxListTemp[vIndexList[j]].y,	xj =VtxListTemp[vIndexList[j]].x;
				int yjPre = VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].y,	xjPre =VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].x;
				int yjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].y,	xjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].x;

				EdgeElem  temp,*p;
				temp.next = NULL;
				p = &temp;

				Point Vtx = VtxListTemp[vIndexList[j]];
				Point PreVtx =  VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]];
				Point NextVtx = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]];

				Point StartPoint, EndPoint;
				if(Vtx.y < PreVtx.y)
				{
					StartPoint = Vtx; EndPoint = PreVtx;
				}
				else 
				{	StartPoint = PreVtx; EndPoint = Vtx;
				}
	
				//----���������ƽ�б߲�����
				if(yj == yjPre)
					continue;
				//--�����������Ϣ��Ԫ---
				p=new EdgeElem;
				p->ID = i;
				p->xmin = StartPoint.x;
				p->ymax = EndPoint.y;
				float a=(float)Vtx.x -  (float)PreVtx.x; //ע�⣬floatһ����������
				float  b=(float)Vtx.y - (float)PreVtx.y;
				//p->delta = ( V(eIndex,i).x -  V(eIndex,i-1).x) / ( V(eIndex,i).y - V(eIndex,i-1).y);
				p->delta = a/b;
				
				p->color = StartPoint.r;
				p->deltacolor = ((float)Vtx.r -  (float)PreVtx.r)/b;

				p->next = NULL;

				if(Vtx.y>PreVtx.y)
				{
					if(Vtx.y<NextVtx.y)
						p->ymax-- ;
				}else if(Vtx.y<PreVtx.y)
				{
					if(Vtx.y>NextVtx.y)
					{
						yj++;
						p->xmin += p->delta;
					}
				}

				if(ET[min(yjPre,yj)] ==	NULL)
					ET[min(yjPre,yj)] = p;
				else 
				{
					p->next = ET[min(yjPre,yj)];
					ET[min(yjPre,yj)] = p;
				}
			}
		}
		for(int y=ymin; y<=ymax; y++)  //���½����ı߱��������
			this->SortList(ET[y]);

	//{
	//		FILE * fp = fopen("info_of_test_Parameter.txt","w");
	//		if(!fp) AfxMessageBox("Error ");

	//		for(int i = 0; i < VertexList.size(); i++)
	//		{
	//			Point p = VertexList[i];
	//			fprintf(fp, "%10.7lf\t%10.7lf\t%10.7lf\t\n", p.x, p.y,  p.z);
	//		}
	//		
	//		fclose(fp);

	//	}
		return true;
	}
	void	Model::MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL)
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
	void	Model::SortList(EdgeElem * p)
	{
		//use select sorting
		EdgeElem *q,*pRec; //p points to the leftmost element of an array left to sorted
		// q Point to the current element being checked 
		//prec Point to the min element checked by q
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
			this->exchange(p->ID  , pRec->ID);
			this->exchange(p->fp,	pRec->fp);
			p=p->next;

		}

	}
	void	Model::Remove(EdgeElem* &pHead,EdgeElem* &q)
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

	void    Model::FillArea()
	{
		CDC* pDC = pView->GetDC();	//��ͼ���
		EdgeElem *pTemp;			//��ʱ����
	
		if(!bFileLoaded) return;


		Point p1= VertexList[1];

		this->CreateET();	//�����߱�
		AET = NULL		;	//��߱��ÿ�
		
		for(int y=ymin; y<=ymax; y++)  //����ÿһ��ɨ���߽������
		{
			//�߲��룬����AET��ET[y]�����ݽ��кϲ�������AET����
  			 this->MergeList(ET[y],AET,pTemp);
			AET = pTemp;
			
			//��fp
			//��ʼ��, PolygenList�и�Ԫ�ص�inside�ü�
			{
				vector<int> APL;	//���insideΪtrue�����

				for(int i = 0; i < PolyList.size(); i++) PolyList[i].Inside = false;

				while(pTemp)		//�Ե�ǰAET�е����б�
				{
					int curID = pTemp->ID;
					PolyList[curID].Inside = !PolyList[curID].Inside;
						
					if(PolyList[curID].Inside)  //��֤APL�м�¼�Ķ���insideΪ��Ķ�������
						APL.push_back(curID);
					else
					{
						for (vector<int>::iterator itr = APL.begin(); itr != APL.end(); itr++)
							if(*itr == curID)
							{
								APL.erase(itr);
								break;
							}
					}
					 
					if(APL.size() == 0) pTemp->fp  = 0;		//������û�ж����
					else if(APL.size() == 1) pTemp->fp = APL[0];
					else
					{
						int fp_temp = 1;	//�����Сzֵ�ö�������
						float  z_temp	= 1.0e100;	//��¼��С�����ֵ
						
						for (vector<int>::iterator itr = APL.begin(); itr != APL.end(); itr++)
						{
							Poly poly = PolyList[*itr];
							//������С��z
							float z = (-poly.D - poly.A * (pTemp->xmin + 1) - poly.B * y) / poly.C;
							if(z < z_temp) 
							{
								z_temp = z;
								fp_temp = *itr;
							}
						}
						pTemp->fp = fp_temp;
					}
					pTemp = pTemp->next;
				}

			}
			
			//��ɫ(����߱�����������Ԫ�ص�xmin��ͬ�Ļ���Ӧ��ɾ��һ��)
			pTemp = AET;
			while(pTemp && pTemp->next)
			{
				if (pTemp->fp == 0) {pTemp = pTemp->next;continue;};
				int x1 = pTemp->xmin, y1 = y;
				float c1 = pTemp->color;

				int formerid = pTemp->ID;

				int x2 = pTemp->next->xmin, y2 = y;
				float c2 = pTemp->next->color;

				//while(pTemp->next && pTemp->next->fp == pTemp->fp)
				//	pTemp = pTemp->next;
				//int x2 = pTemp->next->xmin;
				//int y2 = y;
				//
				//EdgeElem* pTemp2 = pTemp->next;
				//while(pTemp2&&pTemp2->ID != formerid)
				//	pTemp2 = pTemp2->next;
				//float c2 = pTemp->color;
				//DWORD color = PolyList[pTemp->fp].b<<16 + PolyList[pTemp->fp].g<<8 + PolyList[pTemp->fp].r;

				//Poly temp = PolyList[pTemp->fp];
				//
				//int r = pTemp->color;
				//int g = pTemp->color;
				//int b = pTemp->color;

				//DWORD color = (b<<16) + (g<<8) + r;  //��Ϊ+���ȼ�����<<,Ӧ��������
				

				line2(pDC,x1, y1, x2, y2, c1, c2);

				//line(pDC, x1, y1, x2, y2, c1);
				//pDC->SetPixel(x1, y1, color);
				//pDC->SetPixel(x2, y2, color);

				pTemp = pTemp->next;
			}

			pTemp = AET;
			while(pTemp!=NULL)
			{
				if(y >= (int)(pTemp->ymax))		//ɾ��һЩ��������y>=ymax�ı�
				{
					this->Remove(AET,pTemp);
					continue; //�ز�����
				}
				else				
				{
					pTemp->xmin += pTemp->delta;
					pTemp->color  += pTemp->deltacolor;
					if(pTemp)
						pTemp = pTemp->next;
				}
			}
			SortList(AET);
		}
	}
	void	Model::ReceiveMsg(MSG& msg)
	{
		switch(msg.message) {
		case IDC_3D_OPEN:
			OpenObjFile();
			break;
		case WM_CHAR:
			OnChar(msg.lParam);
			break;
		case IDC_SUB_SELECT:
			sState = msg.wParam;
			break;
	
		}
	}

	bool Model::OpenObjFile()
	{
		CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, "3D �ļ�(*.obj)|*.obj|�����ļ�(*.*)|*.*||");  
		if(dlg.DoModal() != IDOK) 
			return false;   
		
		char fname[100];
		strcpy(fname, dlg.GetPathName());

		ReadObjFile(fname) ;

		//{//temporary 
		//	FILE  *fp = fopen("debug_info.txt", "w");
  //          for(int i = 1; i< VnList.size(); i++)
		//		fprintf(fp, "%f\t%f\t%f\n", VnList[i].x, VnList[i].y, VnList[i].z);
		//	fclose(fp);
		//}

		bFileLoaded = true;

		return true;
	}

	void Model::Transform(Matrix<float>& M)
	{
		//Ϊ��֤ɨ���ߵ���ȷ�ԣ�
		for (int i=1; i< VertexList.size(); i++)
		{
			Point p1= VertexList[i];

			VertexList[i].Transform(M);
			Point p2 = VertexList[i];
			VtxListTemp[i].x = (float)(int)VertexList[i].x;
			VtxListTemp[i].y = (float)(int)VertexList[i].y;
			VtxListTemp[i].z = (float)(int)VertexList[i].z;
		}
		//ע������궥���Ժ�һ��Ҫ����ƽ�淽�̵Ĳ���
		for (int i = 1; i < PolyList.size(); i++)
			GetPolyParam(PolyList[i]);
	}

	void Model::OnChar(UINT ch)
	{
		float delta = 0.1;

		float rotatez[] = 
		{
				cos(delta), -sin(delta),0,	0,
				sin(delta),	cos(delta),	0,	0,
				0,			0,			1,	0,
				0,			0,			0,	1	
		};
		
		float rotatex[] = 
		{
				1,	0,			0,			0,
				0,	cos(delta),-sin(delta),	0,
				0,	sin(delta),	cos(delta),	0,
				0,	0,			0,			1	
		};

		float rotatey[] = 
		{
			cos(delta), 0,	-sin(delta),0,
				0,		1,	0,			0,
			sin(delta),	0,	cos(delta),			0,
			0,			0,	0,			1	
		};

		float trans[]=
		{
			1,	0,	0,	250,
			0,	1,	0,	250,
			0,	0,	1,	250,
			0,	0,	0,	1
		};
		float retrans[]=
		{
			1,	0,	0,	-250,
			0,	1,	0,	-250,
			0,	0,	1,	-250,
			0,	0,	0,	1
		};

		float leave[]=
		{
			1,	0,	0,	0,
			0,	1,	0,	0,
			0,	0,	1,	5,
			0,	0,	0,	1
		};

		float come[]=
		{
			1,	0,	0,	0,
			0,	1,	0,	0,
			0,	0,	1,	-5,
			0,	0,	0,	1
		};

		Matrix<float>   Mleave(4, 4, leave);
		Matrix<float>   Mcome(4, 4, come);
		Matrix<float> Mrx(4, 4, rotatex);
		Matrix<float> Mry(4, 4, rotatey);
		Matrix<float> Mrz(4, 4, rotatez);
		Matrix<float> Mt(4, 4, trans);
		Matrix<float> Mret(4, 4, retrans);

		switch(ch) {
		//case 'x':	Transform(Mt * Mrx * Mret);	break;
		//case 'y':	Transform(Mt * Mry * Mret);	break;
		//case 'z':	Transform(Mt * Mrz * Mret);	break;
		case 'x':	Transform(Mrx);	break;
		case 'y':	Transform(Mry);	break;
		case 'z':	Transform(Mrz);	break;
		case 'f':	Transform(Mleave);break;
		case 'n':   Transform(Mcome); break;
		default	:	break;
		}

		//{//to be delte
		//	FILE * fp = fopen("info_of_test_total.txt","w");



		//	for(int i = 1; i < VertexList.size(); i++)
		//	{
		//		float x =  VertexList[i].x;
		//		float y = VertexList[i].y;
		//		float  z = VertexList[i].z;

		//		fprintf(fp, "v  %10.6lf %10.6lf %10.6lf\n", x - 250 , y - 250, z-250);
		//	}
		//	
		//	fprintf(fp, "\n");

		//	for(int i = 1; i< PolyList.size(); i++)
		//	{
		//		Poly poly = PolyList[i];
		//		vector<int> v = poly.VertexIndex;


		//		fprintf(fp, "f  ");
		//		for(vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
		//			fprintf(fp, "%d ",  *itr);
		//		fprintf(fp, "\n");
		//	}
		//	fclose(fp);
		//}
		
	}

	void Model::UpdateTempVertex()
	{
		float D = 200.0;
		float proj[]=
			{
				1,	0,	 0,	0,
				0,	1,	 0,	0,
				0,	0,	 1,	0,
				0 ,	0 , 1/D, 1
			};
		Matrix<float>  M(4,4,proj);

		float trans[]=
		{
			1,	0,	0,	250,
			0,	1,	0,	250 ,
			0,	0,	1,	250 ,
			0,	0,	0,	1
		};
		Matrix<float>   Mtrans(4, 4, trans);

		for(int i=1; i<VertexList.size(); i++)
		{
			VtxListTemp[i] = VertexList[i];
		 //	VtxListTemp[i].Transform(M );
		 	VtxListTemp[i].Transform(Mtrans);
			
			VtxListTemp[i].x = (float)(int)VtxListTemp[i].x;
			VtxListTemp[i].y = (float)(int)VtxListTemp[i].y;
			VtxListTemp[i].z = (float)(int)VtxListTemp[i].z;
			
			//���㶥��Ĺ���
			Point vec = light.Dir;
			Vector3  norm = VnList[i];
			float cos_theta = (norm.x*vec.x + norm.y*vec.y + norm.z*vec.z)/
				(sqrt(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z) * sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
			float color = light.Kd * light.Il * cos_theta;

			if(color < 0)
				VtxListTemp[i].r = VtxListTemp[i].g = VtxListTemp[i].b = 0.0f;
			else 
				VtxListTemp[i].r = VtxListTemp[i].g = VtxListTemp[i].b = 256.0 * color;
			
		}
		for (int i = 1; i < PolyList.size(); i++)
			GetPolyParam(PolyList[i]);


	//this->GetVectorOfVertex();
	}


	
	void Model::GetColor(Poly &poly)
		{
			poly.r = 256.0 * rand()/RAND_MAX;
			poly.g = 256.0 * rand()/RAND_MAX;
			poly.b = 256.0 * rand()/RAND_MAX;
		}

	void Model::GetVectorOfVertex()  //��ȡ�˶���ķ����Ϳ��Լ���
		{
			for(int i=1 ; i<PolyList.size(); i++)
			{
				vector<int> vlist = PolyList[i].VertexIndex;
				for(vector<int>::iterator itr = vlist.begin(); itr!= vlist.end(); itr++)
				{
					//���ö���η�����Ϣ��ӵ���Ӧ�Ķ��ϣ��Ա���ƽ��
					float x = PolyList[i].A;
					float y = PolyList[i].B;
					float z = PolyList[i].C;

					VertexList[*itr].temp.push_back(Vector3(x, y,z));
				}
			}
			
			for(int i=1; i< VertexList.size(); i++)
			{
				Point  &point = VertexList[i];
				Vector3 sum;

				for(vector<Vector3>::iterator itr = point.temp.begin(); itr!=point.temp.end(); itr++)
					sum = sum + (*itr);
				
				int size = point.temp.size();
				point.xn = sum.x / size;
				point.yn = sum.y / size ;
				point.zn = sum.z / size;

						//Lighting realted 
				Point vec = light.Dir;
				float cos_theta = (point.xn*vec.x + point.yn*vec.y + point.zn*vec.z)/
					(sqrt(point.xn*point.xn + point.yn*point.yn + point.zn*point.zn) * sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
				float color = light.Kd * light.Il * cos_theta;
				point.r  = point.g = point.b = 256.0*color;
			}
		}
		void Model::LocalLine(int x1, int y1, int x2, int y2, Vector3 color1, Vector3 color2)
		{
			 
			CDC* pDC = pView->GetDC();	//��ͼ���
			CPoint pb(x1, y1);
			CPoint pe(x2, y2);
			float x,y;
			float L=max(abs(pe.x-pb.x),abs(pe.y-pb.y));
			float deltax=(pe.x-pb.x)/L;
			float  deltay=(pe.y-pb.y)/L;
			x=(float)pb.x;
			y=(float)pb.y;

			float colorstart = color1.x;
			float colorend = color2.x;
			float deltacolor = (colorend-colorstart)/L;
			float color = (int)colorstart;
			for(int i=0;i<L;i++)
			{
				x += deltax;
				y += deltay;
				color += deltacolor;
				pDC->SetPixel((int)x,(int)y, (int)color);
			}

			pDC->SetPixel(x1, y1, color);
			pDC->SetPixel(x2, y2, color);
		}
}//end of namespace 
