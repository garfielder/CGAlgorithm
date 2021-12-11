// CGAlgorithmDoc.cpp :  CCGAlgorithmDoc ���ʵ��
//

#include "stdafx.h"
#include "CGAlgorithm.h"

//#include "./Frame/CGAlgorithmDoc.h"
//#include "./Frame/LeftView.h"
//#include "./Frame/RightView.h"

#include "CGAlgorithmDoc.h"
#include "LeftView.h"
#include "RightView.h"

#include "./graphics/graphics.h"
#include "./graphics/line.h"
#include "./Graphics/Circle.h"
#include "./Graphics/Polygon.h"
#include "./Graphics/PolyFill.h"
#include "Graphics/Clipping.h"
#include "Graphics/ClipPoly.h"
#include "Graphics/LineCulling.h"
#include "Graphics/3DLoader.h"
#include "Graphics/lighting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGAlgorithmDoc

IMPLEMENT_DYNCREATE(CCGAlgorithmDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGAlgorithmDoc, CDocument)
END_MESSAGE_MAP()


// CCGAlgorithmDoc ����/����

CCGAlgorithmDoc::CCGAlgorithmDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCGAlgorithmDoc::~CCGAlgorithmDoc()
{
}

BOOL CCGAlgorithmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	//pGraph = new Drawing::Line(this->GetRightView());

	//pGraph->Draw();
	pGraph = NULL;

	

	

	return TRUE;
}

//void CCGAlgorithmDoc::Test()
//{
//	this->GetRightView()->GetDC()->Rectangle(100,100,300,300);
//}




// CCGAlgorithmDoc ���л�

void CCGAlgorithmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

CView* CCGAlgorithmDoc::GetRightView(void)
{
	CView* pView;
	POSITION pos=GetFirstViewPosition();

	while(pos!=NULL){
		pView=GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CRightView)))
			break;
	}

	if(!pView->IsKindOf(RUNTIME_CLASS(CRightView)))
		AfxMessageBox("can't find CRightView");
	//if(!pView->IsKindOf(RUNTIME_CLASS(CMyView))){
	//	AfxMessageBox("Connt Locate the CMyView.");
	//	//return NULL;
	//}

	return pView;
}
CView* CCGAlgorithmDoc::GetLeftView(void)
{
	CView* pView;
	POSITION pos=GetFirstViewPosition();

	while(pos!=NULL){
		pView=GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CLeftView)))
			break;
	}

	if(!pView->IsKindOf(RUNTIME_CLASS(CLeftView)))
		AfxMessageBox("can't find CLeftView");
	//if(!pView->IsKindOf(RUNTIME_CLASS(CMyView))){
	//	AfxMessageBox("Connt Locate the CMyView.");
	//	//return NULL;
	//}

	return pView;
}


void CCGAlgorithmDoc::ReceiveMSG(MSG &msg)
{
	if(msg.message == IDC_SELECT_MODE)  //����Ǹ�����ѡ��ģʽ����Ϣ
	{
		
		ClearpGraph();
		
		switch (msg.wParam)
		{
			case LINE:
				pGraph = new Drawing::Line(GetRightView()); break;
			case CIRCLE:
				pGraph = new Drawing::Circle(GetRightView());break;
			case FILL:	
				pGraph = new Drawing::PolyFill(GetRightView());break;
			case CLIPPING: 
				pGraph = new Drawing::Clip(GetRightView());break;
			case CLIPPOLYGON: 
				pGraph = new Drawing::ClipPoly(GetRightView());break;
			case LINECULLING:
				pGraph = new Drawing::LineCulling(GetRightView());break;
			case SCAN_ZBUFFER:
				pGraph = new Drawing::Model(GetRightView());break;
			case LIGHTING:
				pGraph = new Drawing::Lighting(GetRightView());break;

		}
	}else if(this->pGraph)				//������Ϣ����Graphics�ദ��
		pGraph->ReceiveMsg(msg);

	 this->UpdateAllViews(NULL);
}

void CCGAlgorithmDoc::ClearpGraph()
{
	if(pGraph != NULL)
	{
		delete pGraph;
		pGraph = NULL;
	}
	

}

// CCGAlgorithmDoc ���

#ifdef _DEBUG
void CCGAlgorithmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGAlgorithmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCGAlgorithmDoc ����
