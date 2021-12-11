
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"

namespace Drawing
{
	class Circle: public Graphics
	{
	public:
		Circle(CView* p);

		virtual void ReceiveMsg(MSG& msg);
		virtual void OnChar(UINT ch);
		virtual void OnLeftBtnDown(CPoint p);
		virtual void OnRightBtnDown(CPoint p);
		virtual	void OnCmdBtnDown(UINT ID);
	//	virtual SUBMODE GetCurState();
		virtual void Transform(Matrix<float>& M){};
	
		virtual void Draw();
		virtual void DDACircle();
		virtual void BreshamCircle() const;
	protected:
		//--��㣬�յ�-----------
		enum STATE{ONE, TWO} sState;  //ָʾ��ǰ�Ѿ�ʰȡ���˼����㣬һ�������Բ�ģ�
										//�������ɼ���뾶
		CPoint pCen;  //Բ��
		int iRadius;	//�뾶
		
		

	};
};