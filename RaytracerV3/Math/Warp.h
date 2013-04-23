/*! \file Warp.h
    \brief Contains mappings between various useful domains.
    \author Wojciech Jarosz
*/
#ifndef MATH_WARP_H
#define MATH_WARP_H

#include <Math/Vec2.h>
#include <Math/Vec3.h>
#include <Math/Core.h>
#include <cmath>
namespace Math
{

    
    enum WarpFunction {
        UNIFORM_SQUARE,
        UNIFORM_DISK,
        
        UNIFORM_CYLINDER,
        
        UNIFORM_SPHERE,
        UNIFORM_SPHERE_CAP,
        
        UNIFORM_HEMISPHERE,
        COSINE_HEMISPHERE,
        PHONG_HEMISPHERE,
        
        UNIFORM_TRIANGLE,
        NUM_WARP_MODES
    };
    
//    const char *warpModes[] =
//	{
//		"Uniform Square",
//		"Uniform Disk",
//		
//		"Uniform Cylinder",
//		
//		"Uniform Sphere",
//		"Uniform Sphere Cap",
//		
//		"Uniform Hemisphere",
//		"Cosine Hemisphere",
//		"Phong Hemisphere",
//        "Uniform Triangle",
//	};
//! Encapsulates various useful mappings
/*!
    This class provides functions to map from various useful domains, such as
    disks, spheres, hemispheres, etc.
    
    You may find the following useful for reference:
    
        Shirley, Pete. "Nonuniform Random Points Via Warping."
            Graphics Gems III. pp. 80--83
    and
        Dutré, Philip. "Global Illumination Compendium." 
            http://www.cs.kuleuven.ac.be/~phil/GI/
            
    among other sources.
        
*/
class Warp
{
public:
    //-----------------------------------------------------------------------
    //@{ \name Mappings to the 2D square.
    //-----------------------------------------------------------------------
    static void  uniformSquare(Vec2d* v, double s, double t);
    static double uniformSquarePdf();
    //@}


    //-----------------------------------------------------------------------
    //@{ \name Disk.
    //-----------------------------------------------------------------------
    static void  uniformDisk(Vec2d* v, double s, double t);
    static double uniformDiskPdf();
    //@}
    
    static void  uniformCylinder(Vec3d* v, double s, double t);
    static double uniformCylinderPdf();

    static void uniformTriangle(Vec3d* v, Vec3d &a, Vec3d &b, Vec3d &c, double s, double t);
    static double uniformTrianglePdf(Vec3d &a, Vec3d &b, Vec3d &c);

    //-----------------------------------------------------------------------
    //@{ \name Mappings to sections of the 3D sphere.
    //-----------------------------------------------------------------------
    static void  uniformSphere(Vec3d* v, double, double);
    static double uniformSpherePdf();

    static void  uniformSphericalCap(Vec3d* v, double, double, double);
    static double uniformSphericalCapPdf(double cosThetaMax);
    
    static void  uniformHemisphere(Vec3d* v, double s, double t);
    static double uniformHemispherePdf();
    
    static void  cosineHemisphere(Vec3d* v, double s, double t);
    static double cosineHemispherePdf(const Vec3d& v);
    
    static void  phongHemisphere(Vec3d* v, double s, double t, double n);
    static double phongHemispherePdf(const Vec3d& v, double n);
    //@}
    
    // Warp Point
    static void warpPoint(double s, double t, Vec3d& v, WarpFunction warpFunction);
    static void warpPoint(Vec2d &p, Vec3d& v, WarpFunction warpFunction);
    
    static double getPDF(Vec3d &v, Math::WarpFunction warpFunction);

};
    
    inline double
    Warp::getPDF(Vec3d &v, Math::WarpFunction warpFunction)
    {
        switch (warpFunction) {
            case UNIFORM_DISK:
                return 1;
            case UNIFORM_CYLINDER:
                return uniformCylinderPdf();
            case UNIFORM_SPHERE:
                return uniformSpherePdf();
            case UNIFORM_HEMISPHERE:
                return Warp::uniformHemispherePdf();
            case COSINE_HEMISPHERE:
                return Warp::cosineHemispherePdf(v);
            default:
                return 1;
            
        }
    }
    
    inline void
    Warp::warpPoint(Vec2d &p, Vec3d &v, Math::WarpFunction warpFunction)
    {
        warpPoint(p.x, p.y, v, warpFunction);
    }

    inline void
    Warp::warpPoint(double s, double t, Vec3d& v, WarpFunction warpFunction)
    {
        // TODO: warp points according to the warp mode here
        // you can call this to warp your input point coordinates (s,t) into point
        // you will visualize in OpenGL
        Vec2d v2;
        switch (warpFunction)
        {
            case UNIFORM_DISK:
                Warp::uniformDisk(&v2, s, t);
                v.x = v2.x;
                v.y = v2.y;
                v.z = 0.0f;
                break;
            case UNIFORM_CYLINDER:
                Warp::uniformCylinder(&v, s, t);
                break;
            case UNIFORM_SPHERE:
                Warp::uniformSphere(&v, s, t);
                break;
            case UNIFORM_HEMISPHERE:
                Warp::uniformHemisphere(&v, s, t);
                break;
            case COSINE_HEMISPHERE:
                Warp::cosineHemisphere(&v, s, t);
                break;
                //            case UNIFORM_SPHERE_CAP:
                //                Warp::uniformSphericalCap(&v, s, t, costheta_max);
                //                break;
                //            case PHONG_HEMISPHERE:
                //                Warp::phongHemisphere(&v, s, t, phong_cos_n);
                //                break;
                //            case UNIFORM_TRIANGLE:
                //                Warp::uniformTriangle(&v, triangle_a, triangle_b, triangle_c, s, t);
                //                break;
            default:
                v.x = 2*s - 1;
                v.y = 2*t - 1;
                v.z = 0.0f;
        }
    }
    
    inline void
    Warp::uniformTriangle(Vec3d *v, Vec3d &a, Vec3d &b, Vec3d &c, double s, double t)
    {
        double sq = sqrtf(s);
        *v = (1.0-sq)*a+sq*(1-t)*b+sq*t*c;
    }
    
    inline double
    Warp::uniformTrianglePdf(Vec3d &a, Vec3d &b, Vec3d &c) {
        Vec3d d = cross((b-a),(c-a));
        return 2.0/(d.length());
    }
    
    inline void
    Warp::uniformSquare(Vec2d* v, double s, double t)
    {
        v->x = s;
        v->y = t;
    }
    
    
    inline double
    Warp::uniformSquarePdf()
    {
        return 1.0/4.0f;
    }
    
    
    inline void
    Warp::uniformDisk(Vec2d* v, double s, double t)
    {
        // Used function from PBRT Book
        double r = sqrtf(s);
        double phi = 2.0*M_PI*t;
        v->x = r*cosf(phi);
        v->y = r*sinf(phi);
    }
    
    
    inline double
    Warp::uniformDiskPdf()
    {
        return 1.0/(M_PI);
    }
    
    
    inline void
    Warp::uniformCylinder(Vec3d* v, double s, double t)
    {
        double phi = 2.0*M_PI*s;
        v->x = sinf(phi);
        v->y = cosf(phi);
        v->z = 2*t-1.0;
    }
    
    
    inline double
    Warp::uniformCylinderPdf()
    {
        return 1.0f/(4.0*M_PI);
    }
    
    
    //! Samples a unit sphere uniformily.
    /*!
     Generates a direction on the unit sphere proportional to solid angle.
     
     Uses Archimedes Theorem to sample the cylinder and then projects back
     onto the sphere.
     */
    inline void
    Warp::uniformSphere(Vec3d* v, double s, double t)
    {
        uniformCylinder(v, s, t);
        double h = (t-0.5)/0.5;
        double a = sqrt(1.0-h*h);
        v->x *= a;
        v->y *= a;
    }
    
    
    inline double
    Warp::uniformSpherePdf()
    {
        return 1.0f/(4.0*M_PI);
    }
    
    
    inline void
    Warp::uniformSphericalCap(Vec3d* v, double s, double t, double cosThetaMax)
    {
        uniformCylinder(v, s, t);
        double h = t*(1.0-cosThetaMax)+cosThetaMax;
        double a = sqrt(1.0-h*h);
        v->x *= a;
        v->y *= a;
        v->z = h;
    }
    
    
    inline double
    Warp::uniformSphericalCapPdf(double cosThetaMax)
    {
        double h = 1.0 - cosThetaMax;
        double r = 1.0/(2.0*M_PI*h);
        return r; // use archimedes hat box theorem
    }
    
    
    //! Samples a unit hemisphere uniformily.
    /*!
     Generates a direction on the unit hemisphere uniformily distributed wrto
     solid angle.
     */
    inline void
    Warp::uniformHemisphere(Vec3d* v, double s, double t)
    {
        uniformCylinder(v, s, t);
        double h = t;
        double a = sqrt(1.0-h*h);
        v->x *= a;
        v->y *= a;
        v->z = t;
    }
    
    inline double
    Warp::uniformHemispherePdf()
    {
        return 1.0f/(2.0*M_PI);
    }
    
    
    //! Samples a cosine-weighted hemisphere.
    /*!
     Generates a direction on the unit hemisphere distributed proportional
     to cosine-weighted solid angle.
     
     The technique used is to just use spherical coordinates directly.
     */
    inline void
    Warp::cosineHemisphere(Vec3d* v, double s, double t)
    {
        Vec2d v2;
        // uniform disk function.
        uniformDisk(&v2, s, t);
        v->x = v2.x;
        v->y = v2.y;
        v->z = sqrtf(std::max<double>(0.0, 1.0-v2.x*v2.x-v2.y*v2.y));
    }
    
    inline double
    Warp::cosineHemispherePdf(const Vec3d& v)
    {
        // pbrt page 669
//        double theta = acosf(v.x);
//        return 1.0/M_PI*sin(theta)*cos(theta);
        return 1.0/M_PI*abs(v.z);
    }
    
    
    //! Samples a phong-weighted hemisphere.
    /*!
     Generates a direction on the unit hemisphere distributed proportional
     to cosine^n-weighted solid angle.
     */
    inline void
    Warp::phongHemisphere(Vec3d* v, double s, double t, double n)
    {
        // implemented using the slides and pbrt 662
        
        double costheta = std::pow((1.0-t),1.0/double(n+1));
        double sintheta = sqrtf(1.0-costheta*costheta);
        double phi = 2.0*M_PI*s;
        
        v->x = sintheta*cos(phi);
        v->y = sintheta*sinf(phi);
        v->z = costheta;
    }
    
    
    inline double
    Warp::phongHemispherePdf(const Vec3d& v, double n)
    {
        // implemented using the slides
        return (n+1.0)/(M_PI*2.0)*std::pow(v.z, n);
    }
    
    
} // namespace Math



#endif // MATH_WARP_H
