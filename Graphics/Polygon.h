
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"


namespace Drawing
{

	//一个面的结构
	class SurfaceElem  
	{
	public:
		SurfaceElem(){};
		~SurfaceElem(){};

		void push_back(int I)	{EdgeIndexArr.push_back(I);  }
		int size()				{	return EdgeIndexArr.size();	}
		int& operator[] (int i)	{return EdgeIndexArr[i];	}
		void clear()			{EdgeIndexArr.clear();}

	protected:
	private:
		vector<int> EdgeIndexArr;  //存放边的索引
	};

	//多边形的定义
	class Polygon: public Graphics
	{
	public:
		Polygon(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
	//	virtual SUBMODE GetCurState();
	
		virtual void Draw();

		virtual void Transform(Matrix<float>& M);
	
		// 新增一个函数，用于索引第nPolyIndex个多边形的nVertexIndex个顶点,
		Vector3& V(int nPolyIndex,int nVertexIndex);	
		int	    EdgeCnt(int i){ return SurfaceTable[i].size(); };	//第i个多边形的边的数目

		int		GetSurfaceCnt(){ return SurfaceTable.size(); };

	public:
		//--起点，终点-----------
		enum STATE{INIT, ADDING, ENCLOSE} sState;  // 当前状态
	
		vector<Vector3> VertexTable;
		vector<Edge>  EdgeTable;

							
		vector<SurfaceElem>  SurfaceTable;
		SurfaceElem sElem;		 //SurfaceTable 中存放的元素，即边的索引的序列
	};
};