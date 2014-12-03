#include "MotionGoto.h"
#define SmartLog gLog<< "[motion] " << "Smart "

bool MotionGoto::SmartTurn( Angle targetAngle )
{
	if( fabs(mTransSpeed) > mTransAccSpeed / 10.0f )
	{
		TransSpeedLimit( mTransSpeed * 0.95f );

		mAct->CrazyTrans( mTransSpeed );

		return false;
	}
	else if( fabs(mTransSpeed) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;	
	}
	else if( fabs(mForSpeed) > mForAccSpeed  )
	{		
		ForSpeedLimit( mForSpeed * 0.9f);

		mAct->Walk( mForSpeed, 0.0f, 0.0f );

		return false;
	}
	else if( fabs(mForSpeed) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;
	}

	Angle angToTarget;

	// 防止决策摇摆
	if( fabs( fabs( AngToTarAngle( targetAngle ) ) - 45.0f ) < 5.0f )
	{
		angToTarget = AngToTarAngle( targetAngle );
	}
	else
	{
		angToTarget = AngleLimit45( AngToTarAngle( targetAngle ) );
	}

	angToTarget = AngleLimit45( AngToTarAngle( targetAngle ) );

	float temAng;

	if( fabs(angToTarget) > mGotoAngEPS[mAngEps] * 4.0f )
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;

		}
	}
	else
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
	}
		
	ForSpeedLimit( 0.0f );
	TurnSpeedLimit( temAng );
	TransSpeedLimit( 0.0f );

	mAct->CrazyTurn( mTurnSpeed );

	return true;
}

bool MotionGoto::SmartFor( float dist )
{
	if( fabs(mTransSpeed) > EPS )
	{
		TransSpeedLimit( 0.0f );

		mAct->CrazyTrans( mTransSpeed );

		return false;
	}
	else if( fabs(mTurnSpeed) > EPS )
	{
		TurnSpeedLimit( 0.0f );

		mAct->CrazyTurn( mTurnSpeed );

		return false;
	}
	
	float tempSpeed;

	SetForAccSpeed( mForAccSpeed * 2.0f );

	if( dist >= 0.0f )
	{
		tempSpeed = sqrt( 2 * fabs(dist)/ (mForAccSpeed * mForProportion) ) * mForAccSpeed;
	}
	else
	{
		tempSpeed = - sqrt( 2 * fabs(dist)/ (mForAccSpeed * mForProportion) ) * mForAccSpeed;
	}

	ForSpeedLimit( tempSpeed );
	TurnSpeedLimit( 0.0f );
	TransSpeedLimit( 0.0f );

	mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

	SetForAccSpeed( mForAccSpeed / 2.0f );

	return true;
}

bool MotionGoto::SmartTrans( float dist )
{
	if( fabs(mForSpeed) > EPS )
	{
		ForSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, 0.0f, 0.0f );

		return false;
	}
	else if( fabs(mTurnSpeed) > EPS )
	{
		TurnSpeedLimit( 0.0f );

		mAct->CrazyTurn( mTurnSpeed );

		return false;
	}

	if( fabs(mTransSpeed) < EPS && fabs(mWorldModel->mBodyFaceTo.angPhi()) > 2.0f )
	{
		mAct->Stand();

		ClearSpeed();

		return false;
	}

	float tempSpeed;

	if( dist >= 0.0f )
	{
		tempSpeed = sqrt( 2 * fabs(dist)/ (mTransAccSpeed * mTransProportion) ) * mTransAccSpeed;
	}
	else
	{
		tempSpeed = - sqrt( 2 * fabs(dist)/ (mTransAccSpeed * mTransProportion) ) * mTransAccSpeed;
	}
	
	if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 2.0f )
	{
		SlowDownSpeedToStand();
	}
	else
	{
		TransSpeedLimit( tempSpeed );

		mAct->CrazyTrans( mTransSpeed );
	}

	return true;
}

bool MotionGoto::SmartGoto( Vector3f targetVector )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );
	float angleToTarVector = AngleLimit45( Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() ) );
	float angleEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );


	if( distToTarget <= distEps )
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}

	if( fabs(AngToTarAngle(angleToTarVector) ) > angleEps 
		&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) > angleEps
		&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 90.0f ) > angleEps * 4.0f
		)
	{
		SmartTurn( angleToTarVector );

		return false;
	}
	
	float tempSpeed;

	// ngleEps * 2.0f 是为了防止摇摆
	if( fabs(AngToTarAngle(angleToTarVector) ) <= angleEps * 2.0f )
	{
		SmartFor( fabs(distToTarget) );
	}
	else if( fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) <= angleEps * 2.0f )
	{
		SmartFor( - fabs(distToTarget) );
	}
	else if( fabs( AngToTarAngle(angleToTarVector) + 90.0f ) <= angleEps * 8.0f )
	{
		SmartTrans( fabs(distToTarget) );
	}
	else if( fabs( AngToTarAngle(angleToTarVector) - 90.0f ) <= angleEps * 8.0f )
	{
		SmartTrans( - fabs(distToTarget) );
	}
	else 
	{
		SmartLog << "Smart Goto Error Code: " << "Don't Know What To Do ! " << endl;
	}
	
	return false;
}

bool MotionGoto::SmartGoto( Vector3f targetVector, Angle targetAngle )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );

	float angleToTarVector = Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() );
	float angleToTarVecEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );

	float angleToTarAng = AngToTarAngle( targetAngle );
	float angleToTarAngEps = Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn );

	if( distToTarget > distEps )
	{
		SmartGoto( targetVector );

		return false;
	}
	else if( fabs(angleToTarAng) > angleToTarAngEps )
	{
		Turn( targetAngle );

		return false;
	}	
	else
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}
}

bool MotionGoto::SmartTurnForGoto( Angle targetAngle, float distEps )
{

}

bool MotionGoto::SmartFastGoto( Vector3f targetVector, float distEps )
{
	Vector3f tarPos = GetRidOfObstacle( targetVector );

	Angle bodyForAngle = mWorldModel->mBodyAngle;
	Angle bodyLeftTransAngle = Normalize( mWorldModel->mBodyAngle + 90.0f ); 
	Angle bodyRightTransAngle = Normalize( mWorldModel->mBodyAngle - 90.0f );
	Angle bodyBackAngle = Normalize( mWorldModel->mBodyAngle + 180.0f );

	Angle bodyToTar = Normalize( (tarPos - mWorldModel->mSelf.mPos).angTheta() );

	float staticAngleEps = Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn );
	float distToTar = mWorldModel->mSelf.DistXyTo( tarPos );
	float tempSpeed = sqrt( 2 * fabs(distToTar)/ (mTransAccSpeed * mTransProportion) ) * mTransAccSpeed;

	// 如果距离目标点在误差范围内，则停止移动
	if( distToTar < distEps )
	{
		// 减速
		if( fabs(GetTransSpeed()) > EPS )
		{
			SlowDownSpeedToStand();

			return false;
		}
		// 静止
		else
		{
			mAct->Stand();

			return true;
		}
	}
	// 如果尚未到达目标点
	//		并且平移速度为零
	else if( fabs( GetTransSpeed() ) < EPS  )
	{
		// 如果瞄准了目标区域，就要开始加速
		if( fabs(bodyLeftTransAngle -  bodyToTar) < staticAngleEps 
			|| fabs(bodyRightTransAngle -  bodyToTar) < staticAngleEps )
		{
			if( fabs(GetForSpeed()) > EPS 
				|| fabs(GetTurnSpeed()) > EPS )
			{
				SlowDownSpeedToStand();

				return false;
			}
			else if( fabs(bodyLeftTransAngle -  bodyToTar) < 90.0f )
			{
				tempSpeed = -tempSpeed;

				TransSpeedLimit( tempSpeed );

				mAct->CrazyTrans( mTransSpeed );
			}
			else
			{
				TransSpeedLimit( tempSpeed );

				mAct->CrazyTrans( mTransSpeed );
			}
		}
		// 如果没有瞄准目标区域，就要开始转身
		else
		{ 
			if( fabs(GetForSpeed()) > EPS 
				|| fabs(GetTransSpeed()) > EPS )
			{
				SlowDownSpeedToStand();

				return false;
			}
			else if( fabs(bodyLeftTransAngle -  bodyToTar) < 95.0f )
			{
				Turn( Normalize(bodyToTar - 90.0f) );
			}
			else
			{
				Turn( Normalize(bodyToTar + 90.0f) );
			}
		}
	}
	// 如果尚未到达目标点
	//		并且正在平移
	else
	{
		Line bodyTransLine = Line::makeLineFromPositionAndAngle( mWorldModel->mSelf.mPos, bodyLeftTransAngle );	
		float distLineToTar = bodyTransLine.getDistanceWithPoint( tarPos );
		
		// 判断当前平移方向是否指向目标区域

		// 如果当前平移方向没有指向目标区域
		//		减速
		if( distLineToTar > distEps )
		{
			if( fabs(mTransSpeed) > mTransAccSpeed / 10.0f )
			{
				TransSpeedLimit( mTransSpeed * 0.95f );

				mAct->CrazyTrans( mTransSpeed );

				return false;
			}
			else if( fabs(mTransSpeed) > EPS )
			{
				//ClearSpeed();

				TransSpeedLimit( 0.0f );

				mAct->CrazyTrans( mTransSpeed );

				return false;	
			}
		}
		// 如果当前平移方向指向目标区域
		else
		{
			// 如果身体倾斜了，就需要减速
			if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 1.0f )
			{
				//if( ( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 7.3f 
				//		&& fabs(mWorldModel->mBodyFaceTo.angPhi()) < 7.7f )
				//	||( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 19.0f 
				//		&& fabs(mWorldModel->mBodyFaceTo.angPhi()) < 20.0f )
				//	)
				//{	
				//	// 机器人在平移时，如果倾角为此值，则说明机器人自己卡住自己了（困在原地不能动）……囧
				//	TransSpeedLimit( mTransMaxSpeed);

				//	mAct->CrazyTrans( mTransSpeed );

				//	return false;
				//}
				//else 
					if( fabs(mTransSpeed) > mTransAccSpeed / 10.0f )
				{
					TransSpeedLimit( mTransSpeed * 0.95f );

					mAct->CrazyTrans( mTransSpeed );

					return false;
				}
				else if( fabs(mTransSpeed) > EPS )
				{
					ClearSpeed();

					mAct->Stand();

					return false;	
				}	
			}
			// 身体位置平衡，平移
			else if( fabs(bodyLeftTransAngle - bodyToTar) < 90.0f )
			{
				tempSpeed = -tempSpeed;

				TransSpeedLimit( tempSpeed );

				mAct->CrazyTrans( mTransSpeed );
			}
			else
			{
				TransSpeedLimit( tempSpeed );

				mAct->CrazyTrans( mTransSpeed );
			}
		}
	}

	return false;
}
