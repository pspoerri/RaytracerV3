/*! \file Ray.cpp
    \brief Implementation of the Ray class.
    \author Wojciech Jarosz
*/
#if HAVE_CONFIG_H
#  include <config.h>
#endif // HAVE_CONFIG_H

#include "Ray.h"
#include <Math/Core.h>
#include <Math/LimitsT.h>

#if defined(_WIN32)
#define isnan _isnan
#endif


/*!
    Creates a ray.
*/
Ray::Ray() :
    Math::Line3d(), tMin(Math::FEQ_EPS), tMax(Math::Limits<double>::max())
{
    // empty
}


/*!
    Creates a child ray.
    \param origin The initial origin of Ray, defaults to an uninitialized
                    Vec3d.
    \param direction The initial direction of Ray, defaults to an
                    uninitialized Vec3d.
    \param r The parent ray.
    
    The remaining parameters for the ray are automatically inferred from the
    parent ray.
*/
Ray::Ray(const Math::Vec3d & origin,
         const Math::Vec3d & direction,
         const Ray & r) :
    Math::Line3d(origin, direction),
    tMin(Math::FEQ_EPS), tMax(Math::Limits<double>::max())
{
    // empty
}

/*!
    Creates a child ray.
    \param origin The initial origin of Ray, defaults to an uninitialized
                    Vec3d.
    \param direction The initial direction of Ray, defaults to an
                    uninitialized Vec3d.

    The remaining parameters for the ray are automatically inferred from the
    parent ray.
*/
Ray::Ray(const Math::Vec3d & origin,
         const Math::Vec3d & direction) :
    Math::Line3d(origin, direction),
    tMin(Math::FEQ_EPS), tMax(Math::Limits<double>::max())
{
    // empty
}
