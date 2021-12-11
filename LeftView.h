#pragma once
#include "MyHead.h"

#include <vector>
using namespace std;


#include "CGAlgorithmDoc.h"

// CLeftView 窗体视图

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();
public:
	CCGAlgorithmDoc* GetDocument() const;


protected:
	CComboBox mCombBox;

public:
	enum { IDD = IDD_LEFTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    

	//second ,定义相应的消息影射函数
	afx_msg void OnModeChange();				//选择相应绘制模式
	afx_msg void OnSub1();
	afx_msg void OnSub2();
	afx_msg void OnSub3();

	afx_msg void OnBtnFill();
	afx_msg void On3DOpen();
	//下一步去.cpp终声明
	DECLARE_MESSAGE_MAP()


public:
	
	afx_msg void OnBnClickedButton1();
	void InitCtlItem();		//创建一些控件

protected:
	CComboBox mSelectMode;
	//CButton *pSub1;
	//CButton *pSub2;
	//CButton *pSub3;

	CButton  subArr[3];			//MAX_SUB_STATE 
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


