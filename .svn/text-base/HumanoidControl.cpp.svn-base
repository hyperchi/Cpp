#include "stdafx.h"
#include "HumanoidControl.h"

#define HCLOG gLog << "[human ] "

const bool bLeftLeg = true;
const bool bRightLeg = false;

Humanoid::Humanoid():
cInitLeftTransLen(-0.055f),
cInitRightTransLen(0.055f),
cInitForLen(0.0f),
cInitHeight(0.0f),
cBodyAngle(7.5f)
{
	InitUpperJoitnAngle();

	InitLegPara( bLeftLeg );
	InitLegPara( bRightLeg );
	InitLegAngle( bLeftLeg, 1 );
	InitLegAngle( bRightLeg, 1 );
	UpdateLegPosAndR( bLeftLeg );
	UpdateLegPosAndR( bRightLeg );

	mFootStep = LeftStep;

	// 静止状态 1：	0.0550	-0.0141	-0.2082		
	mUltiLeftForLen		= -0.0141f;
	mUltiLeftTransLen	= -0.0550f;	
	mUltiLeftHeight		= -0.2082f;
	mUltiLeftTurn		= 0.0f;
	mUltiRightForLen	= -0.0141f;	
	mUltiRightTransLen	= 0.0550f;
	mUltiRightHeight	= -0.2082f;	
	mUltiRightTurn		= 0.0f;
}

Humanoid::~Humanoid()
{

}

Matrix Humanoid::Rot2Omega( Matrix R )
{
	Matrix resMatrix(3, 1);

	Matrix unixMatrixE;
	unixMatrixE.MakeUnitMatrix( 3 );

	if( R.FloatEqual( unixMatrixE) ) 
	{
		return resMatrix;
	}

	float r11, r12, r13, r21, r22, r23, r31, r32, r33;

	r11 = R.GetElement(0, 0);
	r12 = R.GetElement(0, 1);
	r13 = R.GetElement(0, 2);
	r21 = R.GetElement(1, 0);
	r22 = R.GetElement(1, 1);
	r23 = R.GetElement(1, 2);
	r31 = R.GetElement(2, 0);
	r32 = R.GetElement(2, 1);
	r33 = R.GetElement(2, 2);

	float theta = acos( ( r11 + r22 + r33 - 1 ) / 2 );

	if( theta != theta )			// 说明 theta 无法计算出来。
	{
		return resMatrix;
	}

	if( fabs( sin( theta ) )< EPS )
	{
		return resMatrix;
	}

	float coefficient = ( theta ) / ( 2 * sin( theta ) );

	resMatrix.SetElement( 0, 0, r32 - r23 );
	resMatrix.SetElement( 1, 0, r13 - r31 );
	resMatrix.SetElement( 2, 0, r21 - r12 );

	resMatrix *= coefficient;

	return resMatrix;
}

Matrix Humanoid::CalcVWerr( Matrix pTar, Matrix pNow, Matrix RTar, Matrix RNow )
{
	Matrix pErr;
	pErr = pTar - pNow;

	Matrix wErr;
	Matrix Rerr;
	Rerr = RNow.Transpose() * RTar;
	wErr = RNow * Rot2Omega( Rerr );

	Matrix err(6, 1);

	err.SetElement( 0, 0, pErr.GetElement(0, 0) );
	err.SetElement( 1, 0, pErr.GetElement(1, 0) );
	err.SetElement( 2, 0, pErr.GetElement(2, 0) );

	err.SetElement( 3, 0, wErr.GetElement(0, 0) );
	err.SetElement( 4, 0, wErr.GetElement(1, 0) );
	err.SetElement( 5, 0, wErr.GetElement(2, 0) );

	return err;
}

Matrix Humanoid::Rpy2Rot( AngRad a, AngRad b, AngRad c)
{
	Matrix res(3, 3);

	res.SetElement( 0, 0, cos(c)*cos(b) );
	res.SetElement( 0, 1, -sin(c)*cos(a)+cos(c)*sin(b)*sin(a) );
	res.SetElement( 0, 2, sin(c)*sin(a)+cos(c)*sin(b)*cos(a) );
	res.SetElement( 1, 0, sin(c)*cos(b) );
	res.SetElement( 1, 1, cos(c)*cos(a)+sin(c)*sin(b)*sin(a) );
	res.SetElement( 1, 2, -cos(c)*sin(a)+sin(c)*sin(b)*cos(a) );
	res.SetElement( 2, 0, -sin(b) );
	res.SetElement( 2, 1, cos(b)*sin(a) );
	res.SetElement( 2, 2, cos(b)*cos(a) );

	return res;
}

Matrix Humanoid::Rodrigues( Matrix ang, float theta )
{
	Matrix unixMatrixE;
	unixMatrixE.MakeUnitMatrix( 3 );

	Matrix A(3, 3);

	float a1 = ang.GetElement(0, 0);
	float a2 = ang.GetElement(1, 0);
	float a3 = ang.GetElement(2, 0);

	A.SetElement( 0, 0, 0 );
	A.SetElement( 0, 1, -a3 );
	A.SetElement( 0, 2, a2 );
	A.SetElement( 1, 0, a3 );
	A.SetElement( 1, 1, 0 );
	A.SetElement( 1, 2, -a1 );
	A.SetElement( 2, 0, -a2 );
	A.SetElement( 2, 1, a1 );
	A.SetElement( 2, 2, 0 );

	Matrix res;
	res =  unixMatrixE + A * sin(theta) + A * A * ( 1 - cos(theta) );

	return res;
}

Matrix Humanoid::CrossMulti( Matrix w, Matrix p )
{
	float wx = w.GetElement(0, 0);
	float wy = w.GetElement(0, 1);
	float wz = w.GetElement(0, 2);
	float px = p.GetElement(0, 0);
	float py = p.GetElement(0, 1);
	float pz = p.GetElement(0, 2);

	Matrix res(3, 1);

	res.SetElement( 0, 0, wy * pz - wz * py );
	res.SetElement( 1, 0, wz * px - wx * pz );
	res.SetElement( 2, 0, wx * py - wy * px );

	return res;
}

Matrix Humanoid::CalcLegJacobian( bool isLeftLeg, const Matrix &pTar )
{
	Matrix a1,a2,a3,a4,a5,a6;
	Matrix R1,R2,R3,R4,R5,R6;
	Matrix p1,p2,p3,p4,p5,p6;
	Matrix wa1,wa2,wa3,wa4,wa5,wa6;

	if( isLeftLeg )
	{
		a1 = mLeftLeg.at(1).a;
		a2 = mLeftLeg.at(2).a;
		a3 = mLeftLeg.at(3).a;
		a4 = mLeftLeg.at(4).a;
		a5 = mLeftLeg.at(5).a;
		a6 = mLeftLeg.at(6).a;

		R1 = mLeftLeg.at(1).R;
		R2 = mLeftLeg.at(2).R;
		R3 = mLeftLeg.at(3).R;
		R4 = mLeftLeg.at(4).R;
		R5 = mLeftLeg.at(5).R;
		R6 = mLeftLeg.at(6).R;

		p1 = mLeftLeg.at(1).p;
		p2 = mLeftLeg.at(2).p;
		p3 = mLeftLeg.at(3).p;
		p4 = mLeftLeg.at(4).p;
		p5 = mLeftLeg.at(5).p;
		p6 = mLeftLeg.at(6).p;
	}
	else
	{
		a1 = mRightLeg.at(1).a;
		a2 = mRightLeg.at(2).a;
		a3 = mRightLeg.at(3).a;
		a4 = mRightLeg.at(4).a;
		a5 = mRightLeg.at(5).a;
		a6 = mRightLeg.at(6).a;

		R1 = mRightLeg.at(1).R;
		R2 = mRightLeg.at(2).R;
		R3 = mRightLeg.at(3).R;
		R4 = mRightLeg.at(4).R;
		R5 = mRightLeg.at(5).R;
		R6 = mRightLeg.at(6).R;

		p1 = mRightLeg.at(1).p;
		p2 = mRightLeg.at(2).p;
		p3 = mRightLeg.at(3).p;
		p4 = mRightLeg.at(4).p;
		p5 = mRightLeg.at(5).p;
		p6 = mRightLeg.at(6).p;
	}

	wa1 =   R1 * a1;
	wa2 =   R2 * a2;
	wa3 =   R3 * a3;
	wa4 =   R4 * a4;
	wa5 =   R5 * a5;
	wa6 =   R6 * a6;

	Matrix j1 = CrossMulti( wa1, pTar - p1 );
	Matrix j2 = CrossMulti( wa2, pTar - p2 );
	Matrix j3 = CrossMulti( wa3, pTar - p3 );
	Matrix j4 = CrossMulti( wa4, pTar - p4 );
	Matrix j5 = CrossMulti( wa5, pTar - p5 );

	Matrix Jacobian(6, 6);

	Jacobian.SetElement( 0, 0, j1.GetElement(0, 0) );
	Jacobian.SetElement( 1, 0, j1.GetElement(1, 0) );
	Jacobian.SetElement( 2, 0, j1.GetElement(2, 0) );
	Jacobian.SetElement( 3, 0, wa1.GetElement(0, 0) );
	Jacobian.SetElement( 4, 0, wa1.GetElement(1, 0) );
	Jacobian.SetElement( 5, 0, wa1.GetElement(2, 0) );

	Jacobian.SetElement( 0, 1, j2.GetElement(0, 0)  );
	Jacobian.SetElement( 1, 1, j2.GetElement(1, 0)  );
	Jacobian.SetElement( 2, 1, j2.GetElement(2, 0)  );
	Jacobian.SetElement( 3, 1, wa2.GetElement(0, 0) );
	Jacobian.SetElement( 4, 1, wa2.GetElement(1, 0) );
	Jacobian.SetElement( 5, 1, wa2.GetElement(2, 0) );

	Jacobian.SetElement( 0, 2, j3.GetElement(0, 0)  );
	Jacobian.SetElement( 1, 2, j3.GetElement(1, 0)  );
	Jacobian.SetElement( 2, 2, j3.GetElement(2, 0)  );
	Jacobian.SetElement( 3, 2, wa3.GetElement(0, 0) );
	Jacobian.SetElement( 4, 2, wa3.GetElement(1, 0) );
	Jacobian.SetElement( 5, 2, wa3.GetElement(2, 0) );

	Jacobian.SetElement( 0, 3, j4.GetElement(0, 0)  );
	Jacobian.SetElement( 1, 3, j4.GetElement(1, 0)  );
	Jacobian.SetElement( 2, 3, j4.GetElement(2, 0)  );
	Jacobian.SetElement( 3, 3, wa4.GetElement(0, 0) );
	Jacobian.SetElement( 4, 3, wa4.GetElement(1, 0) );
	Jacobian.SetElement( 5, 3, wa4.GetElement(2, 0) );

	Jacobian.SetElement( 0, 4, j5.GetElement(0, 0)  );
	Jacobian.SetElement( 1, 4, j5.GetElement(1, 0)  );
	Jacobian.SetElement( 2, 4, j5.GetElement(2, 0)  );
	Jacobian.SetElement( 3, 4, wa5.GetElement(0, 0) );
	Jacobian.SetElement( 4, 4, wa5.GetElement(1, 0) );
	Jacobian.SetElement( 5, 4, wa5.GetElement(2, 0) );

	Jacobian.SetElement( 0, 5, 0.0f  );
	Jacobian.SetElement( 1, 5, 0.0f  );
	Jacobian.SetElement( 2, 5, 0.0f  );
	Jacobian.SetElement( 3, 5, wa6.GetElement(0, 0) );
	Jacobian.SetElement( 4, 5, wa6.GetElement(1, 0) );
	Jacobian.SetElement( 5, 5, wa6.GetElement(2, 0) );

	return Jacobian;
}

void Humanoid::InitUpperJoitnAngle()
{
	mUpperJoints.resize( 11 );

	for( unsigned int i = 0; i < 11; i ++ )
	{
		mUpperJoints.at(i).q = 0.0f;
	}
}

void Humanoid::InitLegPara( bool isLeftLeg )
{
	if( isLeftLeg )
	{
		mLeftLeg.resize(7);
	}
	else
	{
		mRightLeg.resize(7);
	}

	for( int i = 0; i < 7; i ++ )
	{
		if( isLeftLeg )
		{
			mLeftLeg.at(i).a.Init(3,1);
			mLeftLeg.at(i).b.Init(3,1);
			mLeftLeg.at(i).p.Init(3,1);
			mLeftLeg.at(i).R.Init(3,3);
		}
		else
		{
			mRightLeg.at(i).a.Init(3,1);
			mRightLeg.at(i).b.Init(3,1);
			mRightLeg.at(i).p.Init(3,1);
			mRightLeg.at(i).R.Init(3,3);
		}
	}

	float a0[3] = {   1,		0,		0,   };
	float la1[3] ={   -0.7071f, 0,		-0.7071f, };
	float ra1[3] ={   -0.7071f, 0,		0.7071f,  };
	float a2[3] = {   0,		1,		0,   };
	float a3[3] = {   1,		0,		0,   };
	float a4[3] = {   1,		0,		0,   };
	float a5[3] = {   1,		0,		0,   };
	float a6[3] = {   0,		1,		0,   };

	float b0[3] = {   0,		0,		0,   };
	float lb1[3] ={   -0.055f,   -0.01f, -0.115f,  };
	float rb1[3] ={   0.055f,   -0.01f, -0.115f,  };
	float b2[3] = {   0,		0,		0,   };
	float b3[3] = {   0,		0,		0,   };
	float b4[3] = {   0,        -0.005f,-0.080f,  };
	float b5[3] = {   0,        -0.01f, -0.055f,  };
	float b6[3] = {   0,		0,		0,   };

	if( isLeftLeg )
	{
		mLeftLeg.at(0).a.SetData( a0 );
		mLeftLeg.at(1).a.SetData( la1 );
		mLeftLeg.at(2).a.SetData( a2 );
		mLeftLeg.at(3).a.SetData( a3 );
		mLeftLeg.at(4).a.SetData( a4 );
		mLeftLeg.at(5).a.SetData( a5 );
		mLeftLeg.at(6).a.SetData( a6 );

		mLeftLeg.at(0).b.SetData( b0 );
		mLeftLeg.at(1).b.SetData( lb1 );
		mLeftLeg.at(2).b.SetData( b2 );
		mLeftLeg.at(3).b.SetData( b3 );
		mLeftLeg.at(4).b.SetData( b4 );
		mLeftLeg.at(5).b.SetData( b5 );
		mLeftLeg.at(6).b.SetData( b6 );
	}
	else
	{
		mRightLeg.at(0).a.SetData( a0 );
		mRightLeg.at(1).a.SetData( ra1 );
		mRightLeg.at(2).a.SetData( a2 );
		mRightLeg.at(3).a.SetData( a3 );
		mRightLeg.at(4).a.SetData( a4 );
		mRightLeg.at(5).a.SetData( a5 );
		mRightLeg.at(6).a.SetData( a6 );
		mRightLeg.at(0).b.SetData( b0 );
		mRightLeg.at(1).b.SetData( rb1 );
		mRightLeg.at(2).b.SetData( b2 );
		mRightLeg.at(3).b.SetData( b3 );
		mRightLeg.at(4).b.SetData( b4 );
		mRightLeg.at(5).b.SetData( b5 );
		mRightLeg.at(6).b.SetData( b6 );
	}
}

void Humanoid::InitLegAngle( bool isLeftLeg, int iPlan )
{
	if( iPlan == 1 )
	{
		if( isLeftLeg )
		{
			mLeftLeg.at(0).q = 0.0f;	//10.0f * PI / 180.0f; // 上半身倾斜
			mLeftLeg.at(1).q = 0.0f;
			mLeftLeg.at(2).q = 0.0f;
			mLeftLeg.at(3).q = 9.28f * PI / 180.0f;
			mLeftLeg.at(4).q = -15.65f * PI / 180.0f;
			mLeftLeg.at(5).q = 8.98f * PI / 180.0f;
			mLeftLeg.at(6).q = 0.0f;
		}
		else
		{
			mRightLeg.at(0).q = 0.0f;	//10.0f * PI / 180.0f; // 上半身倾斜
			mRightLeg.at(1).q = 0.0f;
			mRightLeg.at(2).q = 0.0f;
			mRightLeg.at(3).q = 9.28f * PI / 180.0f;
			mRightLeg.at(4).q = -15.65f * PI / 180.0f;
			mRightLeg.at(5).q = 8.98f * PI / 180.0f;
			mRightLeg.at(6).q = 0.0f;
		}
	}
	//else if( iPlan == 2 )
	//{
	//	mLeftLeg.at(0).q = 0.0f;
	//	mLeftLeg.at(1).q = 0.0f;
	//	mLeftLeg.at(2).q = 0.0f;
	//	mLeftLeg.at(3).q = 0.0f;
	//	mLeftLeg.at(4).q = 0.0f;
	//	mLeftLeg.at(5).q = 0.0f;
	//	mLeftLeg.at(6).q = 0.0f;

	//	mRightLeg.at(0).q = 0.0f;
	//	mRightLeg.at(1).q = 0.0f;
	//	mRightLeg.at(2).q = 0.0f;
	//	mRightLeg.at(3).q = 0.0f;
	//	mRightLeg.at(4).q = 0.0f;
	//	mRightLeg.at(5).q = 0.0f;
	//	mRightLeg.at(6).q = 0.0f;
	//}
	//else if( iPlan == 3 )
	//{
	//	mLeftLeg.at(0).q = 0.0f;
	//	mLeftLeg.at(1).q = 0.0f;
	//	mLeftLeg.at(2).q = 0.0f;
	//	mLeftLeg.at(3).q = 0.0f;
	//	mLeftLeg.at(4).q = 0.0f;
	//	mLeftLeg.at(5).q = 0.0f;
	//	mLeftLeg.at(6).q = 0.0f;

	//	mRightLeg.at(0).q = 0.0f;
	//	mRightLeg.at(1).q = 0.0f;
	//	mRightLeg.at(2).q = 0.0f;
	//	mRightLeg.at(3).q = 0.0f;
	//	mRightLeg.at(4).q = 0.0f;
	//	mRightLeg.at(5).q = 0.0f;
	//	mRightLeg.at(6).q = 0.0f;
	//}
	//else
	//{
	//	mLeftLeg.at(0).q = 0.0f;
	//	mLeftLeg.at(1).q = 0.0f;
	//	mLeftLeg.at(2).q = 0.0f;
	//	mLeftLeg.at(3).q = 0.0f;
	//	mLeftLeg.at(4).q = 0.0f;
	//	mLeftLeg.at(5).q = 0.0f;
	//	mLeftLeg.at(6).q = 0.0f;

	//	mRightLeg.at(0).q = 0.0f;
	//	mRightLeg.at(1).q = 0.0f;
	//	mRightLeg.at(2).q = 0.0f;
	//	mRightLeg.at(3).q = 0.0f;
	//	mRightLeg.at(4).q = 0.0f;
	//	mRightLeg.at(5).q = 0.0f;
	//	mRightLeg.at(6).q = 0.0f;
	//}
}

void Humanoid::UpdateLegPosAndR( bool isLeftLeg )
{
	if( isLeftLeg )
	{
		mLeftLeg.at(0).p = mLeftLeg.at(0).b;
		mLeftLeg.at(0).R = Rodrigues( mLeftLeg.at(0).a, mLeftLeg.at(0).q );
	}
	else
	{
		mRightLeg.at(0).p = mRightLeg.at(0).b;
		mRightLeg.at(0).R = Rodrigues( mRightLeg.at(0).a, mRightLeg.at(0).q );
	}

	for( int i = 1; i < 7; i ++ )
	{
		if( isLeftLeg )
		{
			mLeftLeg.at(i).p = mLeftLeg.at( i - 1 ).R * mLeftLeg.at(i).b + mLeftLeg.at( i - 1 ).p;
			mLeftLeg.at(i).R = mLeftLeg.at( i - 1 ).R * Rodrigues( mLeftLeg.at(i).a, mLeftLeg.at(i).q );

		}
		else
		{
			mRightLeg.at(i).p = mRightLeg.at( i - 1 ).R * mRightLeg.at(i).b + mRightLeg.at( i - 1 ).p;
			mRightLeg.at(i).R = mRightLeg.at( i - 1 ).R * Rodrigues( mRightLeg.at(i).a, mRightLeg.at(i).q );
		}	
	}
}	

void Humanoid::UpdateLegAngle( AngRad &initQ, AngRad deltaQ )
{
	initQ = initQ + deltaQ;
}

bool Humanoid::InverseKinmatics( bool isLeftLeg, const Matrix &pTar, const Matrix &RTar )
{
	float Eps = 1E-6f;
	float lamda = 0.99f;
	const int maxCalcTime = 4;
	int calcTime = 0;

	Matrix pNow,RNow;
	bool equationFlag = true;

	InitLegPara( isLeftLeg );
	InitLegAngle( isLeftLeg, 1 );
	UpdateLegPosAndR( isLeftLeg );

	while( calcTime <= maxCalcTime )
	{
		if ( isLeftLeg )
		{
			pNow = mLeftLeg.at(6).p;
			RNow = mLeftLeg.at(6).R;
		}
		else
		{
			pNow = mRightLeg.at(6).p;
			RNow = mRightLeg.at(6).R;
		}

		Matrix J = CalcLegJacobian( isLeftLeg, pTar );
		Matrix err = CalcVWerr( pTar, pNow, RTar, RNow );

		if( err.Norm() <= Eps )
		{
			break;
		}

		//LEquations lEquations(6);

		//lEquations.mCoef = J;
		//lEquations.mRoot = err.GetData();

		//if( !lEquations.GetRoot() )
		//{
		//	equationFlag = false;
		//	break;
		//}
		if( !J.Invert() )
		{
			return false;
		}

		Matrix dQ;
		//dQ.SetData( lEquations.mRoot );
		dQ = J * err;
		dQ *= lamda;

		for( int i = 0; i < 6; i ++ )
		{
			if( isLeftLeg )
			{
				UpdateLegAngle( mLeftLeg.at( i + 1 ).q, dQ.GetElement( i, 0 ) );
			}
			else
			{
				UpdateLegAngle( mRightLeg.at( i + 1 ).q, dQ.GetElement( i, 0 ) );
			}
		}

		UpdateLegPosAndR( isLeftLeg );

		calcTime ++;
	}

	if( !equationFlag )
	{
		return false;
	}

	if( calcTime > maxCalcTime )
	{
		return false;
	}
	//cout<< "countTimes " << calcTime << endl << endl;
	return true;
}

bool Humanoid::IfLegJointLegal( bool isLeftLeg )
{
	const float leftLegJointMin[6] = { -90.0f,		-25.0f,		-25.0f,		-130.0f,	-45.0f,		-45.0f, };
	const float leftLegJointMax[6] = { 1.0f,		45.0f,		100.0f,		1.0f,		75.0f,		25.0f,	};

	const float rightLegJointMin[6] = { -90.0f,		-45.0f,		-25.0f,		-130.0f,	-45.0f,		-25.0f, };
	const float rightLegJointMax[6] = { 1.0f,		25.0f,		100.0f,		1.0f,		75.0f,		45.0f,	};

	for( unsigned int i = 0; i < 6; i ++ )
	{
		if( isLeftLeg )
		{
			if( GetLegJoint( bLeftLeg, i+1 ) < leftLegJointMin[i] 
			|| GetLegJoint( bLeftLeg, i+1 ) > leftLegJointMax[i] )
			{
				//cout<<"left"<<endl;
				return false;	
			}
		}
		else
		{
			if( GetLegJoint( bRightLeg, i+1 ) < rightLegJointMin[i] 
			|| GetLegJoint( bRightLeg, i+1 ) > rightLegJointMax[i] )
			{
				//cout<<"right"<<endl;
				return false;
			}
		}
	}

	//cout<< "All Angles Legal! " << endl;

	return true;
}

void Humanoid::IllegalJointLog( float forLength, float transLengh, float turnAng )
{
	HCLOG << " IllegalJointLog " << forLength << " " << transLengh << " " << turnAng << endl;

	//FILE *fp;

	//if( (fp = fopen( "IllegalJoint.log", "a" ) ) == NULL )
	//{
	//	return;
	//}

	//fprintf( fp, " %.2f %.2f %.2f \n", 
	//	forLength, transLengh, turnAng
	//	);

	//fclose(fp);
}

bool Humanoid::GetTarFoot( bool isLeftLeg, float posX, float posY, float posZ, Angle angX, Angle angY, Angle angZ )
{
	Matrix pTar;
	pTar.Init(3, 1);

	pTar.SetElement(0, 0, posX);
	pTar.SetElement(1, 0, posY);
	pTar.SetElement(2, 0, posZ);

	Matrix RTar;
	RTar = Rpy2Rot( angX * PI / 180.0f, angY * PI / 180.0f, angZ * PI / 180.0f );

	return InverseKinmatics( isLeftLeg, pTar, RTar );
}

Angle Humanoid::GetUpperJoint( unsigned int legJointNum )
{
	if( legJointNum <= 0 || legJointNum >= 11 )
	{
		return 0.0f;
	}

	return mUpperJoints.at( legJointNum ).q * 180.0f / PI;
}

Angle Humanoid::GetLegJoint( bool isLeftLeg, unsigned int legJointNum )
{
	if( legJointNum <= 0 || legJointNum >= 7 )
	{
		return 0.0f;
	}

	if( isLeftLeg )
	{
		return mLeftLeg.at( legJointNum ).q * 180.0f / PI;
	}
	else
	{
		return mRightLeg.at( legJointNum ).q * 180.0f / PI;
	}
}

bool Humanoid::SetTarFoot( bool isLeftLeg, float posX, float posY, float posZ, Angle yawAng, Angle bodyAng, unsigned int frameNum )
{
	unsigned int walkT = 36 / 2;
	bool legJointsLegal = true;

	if ( GetTarFoot( isLeftLeg, posX, posY, posZ, bodyAng, 0.0f, yawAng ) )
	{
		if( !IfLegJointLegal(isLeftLeg) )
		{
			//cout<< " Joint Illegal! " << endl;

			if( isLeftLeg )
			{
				GetTarFoot( isLeftLeg, -0.055f, -0.0181f, -0.238f, 7.0f, 0.0f, 0.0f );
			}
			else
			{
				GetTarFoot( isLeftLeg, 0.055f, -0.0181f, -0.238f, 7.0f, 0.0f, 0.0f );
			}

			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void Humanoid::GetJoints( Joint &joints )
{
	joints.joint[Head_1] = GetUpperJoint( 1 );
	joints.joint[Head_2] = GetUpperJoint( 2 );
	joints.joint[LARM_1] = GetUpperJoint( 3 );
	joints.joint[RARM_1] = GetUpperJoint( 7 );
	joints.joint[LARM_2] = GetUpperJoint( 4 );
	joints.joint[RARM_2] = GetUpperJoint( 8 );
	joints.joint[LARM_3] = GetUpperJoint( 5 );
	joints.joint[RARM_3] = GetUpperJoint( 9 );
	joints.joint[LARM_4] = GetUpperJoint( 6 );
	joints.joint[RARM_4] = GetUpperJoint( 10 );

	joints.joint[LLEG_1] = GetLegJoint( bLeftLeg, 1 );
	joints.joint[RLEG_1] = GetLegJoint( bRightLeg, 1 );
	joints.joint[LLEG_2] = GetLegJoint( bLeftLeg, 2 );
	joints.joint[RLEG_2] = GetLegJoint( bRightLeg, 2 );
	joints.joint[LLEG_3] = GetLegJoint( bLeftLeg, 3 );
	joints.joint[RLEG_3] = GetLegJoint( bRightLeg, 3 );
	joints.joint[LLEG_4] = GetLegJoint( bLeftLeg, 4 );
	joints.joint[RLEG_4] = GetLegJoint( bRightLeg, 4 );
	joints.joint[LLEG_5] = GetLegJoint( bLeftLeg, 5 );
	joints.joint[RLEG_5] = GetLegJoint( bRightLeg, 5 );
	joints.joint[LLEG_6] = GetLegJoint( bLeftLeg, 6 );
	joints.joint[RLEG_6] = GetLegJoint( bRightLeg, 6 );
}

bool Humanoid::Walk( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV )
{
	
	// 全部关节为0 ==>　0.055f, -0.025f, -0.25f,
	// 静止状态 1：	0.0550	-0.0141	-0.2082		
	float T = 36.0f;
//  	if( fabs(forLength) < 0.06f )
//  	{
//  		T = 40.0f;
//  	}
	const float leftPhi = 7.0f / 40.0f * T;
	const float rightPhi = leftPhi + T/4.0f;
	const float phaseT = 3.0f / 40.0f * T;
	//mFootStep = !mFootStep;

	tempjointsV.resize( (unsigned int)(T / 4.0f + 0.1f) );

	float forStep = forLength;		// 前进： > 0.0f
									// 后退： < 0.0f
	float transLen = transLengh;	// 向左平移：
									// 向右平移：
	Angle turnAngle = turnAng;		// 向左转： > 0.0f
									// 向右转： < 0.0f
	float startTNum = 0.0f;
	float endTNum = T / 4.0f;
	if( mFootStep )
	{
		startTNum = T / 4.0f;
		endTNum = T / 2.0f;
	}
	unsigned int tempjointsVNum = 0;
 	float m = mWalkFrameNum;
	//for( float m = startTNum; m < endTNum; m +=1.0f )
	{
		float n = m;
		tempjointsVNum = (int)m;
		if( tempjointsVNum >= tempjointsV.size() )
		{
			tempjointsVNum = tempjointsVNum % tempjointsV.size();
		}
		else if( tempjointsVNum < 0 )
		{
			tempjointsVNum = 0;
		}
		float cycle = T * 0.25f;

		// ********** 平移 **************** //
		float standingTrans = 0.055f;
		float basicTransLenth = 0.002f;
		float basicDeltaLeftTrans  /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		float basicDeltaRightTrans /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		basicDeltaLeftTrans = -basicTransLenth;
		basicDeltaRightTrans = basicTransLenth;		
		//if( n < cycle )
		//{
		//	basicDeltaLeftTrans = basicTransLenth - basicTransLenth / cycle * n;
		//}
		//else
		//{
		//	basicDeltaLeftTrans = basicTransLenth - basicTransLenth / cycle * cycle + 2.0f * basicTransLenth * sin( 2*PI/(4*cycle)*(n-cycle)) - basicTransLenth / cycle * (n-cycle);
		//}
		//basicDeltaRightTrans = -basicDeltaLeftTrans;		
		float leftTransStep = 0.0f;
		float rightTransStep = 0.0f;

		float transLenAbs = fabs(transLen);

		gProcessingLog << "Humanoid::Walk  "<< n<<"  forLength  "<<forLength<<"  transLengh "<<transLengh<<"  turnAng "<<turnAng<<"\n";

		if( transLen >= 0.0f )		
		{
			if( n < cycle )
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * n;
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*n) + transLenAbs / cycle * n;
			}
			else
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - transLenAbs / cycle * (n-cycle);
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n-cycle);
			}
		}
		else
		{
			if( n > cycle )
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * (n-cycle);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) + transLenAbs / cycle * (n-cycle);
			}
			else
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n)) - transLenAbs / cycle * (n);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n);
			}
		}

		float leftTransSum = basicDeltaLeftTrans - leftTransStep;
		float rightTransSum = basicDeltaRightTrans + rightTransStep;

		float leftTransLenth = -standingTrans + leftTransSum;
		float rightTransLenth = standingTrans + rightTransSum;

		// ********** 前进/后退 **************** //
		float forStepAbs = fabs( forStep );
// 		if( forStep >= 0.0f && forStep <= 0.005f )
// 		{
// 			forStepAbs = 0.005f;
// 		}
// 		else if( forStep < 0.0f && forStep >= -0.005f )
// 		{
// 			forStepAbs = -0.005f;
// 		}
 		if( forStep >= 0.0f && forStep <= 0.005f )
 		{
 			forStepAbs = 0.005f;
 		}
 		else if( forStep < 0.0f && forStep >= -0.005f )
 		{
 			forStepAbs = -0.005f;
 		}
        float forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		if( forStep < 0.0f )
		{
			forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		}
		if( forStandLen <= 0.01f )
		{
			forStandLen = 0.01f;
		}
		float leftForLenth;
		float rightForLenth;

		if( forStep >= 0.0f )
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * n;
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*n) - forStepAbs / cycle * n;
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - forStepAbs / cycle * (n-cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * (n-cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}
		else
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * (cycle-n);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(cycle-n)) - forStepAbs / cycle * (cycle-n);
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*((cycle-n)+cycle)) - forStepAbs / cycle * ((cycle-n)+cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * ((cycle-n)+cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}

		// ********** 转身 **************** //
		Angle steadyAngleAdjust = 2.0f;
		Angle turnAngAbs = fabs(turnAngle + steadyAngleAdjust);
		Angle turnLeft = 0.0f;		// > 0.0f;
		Angle turnRight = 0.0f;		// < 0.0f;

		if( turnAngle <= 0.0f )
		{
			if( n < cycle )
			{
				turnLeft =  turnAngAbs / cycle * n;
				turnRight =  -turnAngAbs / cycle * n;
			}
			else
			{
				turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n-cycle);
				turnRight =  - turnAngAbs / cycle * cycle + turnAngAbs / cycle * (n-cycle);
			}
		}
		else
		{
			if( n >= cycle )
			{
				turnLeft =  turnAngAbs / cycle * (n-cycle);
				turnRight =  -turnAngAbs / cycle * (n-cycle);
			}
			else
			{
				turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n);
				turnRight =  -turnAngAbs / cycle * cycle + turnAngAbs / cycle * (n);
			}
		}

		//float standingHeight = 0.224f;
		//if( turnAngle <= 0.0f )
		//{
		//	if( !leftStep )
		//	{
		//		turnLeft = turnAngAbs / cycle * n;
		//	}
		//	else
		//	{
		//		turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n - cycle);
		//		//turnLeft = 0.0f;
		//	}
		//}
		//else
		//{
		//	if( leftStep )
		//	{
		//		turnRight = -turnAngAbs / cycle * (n - cycle);
		//	}
		//	else
		//	{
		//		turnRight =  -turnAngAbs / cycle * cycle + turnAngAbs / cycle * n;
		//		//turnLeft = 0.0f;
		//	}
		//}

		//float standingHeight = 0.04f * (forStepAbs - 0.09f) + 0.224f;
		float standingHeight = 0.05f * (forStepAbs - 0.09f) + 0.224f;
		if( standingHeight <= 0.223f )
		{
			standingHeight = 0.223f;
		}
		if( standingHeight >= 0.223f )
		{
			standingHeight = 0.223f;
		}
		standingHeight = 0.22f;
		float leftStepHeight = 0.0f;
		float rightStepHeight = 0.0f;
		float deltaHeight = 0.008f;
		float adjustHeight = 0.0021f;
		float deltaHeightProp = 1.0f / 0.08f * ( fabs(forStepAbs) - 0.005f ) + 0.5f;
		//if( deltaHeightProp < 0.0f )
		//{
		//	//deltaHeightProp = -deltaHeightProp;
		//	deltaHeightProp = 0.0f;
		//}
		if( forLength < 0.0f )
		{
			deltaHeightProp = -1.0f / 0.08f * ( (forLength) - 0.005f ) - 0.5f;
			//if( deltaHeightProp > 0.0f )
			//{
			//	deltaHeightProp = -deltaHeightProp;
			//	deltaHeightProp = 0.0f;
			//}
		}

		if( n < T / 4.0f )
		{
			//leftStepHeight = -sqrt( standingHeight * standingHeight + leftForLenth * leftForLenth + leftTransLenth * leftTransLenth )+ adjustHeight * 0.5f;
			leftStepHeight = -standingHeight - deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) *deltaHeightProp;
		}
		else
		{
			leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) * 1.2f - standingHeight+adjustHeight - leftForLenth * 0.1f;
		}

		if( n >= T / 4.0f )
		{
			//rightStepHeight = -sqrt( standingHeight * standingHeight + rightForLenth * rightForLenth + rightTransLenth * rightTransLenth ) +adjustHeight * 0.5f;
			rightStepHeight = -standingHeight + deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * deltaHeightProp;
		}
		else
		{
			rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * 1.2f - standingHeight+adjustHeight - rightForLenth * 0.1f;
		}

		leftStepHeight *= 1.03f;
		rightStepHeight *= 1.03f;
		
		if( !SetTarFoot( bLeftLeg, leftTransLenth, leftForLenth, leftStepHeight, turnLeft, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		if( !SetTarFoot( bRightLeg, rightTransLenth, rightForLenth, rightStepHeight, turnRight, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}


 

//		float lArm_1 = -115.0f;	//-115.0f;
//		float lArm_2 = 0.0f;	//0.0f;
//		float lArm_3 = -85.0f;	//-85.0f;
//		float lArm_4 = -0.0f;	//-85.0f;
//		float rArm_1 = -115.0f;		//-115.0f;	
//		float rArm_2 = 0.0f;		//0.0f;	
//		float rArm_3 = 85.0f;		//85.0f;	
//		float rArm_4 = 0.0f;		//85.0f;	
//
//// 		if( n > cycle )
//// 		{
//// 			lArm_1 = -80.0f - 25 * sin( PI *(n -cycle) /cycle);
//// 			rArm_1 = -80.0f + 25 * sin( PI *(n -cycle) /cycle);
//// 		}
//// 		else
//// 		{
//// 			lArm_1 = -80.0f + 25 * sin( PI * n / cycle);
//// 			rArm_1 = -80.0f - 25 * sin( PI * n / cycle);
//// 		}
//		
// 		mUpperJoints.at(3).q = lArm_1 * PI / 180.0f;
// 		mUpperJoints.at(7).q = rArm_1 * PI / 180.0f;
// 		mUpperJoints.at(4).q = lArm_2 * PI / 180.0f;
// 		mUpperJoints.at(8).q = rArm_2 * PI / 180.0f;
// 		mUpperJoints.at(5).q = lArm_3* PI / 180.0f;
// 		mUpperJoints.at(9).q = rArm_3* PI / 180.0f;
// 		mUpperJoints.at(6).q = lArm_4* PI / 180.0f;
// 		mUpperJoints.at(10).q = rArm_4* PI / 180.0f;
  		float Arm_1 = -115.0f;
   		float Arm_2 = 0.0f;
   		float leftArm_3 = -90.0f;
   		float leftArm_4 = -85.0f;
   		float rightArm_3 = 90.0f;
   		float rightArm_4 = 85.0f;
   
   		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
   		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
   		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
   		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
   		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
   		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
   		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;

		GetJoints( tempjointsV.at( tempjointsVNum ) );
		//tempjointsVNum = (tempjointsVNum + 1)%tempjointsV.size();
	}

	m +=1.0f;
	mWalkFrameNum += 1.0f;
	//leftStep = !leftStep;

	return true;
}
bool Humanoid::TurnAndTrans( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV )
{
	// 全部关节为0 ==>　0.055f, -0.025f, -0.25f,
	// 静止状态 1：	0.0550	-0.0141	-0.2082		
	float T = 36.0f;
	//if( fabs(forLength) > EPS && fabs(forLength) < 0.03f )
	//{
	//	T = 40.0f;
	//}
	const float leftPhi = 7.0f / 40.0f * T;
	const float rightPhi = leftPhi + T/4.0f;
	const float phaseT = 3.0f / 40.0f * T;

	tempjointsV.resize( (unsigned int)(T / 2.0f + 0.1f) );

	float forStep = forLength;		// 前进： > 0.0f
	// 后退： < 0.0f
	float transLen = transLengh;	// 向左平移：
	// 向右平移：
	Angle turnAngle = turnAng;		// 向左转： > 0.0f

	float startTNum = 0.0f;
	if( mFootStep )
	{
		startTNum = T / 4.0f;
	}

	unsigned int tempjointsVNum = 0;
 	float m = mTurnAndTransFrameNum;

	//for( float m = 0.0f; m < T / 2.0f; m +=1.0f )
	{
		tempjointsVNum = (int)m;
		if( tempjointsVNum >= tempjointsV.size() )
		{
			tempjointsVNum = tempjointsVNum % tempjointsV.size();
		}
		else if( tempjointsVNum < 0 )
		{
			tempjointsVNum = 0;
		}
		float n = m + startTNum;
		float cycle = T * 0.25f;
		if( n >= T / 2.0f )
		{
			n -= T / 2.0f;
		}

		// ********** 平移 **************** //
		float standingTrans = 0.055f;
		//float basicTransLenth = 0.002f;
		//float basicDeltaLeftTrans  /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		//float basicDeltaRightTrans /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		//basicDeltaLeftTrans = -basicTransLenth;
		//basicDeltaRightTrans = basicTransLenth;

		//if( n < cycle )
		//{
		//	basicDeltaLeftTrans = basicTransLenth - basicTransLenth / cycle * n;
		//}
		//else
		//{
		//	basicDeltaLeftTrans = basicTransLenth - basicTransLenth / cycle * cycle + 2.0f * basicTransLenth * sin( 2*PI/(4*cycle)*(n-cycle)) - basicTransLenth / cycle * (n-cycle);
		//}
		//basicDeltaRightTrans = -basicDeltaLeftTrans;
 		float basicTransLenth = 0.002f;
 		float basicDeltaLeftTrans  /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
 		float basicDeltaRightTrans /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
 		basicDeltaLeftTrans = -basicTransLenth;
 		basicDeltaRightTrans = basicTransLenth;
		float leftTransStep = 0.0f;
		float rightTransStep = 0.0f;

		//if( transLen >= 0.0f )		
		//{
		//	leftTransStep = fabs(transLen) * fabs( cos( ( 2 * PI / T ) * (n) ) ) ;
		//	rightTransStep = fabs(transLen) * fabs( cos( ( 2 * PI / T ) * (n) ) );
		//}
		//else
		//{
		//	leftTransStep = fabs(transLen) * fabs( cos( ( 2 * PI / T ) * (n+T / 4.0f) ) ) ;
		//	rightTransStep = fabs(transLen) * fabs( cos( ( 2 * PI / T ) * (n+T / 4.0f) ) );
		//}
		float transLenAbs = fabs(transLen);
		if( transLen >= 0.0f )		
		{
			if( n < cycle )
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * n;
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*n) + transLenAbs / cycle * n;
			}
			else
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - transLenAbs / cycle * (n-cycle);
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n-cycle);
			}
		}
		else
		{
			if( n > cycle )
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * (n-cycle);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) + transLenAbs / cycle * (n-cycle);
			}
			else
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n)) - transLenAbs / cycle * (n);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n);
			}
		}

		float leftTransSum = basicDeltaLeftTrans - leftTransStep;
		float rightTransSum = basicDeltaRightTrans + rightTransStep;

		float leftTransLenth = -standingTrans + leftTransSum;
		float rightTransLenth = standingTrans + rightTransSum;

		// ********** 前进/后退 **************** //
		float forStepAbs = fabs( forStep );
		if( forStep >= 0.0f && forStep <= 0.005f )
		{
			forStepAbs = 0.005f;
		}
		else if( forStep < 0.0f && forStep >= -0.005f )
		{
			forStepAbs = -0.005f;
		}
		float forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		if( forStep < 0.0f )
		{
			forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		}
		if( forStandLen <= 0.01f )
		{
			forStandLen = 0.01f;
		}
		float leftForLenth;
		float rightForLenth;

		if( forStep >= 0.0f )
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * n;
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*n) - forStepAbs / cycle * n;
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - forStepAbs / cycle * (n-cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * (n-cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}
		else
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * (cycle-n);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(cycle-n)) - forStepAbs / cycle * (cycle-n);
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*((cycle-n)+cycle)) - forStepAbs / cycle * ((cycle-n)+cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * ((cycle-n)+cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}

		// ********** 转身 **************** //
		Angle steadyAngleAdjust = 2.0f;
		Angle turnAngAbs = fabs(turnAngle+steadyAngleAdjust);
		Angle turnLeft = 0.0f;		// > 0.0f;
		Angle turnRight = 0.0f;		// < 0.0f;

		if( turnAngle <= 0.0f )
		{
			if( n < cycle )
			{
				turnLeft = turnAngAbs / cycle * n;
			}
			else
			{
				turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n - cycle);
				//turnLeft = 0.0f;
			}
		}
		else
		{
			if( n >= cycle )
			{
				turnRight = -turnAngAbs / cycle * (n - cycle);
			}
			else
			{
				turnRight =  -turnAngAbs / cycle * cycle + turnAngAbs / cycle * n;
			}
		}

		float standingHeight = 0.05f * (fabs(forStepAbs) - 0.09f) + 0.224f;
		if( standingHeight <= 0.218f )
		{
			standingHeight = 0.218f;
		}
		standingHeight = 0.223f;
		standingHeight = 0.22f;
		float leftStepHeight = 0.0f;
		float rightStepHeight = 0.0f;
		float deltaHeight = 0.008f;
		float adjustHeight = 0.0021f;
		float deltaHeightProp = 1.0f / 0.08f * ( sqrt(fabs(forStepAbs*forStepAbs)/* + fabs(transLen*transLen) * 1.0f*/ )- 0.005f ) + 0.5f;
		//if( deltaHeightProp < 0.0f )
		//{
		//	deltaHeightProp = -deltaHeightProp;
		//	deltaHeightProp = 0.0f;
		//}

		if( forLength < 0.0f )
		{
			deltaHeightProp = -1.0f / 0.08f * ( (forLength) - 0.005f ) - 0.5f;
			//if( deltaHeightProp > 0.0f )
			//{
			//	deltaHeightProp = -deltaHeightProp;
			//	deltaHeightProp = 0.0f;
			//}
		}

 		if( n < T / 4.0f )
 		{
 			//leftStepHeight = -sqrt( standingHeight * standingHeight + leftForLenth * leftForLenth + leftTransSum * leftTransSum )-adjustHeight * 1.5f;
 			leftStepHeight = -standingHeight - deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) *deltaHeightProp/* * 0.5f*/;
 			//leftStepHeight = -standingHeight;
 		}
 		else
 		{
 			leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) * 1.2f - standingHeight+adjustHeight - leftForLenth * 0.1f;
 			//leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) - standingHeight+adjustHeight;leftTransSum
 		}
 
 		if( n >= T / 4.0f )
 		{
 			//rightStepHeight = -sqrt( standingHeight * standingHeight + rightForLenth * rightForLenth + rightTransSum * rightTransSum ) -adjustHeight * 1.5f;
 			rightStepHeight = -standingHeight + deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * deltaHeightProp/* * 0.5f*/;
 			//rightStepHeight = -standingHeight;
 		}
 		else
 		{
 			rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * 1.2f - standingHeight+adjustHeight - rightForLenth * 0.1f;
 			//rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) - standingHeight+adjustHeight;
 		}
// 		if( n < T / 4.0f )
// 		{
// 			leftStepHeight = -sqrt( standingHeight * standingHeight + leftForLenth * leftForLenth + leftTransSum * leftTransSum )-adjustHeight * 1.5f;
// 			leftStepHeight = -standingHeight - deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) *deltaHeightProp;
// 		}
// 		else
// 		{
// 			leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) - standingHeight+adjustHeight - leftForLenth * 0.1f;
// 		}
// 
// 		if( n >= T / 4.0f )
// 		{
// 			rightStepHeight = -sqrt( standingHeight * standingHeight + rightForLenth * rightForLenth + rightTransSum * rightTransSum ) -adjustHeight * 1.5f;
// 			rightStepHeight = -standingHeight + deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * deltaHeightProp;
// 		}
// 		else
// 		{
// 			rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) - standingHeight+adjustHeight - rightForLenth * 0.1f;
// 		}
		leftStepHeight *= 1.03f;
		rightStepHeight *= 1.03f;

		mUltiLeftForLen		= leftForLenth;
		mUltiLeftTransLen	= leftTransLenth;
		mUltiLeftHeight		= leftStepHeight;
		mUltiLeftTurn		= turnLeft;
		mUltiRightForLen	= rightForLenth;
		mUltiRightTransLen	= rightTransLenth;
		mUltiRightHeight	= rightStepHeight;
		mUltiRightTurn		= turnRight;

		if( !SetTarFoot( bLeftLeg, leftTransLenth, leftForLenth, leftStepHeight, turnLeft, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		if( !SetTarFoot( bRightLeg, rightTransLenth, rightForLenth, rightStepHeight, turnRight, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

 		float Arm_1 = -115.0f;
 		float Arm_2 = 0.0f;
 		float leftArm_3 = -90.0f;
 		float leftArm_4 = -85.0f;
 		float rightArm_3 = 90.0f;
 		float rightArm_4 = 85.0f;
 
 		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
 		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
 		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
 		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
 		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
 		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
 		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
 		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;

		GetJoints( tempjointsV.at( tempjointsVNum ) );
		//tempjointsVNum = (tempjointsVNum + 1)%tempjointsV.size();
	}

	mTurnAndTransFrameNum += 1.0f;

	return true;
}
bool Humanoid::QuickTurn( float turnAng, vector<Joint> &tempjointsV )
{
	// 全部关节为0 ==>　0.055f, -0.025f, -0.25f,
	// 静止状态 1：	0.0550	-0.0141	-0.2082		
	float T = 16.0f;
	const float leftPhi = 7.0f / 40.0f * T;
	const float rightPhi = leftPhi + T/4.0f;
	const float phaseT = 3.0f / 40.0f * T;
	float forLength = 0.0f;
	float transLengh = 0.0f;

	tempjointsV.resize( (unsigned int)(T / 2.0f + 0.1f) );

	float forStep = forLength;		// 前进： > 0.0f
	// 后退： < 0.0f
	float transLen = transLengh;	// 向左平移：
	// 向右平移：
	Angle turnAngle = turnAng;		// 向左转： > 0.0f

	bool leftStep = false;
	if( turnAng >= 0.0f )
	{	
		leftStep = true;
	}

	float startTNum = 0.0f;
	if( leftStep )
	{
		startTNum = T / 4.0f;
	}

	unsigned int tempjointsVNum = 0;

	float m = mQuickTurnFrameNum;

	//for( float m = 0.0f; m < T / 2.0f; m +=1.0f )
	{
		tempjointsVNum = (int)m;
		if( tempjointsVNum >= tempjointsV.size() )
		{
			tempjointsVNum = tempjointsVNum % tempjointsV.size();
		}
		else if( tempjointsVNum < 0 )
		{
			tempjointsVNum = 0;
		}
		float n = m + startTNum;
		float cycle = T * 0.25f;
		if( n >= T / 2.0f )
		{
			n -= T / 2.0f;
		}

		// ********** 平移 **************** //
		float standingTrans = 0.055f;
		float basicTransLenth = 0.002f;
		float basicDeltaLeftTrans  /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		float basicDeltaRightTrans /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		basicDeltaLeftTrans = -basicTransLenth;
		basicDeltaRightTrans = basicTransLenth;
		float leftTransStep = 0.0f;
		float rightTransStep = 0.0f;

		float leftTransSum = basicDeltaLeftTrans - leftTransStep;
		float rightTransSum = basicDeltaRightTrans + rightTransStep;

		float leftTransLenth = -standingTrans + leftTransSum;
		float rightTransLenth = standingTrans + rightTransSum;

		// ********** 前进/后退 **************** //
		float forStepAbs = fabs( forStep );
		if( forStep >= 0.0f && forStep <= 0.005f )
		{
			forStepAbs = 0.005f;
		}
		else if( forStep < 0.0f && forStep >= -0.005f )
		{
			forStepAbs = -0.005f;
		}
		float forStandLen = 0.011f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
 		if( forStandLen <= 0.01f )
 		{
 			forStandLen = 0.01f;
 		}
		float leftForLenth = -forStandLen;
		float rightForLenth = -forStandLen;

		// ********** 转身 **************** //
		Angle turnAngAbs = fabs(turnAngle);
		Angle turnLeft = 0.0f;		// > 0.0f;
		Angle turnRight = 0.0f;		// < 0.0f;

		if( turnAngle <= 0.0f )
		{
			if( n < cycle )
			{
				turnLeft = turnAngAbs / cycle * n;
			}
			else
			{
				turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n - cycle);
			}
		}
		else
		{
			if( n >= cycle )
			{
				turnRight = -turnAngAbs / cycle * (n - cycle);
			}
			else
			{
				turnRight =  -turnAngAbs / cycle * cycle + turnAngAbs / cycle * n;
			}
		}

		float standingHeight = 0.223f;
		standingHeight = 0.22f;
		float leftStepHeight = 0.0f;
		float rightStepHeight = 0.0f;
		float deltaHeight = 0.0005f;
		float adjustHeight = 0.0021f;
		float deltaHeightProp = 1.0f / 0.08f * ( fabs(forStepAbs) - 0.005f ) + 0.5f;

		if( n < T / 4.0f )
		{
			leftStepHeight = -standingHeight - deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) *deltaHeightProp;
		}
		else
		{
			leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) - standingHeight+adjustHeight - leftForLenth * 0.1f;
		}

		if( n >= T / 4.0f )
		{
			rightStepHeight = -standingHeight + deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * deltaHeightProp;
		}
		else
		{
			rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) - standingHeight+adjustHeight - rightForLenth * 0.1f;
		}

		leftStepHeight *= 1.03f;
		rightStepHeight *= 1.03f;

		mUltiLeftForLen		= leftForLenth;
		mUltiLeftTransLen	= leftTransLenth;
		mUltiLeftHeight		= leftStepHeight;
		mUltiLeftTurn		= turnLeft;
		mUltiRightForLen	= rightForLenth;
		mUltiRightTransLen	= rightTransLenth;
		mUltiRightHeight	= rightStepHeight;
		mUltiRightTurn		= turnRight;

		if( !SetTarFoot( bLeftLeg, leftTransLenth, leftForLenth, leftStepHeight, turnLeft, cBodyAngle/* - 2.0f*/, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		if( !SetTarFoot( bRightLeg, rightTransLenth, rightForLenth, rightStepHeight, turnRight, cBodyAngle/* - 2.0f*/, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		/*float Arm_1 = -115.0f;
		float Arm_2 = 0.0f;
		float leftArm_3 = -90.0f;
		float leftArm_4 = -85.0f;
		float rightArm_3 = 90.0f;
		float rightArm_4 = 85.0f;

		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;*/

		float lArm_1 = -115.0f;	//-115.0f;
		float lArm_2 = 0.0f;	//0.0f;
		float lArm_3 = -85.0f;	//-85.0f;
		float lArm_4 = -0.0f;	//-85.0f;
		float rArm_1 = -115.0f;		//-115.0f;	
		float rArm_2 = 0.0f;		//0.0f;	
		float rArm_3 = 85.0f;		//85.0f;	
		float rArm_4 = 0.0f;		//85.0f;	
// 
// 		if( n > cycle )
// 		{
// 			lArm_1 = -80.0f - 25 * sin( PI *(n -cycle) /cycle);
// 			rArm_1 = -80.0f + 25 * sin( PI *(n -cycle) /cycle);
// 		}
// 		else
// 		{
// 			lArm_1 = -80.0f + 25 * sin( PI * n / cycle);
// 			rArm_1 = -80.0f - 25 * sin( PI * n / cycle);
// 		}

		mUpperJoints.at(3).q = lArm_1 * PI / 180.0f;
		mUpperJoints.at(7).q = rArm_1 * PI / 180.0f;
		mUpperJoints.at(4).q = lArm_2 * PI / 180.0f;
		mUpperJoints.at(8).q = rArm_2 * PI / 180.0f;
		mUpperJoints.at(5).q = lArm_3* PI / 180.0f;
		mUpperJoints.at(9).q = rArm_3* PI / 180.0f;
		mUpperJoints.at(6).q = lArm_4* PI / 180.0f;
		mUpperJoints.at(10).q = rArm_4* PI / 180.0f;

		GetJoints( tempjointsV.at( tempjointsVNum ) );
		//tempjointsVNum = (tempjointsVNum + 1)%tempjointsV.size();
	}
	m +=1.0f;
	mQuickTurnFrameNum += 1.0f;
	return true;
}
bool Humanoid::SteadyAdjust( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV )
{
	// 全部关节为0 ==>　0.055f, -0.025f, -0.25f,
	// 静止状态 1：	0.0550	-0.0141	-0.2082		
	float T = 24.0f;
	//if( fabs(forLength) > EPS && fabs(forLength) < 0.03f )
	//{
	//	T = 40.0f;
	//}
	const float leftPhi = 7.0f / 40.0f * T;
	const float rightPhi = leftPhi + T/4.0f;
	const float phaseT = 3.0f / 40.0f * T;

	tempjointsV.resize( (unsigned int)(T / 2.0f + 0.1f) );

	float forStep = forLength;		// 前进： > 0.0f
	// 后退： < 0.0f
	float transLen = transLengh;	// 向左平移：
	// 向右平移：
	Angle turnAngle = turnAng;		// 向左转： > 0.0f

	float startTNum = 0.0f;
	if( mFootStep )
	{
		startTNum = T / 4.0f;
	}

	unsigned int tempjointsVNum = 0;
	float m = mSteadyAdjustFrameNum;

	{
		tempjointsVNum = (int)m;
		if( tempjointsVNum >= tempjointsV.size() )
		{
			tempjointsVNum = tempjointsVNum % tempjointsV.size();
		}
		else if( tempjointsVNum < 0 )
		{
			tempjointsVNum = 0;
		}
		float n = m + startTNum;
		float cycle = T * 0.25f;
		if( n >= T / 2.0f )
		{
			n -= T / 2.0f;
		}

		// ********** 平移 **************** //
		float standingTrans = 0.055f;
		float basicTransLenth = 0.002f;
		float basicDeltaLeftTrans  /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		float basicDeltaRightTrans /*= basicTransLenth * sin( ( 2 * PI / (T / 2.0f) ) * n )*/;
		basicDeltaLeftTrans = -basicTransLenth;
		basicDeltaRightTrans = basicTransLenth;
		float leftTransStep = 0.0f;
		float rightTransStep = 0.0f;
		float transLenAbs = fabs(transLen);
		if( transLen >= 0.0f )		
		{
			if( n < cycle )
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * n;
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*n) + transLenAbs / cycle * n;
			}
			else
			{
				leftTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - transLenAbs / cycle * (n-cycle);
				rightTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n-cycle);
			}
		}
		else
		{
			if( n > cycle )
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * (n-cycle);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n-cycle)) + transLenAbs / cycle * (n-cycle);
			}
			else
			{
				rightTransStep = transLenAbs - transLenAbs / cycle * cycle + 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*(n)) - transLenAbs / cycle * (n);
				leftTransStep = transLenAbs - 2.0f * transLenAbs * sin( 2*PI/(4*cycle)*cycle) + transLenAbs / cycle * cycle + transLenAbs / cycle * (n);
			}
		}

		float leftTransSum = basicDeltaLeftTrans - leftTransStep;
		float rightTransSum = basicDeltaRightTrans + rightTransStep;

		float leftTransLenth = -standingTrans + leftTransSum;
		float rightTransLenth = standingTrans + rightTransSum;

		// ********** 前进/后退 **************** //
		float forStepAbs = fabs( forStep );
		if( forStep >= 0.0f && forStep <= 0.005f )
		{
			forStepAbs = 0.005f;
		}
		else if( forStep < 0.0f && forStep >= -0.005f )
		{
			forStepAbs = -0.005f;
		}
		float forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		if( forStep < 0.0f )
		{
			forStandLen = 0.01f + ( forStepAbs - 0.02f ) / 0.065f * 0.008f;
		}
		if( forStandLen <= 0.01f )
		{
			forStandLen = 0.01f;
		}
		float leftForLenth;
		float rightForLenth;

		if( forStep >= 0.0f )
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * n;
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*n) - forStepAbs / cycle * n;
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(n-cycle)) - forStepAbs / cycle * (n-cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * (n-cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}
		else
		{
			if( n < cycle )
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * (cycle-n);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*(cycle-n)) - forStepAbs / cycle * (cycle-n);
			}
			else
			{
				leftForLenth = forStepAbs * 0.5f - forStepAbs / cycle * cycle + 2 * forStepAbs * sin( 2*PI/(4*cycle)*((cycle-n)+cycle)) - forStepAbs / cycle * ((cycle-n)+cycle);
				rightForLenth = -forStepAbs * 0.5f + 2 * forStepAbs * sin( 2*PI/(4*cycle)*cycle) - forStepAbs / cycle * cycle - forStepAbs / cycle * ((cycle-n)+cycle);
			}

			leftForLenth -= forStandLen;
			rightForLenth -= forStandLen;
		}

		// ********** 转身 **************** //
		Angle steadyAngleAdjust = 2.0f;
		Angle turnAngAbs = fabs(turnAngle+steadyAngleAdjust);
		Angle turnLeft = 0.0f;		// > 0.0f;
		Angle turnRight = 0.0f;		// < 0.0f;

		if( turnAngle <= 0.0f )
		{
			if( n < cycle )
			{
				turnLeft = turnAngAbs / cycle * n;
			}
			else
			{
				turnLeft =  turnAngAbs / cycle * cycle - turnAngAbs / cycle * (n - cycle);
			}
		}
		else
		{
			if( n >= cycle )
			{
				turnRight = -turnAngAbs / cycle * (n - cycle);
			}
			else
			{
				turnRight =  -turnAngAbs / cycle * cycle + turnAngAbs / cycle * n;
			}
		}

		float standingHeight = 0.05f * (fabs(forStepAbs) - 0.09f) + 0.224f;
		if( standingHeight <= 0.218f )
		{
			standingHeight = 0.218f;
		}
		standingHeight = 0.223f;
		standingHeight = 0.22f;
		float leftStepHeight = 0.0f;
		float rightStepHeight = 0.0f;
		float deltaHeight = 0.001f;
		float adjustHeight = 0.0021f;
		float deltaHeightProp = 1.0f / 0.08f * ( sqrt(fabs(forStepAbs*forStepAbs)/* + fabs(transLen*transLen) * 1.0f*/ )- 0.005f ) + 0.5f;

		if( forLength < 0.0f )
		{
			deltaHeightProp = -1.0f / 0.08f * ( (forLength) - 0.005f ) - 0.5f;
		}

		if( n < T / 4.0f )
		{
			leftStepHeight = -standingHeight - deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) *deltaHeightProp/* * 0.5f*/;
		}
		else
		{
			leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n) ) * 1.2f - standingHeight+adjustHeight - leftForLenth * 0.1f;
		}

		if( n >= T / 4.0f )
		{
			rightStepHeight = -standingHeight + deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * deltaHeightProp/* * 0.5f*/;
		}
		else
		{
			rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n) ) * 1.2f - standingHeight+adjustHeight - rightForLenth * 0.1f;
		}
		leftStepHeight *= 1.03f;
		rightStepHeight *= 1.03f;

		mUltiLeftForLen		= leftForLenth;
		mUltiLeftTransLen	= leftTransLenth;
		mUltiLeftHeight		= leftStepHeight;
		mUltiLeftTurn		= turnLeft;
		mUltiRightForLen	= rightForLenth;
		mUltiRightTransLen	= rightTransLenth;
		mUltiRightHeight	= rightStepHeight;
		mUltiRightTurn		= turnRight;

		if( !SetTarFoot( bLeftLeg, leftTransLenth, leftForLenth, leftStepHeight, turnLeft, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		if( !SetTarFoot( bRightLeg, rightTransLenth, rightForLenth, rightStepHeight, turnRight, cBodyAngle, tempjointsVNum ) )
		{
			IllegalJointLog( forLength, transLengh, turnAng );
		}

		float Arm_1 = -115.0f;
		float Arm_2 = 0.0f;
		float leftArm_3 = -90.0f;
		float leftArm_4 = -85.0f;
		float rightArm_3 = 90.0f;
		float rightArm_4 = 85.0f;

		int ntemp = (unsigned int)(T / 4.0f + 0.1f);
		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;

		//float lArm_1 = -115.0f;	//-115.0f;
		//float lArm_2 = 0.0f;	//0.0f;
		//float lArm_3 = -85.0f;	//-85.0f;
		//float lArm_4 = -0.0f;	//-85.0f;
		//float rArm_1 = -115.0f;		//-115.0f;	
		//float rArm_2 = 0.0f;		//0.0f;	
		//float rArm_3 = 85.0f;		//85.0f;	
		//float rArm_4 = 0.0f;		//85.0f;	

// 		if( n > cycle )
// 		{
// 			lArm_1 = -85.0f - 20 * sin( PI *(n -cycle) /cycle);
// 			rArm_1 = -85.0f + 20 * sin( PI *(n -cycle) /cycle);
// 		}
// 		else
// 		{
// 			lArm_1 = -85.0f + 20 * sin( PI * n / cycle);
// 			rArm_1 = -85.0f - 20 * sin( PI * n / cycle);
// 		}

// 		mUpperJoints.at(3).q = lArm_1 * PI / 180.0f;
// 		mUpperJoints.at(7).q = rArm_1 * PI / 180.0f;
// 		mUpperJoints.at(4).q = lArm_2 * PI / 180.0f;
// 		mUpperJoints.at(8).q = rArm_2 * PI / 180.0f;
// 		mUpperJoints.at(5).q = lArm_3* PI / 180.0f;
// 		mUpperJoints.at(9).q = rArm_3* PI / 180.0f;
// 		mUpperJoints.at(6).q = lArm_4* PI / 180.0f;
// 		mUpperJoints.at(10).q = rArm_4* PI / 180.0f;


		//mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
 	//	mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
 	//	mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
 	//	mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
 	//	mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
 	//	mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
 	//	mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
 	//	mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;

		GetJoints( tempjointsV.at( tempjointsVNum ) );
		//tempjointsVNum = (tempjointsVNum + 1)%tempjointsV.size();
	}


	mSteadyAdjustFrameNum += 1.0f;

	return true;
}
bool Humanoid::BufferAction( vector<Joint> &tempjointsV )
{	
	unsigned standByFrameNum = 8;
	unsigned int tempjointsVNum = 0;
 	const float T = 0.0f;	

 	tempjointsV.resize( (unsigned int)(T / 2.0f + 0.1f) + standByFrameNum );
// 
// 	float startTNum = 0.0f;
// 	if( mFootStep )
// 	{
// 		startTNum = T / 4.0f;
// 	}
// 
// 
// 	for( float m = 0.0f; m < T / 2.0f; m +=1.0f )
// 	{
// 		float n = m + startTNum;
// 		float cycle = T * 0.25f;
// 
// 		// ********** 平移 **************** //
// 		float standingTrans = 0.055f;
// 
// 		float leftTransLenth = -standingTrans;
// 		float rightTransLenth = standingTrans;
// 
// 		// ********** 前进/后退 **************** //
// 		float leftForLenth = -0.01f;
// 		float rightForLenth = -0.01f;	
// 
// 		Angle turnLeft = 0.0f;		// > 0.0f;
// 		Angle turnRight = 0.0f;		// < 0.0f;
// 
// 		float standingHeight = -0.2247f;
// 		float deltaHeight = 0.008f;
// 		float leftStepHeight;
// 		float rightStepHeight;
// 
// 		leftStepHeight = -deltaHeight * sin( ( 2 * PI / T * 2) * (n+T/4.0f + 1.0f) ) +standingHeight; 
// 		rightStepHeight = deltaHeight * sin( ( 2 * PI / T * 2 ) * (n+T/4.0f+ 1.0f) ) +standingHeight; 
// cout<< "		"
// 	<< leftStepHeight << " "
// 	<< leftForLenth << " "
// 	<< leftTransLenth << endl;
// 		SetTarFoot( bLeftLeg, leftTransLenth, leftForLenth, leftStepHeight, turnLeft );
// 		SetTarFoot( bRightLeg, rightTransLenth, rightForLenth, rightStepHeight, turnRight );
// 
// 		float Arm_1 = -115.0f;
// 		float Arm_2 = 0.0f;
// 		float leftArm_3 = -90.0f;
// 		float leftArm_4 = -85.0f;
// 		float rightArm_3 = 90.0f;
// 		float rightArm_4 = 85.0f;
// 
// 		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
// 		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
// 		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
// 		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
// 		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
// 		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
// 		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
// 		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;
// 
// 		GetJoints( tempjointsV.at( tempjointsVNum ) );
// 		tempjointsVNum ++;
// 	}

	for( int i = 0; i < standByFrameNum; i ++ )
	{
		Angle bodyAng = 7.5f;

		SetTarFoot( bLeftLeg, -0.055f, -0.015f, -0.2247f, 0.0f, bodyAng, tempjointsVNum );
		SetTarFoot( bRightLeg, 0.055f, -0.015f, -0.2247f, 0.0f, bodyAng, tempjointsVNum );

 		float Arm_1 = -115.0f;
 		float Arm_2 = 0.0f;
 		float leftArm_3 = -90.0f;
 		float leftArm_4 = -85.0f;
 		float rightArm_3 = 90.0f;
 		float rightArm_4 = 85.0f;
 
 		mUpperJoints.at(3).q = Arm_1 * PI / 180.0f;
 		mUpperJoints.at(7).q = Arm_1 * PI / 180.0f;
 		mUpperJoints.at(4).q = Arm_2 * PI / 180.0f;
 		mUpperJoints.at(8).q = Arm_2 * PI / 180.0f;
 		mUpperJoints.at(5).q = leftArm_3 * PI / 180.0f;
 		mUpperJoints.at(9).q = rightArm_3 * PI / 180.0f;
 		mUpperJoints.at(6).q = leftArm_4 * PI / 180.0f;
 		mUpperJoints.at(10).q = rightArm_4 * PI / 180.0f;
	
		GetJoints( tempjointsV.at( tempjointsVNum ) );
		tempjointsVNum ++;
	}

	return true;
}
void Humanoid::ResetFrameNum()
{
	float walkT = 36.0f;
	float startTNum = 0.0f;

	if( mFootStep )
	{
		startTNum = walkT / 4.0f;
	}

	mWalkFrameNum = startTNum;
	mTurnAndTransFrameNum = 0.0f;
	mQuickTurnFrameNum = 0.0f;
	mSteadyAdjustFrameNum = 0.0f;
}
void Humanoid::ResetFrameNum( float forLen )
{
	float walkT = 36.0f;
// 	if( fabs(forLen) < 0.06f )
// 	{
// 		walkT = 40.0f;
// 	}
	float startTNum = 0.0f;

	if( mFootStep )
	{
		startTNum = walkT / 4.0f;
	}

	mWalkFrameNum = startTNum;
	mTurnAndTransFrameNum = 0.0f;
	mQuickTurnFrameNum = 0.0f;
	mSteadyAdjustFrameNum = 0.0f;
}
void Humanoid::SetFootStep()
{
	mFootStep = !mFootStep;
}
