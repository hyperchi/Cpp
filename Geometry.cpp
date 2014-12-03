#include "stdafx.h"
/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*	一些有用的几何工具
*change log
*2007年8月22日　完成初期框架
*
*////////////////////////////////////////////////////////////
#include "Geometry.h"
#include <iostream>
using namespace std;

/******************************************************************************/

/********************** CLASS CIRCLE ******************************************/

/******************************************************************************/



/*! This is the constructor of a circle.

\param pos first point that defines the center of circle

\param dR the radius of the circle

\return circle with pos as center and radius as radius*/

Circle::Circle( Vector3f pos, float dR )

{

	setCircle( pos, dR );

}



/*! This is the constructor of a circle which initializes a circle with a

radius of zero. */

Circle::Circle( )

{

	setCircle( Vector3f(-1000.0,-1000.0), 0);

}





/*! This method sets the values of the circle.

\param pos new center of the circle

\param dR new radius of the circle

( > 0 )

\return bool indicating whether radius was set */

bool Circle::setCircle( Vector3f pos, float dR )

{

	setCenter( pos );

	return setRadius( dR  );

}

/*! This method sets the radius of the circle.

\param dR new radius of the circle ( > 0 )

\return bool indicating whether radius was set */

bool Circle::setRadius( float dR )

{

	if( dR > 0 )

	{

		m_dRadius = dR;

		return true;

	}

	else

	{

		m_dRadius = 0.0;

		return false;

	}

}



/*! This method returns the radius of the circle.

\return radius of the circle */

float Circle::getRadius()

{

	return m_dRadius;

}



/*! This method sets the center of the circle.

\param pos new center of the circle

\return bool indicating whether center was set */

bool Circle::setCenter( Vector3f pos )

{

	m_posCenter = pos;

	return true;

}



/*! This method returns the center of the circle.

\return center of the circle */

Vector3f Circle::getCenter()

{

	return m_posCenter;

}



/*! This method returns the circumference of the circle.

\return circumference of the circle */

float Circle::getCircumference()

{

	return 2.0f*PI*getRadius();

}



/*! This method returns the area inside the circle.

\return area inside the circle */

float Circle::getArea()

{

	return PI*getRadius()*getRadius();

}



/*! This method returns a boolean that indicates whether 'pos' is located inside

the circle.

\param pos position of which should be checked whether it is located in the

circle

\return bool indicating whether pos lies inside the circle */

bool Circle::isInsideBall(Vector3f &pos )

{

	return (m_posCenter - pos).mod() < getRadius() ;

}

bool Circle::isInsideCircle(Vector3f &pos )

{

	return (m_posCenter - pos).modXY() < getRadius() ;

}


/*! This method returns the two possible intersection points between two

circles. This method returns the number of solutions that were found.

\param c circle with which intersection should be found

\param p1 will be filled with first solution

\param p2 will be filled with second solution

\return number of solutions. */

int Circle::getIntersectionPoints(Circle &c, Vector3f &p1, Vector3f &p2 )

{

	float x0, y0, r0;

	float x1, y1, r1;



	x0 = getCenter( ).x;

	y0 = getCenter( ).y;

	r0 = getRadius( );

	x1 = c.getCenter( ).x;

	y1 = c.getCenter( ).y;

	r1 = c.getRadius( );



	float      d, dx, dy, h, a, x, y, p2_x, p2_y;



	// first calculate distance between two centers circles P0 and P1.

	dx = x1 - x0;

	dy = y1 - y0;

	d = sqrt(dx*dx + dy*dy);



	// normalize differences

	dx /= d; dy /= d;



	// a is distance between p0 and point that is the intersection point P2

	// that intersects P0-P1 and the line that crosses the two intersection

	// points P3 and P4.

	// Define two triangles: P0,P2,P3 and P1,P2,P3.

	// with distances a, h, r0 and b, h, r1 with d = a + b

	// We know a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2 which then gives

	// a^2 + r1^2 - b^2 = r0^2 with d = a + b ==> a^2 + r1^2 - (d-a)^2 = r0^2

	// ==> r0^2 + d^2 - r1^2 / 2*d

	a = (r0*r0 + d*d - r1*r1) / (2.0f * d);



	// h is then a^2 + h^2 = r0^2 ==> h = sqrt( r0^2 - a^2 )

	float      arg = r0*r0 - a*a;

	h = (arg > 0.0f) ? sqrt(arg) : 0.0f;



	// First calculate P2

	p2_x = x0 + a * dx;

	p2_y = y0 + a * dy;



	// and finally the two intersection points

	x =  p2_x - h * dy;

	y =  p2_y + h * dx;

	p1.x = x; p1.y = y;

	x =  p2_x + h * dy;

	y =  p2_y - h * dx;

	p2.x = x; p2.y = y;



	return (arg < 0.0) ? 0 : ((arg == 0.0 ) ? 1 :  2);

}





/******************************************************************************/

/***********************  CLASS LINE *******************************************/

/******************************************************************************/



/*! This constructor creates a line by given the three coefficents of the line.

A line is specified by the formula ay + bx + c = 0.

\param dA a coefficients of the line

\param dB b coefficients of the line

\param dC c coefficients of the line */

Line::Line( float dA, float dB, float dC )

{

	m_a = dA;

	m_b = dB;

	m_c = dC;

}



/*! This method returns the intersection point between the current Line and

the specified line.

\param line line with which the intersection should be calculated.

\return Vector3f position that is the intersection point. */

Vector3f Line::getIntersection( Line &line )

{

	Vector3f pos;

	float x, y;



	if( fabs(m_b - line.getB()) <= EPS ) // lines are parallel, no intersection

	{

		return pos;

	}

	if( fabs(m_a) <= EPS )               // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b

	{                          // calculate x using the current line

		x = -m_c/m_b;                // and calculate the y using the second line

		y = line.getYGivenX(x);

	}

	else if( fabs(line.getA()) <= EPS )

	{									// ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2

		x = -line.getC()/line.getB();	// calculate x using

		y = getYGivenX(x);				// 2nd line and calculate y using current line

	}

	// ay + bx + c = 0 and a2y + b2*x + c2 = 0

	// y = (-b2/a2)x - c2/a2

	// bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>

	// ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)

	// calculate x using the above formula and the y using the current line

	else

	{

		x = (m_a*line.getC() - line.getA()*m_c)/

			(line.getA()*m_b - m_a*line.getB());

		y = getYGivenX(x);

	}



	return Vector3f( x, y );

}





/*! This method returns the tangent line to a Vector3f. This is the line

between the specified position and the closest point on the line to this

position.

\param pos Vector3f point with which tangent line is calculated.

\return Line line tangent to this position */

Line Line::getTangentLine( Vector3f &pos )

{

	// ay + bx + c = 0 -> y = (-b/a)x + (-c/a)

	// tangent: y = (a/b)*x + C1 -> by - ax + C2 = 0 => C2 = ax - by

	// with pos.y = y, pos.x = x

	return Line( m_b, -m_a, m_a*pos.x - m_b*pos.y );

}



/*! This method returns the closest point on a line to a given position.

\param pos point to which closest point should be determined

\return Vector3f closest point on line to 'pos'. */

Vector3f Line::getPointOnLineClosestTo( Vector3f &pos )

{

	Line l2 = getTangentLine( pos );  // get tangent line

	return getIntersection( l2 );     // and intersection between the two lines

}



/*! This method returns the distance between a specified position and the

closest point on the given line.

\param pos position to which distance should be calculated

\return float indicating the distance to the line. */

float Line::getDistanceWithPoint( Vector3f &pos )

{

	return (pos - getPointOnLineClosestTo(pos)).mod();

}



/*! This method determines whether the projection of a point on the current line

lies between two other points ('point1' and 'point2') that lie on the same

line.

\param pos point of which projection is checked.

\param point1 first point on line

\param point2 second point on line

\return true when projection of 'pos' lies between 'point1' and 'point2'.*/

bool Line::isInBetween( Vector3f &pos, Vector3f &point1, Vector3f &point2)

{

	pos          =getPointOnLineClosestTo( pos ); // get closest point

	float dDist = (point1 - point2).mod(); // get distance between 2 pos



	// if the distance from both points to the projection is smaller than this

	// dist, the pos lies in between.

	return (pos - point1).mod() <= dDist &&

		(pos - point2).mod() <= dDist;

}



/*! This method calculates the y coordinate given the x coordinate

\param x coordinate

\return y coordinate on this line */

float Line::getYGivenX( float x )

{

	if( m_a == 0 )

	{
		
		return 0;

	}

	// ay + bx + c = 0 ==> ay = -(b*x + c)/a

	return -(m_b*x+m_c)/m_a;

}



/*! This method calculates the x coordinate given the x coordinate

\param y coordinate

\return x coordinate on this line */

float Line::getXGivenY( float y )

{

	if( m_b == 0 )

	{

		//cerr << "(Line::getXGivenY) Cannot calculate X coordinate\n" ;

		return 0;

	}

	// ay + bx + c = 0 ==> bx = -(a*y + c)/a

	return -(m_a*y+m_c)/m_b;

}



/*! This method creates a line given two points.

\param pos1 first point

\param pos2 second point

\return line that passes through the two specified points. */

Line Line::makeLineFromTwoPoints( Vector3f pos1, Vector3f pos2 )

{

	// 1*y + bx + c = 0 => y = -bx - c

	// with -b the direction coefficient (or slope)

	// and c = - y - bx

	float dA=1.0, dB, dC;

	float dTemp = pos2.x - pos1.x; // determine the slope

	if( fabs(dTemp) < EPS )

	{

		// ay + bx + c = 0 with vertical slope=> a = 0, b = 1

		dA = 0.0;

		dB = 1.0;

	}

	else

	{

		// y = (-b)x -c with -b the slope of the line

		dA = 1.0;

		dB = -(pos2.y - pos1.y)/dTemp;

	}

	// ay + bx + c = 0 ==> c = -a*y - b*x

	dC =  - dA*pos2.y  - dB * pos2.x;

	return Line( dA, dB, dC );

}



/*! This method creates a line given a position and an angle.

\param vec position through which the line passes

\param angle direction of the line.

\return line that goes through position 'vec' with angle 'angle'. */

Line Line::makeLineFromPositionAndAngle( Vector3f vec, Angle angle )

{

	// calculate point somewhat further in direction 'angle' and make

	// line from these two points.

	return makeLineFromTwoPoints( vec, Vector3f(1,angle,0,POLAR)+vec);

}


/******************************************************************************/

/********************** CLASS RECTANGLE ***************************************/

/******************************************************************************/



/*! This is the constructor of a Rectangle. Two points will be given. The

order does not matter as long as two opposite points are given (left

top and right bottom or right top and left bottom).

\param pos first point that defines corner of rectangle

\param pos2 second point that defines other corner of rectangle

\return rectangle with 'pos' and 'pos2' as opposite corners. */

Rectangle::Rectangle( Vector3f pos, Vector3f pos2 )

{

	setRectanglePoints( pos, pos2 );

}



/*! This method sets the upper left and right bottom point of the current

rectangle.

\param pos first point that defines corner of rectangle

\param pos2 second point that defines other corner of rectangle */

void Rectangle::setRectanglePoints( Vector3f pos1, Vector3f pos2 )

{

	m_posLeftTop.x = ( Max( pos1.x, pos2.x ) );

	m_posLeftTop.y = ( Min( pos1.y, pos2.y ) );

	m_posRightBottom.x = ( Min( pos1.x, pos2.x ) );

	m_posRightBottom.y = ( Max( pos1.y, pos2.y ) );

}



/*! This method determines whether the given position lies inside the current

rectangle.

\param pos position which is checked whether it lies in rectangle

\return true when 'pos' lies in the rectangle, false otherwise */

bool Rectangle::isInside( Vector3f pos )

{

	return pos.x > m_posRightBottom.x && pos.x < m_posLeftTop.x &&

		pos.y > m_posLeftTop.y && pos.y < m_posRightBottom.y;



}



/*! This method sets the top left position of the rectangle

\param pos new top left position of the rectangle

\return true when update was successful */

bool Rectangle::setPosLeftTop( Vector3f pos )

{

	m_posLeftTop = pos;

	return true;

}



/*! This method returns the top left position of the rectangle

\return top left position of the rectangle */

Vector3f Rectangle::getPosLeftTop( )

{

	return m_posLeftTop;

}



/*! This method sets the right bottom position of the rectangle

\param pos new right bottom position of the rectangle

\return true when update was succesfull */

bool Rectangle::setPosRightBottom( Vector3f pos )

{

	m_posRightBottom = pos;

	return true;

}



/*! This method returns the right bottom position of the rectangle

\return top right bottom of the rectangle */

Vector3f Rectangle::getPosRightBottom( )

{

	return m_posRightBottom;

}




/******************************************************************************/

/********************** CLASS RAY *********************************************/

/******************************************************************************/



Ray::Ray(const Vector3f& orig, float ang)

{

	m_origin = orig;

	m_direction =  Vector3f(1.0, ang,POLAR);

	m_angle = ang;

	Line tmp = makeLineFromPositionAndAngle(m_origin,ang);

	m_a = tmp.getA();

	m_b = tmp.getB();

	m_c = tmp.getC();

}



Ray::Ray(float a,float b, float c,Vector3f pos,Angle angle)

{

	m_a=a;

	m_b=b;

	m_c=c;

	m_origin=pos;

	m_angle=angle;

	m_direction=Vector3f(1.0,angle,0, POLAR);

}



Angle Ray::Allowed_AngleDiff(float distance)
{

	return float(10 - 5*exp(-distance * 0.2f));

}



Angle Ray::Allowed_AngleDiff(Vector3f point)
{

	return Allowed_AngleDiff((point - m_origin).mod());

}



bool Ray::InRightDir(Vector3f point)
{

	return fabs(Normalize((point - m_origin).angTheta() - m_angle)) < Allowed_AngleDiff(point);

}



bool Ray::InRightDir(Angle ang)
{

	return fabs(Normalize(ang - m_angle)) < Allowed_AngleDiff();

}



bool Ray::InOppositeDir(Vector3f point)
{

	return fabs(Normalize((point - m_origin).angTheta() - m_angle + 180)) < Allowed_AngleDiff(point);

}



bool Ray::InOppositeDir(Angle ang)
{

	return fabs(Normalize(ang - m_angle + 180)) < Allowed_AngleDiff();

}



Ray	 Ray::MakeRayFromPositionAndAngle(Vector3f pos,Angle angle)
{

	Line line=Line::makeLineFromPositionAndAngle(pos,angle);

	return Ray(line.getA(),line.getB(),line.getC(),pos,angle);

}



float Ray::getDistanceFromOrigin(Vector3f pos)
{

	return (pos-this->m_origin).mod();

}

int Ray::CircleIntersect(float radius, const Vector3f& center, Vector3f& psol1, Vector3f& psol2)
{
	//********************************************
	//  原算法解平行于坐标轴的点时会出问题
	//				
	//				Modified by Yin Zhao, Yu WuYi
	//								2008-12-2
	//********************************************

	Vector3f centerPos = center;

	float distCenterToLine = getDistanceWithPoint( centerPos );
	
	if( distCenterToLine > radius )
	{
		return 0;
	}
	
	Vector3f nearestToCenterPos = getPointOnLineClosestTo( centerPos );

	float tempDist = sqrt( Sqr(radius) - Sqr(distCenterToLine) );

	Ray tempRay_1 = MakeRayFromPositionAndAngle( nearestToCenterPos, m_angle );
	Ray tempRay_2 = MakeRayFromPositionAndAngle( nearestToCenterPos, Normalize( m_angle - 180.0f) );

	Vector3f pos1 = tempRay_1.GetPoint( tempDist );
	Vector3f pos2 = tempRay_2.GetPoint( tempDist );

	psol1 = pos1;
	psol2 = pos2;

	//cout<< m_angle << endl;
	
	float distBetweenTwoPos = pos1.distXY2( pos2 );

	if( distBetweenTwoPos <= EPS )
	{
		return 1;
	}

	return 2;


	float a,b,c,disc;

	float t1, t2;

	a = Sqr(m_direction.x) + Sqr(m_direction.y);

	b = 2.0f * ((m_origin.x-center.x) * m_direction.x + (m_origin.y-center.y) * m_direction.y);

	c = Sqr(m_origin.x-center.x) + Sqr(m_origin.y-center.y) - Sqr(radius);
 
	cout<< " m_direction.x " << m_direction.x 
		<< " m_direction.y " << m_direction.y
		<< endl;

	cout<< "a " << a << " b " << b << " c " << c << endl;

	disc = Sqr(b) - 4 * a * c;

	if (disc < 0) 
	{

		return 0; // No solutions

	}



	disc = (float) sqrt(disc);

	t1 = (-b + disc) / (2.0f * a);

	t2 = (-b - disc) / (2.0f * a);



	if (t1 > t2) 
	{

		float temp = t1;

		t1 = t2;

		t2 = temp;

	}

	Vector3f tmp = m_direction;



	if (t1 > 0.0) 
	{

		if (t2 > 0.0) 
		{

			tmp = tmp * t1;

			psol1 = tmp + m_origin ;

			tmp = m_direction;

			tmp = tmp * t2;

			psol2 = tmp + m_origin;

			return 2; // Two solutions

		}

		else
		{

			return 0;

		}

	}

	else if (t2 > 0.0) 
	{

		tmp = m_direction;

		tmp = tmp * t2;

		psol2 = tmp + m_origin;

		psol2 = psol1;

		return 1;

	}

	else

		return 0;

	return 0;

}

Triangle::Triangle( Vector3f point1, Vector3f point2, Vector3f point3 )
{
	MakeTriangle(point1,point2,point3);
}

bool Triangle::MakeTriangle( Vector3f point1, Vector3f point2, Vector3f point3 )
{
	mPoint1=point1;
	mPoint2=point2;
	mPoint3=point3;

	mEdge[0] = mPoint1.distXY2(mPoint2);
	mEdge[1] = mPoint1.distXY2(mPoint3);
	mEdge[2] = mPoint2.distXY2(mPoint3);

	return CheckEdgeLegal();
}

bool Triangle::CheckEdgeLegal()
{
	int j;

	for(int i=0;i<3;i++)//判断边长是否合理
	{
		if(i!=2)
		{
			j=i+1;
		}
		else
		{
			j=0;
		}

		if( fabs(mEdge[i]) < EPS )
		{
			cout<<"Error: Illegal Triangle Parameters Point too near\n";

			return false;
		}
		if(mEdge[i]>=mEdge[j]+mEdge[3-(i+j)]) //0+1+2=3
		{
			cout<<"Error: Illegal Triangle Parameters\n";
			mEdge[0]=3;
			mEdge[1]=4;
			mEdge[2]=5;

			return false;
		}
	}

	return true;
}

float Triangle::Area()
{
	float cos=(mEdge[0]*mEdge[0]+mEdge[1]*mEdge[1]-mEdge[2]*mEdge[2])/(2*mEdge[0]*mEdge[1]);
	float sin=sqrt(1-cos*cos);

	return mEdge[0]*mEdge[1]*sin/2.0f;
}

Vector3f Triangle::Barycenter()
{
	return (mPoint1+mPoint2+mPoint3)/3.0f;
}

bool Triangle::IsInTriangle( Vector3f pos )
{
	Triangle subT1(mPoint1,mPoint2,pos);
	Triangle subT2(mPoint1,mPoint3,pos);
	Triangle subT3(mPoint2,mPoint3,pos);

	float areaT1 = subT1.Area();
	float areaT2 = subT2.Area();
	float areaT3 = subT3.Area();
	float areaT = Area();

	float lamda1 = areaT1/ areaT;
	float lamda2 = areaT2/ areaT;
	float lamda3 = areaT3/ areaT;

	return (lamda1 > 0.0f && lamda2 > 0.0f && lamda3 > 0.0f );
}


