#include "SitUnitSquare.h"

#define SitSquareLog gLog<< "[sition] " 

FieldSquare::FieldSquare( WorldModel * wm )
{
	mWorldModel = wm;
	InitSquare();
}
FieldSquare::~FieldSquare()
{

}

void FieldSquare::InitSquare()
{
	for( unsigned int i = 0; i < RowNum; i ++ )
	{
		for( unsigned int j = 0; j < ColumnNum; j ++ )
		{
			float centerX = j * 1.0f - mWorldModel->mFieldLength / 2.0f + mWorldModel->mFieldLength / ColumnNum / 2.0f;
			float centerY = (i) * (-1.0f) + mWorldModel->mFieldWidth / 2.0f - mWorldModel->mFieldWidth / RowNum / 2.0f;

			mUnitSquare[i][j].SetCenter( centerX, centerY );
		}
	}

	ReadConf rC( mWorldModel->GetFormationConfPath() );
	Predicate tempP;
	float tempWeight[RowNum][ColumnNum];

	rC.Tranversal( "SquareWeight", tempP );

	SitSquareLog<< "SquareWeight Line Nunber: " << (int) tempP.child.size() << endl;

	if( tempP.child.size() != RowNum )
	{
		return ;
	}

	multimap<string,Predicate>::iterator cp = tempP.child.begin();

	while( cp != tempP.child.end() )
	{
		if( (cp->second).attr.size() != ColumnNum + 3 )
		{
			break;
		}

		for( unsigned int i = 0; i < ColumnNum; i ++ )
		{	
			unsigned int weightLineNo = (unsigned int) atoi( ((cp->second)).attr[0].c_str() ) - 1;

			tempWeight[weightLineNo][i] = (float) atof( (cp->second).attr[i + 1].c_str() );
		}

		cp ++;
	}

	for( unsigned int i = 0; i < RowNum; i++ )
	{
		SitSquareLog<< i + 1 << " ";

		for( unsigned int j = 0; j < ColumnNum; j ++ )
		{
			mUnitSquare[i][j].SetWeight( tempWeight[i][j] );

			SitSquareLog<< mUnitSquare[i][j].GetWeight() << " ";
		}

		SitSquareLog<< endl;
	}
}

bool FieldSquare::IsInField( Vector3f tarVectcor )
{
	int ourScore = mWorldModel->mOurScore;
	int oppScore = mWorldModel->mOppScore;
	int scoreLead = ourScore - oppScore;

	// 比分落后的情况下，会倾向于向场外带球
	if( scoreLead <= -2 )
	{
		return true;
	}

	if( fabs(tarVectcor.x) > mWorldModel->mFieldLength / 2.0f )
	{
		return false;
	}

	if( fabs(tarVectcor.y) > mWorldModel->mFieldWidth / 2.0f )
	{
		return false;
	}

	return true;
}

//	比 
//		bool FieldSquare::IsInField( Vector3f tarVectcor )
//	的判断更严格，球靠近边界时也认为会出界
bool FieldSquare::IsInerField( Vector3f tarVectcor )
{
	int ourScore = mWorldModel->mOurScore;
	int oppScore = mWorldModel->mOppScore;
	int scoreLead = ourScore - oppScore;
	const float minDistEps = 0.5f;
	const float bottomLineDistEps = 1.0f;

	// 比分落后的情况下，会倾向于向场外带球
	if( scoreLead <= -2 )
	{
		return true;
	}

	if( fabs(tarVectcor.x) > mWorldModel->mFieldLength / 2.0f - bottomLineDistEps )
	{
		return false;
	}

	if( fabs(tarVectcor.y) > mWorldModel->mFieldWidth / 2.0f - minDistEps )
	{
		return false;
	}

	return true;
}

// 判断目标点是否处在敏感区
//		如靠近我方、对方球门、靠近边线等
//	返回值：	-5		(远远）出界
//				-4		靠近边线
//				-3		靠近底线
//				-2		靠近我方球门
//				-1		靠近对方球门（在球门前的矩形区域外）
//				0		OK		
int FieldSquare::IsInSensitiveArea( Vector3f tarVectcor )
{
	const float inFieldDistEps = 0.2f;

	if( fabs(tarVectcor.x) > mWorldModel->mFieldLength / 2.0f + inFieldDistEps 
		|| fabs(tarVectcor.y) > mWorldModel->mFieldWidth / 2.0f + inFieldDistEps
		)
	{
		return -5;
	}

	float tarDistToOurGoal = tarVectcor.distXY2( mWorldModel->mOurGoalCenter );
	float tarDistToOppGoal = tarVectcor.distXY2( mWorldModel->mOppGoalCenter );
	float goalHalfWidth = mWorldModel->mGoalWidth * 0.6f;

	if( tarDistToOurGoal < goalHalfWidth )
	{
		return -2;
	}

	if( tarDistToOppGoal < goalHalfWidth 
		&& fabs(tarVectcor.y) > mWorldModel->mGoalWidth / 2.0f - inFieldDistEps ) 
	{
		return -1;
	}

	if( fabs(tarVectcor.y) > mWorldModel->mFieldWidth / 2.0f - inFieldDistEps
		&& fabs(tarVectcor.y) < mWorldModel->mFieldWidth / 2.0f + inFieldDistEps
		)
	{
		return -4;
	}

	if( fabs(tarVectcor.x) > mWorldModel->mFieldLength / 2.0f - inFieldDistEps 
		&& fabs(tarVectcor.x) < mWorldModel->mFieldLength / 2.0f + inFieldDistEps 
		)
	{
		return -3;
	}

	return 0;
}

bool FieldSquare::IsNearOurGoal( Vector3f tarVectcor )
{
	const float nearOurGoalMinDist = 3.0f;
	if( tarVectcor.distXY2( mWorldModel->mOurGoalCenter ) < nearOurGoalMinDist )
	{
		return true;
	}

	const float paraLineDistToOurGoal = 4.0f;
	const float verticalLineDistToOurGoal = 1.0f;
	if( tarVectcor.x <= mWorldModel->mOurGoalCenter.x + paraLineDistToOurGoal 
		&& fabs(tarVectcor.y) <= mWorldModel->mGoalWidth / 2.0f + verticalLineDistToOurGoal )
	{
		return true;
	}

	return false;
}
bool FieldSquare::IsNearOppGoal( Vector3f tarVectcor )
{
	const float nearOppGoalMinDist = 2.0f;
	if( tarVectcor.distXY2( mWorldModel->mOurGoalCenter ) < nearOppGoalMinDist )
	{
		return true;
	}

	const float paraLineDistToOppGoal = 3.0f;
	const float verticalLineDistToOppGoal = 0.5f;
	if( tarVectcor.x <= mWorldModel->mOurGoalCenter.x + paraLineDistToOppGoal 
		&& fabs(tarVectcor.y) <= mWorldModel->mGoalWidth / 2.0f + verticalLineDistToOppGoal )
	{
		return true;
	}

	return false;
}

unsigned int FieldSquare::GetSquareRowNum( Vector3f tarVectcor )
{
	int rowNo = (unsigned int)floor(tarVectcor.y) + RowNum / 2;

	if( rowNo < 0 )
	{
		rowNo = 0;
	}
	else if( rowNo > RowNum - 1 )
	{
		rowNo = RowNum - 1;
	}

	return (unsigned int) rowNo;
}

unsigned int FieldSquare::GetSquareColNum( Vector3f tarVectcor )
{
	int columnNo = (unsigned int)floor(tarVectcor.x) + ColumnNum / 2;

	if( columnNo < 0 )
	{
		columnNo = 0;
	}
	else if( columnNo > ColumnNum - 1)
	{
		columnNo = ColumnNum - 1;
	}

	return (unsigned int) columnNo;
}

UnitSquare FieldSquare::GetSqure( unsigned int rowNum, unsigned int colNum )
{
	return mUnitSquare[rowNum][colNum];
}
