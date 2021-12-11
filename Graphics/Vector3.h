
#pragma once
#include <vector>
#include "Matrix.h"

using namespace std;

namespace Drawing
{
	class  Vector3
	{
	public:

		Vector3(float xx, float yy, float zz): x(xx), y(yy), z(zz){};
		Vector3(): x(0), y(0), z(0){};

		Vector3(const Vector3& p)
		{
			x = p.x;
			y = p.y;
			z = p.z;
		};

		void  operator = (const Vector3& p){ x = p.x; y = p.y; z = p.z; }
		Vector3 operator + (const Vector3& p){return Vector3(p.x + x, p.y + y, p.z + z);}
		Vector3 operator - (const Vector3& p){return Vector3(p.x - x, p.y - y, p.z - z);}

		Vector3 Transform(Matrix<float> & M)
		{
			float arr[4]={x, y, z, 1};
			Matrix<float> N(4, 1, arr);
			N = M * N;
			x = N[1][1]/N[4][1];
			y = N[2][1]/N[4][1];
			z = N[3][1]/N[4][1];
			return *this;
		}

		

		//void output(){ cout<<"("<<x <<" "<<y<<" "<<z<<")"<<endl;}

	public:
		float x, y, z;
	};

	class Edge   //用在EdgeTable中，用来存放边的起始顶点的序号
	{
	public:
		Edge(): start(0),end(0){};
		Edge(int x, int y): start(x),end(y){}; 
		Edge(const Edge& e)
		{
			start = e.start;
			end = e.end;

		};

		void operator = (Edge e)
		{
			start = e.start;
			end = e.end;
		}

	public:
		int start;
		int end;
	};

	class	CodeStruct  //裁减算法编码后结构
	{ public:
		int xl;
		int xr;
		int yt;
		int yb;
	};
	
};
