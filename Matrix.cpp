#include "stdafx.h"
#include "Matrix.h"

#define MatrixLog gLog
//////////////////////////////////////////////////////////////////////
// 基本构造函数
//////////////////////////////////////////////////////////////////////
Matrix::Matrix()
{
	nNumColumns = 1;
	nNumRows = 1;
	pData = NULL;
	bool bSuccess = Init(nNumRows, nNumColumns);
	//ASSERT(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 指定行列构造函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
//////////////////////////////////////////////////////////////////////
Matrix::Matrix(int nRows, int nCols)
{
	nNumRows = nRows;
	nNumColumns = nCols;
	pData = NULL;
	bool bSuccess = Init(nNumRows, nNumColumns);
	//ASSERT(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 指定值构造函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
// 3. float value[] - 一维数组，长度为nRows*nCols，存储矩阵各元素的值
//////////////////////////////////////////////////////////////////////
Matrix::Matrix(int nRows, int nCols, float value[])
{
	nNumRows = nRows;
	nNumColumns = nCols;
	pData = NULL;
	bool bSuccess = Init(nNumRows, nNumColumns);
	//ASSERT(bSuccess);

	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// 方阵构造函数
//
// 参数：
// 1. int nSize - 方阵行列数
//////////////////////////////////////////////////////////////////////
Matrix::Matrix(int nSize)
{
	nNumRows = nSize;
	nNumColumns = nSize;
	pData = NULL;
	bool bSuccess = Init(nSize, nSize);
	//ASSERT (bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 方阵构造函数
//
// 参数：
// 1. int nSize - 方阵行列数
// 2. float value[] - 一维数组，长度为nRows*nRows，存储方阵各元素的值
//////////////////////////////////////////////////////////////////////
Matrix::Matrix(int nSize, float value[])
{
	nNumRows = nSize;
	nNumColumns = nSize;
	pData = NULL;
	bool bSuccess = Init(nSize, nSize);
	//ASSERT (bSuccess);

	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// 拷贝构造函数
//
// 参数：
// 1. const Matrix& other - 源矩阵
//////////////////////////////////////////////////////////////////////
Matrix::Matrix(const Matrix& other)
{
	nNumColumns = other.GetNumColumns();
	nNumRows = other.GetNumRows();
	pData = NULL;
	bool bSuccess = Init(nNumRows, nNumColumns);
	//ASSERT(bSuccess);

	// copy the pointer
	memcpy(pData, other.pData, sizeof(float)*nNumColumns*nNumRows);
}

//////////////////////////////////////////////////////////////////////
// 析构函数
//////////////////////////////////////////////////////////////////////
Matrix::~Matrix()
{
	if (pData)
	{
		delete[] pData;
		pData = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// 初始化函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
//
// 返回值：bool 型，初始化是否成功
//////////////////////////////////////////////////////////////////////
bool Matrix::Init(int nRows, int nCols)
{
	if (pData)
	{
		delete[] pData;
		pData = NULL;
	}

	nNumRows = nRows;
	nNumColumns = nCols;
	int nSize = nCols*nRows;
	if (nSize < 0)
		return false;

	// 分配内存
	pData = new float[nSize];

	if (pData == NULL) return false;					// 内存分配失败

	//if (IsBadReadPtr(pData, sizeof(float) * nSize))	return false;

	// 将各元素值置0
	memset(pData, 0, sizeof(float) * nSize);

	return true;
}

//////////////////////////////////////////////////////////////////////
// 将方阵初始化为单位矩阵
//
// 参数：
// 1. int nSize - 方阵行列数
//
// 返回值：bool 型，初始化是否成功
//////////////////////////////////////////////////////////////////////
bool Matrix::MakeUnitMatrix(int nSize)
{
	if (! Init(nSize, nSize))
		return false;

	for (int i=0; i<nSize; ++i)
		for (int j=0; j<nSize; ++j)
			if (i == j)
				SetElement(i, j, 1);

	return true;
}

//////////////////////////////////////////////////////////////////////
// 矩阵的转置
//
// 参数：无
//
// 返回值：Matrix 转置后的矩阵
//////////////////////////////////////////////////////////////////////
Matrix Matrix::Transpose()
{
	// 构造目标矩阵
	Matrix	Trans(nNumColumns, nNumRows);

	// 转置各元素
	for (int i = 0 ; i < nNumRows ; ++i)
	{
		for (int j = 0 ; j < nNumColumns ; ++j)
			Trans.SetElement(j, i, GetElement(i, j)) ;
	}

	return Trans;
}

//////////////////////////////////////////////////////////////////////
// 实矩阵求逆的全选主元高斯－约当法
//
// 参数：无
//
// 返回值：bool型，求逆是否成功
//////////////////////////////////////////////////////////////////////
bool Matrix::Invert()
{
	int *pnRow, *pnCol,i,j,k,l,u,v;
	float d = 0, p = 0;

	// 分配内存
	pnRow = new int[nNumColumns];
	pnCol = new int[nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return false;

	// 消元
	for (k=0; k<=nNumColumns-1; k++)
	{ 
		d=0.0;
		for (i=k; i<=nNumColumns-1; i++)
		{
			for (j=k; j<=nNumColumns-1; j++)
			{ 
				l=i*nNumColumns+j; 
				p=fabs(pData[l]);
				if (p>d) 
				{ 
					d=p; 
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}

		// 失败
		if ( d  < EPS)
		{
			delete[] pnRow;
			delete[] pnCol;		
			return false;
		}

		if (pnRow[k] != k)
		{
			for (j=0; j<=nNumColumns-1; j++)
			{ 
				u=k*nNumColumns+j; 
				v=pnRow[k]*nNumColumns+j;
				p=pData[u]; 
				pData[u]=pData[v]; 
				pData[v]=p;
			}
		}

		if (pnCol[k] != k)
		{
			for (i=0; i<=nNumColumns-1; i++)
			{ 
				u=i*nNumColumns+k; 
				v=i*nNumColumns+pnCol[k];
				p=pData[u]; 
				pData[u]=pData[v]; 
				pData[v]=p;
			}
		}

		l=k*nNumColumns+k;
		pData[l]=1.0f / pData[l];
		for (j=0; j<=nNumColumns-1; j++)
		{
			if (j != k)
			{ 
				u=k*nNumColumns+j; 
				pData[u]=pData[u]*pData[l];
			}
		}
		for (i=0; i<=nNumColumns-1; i++)
		{
			if (i!=k)
			{
				for (j=0; j<=nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=i*nNumColumns+j;
						pData[u]=pData[u]-pData[i*nNumColumns+k]*pData[k*nNumColumns+j];
					}
				}
			}
		}
		for (i=0; i<=nNumColumns-1; i++)
		{			
			if (i!=k)
			{	
				u=i*nNumColumns+k; 
				pData[u]=-pData[u]*pData[l];
			}
		}
	}

	// 调整恢复行列次序
	for (k=nNumColumns-1; k>=0; k--)
	{ 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=nNumColumns-1; j++)
			{ 
				u=k*nNumColumns+j; 
				v=pnCol[k]*nNumColumns+j;
				p=pData[u]; 
				pData[u]=pData[v]; 
				pData[v]=p;
			}
		}

		if (pnRow[k]!=k)
		{
			for (i=0; i<=nNumColumns-1; i++)
			{ 
				u=i*nNumColumns+k; 
				v=i*nNumColumns+pnRow[k];
				p=pData[u]; 
				pData[u]=pData[v]; 
				pData[v]=p;
			}
		}
	}

	// 清理内存
	delete[] pnRow;
	delete[] pnCol;

	// 成功返回
	return true;
}                                               

//////////////////////////////////////////////////////////////////////
// 求行列式值的全选主元高斯消去法
//
// 参数：无
//
// 返回值：float型，行列式的值
//////////////////////////////////////////////////////////////////////
float Matrix::Det()
{ 
	int i,j,k,is,js,l,u,v;
	float f,det,q,d;

	int dsize = nNumRows*nNumColumns;
	float *tData = new float[dsize];
	memcpy(tData, pData, sizeof(float)*dsize);

	// 初值
	f=1.0; 
	det=1.0;

	// 消元
	for (k=0; k<=nNumColumns-2; k++)
	{ 
		q=0.0;
		for (i=k; i<=nNumColumns-1; i++)
		{
			for (j=k; j<=nNumColumns-1; j++)
			{ 
				l=i*nNumColumns+j; 
				d=fabs(tData[l]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}

		if (q < EPS)
		{ 
			det=0.0; 
			return(det);
		}

		if (is!=k)
		{ 
			f=-f;
			for (j=k; j<=nNumColumns-1; j++)
			{ 
				u=k*nNumColumns+j; 
				v=is*nNumColumns+j;
				d=tData[u]; 
				tData[u]=tData[v]; 
				tData[v]=d;
			}
		}

		if (js!=k)
		{ 
			f=-f;
			for (i=k; i<=nNumColumns-1; i++)
			{
				u=i*nNumColumns+js; 
				v=i*nNumColumns+k;
				d=tData[u]; 
				tData[u]=tData[v]; 
				tData[v]=d;
			}
		}

		l=k*nNumColumns+k;
		det=det*tData[l];
		for (i=k+1; i<=nNumColumns-1; i++)
		{ 
			d=tData[i*nNumColumns+k]/tData[l];
			for (j=k+1; j<=nNumColumns-1; j++)
			{ 
				u=i*nNumColumns+j;
				tData[u]=tData[u]-d*tData[k*nNumColumns+j];
			}
		}
	}

	// 求值
	det=f*det*tData[nNumColumns*nNumColumns-1];

	delete[] tData;
	return(det);
}

//////////////////////////////////////////////////////////////////////
// 求矩阵秩的全选主元高斯消去法
//
// 参数：无
//
// 返回值：int型，矩阵的秩
//////////////////////////////////////////////////////////////////////
int Matrix::Rank()
{ 
	int i,j,k,nn,is,js,l,ll,u,v;
	float q,d;

	int dsize = nNumRows*nNumColumns;
	float *tData = new float[dsize];
	memcpy(tData, pData, sizeof(float)*dsize);

	// 秩小于等于行列数
	nn = nNumRows;
	if (nNumRows >= nNumColumns) 
		nn = nNumColumns;

	k=0;

	// 消元求解
	for (l=0; l<=nn-1; l++)
	{ 
		q=0.0;
		for (i=l; i<=nNumRows-1; i++)
		{
			for (j=l; j<=nNumColumns-1; j++)
			{ 
				ll=i*nNumColumns+j; 
				d=fabs(tData[ll]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}

		if (q < EPS) 
			return(k);

		k=k+1;
		if (is!=l)
		{ 
			for (j=l; j<=nNumColumns-1; j++)
			{ 
				u=l*nNumColumns+j; 
				v=is*nNumColumns+j;
				d=tData[u]; 
				tData[u]=tData[v]; 
				tData[v]=d;
			}
		}
		if (js!=l)
		{ 
			for (i=l; i<=nNumRows-1; i++)
			{ 
				u=i*nNumColumns+js; 
				v=i*nNumColumns+l;
				d=tData[u]; 
				tData[u]=tData[v]; 
				tData[v]=d;
			}
		}

		ll=l*nNumColumns+l;
		for (i=l+1; i<=nNumColumns-1; i++)
		{ 
			d=tData[i*nNumColumns+l]/tData[ll];
			for (j=l+1; j<=nNumColumns-1; j++)
			{ 
				u=i*nNumColumns+j;
				tData[u]=tData[u]-d*tData[l*nNumColumns+j];
			}
		}
	}

	delete[] tData;
	return(k);
}

bool Matrix::FloatEqual( Matrix other )
{
	float eps = 1e-6f;

	if( nNumColumns != other.GetNumColumns() || 
		nNumRows != other.GetNumRows() )
	{
		return false;
	}

	for( int i = 0; i < nNumRows; i ++ )
	{
		for( int j = 0; j < nNumColumns; j ++ )
		{
			if( fabs( GetElement(i, j) - other.GetElement(i, j) ) > eps )
			{
				return false;
			}
		}
	}

	return true;
}

float Matrix::Norm()
{
	float sum = 0.0f;

	for( int i = 0; i < nNumRows; i ++ )
	{
		for( int j = 0; j < nNumColumns; j ++ )
		{
			sum += GetElement(i, j) * GetElement(i, j);
		}
	}

	return sum;
}

void Matrix::PrintMatrix()
{
	for( int i = 0; i < GetNumRows(); i ++ )
	{
		for( int j = 0; j < GetNumColumns(); j ++ )
		{
			cout<< GetElement( i, j ) << " ";
		}

		cout<< endl;
	}
	
	cout<< endl;
}

void Matrix::OutPutMatrix()
{
	for( int i = 0; i < GetNumRows(); i ++ )
	{
		for( int j = 0; j < GetNumColumns(); j ++ )
		{
			MatrixLog<< GetElement( i, j ) << " ";
		}

		MatrixLog<< endl;
	}

	MatrixLog<< endl;
}

Matrix Matrix::Rpy2Rot(Angle angleA, Angle angleB, Angle angleC )
{
	AngRad a = angleA * PI / 180.0f;
	AngRad b = angleB * PI / 180.0f;
	AngRad c = angleC * PI / 180.0f;

	Matrix res(3,3);

	 //		cos(c)*cos(b)       -sin(c)*cos(b)+cos(c)*sin(b)*sin(a)         sin(c)*sin(a)+cos(c)*sin(b)*cos(a)
	 //		sin(c)*cos(b)       cos(c)*cos(a)+sin(c)*sin(b)*sin(a)          -cos(c)*sin(a)+sin(c)*sin(b)*cos(a)
	 //		-sin(b)             cos(b)*sin(a)                               cos(b)*cos(a)   
	res.SetElement( 0,0,cos(c)*cos(b) );
	res.SetElement( 0,1,-sin(c)*cos(b)+cos(c)*sin(b)*sin(a) );
	res.SetElement( 0,2,sin(c)*sin(a)+cos(c)*sin(b)*cos(a) );
	res.SetElement( 1,0,sin(c)*cos(b) );
	res.SetElement( 1,1,cos(c)*cos(a)+sin(c)*sin(b)*sin(a) );
	res.SetElement( 1,2,-cos(c)*sin(a)+sin(c)*sin(b)*cos(a) );
	res.SetElement( 2,0,-sin(b) );
	res.SetElement( 2,1,cos(b)*sin(a) );
	res.SetElement( 2,2,cos(b)*cos(a) );

	return res;
}

void Matrix::InvertAngles( Angle &rollX, Angle &pitchY, Angle &yawZ )
{	
	//res = [x, y, z];
	float r11 = GetElement(0,0);
	float r21 = GetElement(1,0);
	float r31 = GetElement(2,0);
	float r32 = GetElement(2,1);
	float r33 = GetElement(2,2);

	//	如果有一个人站在（0，0，0）点，面向X轴正向，头顶向上方向为Y轴正向，右手方向为Z轴正向，那么旋转角度和方向的计算方法如下：
	//	Yaw是围绕Y轴旋转，站在（0，0，0）点的人脚下是XOZ平面，以正角度为参数是向左转，以负角度为参数是向右转。
	//	Pitch是围绕X轴旋转，站在（0，0，0）点的人脚下是XOY平面，以正角度为参数是向右倒，以负角度为参数是向左倒。
	//	Roll是围绕Z轴旋转，站在（0，0，0）点的人脚下是YOZ平面，以正角度为参数是向后倒，以负角度为参数是向前倒。

	if( fabs(r11) < EPS || fabs(sqrt(r32*r32 + r33*r33)) < EPS || fabs(r33) < EPS )
	{
		rollX = 0.0f;
		pitchY = 0.0f;
		yawZ = 0.0f;

		return;
	}
	rollX = atan2( r21, r11 ) * 180.0f / PI;
	pitchY = atan2( -r31, sqrt(r32*r32 + r33*r33) ) * 180.0f / PI;
	yawZ = atan2( r32, r33 ) * 180.0f / PI;
}

LEquations::LEquations()
{
	mConst = NULL;
	mRoot = NULL;

	Init(1);
}

LEquations::LEquations(int num)
{
	mConst = NULL;
	mRoot = NULL;

	Init(num);
}

bool LEquations::Init(int num)
{ 
	Destroy();
	equationNum = num;
	mCoef.Init(num, num);
	mConst =  new float[num];	
	mRoot =  new float[num];
	if (mConst == NULL || mRoot==NULL)
	{
		return false;
	}
	memset(mConst, 0, sizeof(float) * num);
	memset(mRoot, 0, sizeof(float) * num);
	return true;
}

LEquations::~LEquations()
{
	Destroy();
}

void LEquations::Destroy()
{
	if (mConst)
	{
		delete[] mConst;
		mConst = NULL;
	}
	if (mRoot)
	{
		delete[] mRoot;
		mRoot = NULL;
	}
}

bool LEquations::GetRoot()
{ 
	int *pnJs,l,k,i,j,nIs,p,q;
	float d,t;

	// 方程组的属性，将常数向量赋给解向量
	memcpy(mRoot, mConst, sizeof(float)*equationNum);
	float *pDataCoef = mCoef.GetData();
	float *pDataConst = mRoot;
	int n = equationNum;

	// 临时缓冲区，存放列数
	pnJs = new int[n];

	// 消元
	l=1;
	for (k=0;k<=n-2;k++)
	{ 
		d=0.0;
		for (i=k;i<=n-1;i++)
		{
			for (j=k;j<=n-1;j++)
			{ 
				t=fabs(pDataCoef[i*n+j]);
				if (t>d) 
				{ 
					d=t; 
					pnJs[k]=j; 
					nIs=i;
				}
			}
		}

		if (d == 0.0) 
			l=0;
		else
		{ 
			if (pnJs[k]!=k)
			{
				for (i=0;i<=n-1;i++)
				{ 
					p=i*n+k; 
					q=i*n+pnJs[k];
					t=pDataCoef[p]; 
					pDataCoef[p]=pDataCoef[q]; 
					pDataCoef[q]=t;
				}
			}

			if (nIs!=k)
			{ 
				for (j=k;j<=n-1;j++)
				{ 
					p=k*n+j; 
					q=nIs*n+j;
					t=pDataCoef[p]; 
					pDataCoef[p]=pDataCoef[q]; 
					pDataCoef[q]=t;
				}

				t=pDataConst[k]; 
				pDataConst[k]=pDataConst[nIs]; 
				pDataConst[nIs]=t;
			}
		}

		// 求解失败
		if (l==0)
		{ 
			delete[] pnJs;
			return false;
		}

		d=pDataCoef[k*n+k];
		for (j=k+1;j<=n-1;j++)
		{ 
			p=k*n+j; 
			pDataCoef[p]=pDataCoef[p]/d;
		}

		pDataConst[k]=pDataConst[k]/d;
		for (i=k+1;i<=n-1;i++)
		{ 
			for (j=k+1;j<=n-1;j++)
			{ 
				p=i*n+j;
				pDataCoef[p]=pDataCoef[p]-pDataCoef[i*n+k]*pDataCoef[k*n+j];
			}

			pDataConst[i]=pDataConst[i]-pDataCoef[i*n+k]*pDataConst[k];
		}
	}

	// 求解失败
	d=pDataCoef[(n-1)*n+n-1];
	if (d == 0.0)
	{ 
		delete[] pnJs;
		return false;
	}

	// 求解
	pDataConst[n-1]=pDataConst[n-1]/d;
	for (i=n-2;i>=0;i--)
	{ 
		t=0.0;
		for (j=i+1;j<=n-1;j++)
			t=t+pDataCoef[i*n+j]*pDataConst[j];
		pDataConst[i]=pDataConst[i]-t;
	}

	// 调整解的位置
	pnJs[n-1]=n-1;
	for (k=n-1;k>=0;k--)
	{
		if (pnJs[k]!=k)
		{ 
			t=pDataConst[k]; 
			pDataConst[k]=pDataConst[pnJs[k]]; 
			pDataConst[pnJs[k]]=t;
		}
	}

	// 清理内存
	delete[] pnJs;

	return true;
}