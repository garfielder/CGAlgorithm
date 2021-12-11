
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


		// ִ������㷨, ʹ����ԭʼ�ĵݹ麯�������������׾Ͱ�ϵͳ�Ķ�ջ���ľ�(x, y)������
		virtual void SeedFill(CDC *pDC,int x,int y);
		
		//���ö�ջ��ͬʱ�����˵����֮���������
		virtual void SeedFillOptimized(CDC* pDC, int x, int y);


		virtual void Transform(Matrix<float>& M){};

		 ~PolyFill();

	protected:
		//--��㣬�յ�-----------
		enum STATE{POLY, WTFORSEED,FILLED} sState;  // ��ǰ״̬
		CButton* pButton;  // ע�ⲻҪ��CButton�����CButton button,����ָ��*pButton,����
						//���ٶ����������
		CPoint pSeed;	//����
		Polygon* pPoly;		

	//  ɨ��ת�����

		struct EdgeElem 
		{
			float	ymax;		//�ı�����˵��нϴ�� y
			float  xmin;		//yֵ��С�Ķ�Ӧ���Ǹ�xֵ����ɨ�����ϵ�����xֵ
			float  delta;		//����б�ʵĵ���
			struct EdgeElem * next;
		};

		struct EdgeElem* ET[768];//ɨ����Ͱ
		struct EdgeElem * AET;
		int	   ytop,ybottom;		//����ε����¿��
		bool CreateET();		//���ݶ������Ϣ������pΪ��Ԫ�صı߱�,
		void SortList(EdgeElem* p);			//����ɨ�����ϵĸ��߰�x��С����
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