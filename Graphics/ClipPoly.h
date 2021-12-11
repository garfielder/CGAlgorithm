
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"
#include "Polygon.h"
#include "line.h"


namespace Drawing
{


	class ClipPoly: public Graphics
	{
	public:
		enum STATE{INIT, CLIPPING, LINNING} sState;  // ��ǰ״̬
		enum WinTag{LEFT, RIGHT, BOTTOM, TOP};



	public:
		ClipPoly(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		//	virtual SUBMODE GetCurState();

		virtual void Draw();
		virtual void BeginClipPoly();
	protected:
		virtual CodeStruct CodePoint(CPoint p);
		
		bool	IsInWindow(Vector3 p, WinTag tag);
		bool	IsCross(Vector3 p1, Vector3 p2);
		Vector3	GetCrossPoint(Vector3 p1, Vector3 p2, WinTag tag);

		virtual void Transform(Matrix<float>& M);

		~ClipPoly();

	protected:
		//--��㣬�յ�-----------

		CButton* pButton;  // ע�ⲻҪ��CButton�����CButton button,����ָ��*pButton,����
							//���ٶ����������
	
		
		int xleft,xright, ytop, ybottom;


		Polygon* pPoly;

		vector<Vector3> InputList;
		vector<Vector3> OutputList;

        
	};
};