
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"


namespace Drawing
{

	//һ����Ľṹ
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
		vector<int> EdgeIndexArr;  //��űߵ�����
	};

	//����εĶ���
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
	
		// ����һ������������������nPolyIndex������ε�nVertexIndex������,
		Vector3& V(int nPolyIndex,int nVertexIndex);	
		int	    EdgeCnt(int i){ return SurfaceTable[i].size(); };	//��i������εıߵ���Ŀ

		int		GetSurfaceCnt(){ return SurfaceTable.size(); };

	public:
		//--��㣬�յ�-----------
		enum STATE{INIT, ADDING, ENCLOSE} sState;  // ��ǰ״̬
	
		vector<Vector3> VertexTable;
		vector<Edge>  EdgeTable;

							
		vector<SurfaceElem>  SurfaceTable;
		SurfaceElem sElem;		 //SurfaceTable �д�ŵ�Ԫ�أ����ߵ�����������
	};
};