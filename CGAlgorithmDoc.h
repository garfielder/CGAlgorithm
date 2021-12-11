// CGAlgorithmDoc.h :  CCGAlgorithmDoc 类的接口
//


#pragma once
#include "./graphics/graphics.h"

class CCGAlgorithmDoc : public CDocument
{
protected: // 仅从序列化创建
	CCGAlgorithmDoc();
	DECLARE_DYNCREATE(CCGAlgorithmDoc)

// 属性
public:

// 操作
public:

// 重写
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
	CView*   GetLeftView(void);
	CView*	GetRightView(void);
	void	ReceiveMSG(MSG &msg);


protected:
	//定义清除pGraph的指针，保证pGraph在不指向任何对象是为NULL
	void ClearpGraph();


// 实现
public:
	virtual ~CCGAlgorithmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

	Drawing::Graphics* pGraph;
	

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


