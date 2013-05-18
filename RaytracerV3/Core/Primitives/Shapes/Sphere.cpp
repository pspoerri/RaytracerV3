//
//  Sphere.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "Sphere.h"

#include "OGL/Primitive.h"
#include "Math/MathGL.h"
#include "Math/Core.h"

using namespace Math;

Sphere::Sphere(SurfaceShader * ss, const Vec3d & loc, double rad) :
Shape(ss),
location(loc),
radius(rad)
{
	
}

void
Sphere::renderGL() const
{
	glPushMatrix();
    glTranslate(location);
    glutWireSphere(radius, 16, 16);
	glPopMatrix();
}

bool
Sphere::intersect(Ray & ray) const
{
    const Vec3d &c = location;
    const Vec3d &o = ray.o;
    const Vec3d &d = ray.d;
    double r2 = radius*radius;
    double dk = ((c-o).dot(d));
    double D2 = (c-o).length2() - dk*dk;
    // std::cout << D2 << "\n";
    if (D2 > r2)
        return false;
    double f = sqrt(r2-D2);
    double t = dk;
    double t1 = t + f;
    double t2 = t - f;
    
    t = std::min<double>(t1, t2);
    //    if (t < 0.0)
    //        t = std::max<double>(t1, t2);
    if (t < ray.tMin)
    {
        t = std::max<double>(t1, t2);
        if (t < ray.tMax) {
            ray.hit.t = t;
        }
        return false;
    }
    
    if (t < ray.tMin || t > ray.tMax) {
        return false;
    }
    ray.hit.t = t;
    fillHitInfo(ray);
    
    return true;
}

void
Sphere::fillHitInfo(Ray & ray) const
{
    //    const Vec3d &c = location;
    //    const Vec3d &o = ray.o;
    //    const Vec3d &d = ray.d;
    
    //    // new code based on http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
    //
    //    Vec3d o = ray.o-location;
    //
    //    double a = 1.0;
    //    double b = 2.0*ray.d.dot(o);
    //    double c = o.dot(o)-(radius*radius);
    //
    //    double disc = b*b-4.0*c;
    //
    //    if (disc < 0.0) {
    //        //        return false;
    //        std::cerr << "Warning, filling hit information with weird values" << std::endl;
    //    }
    //
    //    double distSqrt = sqrtf(disc);
    //    double q;
    //    if (b < 0.0) {
    //        q = (-b-distSqrt)*0.5;
    //    } else {
    //        q = (-b+distSqrt)*0.5;
    //    }
    //
    //    double t0 = q/a;
    //    double t1 = c/q;
    //
    //    if (t0 > t1) {
    //        double tmp = t0;
    //        t0 = t1;
    //        t1 = tmp;
    //    }
    //
    ////    if (t1 < 0) {
    ////        return false;
    ////    }
    ////
    //    double t = t0;
    //
    //    if (t0 < 0.0 || t0 < ray.tMin) {
    //        t = t1;
    //    }
    
    double t = ray.hit.t;
    ray.hit.shape = this;
    ray.hit.t = t;
    ray.tMax = t-0.0001;
    ray.hit.P = ray.o + t*ray.d;
    ray.hit.O = ray.o;
    ray.hit.I = (ray.hit.P-ray.o).normalize();
    ray.hit.N = (ray.hit.P - location).normalize();
    ray.hit.surfaceShader = surfaceShader;
}
//
//Vec3d Sphere::evalP(double u, double v) const
//{
//    v = v*M_PI;
//    u = u*2.0*M_PI;
//    Vec3d p(radius*sin(u)*cos(v), radius*sin(u)*sin(v), radius*cos(u));
//	
//	return p+location;
//}
//
//Vec3d Sphere::evalN(double u, double v) const
//{
//    v = v*M_PI;
//    u = u*2.0*M_PI;
//    Vec3d p(radius*sin(u)*cos(v), radius*sin(u)*sin(v), radius*cos(u));
//    
//	return p.normalize();
//}
