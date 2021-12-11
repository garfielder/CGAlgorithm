// LeftView.cpp : 实现文件
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


//添加消息影射，first 
BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_CBN_SELCHANGE(IDC_SELECT_MODE, OnModeChange)
	ON_BN_CLICKED(IDC_SUB_SELECT1, OnSub1)
	ON_BN_CLICKED(IDC_SUB_SELECT2, OnSub2)
	ON_BN_CLICKED(IDC_SUB_SELECT3, OnSub3)

	ON_BN_CLICKED(IDC_3D_OPEN,		On3DOpen)
	ON_BN_CLICKED(IDC_BTN_FILL,    OnBtnFill)

	ON_WM_CREATE()
END_MESSAGE_MAP()
//next is in cpp, 声明相应的函数

// CLeftView 诊断

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


// CLeftView 消息处理程序

void CLeftView::OnBnClickedButton1()
{
		CButton *pBtn = new CButton();
		pBtn->Create("裁剪",WS_VISIBLE | WS_CHILD | WS_BORDER , 
			CRect(10 , 10, 100, 40), this, 123);
}
void CLeftView::InitCtlItem()
{
	this->mCombBox.Create(
      WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,
      CRect(10,10,200,100), this, IDC_SELECT_MODE);

	mCombBox.AddString("画线");
	mCombBox.AddString("画圈");
	mCombBox.AddString("填充");
	mCombBox.AddString("直线裁剪");
	mCombBox.AddString("多边形裁减");
	mCombBox.AddString("线消隐");
	mCombBox.AddString("Z-Buffer消隐");
	mCombBox.AddString("光照模型");
	//next is add submode in OnModeChange


	//mCombBox.AddString("Clipping");
}

void CLeftView::OnModeChange()
{
// 更改模式，通知Doc类，模式改变


	CString g_NameArr[][3]=
	{
		"DDA", "Bresham", "",
		"DDA", "Bresham", "",
		"扫描转换", "种子填充", "快速种子填充",
		"Surthland","",   "",
		"Surthland","",   "",
		"浮动水平线", "" , "",
		"线框模型", "填充模型", "",
		"phone shadering","Gaurand shadering",""
	};

	
	int index = mCombBox.GetCurSel();

	for(int i=0; i< MAX_SUB_STATE; i++) //为每一个子模式生成一个单选按钮
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

	//通知CDoc类
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

	// TODO:  在此添加您专用的创建代码
	
	for(int i=0; i< MAX_SUB_STATE; i++)
	{
			subArr[i].Create("aa", WS_CHILD|WS_VISIBLE|WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON, 
			CRect(50,40+50*i,150,70+50*i), this, IDC_SUB_SELECT1+i);
			subArr[i].ShowWindow(false);
	}


	return 0;
}
CCGAlgorithmDoc* CLeftView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgorithmDoc)));
	return (CCGAlgorithmDoc*)m_pDocument;
}