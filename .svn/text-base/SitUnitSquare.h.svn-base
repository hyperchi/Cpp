#ifndef __SITUNITSQUARE_H__
#define __SITUNITSQUARE_H__

#include "WorldModel.h"
#include "ConfFileRead.h"
#include "Logger.h"

class UnitSquare
{
public:
	UnitSquare()
	{	
		centerX = 0.0f;
		centerY = 0.0f;
		weight = 0.0f;
	}
	~UnitSquare(){	}

private:
	float centerX;
	float centerY;
	float weight;

public:
	void SetCenter( const float &x, const float &y )
	{
		centerX = x;
		centerY = y;
	}

	void SetWeight( const float &w )
	{
		weight = w;
	}

	float GetCenterX( )
	{
		return centerX;
	}

	float GetCenterY( )
	{
		return centerY;
	}

	Vector3f GetCenterVector3f()
	{
		Vector3f tempVec( centerX, centerY, 0.0f );

		return tempVec;
	}

	float GetWeight( )
	{
		return weight;
	}

};

const unsigned int RowNum = 8;
const unsigned int ColumnNum = 12;

class FieldSquare
{
public:
	FieldSquare( WorldModel * wm );
	~FieldSquare();

private:
	WorldModel *mWorldModel;

public:
	UnitSquare mUnitSquare[RowNum][ColumnNum];			// Server 0.6 
														// 场地长 12.0f 宽 8.0f 将场地均分为12*8个单元格
														// 按如下顺序编号：
														//
														// 场地左上角
														// 0	1	2	......	9	10	11
														// ...... ...... ...... ...... ......
														// 84	85	86	......	93	94	95
														//						场地右下角	

	void InitSquare();

	bool IsInField( Vector3f tarVectcor );
	bool IsInerField( Vector3f tarVectcor );
	int IsInSensitiveArea( Vector3f tarVectcor );
	bool IsNearOurGoal( Vector3f tarVectcor );
	bool IsNearOppGoal( Vector3f tarVectcor );

	unsigned int GetSquareRowNum( Vector3f tarVectcor );
	unsigned int GetSquareColNum( Vector3f tarVectcor );
	UnitSquare GetSqure( unsigned int rowNum, unsigned int colNum );
};

#endif //__SITUNITSQUARE_H__