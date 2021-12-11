
#pragma once 
#include "../stdafx.h"
#include "Graphics.h"
#include "vector3.h"

namespace Drawing
{
	class Model: public Graphics
	{
		class	Poly
		{

		public:
			float A, B, C, D; //four parameter of the plan's equation
			float r, g, b;	  //stand for the color of the surface 

			bool Inside;	  //Inside is true when the current scope is in the poly
			vector<int>  VertexIndex;  //unlike polylist, vertext list , its subscript starts from 0  as usual
		};


		vector<Vector3>	VertexList;   //it's subscript start from 1
		vector<Vector3>	VtxListTemp;	//和顶点数目一样多，用于存储去掉小鼠部分后顶点坐标，每当顶点读入或者变换后，都要更新他的值
		vector<Poly>	PolyList;		//it's subscript start from 1, compatible with obj file
		
		//稍描转换相关的数据结构
		struct EdgeElem 
		{
			float	ymax;		//改变的两端点中较大的 y
			float  xmin;		//y值较小的对应的那个x值，即扫描线上的这点的x值
			float  delta;		//各边斜率的倒数
			int		ID;			//消隐的扫描线算法所特有的一项，表示改变所在的多边形号
			int		fp;			//AET中用到，表示已改边的x值为左端点的区间上最前面的多边形序号
			struct EdgeElem * next;
		};
		struct EdgeElem* ET[768];//扫描险桶
		struct EdgeElem * AET;	//活动边表 
		int ymax, ymin ;			// 最大的y值与最小的y值

		bool bFileLoaded;			//判断当前是否已经将文件载入
		CButton* pButton;			//显示文件对话框的按钮



		bool CreateET();		//根据多边形信息建立以p为首元素的边表,
		void SortList(EdgeElem* p);			//将该扫描线上的各边按x大小排序
		void MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL);
		void Remove(EdgeElem* &pHead,EdgeElem* &q);

		void UpdateTempVertex();//用于根据VertexList生成VtxListtmp， 并进行投影，并且更新PolyList的参数




		void FillArea();


		inline void exchange(float &a,float &b)
		{
			float temp;
			temp=a;
			a=b;
			b=temp;
		};
		inline void exchange(int  &a, int  &b)
		{
			int temp;
			temp=a;
			a=b;
			b=temp;
		};


	public:
		Model(CView *p);
		~Model();
		void InitList()
			{   //ensure that the list's index start from 1 ,not zero
				
				VertexList.clear();
				PolyList.clear();
				VtxListTemp.clear();

				VertexList.push_back(Vector3());
				PolyList.push_back(Poly());
				VtxListTemp.push_back(Vector3());
			}


		

		virtual bool	OpenObjFile();
		virtual bool	ReadObjFile(const char* FileName);		//根据文件名填充数据。
		virtual bool	GetPolyParam(Poly &poly);			//获取多边形所在的平面方程参数
		virtual void	Transform(Matrix<float>& M);
		virtual void	OnChar(UINT ch);



		virtual void ReceiveMsg(MSG& msg);
		
		
		
		void TestDraw();

		virtual void Draw();

		void GetColor(Poly &poly)
		{
			poly.r = 256.0 * rand()/RAND_MAX;
			poly.g = 256.0 * rand()/RAND_MAX;
			poly.b = 256.0 * rand()/RAND_MAX;
		}
	};
}
