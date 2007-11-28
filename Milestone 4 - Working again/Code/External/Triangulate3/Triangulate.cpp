/*
 * poly_tri.c
 *
 * Program to take a polygon definition and convert it into __triangles
 * that may then be rendered by the standard __triangle rendering
 * algorithms.  This assumes all transformations have been performed
 * already and cuts them up into optimal __triangles based on their
 * screen-space representation.
 *
 *      Copyright (c) 1988, Evans & Sutherland Computer Corporation
 *
 * Permission to use all or part of this program without fee is
 * granted provided that it is not used or distributed for direct
 * commercial gain, the above copyright notice appears, and
 * notice is given that use is by permission of Evans & Sutherland
 * Computer Corporation.
 *
 *      Written by Reid Judd and Scott R. Nelson at
 *      Evans & Sutherland Computer Corporation (January, 1988)
 *
 * To use this program, either write your own "draw___triangle" routine
 * that can draw __triangles from the definitions below, or modify the
 * code to call your own __triangle or polygon rendering code.  Call
 * "draw_poly" from your main program.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Triangulate.h"

//extern int __vp[V_MAX];
//int __vp[V_MAX];

/*
 * orientation
 *
 * Return either clockwise or counter_clockwise for the orientation
 * of the polygon.
 */
//    int n;                      /* Number of vertices */
//    __vertex v[];                 /* The __vertex list */

int __orientation( int n, __vertex v[] )
{
    float area;
    int i;

    /* Do the wrap-around first */
    area = v[n-1].x * v[0].y - v[0].x * v[n-1].y;

    /* Compute the area (times 2) of the polygon */
    for (i = 0; i < n-1; i++)
        area += v[i].x * v[i+1].y - v[i+1].x * v[i].y;

    if (area >= 0.0)
        return COUNTER_CLOCKWISE;
    else
        return CLOCKWISE;
} /* End of orientation */



/*
 * determinant
 *
 * Computes the determinant of the three points.
 * Returns whether the __triangle is clockwise or counter-clockwise.
 */
//    int p1, p2, p3;             /* The vertices to consider */
//    __vertex v[];                 /* The __vertex list */

int __determinant( int p1, int p2, int p3, __vertex v[] )
{
    float x1, x2, x3, y1, y2, y3;
    float determ;

    x1 = v[p1].x;
    y1 = v[p1].y;
    x2 = v[p2].x;
    y2 = v[p2].y;
    x3 = v[p3].x;
    y3 = v[p3].y;

    determ = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if (determ >= 0.0)
        return COUNTER_CLOCKWISE;
    else
        return CLOCKWISE;
} /* End of determinant */



/*
 * distance2
 *
 * Returns the square of the distance between the two points
 */
//    float x1, y1, x2, y2;

float __distance2( float x1, float y1, float x2, float y2 )
{
    float xd, yd;               /* The distances in X and Y */
    float dist2;                /* The square of the actual distance */

    xd = x1 - x2;
    yd = y1 - y2;
    dist2 = xd * xd + yd * yd;

    return dist2;
} /* End of distance2 */



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

int __no_interior( int p1, int p2, int p3, __vertex v[], int vp[], int n, int poly_or )
{
    int i;                      /* Iterative counter */
    int p;                      /* The test point */

    for (i = 0; i < n; i++) {
        p = vp[i];              /* The point to test */
        if ((p == p1) || (p == p2) || (p == p3))
            continue;           /* Don't bother checking against yourself */
        if (   (__determinant( p2, p1, p, v ) == poly_or)
            || (__determinant( p1, p3, p, v ) == poly_or)
            || (__determinant( p3, p2, p, v ) == poly_or) ) {
            continue;           /* This point is outside */
        } else {
            return 0;           /* The point is inside */
        }
    }
    return 1;                   /* No points inside this __triangle */
} /* End of no_interior */



/*
 * draw_poly
 *
 * Call this procedure with a polygon, this divides it into __triangles
 * and calls the __triangle routine once for each __triangle.
 *
 * Note that this does not work for polygons with holes or self
 * penetrations.
 */
//    int n;                      /* Number of vertices in __triangle */
//    __vertex v[];                 /* The __vertex list (implicit closure) */

//void draw_poly( int n, __vertex v[] )
//{
//    int prev, cur, next;        /* Three points currently being considered */
//    int vp[V_MAX];              /* Pointers to vertices still left */
//    int count;                  /* How many vertices left */
//    int min_vert;               /* __vertex with minimum distance */
//    int i;                      /* Iterative counter */
//    float dist;                 /* Distance across this one */
//    float min_dist;             /* Minimum distance so far */
//    int poly_orientation;       /* Polygon orientation */
//    __triangle t;                 /* __triangle structure */
//
//    if (n > V_MAX) {
//        fprintf( stderr, "Error, more than %d vertices.\n", V_MAX);
//        return;
//    }
//
//    poly_orientation = orientation( n, v );
//
//    for (i = 0; i < n; i++)
//        vp[i] = i;              /* Put vertices in order to begin */
//
///* Slice off clean __triangles until nothing remains */
//
//    count = n;
//    while (count > 3) {
//        min_dist = BIG;         /* A real big number */
//        min_vert = 0;           /* Just in case we don't find one... */
//        for (cur = 0; cur < count; cur++) {
//            prev = cur - 1;
//            next = cur + 1;
//            if (cur == 0)       /* Wrap around on the ends */
//                prev = count - 1;
//            else if (cur == count - 1)
//                next = 0;
//            /* Pick out shortest distance that forms a good __triangle */
//            if (   (determinant( vp[prev], vp[cur], vp[next], v ) == poly_orientation)
//                    /* Same orientation as polygon */
//                && no_interior( vp[prev], vp[cur], vp[next], v, vp, count, poly_orientation )
//                    /* No points inside */
//                && ((dist = distance2( v[vp[prev]].x, v[vp[prev]].y,
//                                       v[vp[next]].x, v[vp[next]].y )) < min_dist) )
//                    /* Better than any so far */
//            {
//                min_dist = dist;
//                min_vert = cur;
//            }
//        } /* End of for each __vertex (cur) */
//
//        /* The following error should "never happen". */
//        if (min_dist == BIG)
//            fprintf( stderr, "Error: Didn't find a __triangle.\n" );
//
//        prev = min_vert - 1;
//        next = min_vert + 1;
//        if (min_vert == 0)      /* Wrap around on the ends */
//            prev = count - 1;
//        else if (min_vert == count - 1)
//            next = 0;
//
///* Output this __triangle */
//
//        t[0].x = v[vp[prev]].x;
//        t[0].y = v[vp[prev]].y;
//        t[0].z = v[vp[prev]].z;
//        t[1].x = v[vp[min_vert]].x;
//        t[1].y = v[vp[min_vert]].y;
//        t[1].z = v[vp[min_vert]].z;
//        t[2].x = v[vp[next]].x;
//        t[2].y = v[vp[next]].y;
//        t[2].z = v[vp[next]].z;
//
//        //draw___triangle( t );
//
///* Remove the __triangle from the polygon */
//
//        count -= 1;
//        for (i = min_vert; i < count; i++)
//            vp[i] = vp[i+1];
//    }
//
///* Output the final __triangle */
//
//        t[0].x = v[vp[0]].x;
//        t[0].y = v[vp[0]].y;
//        t[0].z = v[vp[0]].z;
//        t[1].x = v[vp[1]].x;
//        t[1].y = v[vp[1]].y;
//        t[1].z = v[vp[1]].z;
//        t[2].x = v[vp[2]].x;
//        t[2].y = v[vp[2]].y;
//        t[2].z = v[vp[2]].z;
//
//        //draw___triangle( t );
//
//} /* End of draw_poly */

/* End of poly_tri.c */
