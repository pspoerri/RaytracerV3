//
//  Light.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "Light.h"

using namespace Math;
Light::Light(const Math::Vec3d &position,
             const Math::Color4f &color,
             const double power):
position(position),
color(color),
power(power)
{
}

// Lambertian lighting
Math::Color3f
Light::computeIntensity(const HitInfo &hit, const Scene& scene) const
{
    
    return Color3f(color.x*power,
                   color.y*power,
                   color.z*power);
}

Math::Color3f
Light::computeSurfaceIntensity(const HitInfo &hit, const Scene& scene) const
{
    
    return Color3f(color.x*power,
                   color.y*power,
                   color.z*power);
}


Math::Vec3d
Light::warp(const Math::Vec2d &v, const Math::Vec3d &origin) const
{
    return position;
}

double
Light::getPdf(const Math::Vec3d &p, const Math::Vec3d &n) const
{
    return 1.0;
}

double
Light::getArea() const
{
    return 1.0;
}

bool
Light::areaLight() const
{
    return false;
}