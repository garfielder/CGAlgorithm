#pragma once 
#include "./3DLoader.h"


namespace Drawing
{
	class Lighting: public Graphics
	{
	protected:
		class Point: public Vector3
		{
		public:
			Point():Vector3(){
			
			};
			Point(float x, float y, float z):Vector3(x,y,z){};
		public:

			float r,g, b;

			float xn,	yn,	zn;

			//used create vectors of vertexs
			vector<Vector3> temp;

		};


		class Light
		{
		public:
			Light(){
				Dir.x = -1.0; 
				Dir.y = -1.0;
				Dir.z = -1.0;
                
				Il = 1.0;
				Kd = 0.8;
			
			};
			void  SetDirection(float x, float y, float z)
			{
				Dir.x = x;
				Dir.y = y;
				Dir.z = z;
			};
		public:
			float Il;
			float Kd;

			Point Dir;
        };
		class Poly
		{

		public:
			float A, B, C, D; //four parameter of the plan's equation
			float r, g, b;	  //stand for the color of the surface 

			bool Inside;	  //Inside is true when the current scope is in the poly
			vector<int>  VertexIndex;  //unlike polylist, vertext list , its subscript starts from 0  as usual
		};

	
	protected:
		vector<Point>	VertexList;   //it's subscript start from 1
		vector<Point>	VtxListTemp;	//和顶点数目一样多，用于存储去掉小鼠部分后顶点坐标，每当顶点读入或者变换后，都要更新他的值
		vector<Poly>	PolyList;		//it's subscript start from 1, compatible with obj file
		vector<Poly>	PolyListTemp;    //进行稍描转换前， 将PolyList进行裁减，得到PolyListTemp
		vector<Vector3> VnList;
		
		//稍描转换相关的数据结构
		struct EdgeElem 
		{
			float	ymax;		//改变的两端点中较大的 y
			float  xmin;		//y值较小的对应的那个x值，即扫描线上的这点的x值
			float  delta;		//各边斜率的倒数
			float color;
			float deltacolor;
			float normal;
			float deltanormal;

			int		ID;			//消隐的扫描线算法所特有的一项，表示改变所在的多边形号
			int		fp;			//AET中用到，表示已改边的x值为左端点的区间上最前面的多边形序号
			struct EdgeElem * next;
		};
		struct EdgeElem* ET[768];//扫描险桶
		struct EdgeElem * AET;	//活动边表 
		int ymax, ymin ;			// 最大的y值与最小的y值
		
		virtual bool CreateET();		//根据多边形信息建立以p为首元素的边表,
		virtual void SortList(EdgeElem* p);			//将该扫描线上的各边按x大小排序
		virtual void MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL);
		virtual void Remove(EdgeElem* &pHead,EdgeElem* &q);
		virtual void FillArea();
		
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
		}
		


		
		//裁减相关
		int xleft,xright, ytop, ybottom;
		enum WinTag{LEFT, RIGHT, BOTTOM, TOP};
		void Clipping();
		bool IsInWindow(Vector3 p, WinTag tag);
		int	GetCrossPoint(Vector3 p1, Vector3 p2, WinTag tag);  //如果相交， 则在VtxList中生成新顶点，并返回索引


		

		bool bFileLoaded;			//判断当前是否已经将文件载入
		CButton* pButton;			//显示文件对话框的按钮
		Light  light;




		void UpdateTempVertex();//用于根据VertexList生成VtxListtmp， 并进行投影，并且更新PolyList的参数

	
	public:
		Lighting(CView *p);
		~Lighting();
		void InitList()
			{   //ensure that the list's index start from 1 ,not zero
				
				VertexList.clear();
				PolyList.clear();
				VtxListTemp.clear();
				VnList.clear();
				

				VertexList.push_back(Point());
				PolyList.push_back(Poly());
				VtxListTemp.push_back(Point());
				VnList.push_back(Vector3());
			}

		virtual bool	OpenObjFile();
		virtual bool	ReadObjFile(char* FileName);		//根据文件名填充数据。
		virtual bool	GetPolyParam(Poly &poly);			//获取多边形所在的平面方程参数
		virtual void	Transform(Matrix<float>& M);
		virtual void	OnChar(UINT ch);
		virtual void ReceiveMsg(MSG& msg);
	
		void TestDraw();
		virtual void Draw();
		void GetColor(Poly &poly);
		void GetVectorOfVertex();
	};
}
