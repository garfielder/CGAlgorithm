//定义一些程序中一些控件的宏
#pragma once 

#include <cmath>
#define IDC_SELECT_MODE		1010  //选择绘图类型的组合框ID
	
#define IDC_SUB_SELECT1		1011	//定义子模式的单选按钮的ID
#define IDC_SUB_SELECT2		1012
#define IDC_SUB_SELECT3		1013
#define IDC_SUB_SELECT		1014	

#define IDC_BTN_FILL		1015  //PolyFill中创建的那个按钮
#define IDC_3D_OPEN			1016  //Model中打开3D文件的对话框

#define MAX_SUB_STATE       3


#define RENDERCOLOR			0x00ff0000

enum DrawMode   //定义绘图类型
{
	LINE = 0,
	CIRCLE,
	FILL,
	CLIPPING,
	CLIPPOLYGON,
	LINECULLING,
	SCAN_ZBUFFER,
	LIGHTING
};

//if create a new mode, first add it's id here
enum SUBMODE
{
	DDA,
	BRESHAM,
	SEED_FILL,
	BETTER_SEED_FILL,
	SCAN_LINE,
	SUTHURLAND,
	WIRE_FRAME, //Used in scanline algorithm
	SOLID,
	PHONE,
	GAURAND,
	DEFAULT
};
//next is add the item to mcombBox in leftview.cpp

static void line(CDC* pDC, int x1, int y1, int x2, int y2, int color = RENDERCOLOR)
		{
			//transform
			//CPoint ptCenter;
			//CRect  rect		;	
			//pDC->GetClipBox(&rect);

			//ptCenter.x = (rect.left + rect.right)/2;
			//ptCenter.y = (rect.bottom + rect.top)/2;
			//
			//x1 -= ptCenter.x;
			//x2 -= ptCenter.x;

			//y1 -= ptCenter.y;
			//y2 -= ptCenter.y;
			
			CPoint pb(x1, y1);
			CPoint pe(x2, y2);
			float x,y;
			float L=max(abs(pe.x-pb.x),abs(pe.y-pb.y));
			float deltax=(pe.x-pb.x)/L;
			float  deltay=(pe.y-pb.y)/L;
			x=(float)pb.x;
			y=(float)pb.y;

			for(int i=0;i<L;i++)
			{
				x+=deltax;
				y+=deltay;
				pDC->SetPixel((int)x,(int)y, color);
			}

			pDC->SetPixel(x1, y1, color);
			pDC->SetPixel(x2, y2, color);
		}


static void  line2(CDC* pDC, int x1, int y1, int x2, int y2, float color1, float color2)
		{
			 
		
			CPoint pb(x1, y1);
			CPoint pe(x2, y2);
			float x,y;
			float L=max(abs(pe.x-pb.x),abs(pe.y-pb.y));
			float deltax=(pe.x-pb.x)/L;
			float  deltay=(pe.y-pb.y)/L;
			x=(float)pb.x;
			y=(float)pb.y;

			float colorstart = color1 ;
			float colorend = color2 ;
			float deltacolor = (colorend-colorstart)/L;
			float color = (int)colorstart;

			for(int i=0;i<L;i++)
			{
				x += deltax;
				y += deltay;
				color += deltacolor;
				pDC->SetPixel((int)x,(int)y, ((int)color));
			}

			pDC->SetPixel(x1, y1, color1);
			pDC->SetPixel(x2, y2, color2);
		}


static float fun(float x, float z) //在浮动水平线消隐中用到
{
	float y = pow(x, 2) + pow(z, 2);
	return y;
}