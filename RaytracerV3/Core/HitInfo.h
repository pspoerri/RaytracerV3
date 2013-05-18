/*! \file HitInfo.h
    \brief Contains the definition of the HitInfo class.
    \author Wojciech Jarosz
*/
#ifndef CORE_HIT_INFO_H
#define CORE_HIT_INFO_H

class Shape;
class SurfaceShader;

//#include "SurfaceShader.h"
#include "Color.h"
#include "Vec2.h"
#include "Vec3.h"

//! Contains information about a ray hit with a surface.
/*!
    HitInfos are used by object intersection routines. They are useful in
    order to return more than just the hit distance.
*/

class HitInfo
{
public:
    const Shape * shape;				//!< The geometric primitive at the hit point.
    const SurfaceShader * surfaceShader;//!< The shader at the hit point.
	
    double t;							//!< The hit distance
    Math::Vec3d I;						//!< The "incident" vector,
										//!< point from viewer position to the
										//!< shading position P
    Math::Vec3d P;						//!< The hit point.
    Math::Vec2d st;						//!< Texture coordinates
    Math::Vec2d uv;						//!< Texture coordinates
    Math::Vec3d N;						//!< Shading normal vector.
    Math::Vec3d Ng;						//!< Geometric normal vector.
    
    Math::Vec3d O;                      //!< Hit Origin

    Math::Vec3d dPdu, dPdv;				//!< Derivatives of P wrt uv
    Math::Vec3d dNdu, dNdv;				//!< Derivatives of N wrt uv

    //! Default constructor.
    explicit HitInfo(const SurfaceShader * sShader = 0,
                     double t = 0.0f,
                     const Math::Vec3d& P = Math::Vec3d(0.0f),
                     const Math::Vec2d& uv = Math::Vec2d(0.0f),
                     const Math::Vec3d& N = Math::Vec3d(0, 1, 0),
                     const Math::Vec3d& Ng = Math::Vec3d(0, 1, 0)) :
        shape(0), surfaceShader(sShader),
        t(t), P(P), uv(uv), N(N), Ng(Ng),
        dPdu(0.0f), dPdv(0.0f), dNdu(0.0f), dNdv(0.0f)
    {
        // empty
    }
};

#endif // CORE_HIT_INFO_H
