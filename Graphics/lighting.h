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
		vector<Point>	VtxListTemp;	//�Ͷ�����Ŀһ���࣬���ڴ洢ȥ��С�󲿷ֺ󶥵����꣬ÿ�����������߱任�󣬶�Ҫ��������ֵ
		vector<Poly>	PolyList;		//it's subscript start from 1, compatible with obj file
		vector<Poly>	PolyListTemp;    //��������ת��ǰ�� ��PolyList���вü����õ�PolyListTemp
		vector<Vector3> VnList;
		
		//����ת����ص����ݽṹ
		struct EdgeElem 
		{
			float	ymax;		//�ı�����˵��нϴ�� y
			float  xmin;		//yֵ��С�Ķ�Ӧ���Ǹ�xֵ����ɨ�����ϵ�����xֵ
			float  delta;		//����б�ʵĵ���
			float color;
			float deltacolor;
			float normal;
			float deltanormal;

			int		ID;			//������ɨ�����㷨�����е�һ���ʾ�ı����ڵĶ���κ�
			int		fp;			//AET���õ�����ʾ�Ѹıߵ�xֵΪ��˵����������ǰ��Ķ�������
			struct EdgeElem * next;
		};
		struct EdgeElem* ET[768];//ɨ����Ͱ
		struct EdgeElem * AET;	//��߱� 
		int ymax, ymin ;			// ����yֵ����С��yֵ
		
		virtual bool CreateET();		//���ݶ������Ϣ������pΪ��Ԫ�صı߱�,
		virtual void SortList(EdgeElem* p);			//����ɨ�����ϵĸ��߰�x��С����
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
		


		
		//�ü����
		int xleft,xright, ytop, ybottom;
		enum WinTag{LEFT, RIGHT, BOTTOM, TOP};
		void Clipping();
		bool IsInWindow(Vector3 p, WinTag tag);
		int	GetCrossPoint(Vector3 p1, Vector3 p2, WinTag tag);  //����ཻ�� ����VtxList�������¶��㣬����������


		

		bool bFileLoaded;			//�жϵ�ǰ�Ƿ��Ѿ����ļ�����
		CButton* pButton;			//��ʾ�ļ��Ի���İ�ť
		Light  light;




		void UpdateTempVertex();//���ڸ���VertexList����VtxListtmp�� ������ͶӰ�����Ҹ���PolyList�Ĳ���

	
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
		virtual bool	ReadObjFile(char* FileName);		//�����ļ���������ݡ�
		virtual bool	GetPolyParam(Poly &poly);			//��ȡ��������ڵ�ƽ�淽�̲���
		virtual void	Transform(Matrix<float>& M);
		virtual void	OnChar(UINT ch);
		virtual void ReceiveMsg(MSG& msg);
	
		void TestDraw();
		virtual void Draw();
		void GetColor(Poly &poly);
		void GetVectorOfVertex();
	};
}
