================================================================================
    MICROSOFT 基础类库： CGAlgorithm 项目概述
===============================================================================

应用程序向导已为您创建了此 CGAlgorithm 应用程序。此应用程序
不仅介绍了使用 Microsoft 基础类的基本知识，
而且是编写应用程序的起点。

此文件包含组成 CGAlgorithm 应用程序的每个文件的内容摘要。

CGAlgorithm.vcproj
    这是使用“应用程序向导”生成的 VC++ 项目的主项目文件。 
    它包含有关生成文件的 Visual C++ 版本的信息，以及
    有关用“应用程序向导”所选择的平台、配置和
    项目功能的信息。

CGAlgorithm.h
    这是应用程序的主头文件。  它包含其他
    项目特定的头文件（包括 Resource.h），并声明
    CCGAlgorithmApp 应用程序类。

CGAlgorithm.cpp
    这是包含应用程序
    类 CCGAlgorithmApp 的主应用程序源文件。

CGAlgorithm.rc
    这是程序使用的所有 Microsoft Windows 资源
    的列表。  它包含存储在 RES 子目录中
    的图标、位图和光标。  可直接在 Microsoft 
    Visual C++ 中编辑此文件。 项目资源包含在 2052 中。

res\CGAlgorithm.ico
    这是一个图标文件，用作应用程序的图标。  此
    图标包含在主资源文件 CGAlgorithm.rc 中。

res\CGAlgorithm.rc2
    此文件包含不由 Microsoft 
    Visual C++ 编辑的资源。 应将所有不能由
    资源编辑器编辑的资源放在此文件中。
/////////////////////////////////////////////////////////////////////////////

对于主框架窗口：
    项目将包含标准的 MFC 界面。
MainFrm.h, MainFrm.cpp
    这些文件包含框架类 CMainFrame，该类派生自
    CFrameWnd 并控制所有的 SDI 框架功能。
res\Toolbar.bmp
    此位图文件用于创建工具栏的平铺图像。
    初始工具栏和状态栏在 CMainFrame 
    类中构造。 使用资源编辑器编辑此工具栏位图，并
    更新 CGAlgorithm.rc 中的 IDR_MAINFRAME TOOLBAR 数组以添加
    工具栏按钮。
/////////////////////////////////////////////////////////////////////////////

应用程序向导将创建一种文档类型和一个视图：

CGAlgorithmDoc.h、CGAlgorithmDoc.cpp - 文档
    这些文件包含 CCGAlgorithmDoc 类。  编辑这些文件
    以添加特殊的文档数据并实现文件的保存和加载
    （通过 CCGAlgorithmDoc::Serialize）。
CGAlgorithmView.h、CGAlgorithmView.cpp - 文档视图
    这些文件包含 CCGAlgorithmView 类。
    CCGAlgorithmView 对象用于查看 CCGAlgorithmDoc 对象。
/////////////////////////////////////////////////////////////////////////////

其他功能：

ActiveX 控件
    应用程序支持使用 ActiveX 控件。

打印支持和打印预览支持
    应用程序向导已生成了一些代码，通过从 MFC 库调用 CView 类中的成员函数来
    处理打印、打印设置和打印预览命令。
/////////////////////////////////////////////////////////////////////////////

其他标准文件：

StdAfx.h、StdAfx.cpp
    这些文件用于生成名为 CGAlgorithm.pch 的预编译头文件 (PCH)
    和名为 StdAfx.obj 的预编译类型文件。

Resource.h
    这是标准头文件，它定义新资源 ID。
    Microsoft Visual C++ 将读取并更新此文件。

/////////////////////////////////////////////////////////////////////////////

其他说明：

应用程序向导使用“TODO:” 来指示
应添加或自定义的源代码部分。

如果应用程序在共享 DLL 中使用 MFC，且应用程序使用的语言不是
操作系统的当前语言，则需要从 Microsoft Visual C++ 光盘上 
Win\System 目录下将相应的本地化资源 MFC70XXX.DLL 
复制到计算机的 system 或 system32 目录下，
并将其重命名为 MFCLOC.DLL。  （“XXX”代表
语言缩写。  例如，MFC70DEU.DLL 包含翻译成
德语的资源。）  如果不这样做，应用程序的某些 UI 元素
将保留为操作系统的语言。

/////////////////////////////////////////////////////////////////////////////

//back 2006 正月初一

#include "stdafx.h"
#include "./3DLoader.h"
#include "../CGAlgorithmDoc.h"
#include "../RightView.h"

namespace Drawing
{

	Model::Model(CView *p):Graphics(p)
	{
		bFileLoaded = false;

		//获取pLeftView指针
		CCGAlgorithmDoc* pDoc1 = ((CRightView*)pView)->GetDocument();
		CCGAlgorithmDoc* pDoc = (CCGAlgorithmDoc*)pDoc1;
		CView* pLeftView = pDoc->GetLeftView();

		pButton = new CButton;
		pButton->Create("打开3D文件", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(10 , 210, 100, 240), pLeftView, IDC_3D_OPEN);
		InitList();
		//初始化ET与AET
		
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
			sprintf(strmsg, "无法打开文件%s", FileName);
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

				if(inputLine[1] == 'n')  //遇到顶点的法向
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
					//获得下一个数
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
		//-----初始化边表ET与活动边表AET为空----
		
		if(!bFileLoaded) return false;

		Point p1= VertexList[1];

		this->UpdateTempVertex();
		
		//----寻找y的最大值与最小值-----
		ymin = ymax = VtxListTemp[1].y;
		for (int i = 1; i < VtxListTemp.size(); i++)
		{
			if(VtxListTemp[i].y < ymin) ymin = VtxListTemp[i].y;
			if(VtxListTemp[i].y > ymax) ymax = VtxListTemp[i].y;
		}
		
		//清理ET 
		/*for(int i = ymin; i <= ymax; i++)*/
		for(int i = 1; i < 768; i++)
			ET[i] = NULL;
	
		//for (int i = 1; i < PolyList.size(); i++)  //对于每一个多边形
		//{
		//	int VertexjndexSize = PolyList[i].VertexIndex.size();
		//	vector<int> vIndexList = PolyList[i].VertexIndex;
		//	for(int j = 0; j < VertexjndexSize; j++)
		//	{
		//		//---yj当前边的y值，yjPre前一条边的y值，（不要直接用V(eIndex, i).y，因为他们是函数中的局部变量，易出问题） 
		//		int yj = VtxListTemp[vIndexList[j]].y,	xj =VtxListTemp[vIndexList[j]].x;
		//		int yjPre = VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].y,	xjPre =VtxListTemp[vIndexList[(VertexjndexSize+j-1)%VertexjndexSize]].x;
		//		int yjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].y,	xjNext = VtxListTemp[vIndexList[(j+1)%VertexjndexSize]].x;

		//		EdgeElem  temp,*p;
		//		temp.next = NULL;
		//		p = &temp;
	
		//		//----特殊情况：平行边不考虑
		//		if(yj == yjPre)
		//			continue;
		//		//--产生多边形信息单元---
		//		p=new EdgeElem;
		//		p->ID = i;
		//		p->xmin = yj<yjPre?xj:xjPre;
		//		p->ymax = max(yj,yjPre);
		//		float a=(float)xj -  (float)xjPre; //注意，float一个都不能少
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
				
		for (int i = 1; i < PolyList.size(); i++)  //对于每一个多边形
		{
			int VertexjndexSize = PolyList[i].VertexIndex.size();
			vector<int> vIndexList = PolyList[i].VertexIndex;
			for(int j = 0; j < VertexjndexSize; j++)
			{
				//---yj当前边的y值，yjPre前一条边的y值，（不要直接用V(eIndex, i).y，因为他们是函数中的局部变量，易出问题） 
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
	
				//----特殊情况：平行边不考虑
				if(yj == yjPre)
					continue;
				//--产生多边形信息单元---
				p=new EdgeElem;
				p->ID = i;
				p->xmin = StartPoint.x;
				p->ymax = EndPoint.y;
				float a=(float)Vtx.x -  (float)PreVtx.x; //注意，float一个都不能少
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
		for(int y=ymin; y<=ymax; y++)  //对新建立的边表进行排序
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
		CDC* pDC = pView->GetDC();	//绘图相关
		EdgeElem *pTemp;			//临时变量
	
		if(!bFileLoaded) return;


		Point p1= VertexList[1];

		this->CreateET();	//创建边表
		AET = NULL		;	//活动边表置空
		
		for(int y=ymin; y<=ymax; y++)  //对于每一条扫描线进行填充
		{
			//边插入，即将AET与ET[y]的内容进行合并，并对AET排序
  			 this->MergeList(ET[y],AET,pTemp);
			AET = pTemp;
			
			//求fp
			//初始化, PolygenList中各元素的inside置假
			{
				vector<int> APL;	//存放inside为true的序号

				for(int i = 0; i < PolyList.size(); i++) PolyList[i].Inside = false;

				while(pTemp)		//对当前AET中的所有边
				{
					int curID = pTemp->ID;
					PolyList[curID].Inside = !PolyList[curID].Inside;
						
					if(PolyList[curID].Inside)  //保证APL中记录的都是inside为真的多边形序号
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
					 
					if(APL.size() == 0) pTemp->fp  = 0;		//该区间没有多边形
					else if(APL.size() == 1) pTemp->fp = APL[0];
					else
					{
						int fp_temp = 1;	//存放最小z值得多边形序号
						float  z_temp	= 1.0e100;	//记录最小的深度值
						
						for (vector<int>::iterator itr = APL.begin(); itr != APL.end(); itr++)
						{
							Poly poly = PolyList[*itr];
							//计算最小的z
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
			
			//填色(如果边表中相邻两个元素的xmin相同的话，应该删除一个)
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

				//DWORD color = (b<<16) + (g<<8) + r;  //因为+优先级高于<<,应加上括号
				

				line2(pDC,x1, y1, x2, y2, c1, c2);

				//line(pDC, x1, y1, x2, y2, c1);
				//pDC->SetPixel(x1, y1, color);
				//pDC->SetPixel(x2, y2, color);

				pTemp = pTemp->next;
			}

			pTemp = AET;
			while(pTemp!=NULL)
			{
				if(y >= (int)(pTemp->ymax))		//删除一些满足条件y>=ymax的边
				{
					this->Remove(AET,pTemp);
					continue; //必不可少
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
		CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, "3D 文件(*.obj)|*.obj|所有文件(*.*)|*.*||");  
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
		//为保证扫描线的正确性，
		for (int i=1; i< VertexList.size(); i++)
		{
			Point p1= VertexList[i];

			VertexList[i].Transform(M);
			Point p2 = VertexList[i];
			VtxListTemp[i].x = (float)(int)VertexList[i].x;
			VtxListTemp[i].y = (float)(int)VertexList[i].y;
			VtxListTemp[i].z = (float)(int)VertexList[i].z;
		}
		//注意更新完顶点以后，一定要更新平面方程的参数
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
			
			//计算顶点的光照
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

	void Model::GetVectorOfVertex()  //获取了顶点的发向后就可以计算
		{
			for(int i=1 ; i<PolyList.size(); i++)
			{
				vector<int> vlist = PolyList[i].VertexIndex;
				for(vector<int>::iterator itr = vlist.begin(); itr!= vlist.end(); itr++)
				{
					//将该多边形法线信息添加到相应的顶上，以便球平均
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
			 
			CDC* pDC = pView->GetDC();	//绘图相关
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
