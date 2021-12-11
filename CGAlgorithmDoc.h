// CGAlgorithmDoc.h :  CCGAlgorithmDoc ��Ľӿ�
//


#pragma once
#include "./graphics/graphics.h"

class CCGAlgorithmDoc : public CDocument
{
protected: // �������л�����
	CCGAlgorithmDoc();
	DECLARE_DYNCREATE(CCGAlgorithmDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
	CView*   GetLeftView(void);
	CView*	GetRightView(void);
	void	ReceiveMSG(MSG &msg);


protected:
	//�������pGraph��ָ�룬��֤pGraph�ڲ�ָ���κζ�����ΪNULL
	void ClearpGraph();


// ʵ��
public:
	virtual ~CCGAlgorithmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

	Drawing::Graphics* pGraph;
	

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


