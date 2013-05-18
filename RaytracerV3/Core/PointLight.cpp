//
//  PointLight.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "PointLight.h"

using namespace Math;

PointLight::PointLight(const Math::Vec3d& position,
                       const Math::Color4f& color,
                       const double power):
Light(position,
      color,
      power)
{
    
}

Math::Color3f
PointLight::computeIntensity(const HitInfo &hit, const Scene &scene) const
{
    Math::Vec3d d = position-hit.O;
    double d2 = d.length2();
    double f = power/(4.0*M_PI*d2);
    return Color3f(color.x*f,
                   color.y*f,
                   color.z*f);
}