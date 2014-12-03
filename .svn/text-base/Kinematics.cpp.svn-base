#include "Kinematics.h"
Kinematics::Kinematics(Kinematics_Type type)
{
	if (type==Kinematics_Left) InitL();
	if (type==Kinematics_Right) InitR();
}

void Kinematics::InitL()
{
	mJointU.resize(7);
    mJointU[0].R[0] = 1.0f;
	mJointU[0].R[4] = 1.0f;
	mJointU[0].R[8] = 1.0f;
	mJointU[0].P[0] = 0.0f;
	mJointU[0].P[1] = 0.0f;
	mJointU[0].P[2] = 0.0f;
	mJointU[0].Ax[0] = 1.0f;
	mJointU[0].Ax[1] = 0.0f;
	mJointU[0].Ax[2] = 0.0f;

	mJointU[1].Ax[0] = -0.7071f;
	mJointU[1].Ax[1] = 0.0f;
	mJointU[1].Ax[2] = -0.7071f;

	mJointU[2].Ax[0] = 0.0f;
	mJointU[2].Ax[1] = 1.0f;
	mJointU[2].Ax[2] = 0.0f;

	mJointU[3].Ax[0] = 1.0f;
	mJointU[3].Ax[1] = 0.0f;
	mJointU[3].Ax[2] = 0.0f;

	mJointU[4].Ax[0] = 1.0f;
	mJointU[4].Ax[1] = 0.0f;
	mJointU[4].Ax[2] = 0.0f;

	mJointU[5].Ax[0] = 1.0f;
	mJointU[5].Ax[1] = 0.0f;
	mJointU[5].Ax[2] = 0.0f;

	mJointU[6].Ax[0] = 0.0f;
	mJointU[6].Ax[1] = 1.0f;
	mJointU[6].Ax[2] = 0.0f;

	mJointU[0].b[0] = 0.0f;
	mJointU[0].b[1] = 0.0f;
	mJointU[0].b[2] = 0.0f;
    
	mJointU[1].b[0] = -0.055f ;
	mJointU[1].b[1] = -0.01f;
	mJointU[1].b[2] = -0.115f;

	mJointU[2].b[0] =0.0f ;
	mJointU[2].b[1] =0.0f;
	mJointU[2].b[2] =0.0f ;

	mJointU[3].b[0] = 0.0f;
	mJointU[3].b[1] = 0.0f;
	mJointU[3].b[2] = 0.0f;

	mJointU[4].b[0] = 0.0f;
	mJointU[4].b[1] = -0.005f;
	mJointU[4].b[2] = -0.080f;

	mJointU[5].b[0] = 0.0f;
	mJointU[5].b[1] = -0.01f;
	mJointU[5].b[2] = -0.055f;

	mJointU[6].b[0] = 0.0f;
	mJointU[6].b[1] = 0.0f;
	mJointU[6].b[2] = 0.0f;

	mJointU[0].q = 0.0f;
	mJointU[1].q = -10.0f;
	mJointU[2].q = 5.0f;
	mJointU[3].q = 22.0f;
	mJointU[4].q = -27.0f;
	mJointU[5].q = 20.0f;
	mJointU[6].q = 0.0f;

	mTarget.P[0] =   -0.0709164f;
	mTarget.P[1] =  0.036565f;
	mTarget.P[2] = -0.235754f;

	mTarget.R[0] =0.987966f;
	mTarget.R[1] =-0.0466299f;
	mTarget.R[2] = 0.147477f;
	mTarget.R[3] = 0.133021f;
	mTarget.R[4] =   0.742687f;
	mTarget.R[5] = -0.656294f;
	mTarget.R[6] =-0.0789266f;
	mTarget.R[7] = 0.668014f;
	mTarget.R[8] = 0.739952f;

	for (int i=0; i<7; i++)
	{
		mJointU[i].q = Deg2Rad(mJointU[i].q);
	}
}

void Kinematics::InitR()
{
	mJointU.resize(7);
	mJointU[0].R[0] = 1.0f;
	mJointU[0].R[4] = 1.0f;
	mJointU[0].R[8] = 1.0f;
	mJointU[0].P[0] = 0.0f;
	mJointU[0].P[1] = 0.0f;
	mJointU[0].P[2] = 0.0f;
	mJointU[0].Ax[0] = 1.0f;
	mJointU[0].Ax[1] = 0.0f;
	mJointU[0].Ax[2] = 0.0f;

	mJointU[1].Ax[0] = -0.7071f;
	mJointU[1].Ax[1] = 0.0f;
	mJointU[1].Ax[2] = 0.7071f;

	mJointU[2].Ax[0] = 0.0f;
	mJointU[2].Ax[1] = 1.0f;
	mJointU[2].Ax[2] = 0.0f;

	mJointU[3].Ax[0] = 1.0f;
	mJointU[3].Ax[1] = 0.0f;
	mJointU[3].Ax[2] = 0.0f;

	mJointU[4].Ax[0] = 1.0f;
	mJointU[4].Ax[1] = 0.0f;
	mJointU[4].Ax[2] = 0.0f;

	mJointU[5].Ax[0] = 1.0f;
	mJointU[5].Ax[1] = 0.0f;
	mJointU[5].Ax[2] = 0.0f;

	mJointU[6].Ax[0] = 0.0f;
	mJointU[6].Ax[1] = 1.0f;
	mJointU[6].Ax[2] = 0.0f;

	mJointU[0].b[0] = 0.0f;
	mJointU[0].b[1] = 0.0f;
	mJointU[0].b[2] = 0.0f;

	mJointU[1].b[0] =0.055f ;
	mJointU[1].b[1] = -0.01f;
	mJointU[1].b[2] = -0.115f;

	mJointU[2].b[0] =0.0f ;
	mJointU[2].b[1] =0.0f;
	mJointU[2].b[2] =0.0f ;

	mJointU[3].b[0] = 0.0f;
	mJointU[3].b[1] = 0.0f;
	mJointU[3].b[2] = 0.0f;

	mJointU[4].b[0] = 0.0f;
	mJointU[4].b[1] = -0.005f;
	mJointU[4].b[2] = -0.080f;

	mJointU[5].b[0] = 0.0f;
	mJointU[5].b[1] = -0.01f;
	mJointU[5].b[2] = -0.055f;

	mJointU[6].b[0] = 0.0f;
	mJointU[6].b[1] = 0.0f;
	mJointU[6].b[2] = 0.0f;

	mJointU[0].q = 0.0f;
	mJointU[1].q = 0.0f;
	mJointU[2].q = 0.0f;
	mJointU[3].q = 100.0f;
	mJointU[4].q = 0.0f;
	mJointU[5].q = 40.0f;
	mJointU[6].q = 0.0f;

	mTarget.P[0] = -0.0200f;
	mTarget.P[1] = -0.0930f;
	mTarget.P[2] = -0.0892f;

	mTarget.R[0] = 0.7425f;
	mTarget.R[1] = 0.3117f;
	mTarget.R[2] = 0.5929f;
	mTarget.R[3] = -0.5540f;
	mTarget.R[4] = -0.2116f;
	mTarget.R[5] = 0.8051f;
	mTarget.R[6] = 0.3765f;
	mTarget.R[7] = -0.9263f;
	mTarget.R[8] = 0.0156f;

	for (int i=0; i<7; i++)
	{
		mJointU[i].q = Deg2Rad(mJointU[i].q);
	}
}

void Kinematics::InitialAngle(float qAngle[])
{
	mJointU[0].q = 0;
	for (unsigned int i=1; i<mJointU.size(); i++)
	{
		mJointU[i].q = Deg2Rad(qAngle[i-1]);
	}
}
void Kinematics::SetTarget(float p[],float r[])
{
	/*
	for (int i=0; i<3; i++)
	{
		mTarget.P[i] = p[i];
	}
	for (int i=0; i<9; i++)
	{
		mTarget.R[i] = r[i];
	}
	*/
	memcpy(mTarget.P,p,3*sizeof(float));
	memcpy(mTarget.R,r,9*sizeof(float));
}
void Kinematics::SetTarget(float p[])
{
	/*
	for (int i=0; i<3; i++)
	{
	mTarget.P[i] = p[i];
	}
	for (int i=0; i<9; i++)
	{
	mTarget.R[i] = r[i];
	}
	*/
	memcpy(mTarget.P,p,3*sizeof(float));
	
}
void Kinematics::SetmJP(int i,float p[])
{
	memcpy(mJointU[i].P,p,3*sizeof(float));
}
void Kinematics::SetmJR(int i,float r[])
{
	memcpy(mJointU[i].R,r,3*sizeof(float));
}
float* Kinematics::GetmJP(int i)
{
	return(mJointU[i].P);
}
float* Kinematics::GetmJR(int i)
{
	return(mJointU[i].R);
}
void Kinematics::ForwardKine(int startJ)
{

	if (startJ!=0)
	{
		int i = startJ - 1;
		Matrix tem_i_r(3,3,mJointU[i].R);
		Matrix tem_j_b(3,1,mJointU[startJ].b);
		Matrix tem_j_r(3,3);
		Matrix tem(3,1);
				
		tem =  tem_i_r * tem_j_b;
		mJointU[startJ].P [0]  = mJointU[i].P[0]+tem.GetElement(0,0);
		mJointU[startJ].P [1]  = mJointU[i].P[1]+tem.GetElement(1,0);
		mJointU[startJ].P [2]  = mJointU[i].P[2]+tem.GetElement(2,0);

		Matrix tem_a(3);

		tem_a.SetElement(0,0,0);
		tem_a.SetElement(0,1,-mJointU[startJ].Ax[2]);
		tem_a.SetElement(0,2,mJointU[startJ].Ax[1]);

		tem_a.SetElement(1,0,mJointU[startJ].Ax[2]);
		tem_a.SetElement(1,1,0);
		tem_a.SetElement(1,2,-mJointU[startJ].Ax[0]);

		tem_a.SetElement(2,0,-mJointU[startJ].Ax[1]);
		tem_a.SetElement(2,1,mJointU[startJ].Ax[0]);
        tem_a.SetElement(2,2,0);

		Matrix tem_E;
		tem_E.MakeUnitMatrix(3);
        tem_E = tem_E + tem_a*sin(mJointU[startJ].q) + tem_a*tem_a*(1-cos(mJointU[startJ].q));

		tem_j_r = tem_i_r * tem_E;
		

/*
		std::cout<<mJointU[startJ].P [0]<<std::endl;
		std::cout<<mJointU[startJ].P [1]<<std::endl;
		std::cout<<mJointU[startJ].P [2]<<std::endl;
		std::cout<<std::endl;
		tem_j_r.PrintMatrix();
*/			
/*
		for (int n=0; n<3; n++)
			for (int nn=0; nn<3; nn++)
			mJointU[startJ].R[3*n+nn] = tem_j_r.GetElement(n,nn);
*/
		memcpy(mJointU[startJ].R,tem_j_r.GetData(),9*sizeof(float));

	}
/*
    if (startJ==6)
    {
		std::cout<<mJointU[startJ].P [0]<<std::endl;
		std::cout<<mJointU[startJ].P [1]<<std::endl;
		std::cout<<mJointU[startJ].P [2]<<std::endl;
    }
*/	
	if (startJ+1 <mJointU.size()) ForwardKine(startJ+1);
	
}
//toj为目标关节的编号，一般为最末端的关节
void Kinematics::InverseKine(int toj)
{
	Matrix err(6,1);
	Matrix tem(6,1);
	float dq[6];

	const float lambda = 0.99f;
	ForwardKine(0);
	Matrix Jacobian(6);

	for (int n=0; n<10 ; n++)
	{
		CalJacobian(Jacobian);
		//Jacobian.PrintMatrix();

		if (!Jacobian.Invert())
		{
			//std::cout<<"NO Jacobian Invert"<<std::endl;
		}
		

		CalErr(toj,err);
		//err.PrintMatrix();

		if (err.Norm()<1E-6f)
		{
			//TestPrint();
			return;
		}
		tem =Jacobian * err * lambda;
		//tem.PrintMatrix();

		for (int n=0; n<6; n++)
			dq[n] = tem.GetElement(n,0);

		for (unsigned int i = 1 ; i<mJointU.size(); i++)
		{
			mJointU[i].q = mJointU[i].q + dq[i-1];

		}
		ForwardKine(0);

	}
//TestPrint();

}


void Kinematics::CalErr(int to,Matrix &err)
{
	Matrix tem_to_r(3,3,mJointU[to].R);
	Matrix tem_tar_r(3,3,mTarget.R);
	Matrix tem_werr(3,1);
	Matrix tem_rr(3,3);
	

	err.SetElement(0,0, mTarget.P[0] - mJointU[to].P[0]);
	err.SetElement(1,0, mTarget.P[1] - mJointU[to].P[1]);
	err.SetElement(2,0, mTarget.P[2] - mJointU[to].P[2]);
		
	tem_rr = tem_to_r.Transpose() * tem_tar_r;
	//tem_rr.PrintMatrix();
	//tem_to_r.PrintMatrix();
	tem_werr = tem_to_r * CalLnr(tem_rr);
    
	err.SetElement(3,0, tem_werr.GetElement(0,0));
	err.SetElement(4,0, tem_werr.GetElement(1,0));
	err.SetElement(5,0, tem_werr.GetElement(2,0));

}

 Matrix Kinematics::CalLnr(const Matrix &rerr)
{
	Matrix tem;
	Matrix lnr(3,1);
	float theta;
	
	tem.MakeUnitMatrix(3);
	
	lnr.SetElement(0,0,0);
	lnr.SetElement(1,0,0);
	lnr.SetElement(2,0,0);
	if (rerr==tem)
	{
		
	}
	else
	{
       
		theta = acos(  (rerr.GetElement(0,0) + rerr.GetElement(1,1) + rerr.GetElement(2,2) -1 ) / 2 );
		if (theta != theta)
		{
			return(lnr);
		}
		if (fabs(sin(theta))<EPS)
		{
			return(lnr);
		}
		
		lnr.SetElement(0,0, ( theta/(2*sin(theta))*(rerr.GetElement(2,1) - rerr.GetElement(1,2)) ) );
		lnr.SetElement(1,0, ( theta/(2*sin(theta))*(rerr.GetElement(0,2) - rerr.GetElement(2,0)) ) );
		lnr.SetElement(2,0, ( theta/(2*sin(theta))*(rerr.GetElement(1,0) - rerr.GetElement(0,1)) ) );

	}
	return(lnr);
}
void Kinematics::CalJacobian(Matrix &Jacobian)
{
	Matrix tem_i_r(3,3);
	Matrix tem_i_a(3,1);
	Matrix tem(3,1);
	float u1,u2,u3,v1,v2,v3;
	
	for (unsigned int i =1; i<mJointU.size(); i++)
	{
		
		tem_i_r.SetData(mJointU[i].R);
		tem_i_a.SetData(mJointU[i].Ax);
		
		tem = tem_i_r * tem_i_a;
		//tem.PrintMatrix();
	
		v1 = mTarget.P[0] - mJointU[i].P[0];
		v2 = mTarget.P[1] - mJointU[i].P[1];
		v3 = mTarget.P[2] - mJointU[i].P[2];

		u1 = tem.GetElement(0,0);
		u2 = tem.GetElement(1,0);
		u3 = tem.GetElement(2,0);

		//u x v = { u2v3-v2u3 , u3v1-v3u1 , u1v2-u2v1 }

		Jacobian.SetElement(0,i-1,u2*v3 - v2*u3 );
		Jacobian.SetElement(1,i-1,u3*v1 - v3*u1 );
		Jacobian.SetElement(2,i-1,u1*v2 - v1*u2 );
        Jacobian.SetElement(3,i-1,u1);
		Jacobian.SetElement(4,i-1,u2);
		Jacobian.SetElement(5,i-1,u3);
	}
	Jacobian.SetElement(0,5,0.0f );
	Jacobian.SetElement(1,5,0.0f );
	Jacobian.SetElement(2,5,0.0f );
    

}

void Kinematics::TestPrint()
{
	for (int i=0; i<7; i++)
	{
		//std::cout<<mJointU[i].q*180/PI<<std::endl;

	}
	//std::cout<<std::endl;
	/*
	Matrix tem(3,3,mJointU[6].R);
	tem.PrintMatrix();
	Matrix tem2(3,1,mJointU[6].P);
	tem2.PrintMatrix();
	*/
	
}
float* Kinematics::GetAngle()
{
	for (unsigned int i = 1 ; i<mJointU.size(); i++)
	{
		tem_angle[i-1] = mJointU[i].q;
	}
	return(tem_angle);
}
float Kinematics::GetAngle(int i)
{
	return(mJointU[i].q);
}

float* Kinematics::GetTargetP()
{
	return(mTarget.P);
}
float* Kinematics::GetTargetR()
{
	return(mTarget.R);
}
void Kinematics::PrintJP(int i)
{
	//std::cout<<"mJointU["<<i<<"].P:"<<std::endl;
	for (int j=0; j<3; j++)
	{
	//	std::cout<<mJointU[i].P[j]<<"  ";
	}
	//std::cout<<std::endl;
}
void Kinematics::PrintJR(int i)
{
	//std::cout<<"mJointU["<<i<<"].R:"<<std::endl;
	for (int j=0; j<9; j++)
	{
		//std::cout<<mJointU[i].R[j]<<"  ";
		if ((j+1)%3==0)
		{
			//std::cout<<std::endl;
		}
	}

}