#include "BasicWalk.h"
#define PeocessingLog gProcessingLog <<"[BasicWalk ] "

BasicWalk::BasicWalk()
{
    mLLeg = new Kinematics(Kinematics_Left);
	mRLeg = new Kinematics(Kinematics_Right);
	BasicWalkInit();
}
BasicWalk::~BasicWalk()
{
	if(mLLeg)
	{
		delete mLLeg;
		mLLeg = NULL;
	}
	if(mRLeg)
	{
		delete mRLeg;
		mRLeg = NULL;
	}
}

void BasicWalk::BasicWalkInit()
{
	//fop.open( "action.dat" );

	float tem_angle[6];
	float tem[22]={	0.00, 0.00,  -115,		 0.00, -85.00,	 -85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,  -115,		 0.00, 85.00,	 85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,};
	float tem_test[3];
	
	memcpy(mAngle,tem,22*sizeof(float));

    IsyMoveLeft = true;
	IsTurnLeft = true;
	Is2LegsTurn = false;
	//StepLenX + StepLenY<=0.08 保持稳定
	StepLenX = 0.00f;
	StepLenY = 0.00f;
	TurnAng = 0.0f *PI/180.0f;
	mZ = -0.2261f;
   	
	//以下为单腿旋转时的调整
	//TurnAng *= 1.23f;//10度以下调整
	//TurnAng *= 1.36f;

	
	//the following parameters are adjustable
	detCenteOfMx = 0.002f;
	detCenteOfMy_multi = 0.012f;

	g = 9.81;
	T = 0.02;
	g *= 0.1;
	Tc = sqrt(fabs(mZ/g));

	Cycle = 10;

	memcpy(tem_angle,&mAngle[6],6*sizeof(float));
	mLLeg->InitialAngle(tem_angle);
	mLLeg->ForwardKine(0);
	mLLeg->SetTarget(mLLeg->GetmJP(6),mLLeg->GetmJR(6));
	
	memcpy(InitR,mLLeg->GetmJR(6),9*sizeof(float));//左右腿的R相同

	memcpy(tem_angle,&mAngle[16],6*sizeof(float));
	mRLeg->InitialAngle(tem_angle);
	mRLeg->ForwardKine(0);
	mRLeg->SetTarget(mRLeg->GetmJP(6),mRLeg->GetmJR(6));

    InitCenterofM_X();

	memcpy(InitP_L,mLLeg->GetTargetP(),3*sizeof(float));
    memcpy(InitP_R,mRLeg->GetTargetP(),3*sizeof(float));
	memcpy(NowP_L,InitP_L,3*sizeof(float));
	memcpy(NowP_R,InitP_R,3*sizeof(float));
	
	//CalWalk();
	
    //fop.close();

}

void BasicWalk::CalWalk(float forLength, float transLengh, float turnAngle, vector<Joint> &tempjointsV)
{
	if ( FrameNum==1)
	{
		StepLenX = forLength;
		StepLenY = transLengh;
		TurnAng = turnAngle *1.23f;
		if (StepLenY > 0.0f)
		{
			IsyMoveLeft = true;
		} 
		else
		{
			StepLenY = -StepLenY;
			IsyMoveLeft = false;
		}
	}
	
	//StepLenY = transLengh;
	PeocessingLog << "CalWalk "<< " IsLeftLegStay:"<<IsLeftLegStay<<"  "<<FrameNum<<"  forLength  "<<forLength<<"  transLengh "<<transLengh<<"  turnAng "<<turnAngle<<"\n";
	tempjointsV.resize(Cycle);
	
	
    //StateInit();
	//for (int i=0; i<10; i++)
	{
		if (FrameNum ==1)
		{
			memcpy(NowR_L,InitR,9*sizeof(float));
			memcpy(NowR_R,InitR,9*sizeof(float));
		}

		if (FrameNum ==1)
		{
			CalXY();
			InitCenterofM_Y();
		}

		if (!IsLeftLegStay)
		{
			RLegS(tempjointsV);
		}
		else 
		{
			LLegS(tempjointsV);
		}

		if (FrameNum == Cycle)
		{
			IsLeftLegStay = !IsLeftLegStay;
			memcpy(NowR_L,mLLeg->GetTargetR(),9*sizeof(float));
			memcpy(NowR_R,mRLeg->GetTargetR(),9*sizeof(float));
		}

		FrameNum++;

		if (FrameNum > 2*Cycle)
		{
			FrameNum = 1;
			IsLeftLegStay = !IsLeftLegStay;
		}
	  
	}


}


void BasicWalk::RLegS(vector<Joint> &tempjointsV)
{
	//正常10周期的步行，右脚支撑
	int ii = FrameNum % Cycle;
	if (ii==0) ii = Cycle;
	
	//for (int ii=1; ii<Cycle+1; ii++)
	{
		InverInit();

		UpdateTarFoot(mRLeg,mLLeg,x[ii]-x[0],(float)StepLenY/Cycle*ii,ii,(float)ii/Cycle,NowP_R,NowP_L,NowR_R,NowR_L,tempjointsV);
	}
	if (ii == Cycle)
	{
		NowP_L[1] = InitP_L[1] + StepLenX/2;
		NowP_R[1] = InitP_R[1] - StepLenX/2;
		if (IsyMoveLeft)
		{
			NowP_L[0] = InitP_L[0] - StepLenY;
			NowP_R[0] = InitP_R[0] + StepLenY;
		}
		else
		{
			NowP_L[0] = InitP_L[0];
			NowP_R[0] = InitP_R[0];
		}
	}
	
	
}
void BasicWalk::LLegS(vector<Joint> &tempjointsV)
{
	//正常10周期的步行，左脚支撑
	int ii = FrameNum % Cycle;
	if (ii==0) ii = Cycle;
	
	//for (int ii=1; ii<Cycle+1; ii++)
	{
		InverInit();
		
		UpdateTarFoot(mLLeg,mRLeg,x[ii]-x[0],(float)StepLenY/Cycle*ii,ii,(float)ii/Cycle,NowP_L,NowP_R,NowR_L,NowR_R,tempjointsV);
	}
	if (ii == Cycle)
	{
		NowP_L[1] = InitP_L[1] - StepLenX/2;
		NowP_R[1] = InitP_R[1] + StepLenX/2;
		if (IsyMoveLeft)
		{
			NowP_L[0] = InitP_L[0];
			NowP_R[0] = InitP_R[0];
		} 
		else
		{
			NowP_L[0] = InitP_L[0] - StepLenY;
			NowP_R[0] = InitP_R[0] + StepLenY;
		}
	}
	
	
}
void BasicWalk::UpdateTarFoot(Kinematics *mLegS,Kinematics *mLegM,float xMove,float yMove,int i,float per,float NowPosS[],float NowPosM[],float NowRS[],float NowRM[], vector<Joint> &tempjointsV)
{	
	float tem_p[3];
	float deltaHeight = 0.0005f;
	float adjustHeight = 0.0021f;
	float deltaHeightProp = 1.0f / 0.08f * ( fabs(StepLenX) - 0.005f ) + 0.5f;
	
    //支撑腿
	if (IsyMoveLeft)
	{
		tem_p[0] = NowPosS[0] + yMove;
	}
	else
	{
		tem_p[0] = NowPosS[0] - yMove;
	}
    tem_p[1] = NowPosS[1] - xMove;
	
	tem_p[2] = mZ + 0.07f* StepLenX * sin( PI * (1 + per));
	/*
	if (Cycle == Cycle_QuickTurn)
	{
		tem_p[2] = mZ - deltaHeight * sin( PI / Cycle * FrameNum ) *deltaHeightProp;
	}
	*/
	if (Cycle == Cycle_QuickTrans)
	{
		tem_p[2] = mZ; //+ 0.07f* StepLenX * sin( PI * (1 + per));

	}

	mLegS->SetTarget(tem_p);
	if (FrameNum > Cycle) 
	{
		Turnangle(mLegS,NowRS,(float)-TurnAng/Cycle*i);
	}
	else if (Is2LegsTurn)
	{
		Turnangle(mLegS,NowRS,(float)-TurnAng/Cycle*i);
	}
	mLegS->InverseKine(6);

    //游动腿
	if (IsyMoveLeft)
	{
		tem_p[0] = NowPosM[0] - yMove;
	}
	else
	{
		tem_p[0] = NowPosM[0] + yMove ;
	}
	
	tem_p[1] = NowPosM[1] + xMove;
	
	tem_p[2] = mZ + 0.011f * sin( PI * per) + 0.0035f;
/*
	if (Cycle == Cycle_QuickTurn)
	{
		tem_p[2] = mZ - deltaHeight * sin( PI / Cycle * FrameNum ) +adjustHeight - StepLenX * 0.1f;
	}
*/
	if (Cycle == Cycle_QuickTrans)
	{
		tem_p[2] = mZ + 0.007f * sin( PI * per);// + 0.0035f;

	}

	mLegM->SetTarget(tem_p);
	if (FrameNum < Cycle+1) 
	{
		Turnangle(mLegM,NowRM,(float)TurnAng/Cycle*i);
	}
	else if (Is2LegsTurn)
	{
		Turnangle(mLegM,NowRM,(float)TurnAng/Cycle*i);
	}
	mLegM->InverseKine(6);
	
	SetJoints(tempjointsV.at( (FrameNum-1) % Cycle) );
}

void BasicWalk::StateInit()
{
	if (IsyMoveLeft && IsTurnLeft)
	{
		NowP_L[1] = InitP_L[1] - StepLenX/2;
		NowP_R[1] = InitP_R[1] + StepLenX/2;
	} 
	else if (!IsyMoveLeft && !IsTurnLeft)
	{
		NowP_L[1] = InitP_L[1] + StepLenX/2;
		NowP_R[1] = InitP_R[1] - StepLenX/2;
		
	}
	
}

void BasicWalk::InverInit()
{
	float tem_angle[6];
	float tem[22]={	0.00, 0.00,  -115,		 0.00, -85.00,	 -85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,  -115,		 0.00, 85.00,	 85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,};
	memcpy(mAngle,tem,22*sizeof(float));

	memcpy(tem_angle,&mAngle[6],6*sizeof(float));
	mLLeg->InitialAngle(tem_angle);
	

	memcpy(tem_angle,&mAngle[16],6*sizeof(float));
	mRLeg->InitialAngle(tem_angle);
  	
	
}
void BasicWalk::InitCenterofM_X()
{
	float tem[3];

	memcpy(tem,mLLeg->GetmJP(6),3*sizeof(float));
	tem[1] = tem[1] + detCenteOfMx;
	mLLeg->SetTarget(tem,mLLeg->GetmJR(6));

	memcpy(tem,mRLeg->GetmJP(6),3*sizeof(float));
	tem[1] = tem[1] + detCenteOfMx;
	mRLeg->SetTarget(tem,mRLeg->GetmJR(6));

}
void BasicWalk::InitCenterofM_Y()
{
    if (!IsLeftLegStay)
	{
		NowP_R[0] = NowP_R[0] - StepLenX * detCenteOfMy_multi;
	} 
	else
	{
		NowP_L[0] = NowP_L[0] + StepLenX * detCenteOfMy_multi;
	}
	
}

float BasicWalk::CalNextMove(float t,float x,float v)
{
	return(x * cosh(t/Tc) + Tc * v * sinh(t/Tc));
}

void BasicWalk::Turnangle(Kinematics *tLeg,float NowR[],float tAngle)
{
	Matrix tem_R(3,3,NowR);
	Matrix tem_ch_R;
	tem_ch_R.MakeUnitMatrix(3);
	
	if (fabs(tAngle-0.0f)>EPS)
	{
		tem_ch_R.SetElement(0,0,cos(tAngle));
		tem_ch_R.SetElement(0,1,-sin(tAngle));
		tem_ch_R.SetElement(1,0,sin(tAngle));
		tem_ch_R.SetElement(1,1,cos(tAngle));
	}
	

	tem_ch_R = tem_ch_R * tem_R;
	tLeg->SetTarget(tLeg->GetTargetP(),tem_ch_R.GetData());

}
void BasicWalk::CalXY()
{
	float Vx_0; 
	float Vy_0;
	int n = Cycle+1;



	x[0] = -StepLenX/2;
	Vx_0 = (-x[0]) * (cosh(T*Cycle/Tc)+1)/(Tc*sinh(T*Cycle/Tc));
	for (int i=1; i<n; i++)
	{
		x[i] = CalNextMove(T*i,x[0],Vx_0);
	}
	
	y[0] = -StepLenY/2;
    Vy_0 = (-y[0]) * (cosh(T*Cycle/Tc)+1)/(Tc*sinh(T*Cycle/Tc));
	for (int i=1; i<n; i++)
	{
		y[i] = CalNextMove(T*i,y[0],Vy_0);
	}
     
	

}
void BasicWalk::ChangeVtest()
{
    static int count = 0;
	if (StepLenX >= 0.07)
	{
		StepLenX = 0.07;
		count++;
	}
	else 
	{
		StepLenX += 0.02;
	}
	if (count>10)
	{
		StepLenX -=0.02;
		if (StepLenX<0)
		{
			StepLenX=0.01;
		}
	}

}
/*void BasicWalk::PrintDat()
{
	float tem[22]={	0.00, 0.00,  -115,		 0.00, -85.00,	 -85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,  -115,		 0.00, 85.00,	 85.00,	 0.00, 0.00, 32.16, -65.17, 40.01, 0.00,};
    float *tem_l;
	float *tem_r;
	float tem_l_angle[6];
	float tem_r_angle[6];

 	tem_l = mLLeg->GetAngle();
 	tem_r = mRLeg->GetAngle();

	memcpy(tem_l_angle,tem_l,6*sizeof(float));
	memcpy(tem_r_angle,tem_r,6*sizeof(float));


	for (int i=0; i<6; i++)
	{
        tem[6+i] = tem_l_angle[i]*180/PI;
		std::cout<<tem[6+i] <<',';
	}
	std::cout<<std::endl;
	for (int i=0; i<6; i++)
	{
		tem[16+i] = tem_r_angle[i]*180/PI;
		std::cout<<tem[16+i] <<',';
	}
	std::cout<<std::endl;
/*
	float tem_l_jr[9];
	float tem_l_jp[3];
	memcpy(tem_l_jr,mLLeg.GetmJR(6),9*sizeof(float));
	memcpy(tem_l_jp,mLLeg.GetmJP(6),3*sizeof(float));
	for (int i=0; i<9; i++)
	{
		std::cout<<tem_l_jr[i] <<"   ";
		if ((i+1)%3==0)
		{
			std::cout<<std::endl;
		}
	}
	for (int i=0; i<3; i++)
	{
		std::cout<<tem_l_jp[i] <<"   ";
	}
	std::cout<<std::endl;

	float tem_r_jr[9];
	float tem_r_jp[3];
	memcpy(tem_r_jr,mRLeg.GetmJR(6),9*sizeof(float));
	memcpy(tem_r_jp,mRLeg.GetmJP(6),3*sizeof(float));
	for (int i=0; i<9; i++)
	{
		std::cout<<tem_r_jr[i] <<"   ";
		if ((i+1)%3==0)
		{
			std::cout<<std::endl;
		}
	}
	for (int i=0; i<3; i++)
	{
		std::cout<<tem_r_jp[i] <<"   ";
	}
	std::cout<<std::endl;


	
	std::cout<<std::endl;
	for (int i=0; i<22; i++)
	{
		fop<<tem[i]<<',';
	}
	fop<<std::endl;
	
	
}
*/

/*void BasicWalk::Jumptest()
{
	float tem_l_p[3];
	float tem_r_p[3];
	memcpy(tem_l_p,mLLeg->GetmJP(6),3*sizeof(float));
	memcpy(tem_r_p,mRLeg->GetmJP(6),3*sizeof(float));
	for(int i=1;i <4; i++)
	{
		tem_l_p[2] +=0.015;
		tem_r_p[2] +=0.015;
		mLLeg->SetTarget(tem_l_p);
		mRLeg->SetTarget(tem_r_p);
		mLLeg->InverseKine(6);
		mRLeg->InverseKine(6);
		PrintDat();
	}
	for (int i=0; i<10; i++)
	{
		PrintDat();
	}
     PrintDat();
	for(int i=1;i <3; i++)
	{
		tem_l_p[2] -=0.03;
		tem_r_p[2] -=0.03;
		mLLeg->SetTarget(tem_l_p);
		mRLeg->SetTarget(tem_r_p);
		mLLeg->InverseKine(6);
		mRLeg->InverseKine(6);
		PrintDat();
	}

}
*/
/*
void BasicWalk::KeepState(int i)
{
	for (int j=0; j<i; j++)
	{
		PrintDat();
	}
}
*/
void BasicWalk::SetJoints(Joint &joints)
{
	float Arm_1 = -115.0f;
	float Arm_2 = 0.0f;
	float leftArm_3 = -90.0f;
	float leftArm_4 = -85.0f;
	float rightArm_3 = 90.0f;
	float rightArm_4 = 85.0f;

	joints.joint[Head_1] = 0.0f;
	joints.joint[Head_2] = 0.0f;
	joints.joint[LARM_1] = Arm_1;
	joints.joint[RARM_1] = Arm_1;
	joints.joint[LARM_2] = Arm_2;
	joints.joint[RARM_2] = Arm_2;
	joints.joint[LARM_3] = leftArm_3;
	joints.joint[RARM_3] = rightArm_3;
	joints.joint[LARM_4] = leftArm_4;
	joints.joint[RARM_4] = rightArm_4;

	joints.joint[LLEG_1] = mLLeg->GetAngle(1) *180.0f/PI;
	joints.joint[RLEG_1] = mRLeg->GetAngle(1) *180.0f/PI;
	joints.joint[LLEG_2] = mLLeg->GetAngle(2)  *180.0f/PI;
	joints.joint[RLEG_2] = mRLeg->GetAngle(2) *180.0f/PI;
	joints.joint[LLEG_3] = mLLeg->GetAngle(3) *180.0f/PI;
	joints.joint[RLEG_3] = mRLeg->GetAngle(3) *180.0f/PI;
	joints.joint[LLEG_4] = mLLeg->GetAngle(4) *180.0f/PI;
	joints.joint[RLEG_4] = mRLeg->GetAngle(4) *180.0f/PI;
	joints.joint[LLEG_5] = mLLeg->GetAngle(5) *180.0f/PI;
	joints.joint[RLEG_5] = mRLeg->GetAngle(5) *180.0f/PI;
	joints.joint[LLEG_6] = mLLeg->GetAngle(6) *180.0f/PI;
	joints.joint[RLEG_6] = mRLeg->GetAngle(6) *180.0f/PI;
	
	//PeocessingLog<<"my left legs "<<mLLeg->GetAngle(1)<<" "<<mLLeg->GetAngle(2)<<" "<<mLLeg->GetAngle(3)<<" "<<mLLeg->GetAngle(4)<<" "<<mLLeg->GetAngle(5)<<" "<<mLLeg->GetAngle(6)<<" "<<"\n";
}
bool BasicWalk::ResetFrameNum()
{
	FrameNum = 1;
}
bool BasicWalk::SetCycle(int newCycle)
{
	Cycle = newCycle;
}