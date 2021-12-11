//Matrix.h
//参考张耀仁《C++ 语言程序设计与应用》


#pragma once 

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>


#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setprecision;
using std::ios;
using std::cerr;
using std::string;
using std::vector;

inline void  Check(bool ErrorCondition, const string&  Message = "Requirement failed")
{
	if (ErrorCondition)
	{cerr << Message << endl; exit(1);}
}


template <class T>
class Matrix
{
private:
	int M, N;
	T** A;
	void Create(int, int);
	
public:
	// -- 声明构造函数-------------------
	Matrix():M(0),N(0){};
	Matrix(int, int);
	Matrix(int, int, const T*);
	//--- 声明拷贝构造函数
	Matrix(const Matrix<T> &);
	//---声明析构函数
	~Matrix();

	//operator
	Matrix<T> operator=( Matrix<T> &);
	Matrix<T> operator+(const Matrix<T> &);
	Matrix<T> operator-(const Matrix<T> &);
	Matrix<T> operator*(const Matrix<T> &);

	T* operator[](int i){return A[i];}

	void Display();

	void SetCol(int, vector<T>&);
	void SetRow(int, vector<T>&);
	vector<T> PickCol(int);
	vector<T> PickRow(int);

	//--交换矩阵中的两列或两行-------
	void ExchangeCol(int, int,int pos=1);			
	void ExchangeRow(int, int,int pos=1);

	void Simplify();

};

//---------- 成员函数的定义---------------

template <class T>
void Matrix<T>::Create(int Row, int Col)
{ 
	Check((Row <1 ||Col < 1),"矩阵构造错误，行列非法");
	M = Row;
	N = Col;
	A = new T* [M+1];
	A[0] = new T [M*N+1];
	A[1] = A[0];

	for(int i = 2; i<= M; i++)
		A[i] = A[i-1] + N;
};

template <class T>
Matrix<T>::Matrix(int Row, int Col)
{
	Create(Row, Col);
	return;
}

template <class T>
Matrix<T>::Matrix(int Row, int Col, const T* V)
{
	Create(Row, Col);
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=N; j++)
			A[i][j] = V[(i-1)*Col+(j-1)];
	return;
}



template <class T>
Matrix<T>::Matrix(const Matrix<T>& OldM)
{
	Create(OldM.M, OldM.N);
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=N; j++)
			A[i][j] = OldM.A[i][j];
}

template  <class T>
Matrix<T>::~Matrix()
{
	if(M!=0 && N!=0)
	{
		delete[] A[0];
		delete[] A;
	}
}
 
//-------重载一些运算符----------------
template <class T>
Matrix<T>
Matrix<T>::operator = (Matrix<T>& M2)
{
	//if((M != M2.M) || (N != M2.N))
	//	Create(M2.M, M2.N);
	

	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=N; j++)
			A[i][j] =  M2.A[i][j];

	return *this;
    
}

template <class T>
Matrix<T>
Matrix<T>::operator + (const Matrix<T>& M2)
{
	Check((M != M2.M) || (N != M2.N),
		"矩阵加法运算错误，矩阵大小不同");
	
	Matrix<T> temp(M, N);
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=N; j++)
			temp.A[i][j] =  A[i][j] + M2.A[i][j];

	return temp;
}

template <class T>
Matrix<T>
Matrix<T>::operator - (const Matrix<T>& M2)
{
	Check((M != M2.M) || (N != M2.N),
		"矩阵加法运算错误，矩阵大小不同");
	
	Matrix<T> temp(M, N);
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=N; j++)
			temp.A[i][j] =  A[i][j] - M2.A[i][j];

	return temp;
}

template <class T>
Matrix<T>
Matrix<T>::operator * (const Matrix<T>& M2)
{
	Check((N != M2.M),
		"矩阵乘法运算错误，矩阵大小不同");

	
	
	Matrix<T> temp(M, M2.N);

	
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <=M2.N; j++)				//我曾将此处改作j<N,会出现这种情况，单步调试时没关系
		{											//， 但Ctrl+F5时有问题,这正体现了debug与Release的区别.				
			temp.A[i][j] = 0.0;  //?0 or 0.0
			for(int k = 1; k <= N; k++)
				temp.A[i][j] += A[i][k] * M2.A[k][j];
		}

	return temp;
}



template <class T>
void Matrix<T>::Display()
{
	cout<< setiosflags(ios::right)
		<< setiosflags(ios::fixed)
		<< setiosflags(ios::showpoint)
		<< setprecision(4);

			
	for(int i = 1; i <= M; i++)
	{
		for(int j = 1; j<=N; j++) 
			cout << setw(10) << A[i][j] << " ";
		cout<< endl;
	}

}

template <class T>
void Matrix<T>::SetCol(int j, vector<T>& V1)
{
	Check(M != V1.size(), "SetCol中参数有误，向量个数与每列元素个数不符");
	for( int i = 1; i <= M; i++)
		A[i][j] = V1[i-1];
	return;
}

template <class T>
vector<T> Matrix<T>::PickCol(int I)
{

	vector<T> TempV(M);
	for( int i = 1; i <= M; i++)
		TempV[i-1] = A[i][I];

	return TempV;
}

template <class T>
void Matrix<T>::SetRow(int I, vector<T>& V1)
{
	Check(M != V1.size(), "SetRow中参数有误，向量个数与每行元素个数不符");
	for( int j = 1; j <= M; j++)
		A[I][j] = V1[j-1];
	return;
}

template <class T>
vector<T> Matrix<T>::PickRow(int I)
{
	vector<T> TempV(M);
	for( int j = 1; j <= M; j++)
		TempV[j-1] = A[I][j];

	return TempV;
}

template <class T>
void Matrix<T>::ExchangeCol(int i,int j, int pos)
{
	Check((i<1 || i>N) || (j<1 || j>N),
		"ExchangeCol中参数越界");

	vector<T> V1, V2;
	
	V1 = this->PickCol(i);
	V2 = this->PickCol(j);

	//this->SetCol(j, V1);
	//this->SetCol(i, V2);
}

template <class T>
void Matrix<T>::ExchangeRow(int i,int j, int pos)
{
	Check((i<1 || i>M) || (j<1 || j>M),
		"ExchangeRow中参数越界");

	vector<T> V1, V2;
	
	V1 = this->PickRow(i);
	V2 = this->PickRow(j);

	this->SetRow(j, V1);
	this->SetRow(i, V2);
}

template <class T>
void Matrix<T>::Simplify()
{
	int len = M<N ? M : N;
	//for(int k = 1; k <= len-1; k++)
	//{
	//	//寻找主元
	//	int maxi,maxj;
	//	maxi = maxj = k;
	//	
	//	for(int i = k; i <= len; i++)
	//		for(int j = k; j <= len; j++)
	//			if(A[i][j] > A[maxi][maxj])
	//			{
	//				maxi = i;
	//				maxj = j;
	//			}
	//	
	//	//将主元交换到左上角
	//	ExchangeRow(k, maxi);
	//	ExchangeCol(k, maxj);

	//	for(int i = k+1; i <= len; i++)
	//		A[i][k] = A[i][k] / A[k][k];

	//	Display();
 //       
	//	for(int i = k+1; i <= len; i++)
	//		for(int j = k+1; j <= len; j++)
	//			A[i][j] = A[i][j] - A[k][j] * A[i][k];
	//	for(int i = k+1; i <= len; i++)
	//		A[i][k] = 0;
	//	

	//	cout<<"_____________________________"<<endl;
	//	this ->Display();

	//		cout<<"_____________________________"<<endl;

	//}
}