#include "stdafx.h"
#include "Graphics.h"
using namespace std;
namespace Drawing
{
	void Graphics::ReceiveMsg(MSG& msg){};
	void Graphics::OnChar(UINT ch){};
	void Graphics::OnLeftBtnDown(CPoint p){};
	void Graphics::OnRightBtnDown(CPoint p){};
	void Graphics::OnCmdBtnDown(UINT ID){};

	void Graphics::Draw(){};
	void Graphics::DispHintInfo(CString str)
	{
        CDC* pDC = pView->GetDC();
		
		if(str.GetLength()!=0)
			HintInfo = str;

		CRect rect;
		pDC->GetClipBox(rect);

		pDC->TextOut(rect.left+10, rect.bottom-20, HintInfo);

	}

}