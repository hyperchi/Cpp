/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*change log
*2007年8月22日　完成初期框架
*
*////////////////////////////////////////////////////////////
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "FloatMath.h"

enum CoordSystemT 
{
	CARTESIAN,
	POLAR
};

class Polar3f
{
public:
	float dist; 
	float theta;
	float phi;

	Polar3f(float dist = 0, float theta = 0, float phi = 0) 
	{ 
		this->dist = dist; 
		this->theta = theta; 
		this->phi = phi; 
	}

	inline void SetValue(float dist = 0, float theta = 0, float phi = 0) 
	{
		this->dist = dist; 
		this->theta = theta;
		this->phi = phi; 
	}	

	float& operator [](int inx) { return inx ? (inx > 1 ? phi : theta) : dist; }	
	bool operator !=(const Polar3f &a) { return (dist != a.dist) || (theta != a.theta) || (phi != a.phi); }
	bool operator ==(const Polar3f &a) { return (dist == a.dist) && (theta == a.theta) && (phi == a.phi); }

};

class Vector3f 
{
public:
	float x;
	float y;
	float z;
	
	
	Vector3f(float vx = 0, float vy = 0, float vz = 0){	x = vx; y = vy; z = vz;}

	Vector3f(float r, float phi, float vz, CoordSystemT cs) 
	{
		if (cs == POLAR) 
		{
			x = r * cosDeg(phi); y = r * sinDeg(phi); z = vz;
		}
		else 
		{
			x = r; y = phi; z = vz;
		}
	}
	
	//该向量的模
	inline float mod(){	return sqrt(x*x + y*y + z*z);}

	//该向量在水平面的投影的模
	inline float modXY(){ return sqrt(x*x + y*y);}

	inline float modXZ(){ return sqrt(x*x + z*z); }

	inline float modYZ(){ return sqrt(y*y + z*z); }

	//该向量在水平面的投影与X轴的夹角
	inline float angTheta(){ return atan2Deg(y, x);}

	//该向量与水平面的夹角
	inline float angPhi(){ return atan2Deg(z, modXY());}

	//	如果有一个人站在（0，0，0）点，面向X轴正向，头顶向上方向为Y轴正向，右手方向为Z轴正向，那么旋转角度和方向的计算方法如下：
	//	Yaw是围绕Y轴旋转，站在（0，0，0）点的人脚下是XOZ平面，以正角度为参数是向左转，以负角度为参数是向右转。
	//	Pitch是围绕X轴旋转，站在（0，0，0）点的人脚下是XOY平面，以正角度为参数是向右倒，以负角度为参数是向左倒。
	//	Roll是围绕Z轴旋转，站在（0，0，0）点的人脚下是YOZ平面，以正角度为参数是向后倒，以负角度为参数是向前倒。
	inline float angRoll(){ return atan2Deg(x, modYZ()); }

	inline float angPitch(){ return atan2Deg(y, modXZ()); }

	inline float angYaw(){ return atan2Deg(z, modXY()); }

	//该点到目标点的距离
	inline float dist2(Vector3f &pos){ return (pos-(*this)).mod();}

	//该点到目标点的水平距离
	inline float distXY2(Vector3f &pos){ return (pos-(*this)).modXY();}

	//该点指向目标点的向量在水平面的投影与X轴的夹角
	inline float angTheta2(Vector3f &pos){ return (pos-(*this)).angTheta();}	

	//该点指向目标点的向量与水平面的夹角
	inline float angPhi2(Vector3f &pos){ return (pos-(*this)).angPhi();}	

	inline void fromPolar3f(Polar3f &pol)
	{
		x = pol.dist * cosDeg(pol.phi) * cosDeg(pol.theta);
		y = pol.dist * cosDeg(pol.phi) * sinDeg(pol.theta);
		z = pol.dist * sinDeg(pol.phi);
	}

	//对非零的向量进行单位化,使其模为delta
	Vector3f normalize(float delta) 
	{
		float m = mod();
		if (m < EPS) 
		{
			x = y = z = 0;
		}
		else 
		{	
			x /= m; y /= m; z /= m;
			
		}
		x*=delta;y*=delta;z*=delta;
		return *this;
	}

	//缩放原向量使其模为d
	Vector3f setMagnitude(float d) 
	{
		normalize(1.0);
		x *= d; y *= d; z *= d;
		return *this;
	}	

	Vector3f rotate2d(Angle angle) 
	{
		float dMag    = modXY();
		float dNewDir = this->angTheta() + angle;			
		x = dMag * cosDeg(dNewDir); 
		y = dMag * sinDeg(dNewDir); 
		return *this;
	}

	// calculate the cross product (p1-p0) * (p2-p0)
	static Vector3f vecCross(const Vector3f& p1, const Vector3f& p2) 
	{
		return Vector3f(
			p1.y * p2.z - p2.y * p1.z,
			p1.z * p2.x - p2.z * p1.x,
			p1.x * p2.y - p2.x * p1.y
		);
	}

	static float vecCross2d(const Vector3f& p0, const Vector3f& p1, const Vector3f& p2) 
	{
		return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
	}

	float getDistToSeg2d(Vector3f& point1, Vector3f& point2) 
	{
		if ((point1 - point2).mod() < EPS) 
		{
			return (*this - point1).mod();
		}

		Vector3f t = *this;
		t.x += point1.y - point2.y; t.y += point2.x - point1.x;
		if (vecCross2d(point1, t, *this) * vecCross2d(point2, t, *this) > EPS)
			return Min((*this - point1).mod(), (*this - point2).mod());
		return fabs(vecCross2d(*this, point1, point2)) / (point1 - point2).mod();
	}

	~Vector3f(){}

	// operators
	float& operator [](int inx) { return inx ? (inx > 1 ? z : y) : x; }
	Vector3f operator -() { return Vector3f(-x, -y, -z); }
	Vector3f operator +(const Vector3f &a) { return Vector3f(x + a.x, y + a.y, z + a.z); }
	Vector3f operator -(const Vector3f &a) { return Vector3f(x - a.x, y - a.y, z - a.z); }
	Vector3f operator *(const float &a) { return Vector3f(x * a, y * a, z * a); }
	Vector3f operator /(const float &a) { return Vector3f(x / a, y / a,z/a); }
	Vector3f& operator =(const float &a) { x = a; y = a; z=z; return *this;}
	Vector3f& operator =(const Vector3f &a) { x = a.x; y = a.y; z=a.z; return *this;}
	Vector3f& operator +=(const Vector3f &a) { x += a.x;  y += a.y; z +=a.z; return *this;}
	Vector3f& operator +=(const float &a) { x += a;  y += a; z +=a; return *this;}
	Vector3f& operator -=(const Vector3f &a) { x -= a.x;  y -= a.y; z -=a.z; return *this;}
	Vector3f& operator -=(const float &a) { x -= a;  y -= a; z -=a; return *this;}
	Vector3f& operator *=(const float &a) { x *= a;  y *= a; z*=a; return *this;}
	Vector3f& operator /=(const float &a) { x /= a;  y /= a; z/=a; return *this;}
	bool operator !=(const Vector3f &a) { return (x != a.x) || (y != a.y) || (z != a.z); }
	bool operator !=(const float &a) { return (x != a) || (y != a) || (z != a); }
	bool operator ==(const Vector3f &a) { return (x == a.x) && (y == a.y) && (z == a.z); }
	
};

class Circle
{
    Vector3f	m_posCenter;            /*!< Center of the circle  */
    float		m_dRadius;              /*!< Radius of the circle  */

public:
    Circle( );
    Circle( Vector3f pos, float dR );   

    // get and set methods
    bool setCircle ( Vector3f pos, float dR );
    bool setRadius ( float dR );
    float getRadius ( );
    bool setCenter ( Vector3f pos );
    Vector3f getCenter ( );
    float getCircumference ( );
    float getArea ( );

    // calculate intersection points and area with other circle
    bool isInsideBall ( Vector3f &pos );
	bool isInsideCircle( Vector3f &pos );
    int getIntersectionPoints (Circle &c, Vector3f &p1, Vector3f &p2 ); 
    
}  ;

class Line
{
protected:
  // a line is defined by the formula: ay + bx + c = 0
  float m_a; 
  float m_b; 
  float m_c; 

public:
  Line(){}
  Line( float a, float b, float c );
  

  // get intersection points with this line
  Vector3f getIntersection ( Line &line );
  Line  getTangentLine ( Vector3f &pos );
  Vector3f  getPointOnLineClosestTo ( Vector3f &pos );
  float getDistanceWithPoint ( Vector3f &pos );
  bool isInBetween ( Vector3f &pos, Vector3f &point1, Vector3f &point2);
                                           
                                          

  // calculate associated variables in the line
  float getYGivenX ( float x );
  float getXGivenY ( float y );
  float getA ( ) { return m_a; }
  float getB ( ) { return m_b; }
  float getC ( ) { return m_c; }
  void	setA ( float a) { m_a = a; };
  void	setB ( float b) { m_b = b; };
  void	setC ( float c) { m_c = c; };

  // static methods to make a line using an easier representation.
  static Line makeLineFromTwoPoints ( Vector3f pos1,Vector3f pos2 );
                                           
  static Line makeLineFromPositionAndAngle( Vector3f vec,Angle angle );
                                           
};

class Rectangle
{
  Vector3f m_posLeftTop;     /*!< top left position of the rectangle       */
  Vector3f m_posRightBottom; /*!< bottom right position of the rectangle   */

public:
  Rectangle ( Vector3f pos, Vector3f pos2 );

  // checks whether point lies inside the rectangle
  bool isInside ( Vector3f pos );

  // standard get and set methods
  void setRectanglePoints( Vector3f pos1,Vector3f pos2 );
                                  
  bool setPosLeftTop ( Vector3f pos );
  Vector3f getPosLeftTop ( );
  bool setPosRightBottom ( Vector3f pos );
  Vector3f getPosRightBottom ( );
};

class Ray:public Line
{
  Vector3f m_origin;/*射线的初始构造点*/
  Angle m_angle;/*射线的角度*/
  Vector3f m_direction;/*射线的单位方向*/

public:
	Ray(){}
  	Ray(const Vector3f& orig, float ang);

  Ray(float a,float b,float c,Vector3f pos,Angle angle);

  Angle Allowed_AngleDiff(float distance=5.0);/*允许的角度差*/
  Angle Allowed_AngleDiff(Vector3f point);/*允许的角度差*/
  bool	 InRightDir(Vector3f point);/*判断点是否在射线的方向上*/
  bool	 InRightDir(Angle ang);/*判断角度是否在射线的方向上*/
  bool	 InOppositeDir(Vector3f point);/*判断点是否在射线的反方向上*/
  bool   InOppositeDir(Angle ang);/*判断角度是否在射线的反方向上*/
  Vector3f GetPoint(float dist){ return m_origin + m_direction * dist;}
  float  getDistanceFromOrigin(Vector3f pos);
  inline Angle GetRayAngle(){return m_angle;}
  inline Vector3f GetRayDirection(){return m_direction;}
  static Ray	 MakeRayFromPositionAndAngle(Vector3f pos,Angle angle);/*产生射线*/
  int CircleIntersect(float radius, const Vector3f& center, Vector3f& psol1, Vector3f& psol2);
};


class Triangle
{
public:
	Triangle( Vector3f point1, Vector3f point2, Vector3f point3 );
	~Triangle(){};

	bool MakeTriangle( Vector3f point1, Vector3f point2, Vector3f point3 );
	float Area();
	bool IsInTriangle( Vector3f pos );
	Vector3f Barycenter();  

private:
	Vector3f mPoint1;
	Vector3f mPoint2;
	Vector3f mPoint3;

	float mEdge[3];

	bool CheckEdgeLegal();
};
#endif //__GEOMETRY_H__