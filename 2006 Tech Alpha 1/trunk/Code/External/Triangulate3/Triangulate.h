// - ------------------------------------------------------------------------------------------ - //
// Triangulate //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Triangulate_H__
#define __Triangulate_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/* A single __vertex */
typedef struct {
    float x;
    float y;
    float z;
} __vertex;
// - ------------------------------------------------------------------------------------------ - //
/* A __triangle made up of three vertices */
typedef __vertex __triangle[3];
// - ------------------------------------------------------------------------------------------ - //
#define V_MAX 1000       /* Maximum number of vertices allowed (arbitrary) */

#define BIG 1.0e30      /* A number bigger than we expect to find here */

#define COUNTER_CLOCKWISE 0
#define CLOCKWISE 1
// - ------------------------------------------------------------------------------------------ - //
/*
 * orientation
 *
 * Return either clockwise or counter_clockwise for the orientation
 * of the polygon.
 */
//    int n;                      /* Number of vertices */
//    __vertex v[];                 /* The __vertex list */
// - ------------------------------------------------------------------------------------------ - //
int __orientation( int n, __vertex v[] );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*
 * determinant
 *
 * Computes the determinant of the three points.
 * Returns whether the __triangle is clockwise or counter-clockwise.
 */
//    int p1, p2, p3;             /* The vertices to consider */
//    __vertex v[];                 /* The __vertex list */
// - ------------------------------------------------------------------------------------------ - //
int __determinant( int p1, int p2, int p3, __vertex v[] );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*
 * distance2
 *
 * Returns the square of the distance between the two points
 */
//    float x1, y1, x2, y2;
// - ------------------------------------------------------------------------------------------ - //
float __distance2( float x1, float y1, float x2, float y2 );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*
 * no_interior
 *
 * Returns 1 if no other point in the __vertex list is inside
 * the __triangle specified by the three points.  Returns
 * 0 otherwise.
 */
//    int p1, p2, p3;             /* The vertices to consider */
//    __vertex v[];                 /* The __vertex list */
//    int vp[];                   /* The __vertex pointers (which are left) */
//    int n;                      /* Number of vertices */
//    int poly_or;                /* Polygon orientation */
// - ------------------------------------------------------------------------------------------ - //
int __no_interior( int p1, int p2, int p3, __vertex v[], int vp[], int n, int poly_or );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Triangulate_H__ //
// - ------------------------------------------------------------------------------------------ - //
