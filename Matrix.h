#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "stdinc.h"

#include <stdlib.h>
#include <memory.h>

#include "FloatMath.h"
#include "Logger.h"

class Matrix  
{	
public:
	// 基础构造函数
	Matrix();		
	// 指定行列构造函数
	Matrix(int nRows, int nCols);		
	// 指定数据构造函数
	Matrix(int nRows, int nCols, float value[]);	
	// 方阵构造函数
	Matrix(int nSize);				
	// 指定数据方阵构造函数
	Matrix(int nSize, float value[]);	
	// 拷贝构造函数
	Matrix(const Matrix& other);	
	// 初始化矩阵	
	bool Init(int nRows, int nCols);	
	// 将方阵初始化为单位矩阵
	bool MakeUnitMatrix(int nSize);		
	// 析构函数
	~Matrix();								


	// 设置指定元素的值
	bool SetElement(int nRow, int nCol, float value)
	{
		if (nCol < 0 || nCol >= nNumColumns || nRow < 0 || nRow >= nNumRows)
			return false;						// array bounds error
		if (pData == NULL)
			return false;							// bad pointer error

		pData[nCol + nRow * nNumColumns] = value;

		return true;
	}

	// 获取指定元素的值
	float GetElement(int nRow, int nCol) const	
	{
		return pData[nCol + nRow * nNumColumns] ;
	}

	// 获取矩阵的列数
	int GetNumColumns() const
	{
		return nNumColumns;
	}

	// 获取矩阵的行数
	int GetNumRows() const
	{
		return nNumRows;
	}

	// 获取矩阵的指定行矩阵
	int GetRowVector(int nRow, float* pVector) const
	{
		if (pVector == NULL)
			delete pVector;

		pVector = new float[nNumColumns];
		//	ASSERT(pVector != NULL);

		for (int j=0; j<nNumColumns; ++j)
			pVector[j] = GetElement(nRow, j);

		return nNumColumns;
	}

	// 获取矩阵的指定列矩阵
	int GetColVector(int nCol, float* pVector) const
	{
		if (pVector == NULL)
			delete pVector;

		pVector = new float[nNumRows];
		//ASSERT(pVector != NULL);

		for (int i=0; i<nNumRows; ++i)
			pVector[i] = GetElement(i, nCol);

		return nNumRows;
	}

	// 设置矩阵的值
	void SetData(float value[])
	{
		// empty the memory
		memset(pData, 0, sizeof(float) * nNumColumns*nNumRows);
		// copy data
		memcpy(pData, value, sizeof(float)*nNumColumns*nNumRows);
	}

	// 获取矩阵的值
	float* GetData() const
	{
		return pData;
	}


	float& operator[](int n)
	{		
		return pData[n];
	}

	Matrix& operator=(const Matrix& other)
	{
		if (&other != this)
		{
			bool bSuccess = Init(other.GetNumRows(), other.GetNumColumns());
			//ASSERT(bSuccess);

			// copy the pointer
			memcpy(pData, other.pData, sizeof(float)*nNumColumns*nNumRows);
		}

		// finally return a reference to ourselves
		return *this ;
	}

	bool operator==(const Matrix& other) const
	{
		// 首先检查行列数是否相等
		if (nNumColumns != other.GetNumColumns() || nNumRows != other.GetNumRows())
			return false;

		for (int i=0; i<nNumRows; ++i)
		{
			for (int j=0; j<nNumColumns; ++j)
			{
				if (GetElement(i, j) != other.GetElement(i, j))
					return false;
			}
		}

		return true;
	}

	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}

	Matrix	operator+(const Matrix& other) const
	{
		// 首先检查行列数是否相等
		//ASSERT (nNumColumns == other.GetNumColumns() && nNumRows == other.GetNumRows());

		// 构造结果矩阵
		Matrix	result(*this) ;		// 拷贝构造
		// 矩阵加法
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				result.SetElement(i, j, result.GetElement(i, j) + other.GetElement(i, j)) ;
		}

		return result ;
	}

	Matrix& operator+=(const Matrix& other)
	{		
		// 矩阵加法
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				SetElement(i, j, GetElement(i, j) + other.GetElement(i, j)) ;
		}

		return *this;
	}

	Matrix	operator-(const Matrix& other) const
	{
		// 首先检查行列数是否相等
		//ASSERT (nNumColumns == other.GetNumColumns() && nNumRows == other.GetNumRows());

		// 构造目标矩阵
		Matrix	result(*this) ;		// copy ourselves
		// 进行减法操作
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				result.SetElement(i, j, result.GetElement(i, j) - other.GetElement(i, j)) ;
		}

		return result ;
	}

	Matrix& operator-=(const Matrix& other)
	{		
		// 进行减法操作
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				SetElement(i, j, GetElement(i, j) - other.GetElement(i, j)) ;
		}

		return *this;
	}

	Matrix	operator*(float value) const
	{
		// 构造目标矩阵
		Matrix	result(*this) ;		// copy ourselves
		// 进行数乘
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				result.SetElement(i, j, result.GetElement(i, j) * value) ;
		}

		return result ;
	}

	Matrix& operator*=(float value)
	{		
		// 进行数乘
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				SetElement(i, j, GetElement(i, j) * value) ;
		}

		return *this;
	}

	Matrix	operator*(const Matrix& other) const
	{
		// 首先检查行列数是否符合要求

		//ASSERT (nNumColumns == other.GetNumRows());

		// construct the object we are going to return
		Matrix	result(nNumRows, other.GetNumColumns()) ;

		// 矩阵乘法，即
		//
		// [A][B][C]   [G][H]     [A*G + B*I + C*K][A*H + B*J + C*L]
		// [D][E][F] * [I][J] =   [D*G + E*I + F*K][D*H + E*J + F*L]
		//             [K][L]
		//
		float	value ;
		for (int i = 0 ; i < result.GetNumRows() ; ++i)
		{
			for (int j = 0 ; j < other.GetNumColumns() ; ++j)
			{
				value = 0.0 ;
				for (int k = 0 ; k < nNumColumns ; ++k)
				{
					value += GetElement(i, k) * other.GetElement(k, j) ;
				}

				result.SetElement(i, j, value) ;
			}
		}

		return result ;
	}

	Matrix& operator/=(float value)
	{		
		// 进行数除
		for (int i = 0 ; i < nNumRows ; ++i)
		{
			for (int j = 0 ; j <  nNumColumns; ++j)
				SetElement(i, j, GetElement(i, j) / value) ;
		}

		return *this;
	}

	// 矩阵的转置
	Matrix Transpose();	
	// 实矩阵求逆的全选主元高斯－约当法
	bool Invert();      	                                             
	// 求行列式值的全选主元高斯消去法
	float Det();  
	// 求矩阵秩的全选主元高斯消去法
	int Rank();            

protected:
	int	nNumColumns;			// 矩阵列数
	int	nNumRows;				// 矩阵行数
	float*	pData;			// 矩阵数据缓冲区

public:
	bool FloatEqual( Matrix other );
	float Norm();
	void PrintMatrix();
	void OutPutMatrix();
	static Matrix Rpy2Rot(Angle angleA, Angle angleB, Angle angleC );		//	通过角度构建反解矩阵
	void InvertAngles( Angle &rollX, Angle &pitchY, Angle &yawZ );			//	通过旋转矩阵反解角度
};


class LEquations
{
public:
	Matrix mCoef;
	float* mConst;
	float* mRoot;

	LEquations();	
	LEquations(int num);
	bool Init(int num);

	~LEquations();

	// 全选主元高斯消去法
	bool GetRoot();
private:
	int equationNum;

	void Destroy();
};

#endif // __MATRIX_H__
