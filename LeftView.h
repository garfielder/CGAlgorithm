#pragma once
#include "MyHead.h"

#include <vector>
using namespace std;


#include "CGAlgorithmDoc.h"

// CLeftView ������ͼ

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    

	//second ,������Ӧ����ϢӰ�亯��
	afx_msg void OnModeChange();				//ѡ����Ӧ����ģʽ
	afx_msg void OnSub1();
	afx_msg void OnSub2();
	afx_msg void OnSub3();

	afx_msg void OnBtnFill();
	afx_msg void On3DOpen();
	//��һ��ȥ.cpp������
	DECLARE_MESSAGE_MAP()


public:
	
	afx_msg void OnBnClickedButton1();
	void InitCtlItem();		//����һЩ�ؼ�

protected:
	CComboBox mSelectMode;
	//CButton *pSub1;
	//CButton *pSub2;
	//CButton *pSub3;

	CButton  subArr[3];			//MAX_SUB_STATE 
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


