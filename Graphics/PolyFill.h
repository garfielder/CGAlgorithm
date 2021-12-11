
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"


#include "Polygon.h"


namespace Drawing
{

	class PolyFill: public Graphics
	{
	public:
		PolyFill(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		//	virtual SUBMODE GetCurState();

		virtual void Draw();
		virtual void FillArea();


		// 执行填充算法, 使用最原始的递归函数方法，很容易就把系统的堆栈消耗尽(x, y)是种子
		virtual void SeedFill(CDC *pDC,int x,int y);
		
		//利用堆栈，同时利用了点与点之间的连贯性
		virtual void SeedFillOptimized(CDC* pDC, int x, int y);


		virtual void Transform(Matrix<float>& M){};

		 ~PolyFill();

	protected:
		//--起点，终点-----------
		enum STATE{POLY, WTFORSEED,FILLED} sState;  // 当前状态
		CButton* pButton;  // 注意不要把CButton定义成CButton button,而用指针*pButton,否则
						//销毁对象会出问题的
		CPoint pSeed;	//种子
		Polygon* pPoly;		

	//  扫描转换相关

		struct EdgeElem 
		{
			float	ymax;		//改变的两端点中较大的 y
			float  xmin;		//y值较小的对应的那个x值，即扫描线上的这点的x值
			float  delta;		//各边斜率的倒数
			struct EdgeElem * next;
		};

		struct EdgeElem* ET[768];//扫描险桶
		struct EdgeElem * AET;
		int	   ytop,ybottom;		//多边形的上下跨度
		bool CreateET();		//根据多边形信息建立以p为首元素的边表,
		void SortList(EdgeElem* p);			//将该扫描线上的各边按x大小排序
		void MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL);
		void Remove(EdgeElem* &pHead,EdgeElem* &q);

		void PolyFill::ScanLine();

		inline void exchange(float &a,float &b)
		{
			float temp;
			temp=a;
			a=b;
			b=temp;
		};

		

	};
};