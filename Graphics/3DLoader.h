
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
		vector<Vector3>	VtxListTemp;	//�Ͷ�����Ŀһ���࣬���ڴ洢ȥ��С�󲿷ֺ󶥵����꣬ÿ�����������߱任�󣬶�Ҫ��������ֵ
		vector<Poly>	PolyList;		//it's subscript start from 1, compatible with obj file
		
		//����ת����ص����ݽṹ
		struct EdgeElem 
		{
			float	ymax;		//�ı�����˵��нϴ�� y
			float  xmin;		//yֵ��С�Ķ�Ӧ���Ǹ�xֵ����ɨ�����ϵ�����xֵ
			float  delta;		//����б�ʵĵ���
			int		ID;			//������ɨ�����㷨�����е�һ���ʾ�ı����ڵĶ���κ�
			int		fp;			//AET���õ�����ʾ�Ѹıߵ�xֵΪ��˵����������ǰ��Ķ�������
			struct EdgeElem * next;
		};
		struct EdgeElem* ET[768];//ɨ����Ͱ
		struct EdgeElem * AET;	//��߱� 
		int ymax, ymin ;			// ����yֵ����С��yֵ

		bool bFileLoaded;			//�жϵ�ǰ�Ƿ��Ѿ����ļ�����
		CButton* pButton;			//��ʾ�ļ��Ի���İ�ť



		bool CreateET();		//���ݶ������Ϣ������pΪ��Ԫ�صı߱�,
		void SortList(EdgeElem* p);			//����ɨ�����ϵĸ��߰�x��С����
		void MergeList(EdgeElem *p,EdgeElem *q,EdgeElem* &pL);
		void Remove(EdgeElem* &pHead,EdgeElem* &q);

		void UpdateTempVertex();//���ڸ���VertexList����VtxListtmp�� ������ͶӰ�����Ҹ���PolyList�Ĳ���




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
		virtual bool	ReadObjFile(const char* FileName);		//�����ļ���������ݡ�
		virtual bool	GetPolyParam(Poly &poly);			//��ȡ��������ڵ�ƽ�淽�̲���
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
