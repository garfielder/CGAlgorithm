
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "Vector3.h"


#include "Polygon.h"
#include "line.h"


namespace Drawing
{


	class Clip: public Graphics
	{
	public:
		enum STATE{INIT, CLIPPING, LINNING} sState;  // ��ǰ״̬




	public:
		Clip(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
		//	virtual SUBMODE GetCurState();

		virtual void Draw();
		virtual void ClipLine();

		virtual void Transform(Matrix<float>& M);
	protected:
		virtual CodeStruct CodePoint(CPoint p);


		

		~Clip();

	protected:
		//--��㣬�յ�-----------

		CButton* pButton;  // ע�ⲻҪ��CButton�����CButton button,����ָ��*pButton,����
							//���ٶ����������
	
		
		int xleft,xright, ytop, ybottom;

		CPoint pb, pe;
		CPoint newpb, newpe; //�ü����

		Polygon* pPoly;
		Line*	pLine;
        
	};
};