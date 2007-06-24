// - ------------------------------------------------------------------------------------------ - //
// Taken from Wikipedia article on Bezier Curves //
// http://en.wikipedia.org/wiki/Bezier_curve
// - ------------------------------------------------------------------------------------------ - //
// Analysis:
//  The 3.0's found throughout the maths must be an optimization.
// Say, if the values were grinded 3 times.
//
// Also, each vector contains part of the other vectors.  I think... I don't know what I'm talking
// about, to be honest. ;)
//
// Ok.  3 Vectors, weighted by their "high order" time's, from cubed, to squared, to normal.
// Somehow this works out mathematically.  Powerful square/cube stuff.
// I suppose each vector counteracts each other, with the cube/squaring evening the distortion out.
//
// The 3.0's, look to be compounded.  C gets one.  B gets one.  But nevermind.  Order of operation
// would dictate that the multiplication goes first, thusly making the C difference in B not scale
// up.  Hmm.  A Bug?  What I assumed was C was 3x, B was 3x3x, and A... well that math wise just 
// doesn't work out.  C would have to be the 3x3x if I was on to anything. Back to the drawing board
// 
// - ------------------------------------------------------------------------------------------ - //
// Geometry Lib Reinterpretation //
// - ------------------------------------------------------------------------------------------ - //
Vector2D PointOnCubicBezier( Vector2D Curve[4], Real Time )
{
    Real TimeSquared = Time * Time;
    Real TimeCubed = TimeSquared * Time;

    /* calculate the polynomial coefficients */
    Vector2D c = 3.0 * (Curve[1] - Curve[0]);
    Vector2D b = 3.0 * (Curve[2] - Curve[1]) - c;
    Vector2D a = (Curve[3] - Curve[0]) - c - b;
        
    /* calculate the curve point at parameter value t */
    return (a * TimeCubed) + (b * TimeSquared) + (c * Time) + Curve[0];
}
// - ------------------------------------------------------------------------------------------ - //
// Given a curve, ask for a set of points
// - ------------------------------------------------------------------------------------------ - //
vector<Vector2D> PointsOnCubicBezier( Vector2D Curve[4], int Steps )
{
    /* calculate the polynomial coefficients */
    Vector2D c = 3.0 * (Curve[1] - Curve[0]);
    Vector2D b = 3.0 * (Curve[2] - Curve[1]) - c;
    Vector2D a = (Curve[3] - Curve[0]) - c - b;

	vector<Vector2D> Result;

	for ( int idx = 0; idx < Steps; idx++ ) {
		Real Time = Real( idx ) / Real( Steps );
	    Real TimeSquared = Time * Time;
	    Real TimeCubed = TimeSquared * Time;
	        
	    /* calculate the curve point at parameter value t */
	    Result.push_back( (a * TimeCubed) + (b * TimeSquared) + (c * Time) + Curve[0] );
	}
	
	return Result;
}
// - ------------------------------------------------------------------------------------------ - //


/*
Code to generate a cubic Bezier curve
*/

typedef struct
{
    float x;
    float y;
}
Point2D;

/*
cp is a 4 element array where:
cp[0] is the starting point, or P0 in the above diagram
cp[1] is the first control point, or P1 in the above diagram
cp[2] is the second control point, or P2 in the above diagram
cp[3] is the end point, or P3 in the above diagram
t is the parameter value, 0 <= t <= 1
*/

Point2D PointOnCubicBezier( Point2D* cp, float t )
{
    float   ax, bx, cx;
    float   ay, by, cy;
    float   tSquared, tCubed;
    Point2D result;

    /* calculate the polynomial coefficients */

    cx = 3.0 * (cp[1].x - cp[0].x);
    bx = 3.0 * (cp[2].x - cp[1].x) - cx;
    ax = cp[3].x - cp[0].x - cx - bx;
        
    cy = 3.0 * (cp[1].y - cp[0].y);
    by = 3.0 * (cp[2].y - cp[1].y) - cy;
    ay = cp[3].y - cp[0].y - cy - by;
        
    /* calculate the curve point at parameter value t */
        
    tSquared = t * t;
    tCubed = tSquared * t;
        
    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
    result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;
        
    return result;
}

/*
 ComputeBezier fills an array of Point2D structs with the curve   
 points generated from the control points cp. Caller must 
 allocate sufficient memory for the result, which is 
 <sizeof(Point2D) numberOfPoints>
*/

void ComputeBezier( Point2D* cp, int numberOfPoints, Point2D* curve )
{
    float   dt;
    int   i;

    dt = 1.0 / ( numberOfPoints - 1 );

    for( i = 0; i < numberOfPoints; i++)
        curve[i] = PointOnCubicBezier( cp, i*dt );
}


