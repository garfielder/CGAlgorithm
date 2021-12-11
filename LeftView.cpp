// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CGAlgorithm.h"
#include "LeftView.h"
#include "MyHead.h"

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
{

}


CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	

	this->InitCtlItem();



	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_test);

}


//�����ϢӰ�䣬first 
BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_CBN_SELCHANGE(IDC_SELECT_MODE, OnModeChange)
	ON_BN_CLICKED(IDC_SUB_SELECT1, OnSub1)
	ON_BN_CLICKED(IDC_SUB_SELECT2, OnSub2)
	ON_BN_CLICKED(IDC_SUB_SELECT3, OnSub3)

	ON_BN_CLICKED(IDC_3D_OPEN,		On3DOpen)
	ON_BN_CLICKED(IDC_BTN_FILL,    OnBtnFill)

	ON_WM_CREATE()
END_MESSAGE_MAP()
//next is in cpp, ������Ӧ�ĺ���

// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CLeftView ��Ϣ�������

void CLeftView::OnBnClickedButton1()
{
		CButton *pBtn = new CButton();
		pBtn->Create("�ü�",WS_VISIBLE | WS_CHILD | WS_BORDER , 
			CRect(10 , 10, 100, 40), this, 123);
}
void CLeftView::InitCtlItem()
{
	this->mCombBox.Create(
      WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,
      CRect(10,10,200,100), this, IDC_SELECT_MODE);

	mCombBox.AddString("����");
	mCombBox.AddString("��Ȧ");
	mCombBox.AddString("���");
	mCombBox.AddString("ֱ�߲ü�");
	mCombBox.AddString("����βü�");
	mCombBox.AddString("������");
	mCombBox.AddString("Z-Buffer����");
	mCombBox.AddString("����ģ��");
	//next is add submode in OnModeChange


	//mCombBox.AddString("Clipping");
}

void CLeftView::OnModeChange()
{
// ����ģʽ��֪ͨDoc�࣬ģʽ�ı�


	CString g_NameArr[][3]=
	{
		"DDA", "Bresham", "",
		"DDA", "Bresham", "",
		"ɨ��ת��", "�������", "�����������",
		"Surthland","",   "",
		"Surthland","",   "",
		"����ˮƽ��", "" , "",
		"�߿�ģ��", "���ģ��", "",
		"phone shadering","Gaurand shadering",""
	};

	
	int index = mCombBox.GetCurSel();

	for(int i=0; i< MAX_SUB_STATE; i++) //Ϊÿһ����ģʽ����һ����ѡ��ť
	{
		if(g_NameArr[index][i].GetLength())
		{
			subArr[i].SetWindowText(g_NameArr[index][i]);
			subArr[i].SetCheck(false);
			subArr[i].ShowWindow(true);
		}
		else
			subArr[i].ShowWindow(false);

	}

	//next step is to add the corrosponding object in cDoc

	//֪ͨCDoc��
	MSG msg;
	msg.wParam = index;				
	msg.message = IDC_SELECT_MODE;
	GetDocument()->ReceiveMSG(msg);


}

void CLeftView::OnSub1()
{
	SUBMODE subMode[]= 
	{DDA, DDA, SCAN_LINE,SUTHURLAND,DEFAULT,DEFAULT, WIRE_FRAME};

	for(int i=0; i< MAX_SUB_STATE; i++)
			subArr[i].SetCheck(false);
		subArr[0].SetCheck(true);
	int index = mCombBox.GetCurSel();

	MSG msg;
	msg.message = IDC_SUB_SELECT;
	msg.wParam  = subMode[index];
		GetDocument()->ReceiveMSG(msg);


	
}
void CLeftView::OnSub2()
{
	SUBMODE subMode[]= 
	{
		BRESHAM, BRESHAM, SEED_FILL,DEFAULT, DEFAULT,DEFAULT, SOLID
	};
		for(int i=0; i< MAX_SUB_STATE; i++)
			subArr[i].SetCheck(false);
		subArr[1].SetCheck(true);
		int index = mCombBox.GetCurSel();

	MSG msg;
	msg.message = IDC_SUB_SELECT;
	msg.wParam  = subMode[index];
	GetDocument()->ReceiveMSG(msg);
}
void CLeftView::OnSub3()
{
	SUBMODE subMode[]= 
	{
		DEFAULT, DEFAULT, BETTER_SEED_FILL
	};

		for(int i=0; i< MAX_SUB_STATE; i++)
			subArr[i].SetCheck(false);
		subArr[2].SetCheck(true);
		int index = mCombBox.GetCurSel();

	MSG msg;
	msg.message = IDC_SUB_SELECT;
	msg.wParam  = subMode[index];
	GetDocument()->ReceiveMSG(msg);
}

void CLeftView::OnBtnFill()
{
	MSG msg;
	msg.message = IDC_BTN_FILL;
	GetDocument()->ReceiveMSG(msg);
}

void CLeftView::On3DOpen()
{
	MSG msg;
	msg.message = IDC_3D_OPEN;
	GetDocument()->ReceiveMSG(msg);
}
int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	for(int i=0; i< MAX_SUB_STATE; i++)
	{
			subArr[i].Create("aa", WS_CHILD|WS_VISIBLE|WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON, 
			CRect(50,40+50*i,150,70+50*i), this, IDC_SUB_SELECT1+i);
			subArr[i].ShowWindow(false);
	}


	return 0;
}
CCGAlgorithmDoc* CLeftView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgorithmDoc)));
	return (CCGAlgorithmDoc*)m_pDocument;
}