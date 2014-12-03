#ifndef __FLOATMATH_H__
#define __FLOATMATH_H__

#include <math.h>

const float PI = 3.1415926535897932384626433832795f;
const float EPS = 1e-8f;

typedef float AngRad;	//角度(弧度制)
typedef float Angle;	//角度(角度制)
typedef float Dist;		//距离

inline float Min(float a, float b){return (a < b ? a : b);}

inline float Max(float a, float b){return (a > b ? a : b);}

inline float Sqr(float x){ return x*x; }


//弧度转角度
inline Angle Rad2Deg ( float x ){return ( x * 180 / PI );}

//角度转弧度
inline float Deg2Rad ( Angle x ){return ( x * PI / 180 );}

//角度制的cos函数
inline float cosDeg  ( Angle x ){return ( float )( cos( Deg2Rad( x ) ) );}

//角度制的sin函数
inline float sinDeg  ( Angle x ){return ( float )( sin( Deg2Rad( x ) ) );}

//角度制的tan函数
inline float tanDeg  ( Angle x ){return ( float )( tan( Deg2Rad( x ) ) );}

//角度制的atan函数
inline Angle atanDeg ( float x ){return ( Rad2Deg( ( float )atan( x ) ) );}

//角度制的atan2函数(通过两条直角边计算第一条边所对的锐角)
inline Angle atan2Deg( float x,   float y  )
{
	if( ( float )fabs( x ) < EPS && ( float )fabs( y ) < EPS )
	{
		return ( 0.0 );
	}
	else
	{
		return ( Rad2Deg( ( float )atan2( x, y ) ) );
	}
}

//角度制的acos函数
inline Angle acosDeg ( float x )
{
	if( x >= 1 )
		return ( 0.0 );

	else if( x <= -1 )
		return ( 180.0 );

	return ( Rad2Deg( ( float )acos( x ) ) );
}

//角度制的asin函数
inline Angle asinDeg ( float x )
{
	if( x >= 1 )
		return ( 90.0 );

	else if ( x <= -1 )
		return ( -90.0 );

	return ( Rad2Deg( ( float )asin( x ) ) );
}

//将角度限制在-180到180之间
inline Angle Normalize(Angle a)
{
	while(a > 180)

		a -= 360;

	while(a < -180)

		a += 360;

	return a;
}

//将角度限制在0到360之间
inline Angle InNormalize(Angle a)
{
	a = Normalize(a);
	if (a < 0)
	{
		a += 360;
	}
	return a;
}

inline AngRad NormalizeRad(AngRad ang)
{
	float dPi = 2 * PI;

	while (ang > PI)
	{
		ang -= dPi;
	}

	while (ang < -PI)
	{
		ang += dPi;
	}

	return ang;
}

inline void Clamp(float &val, float min, float max)
{
	if (val < min)
	{
		val = min;
	}
	if (val > max)
	{
		val = max;
	}
}

inline void Swap(float &a, float &b)
{
	float t;
	t = a;
	a = b;
	b = t;
}

#endif //__FLOATMATH_H__