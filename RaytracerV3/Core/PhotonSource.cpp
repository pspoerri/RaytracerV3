//
//  PhotonSource.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "PhotonSource.h"

PhotonSource::PhotonSource(const Math::Vec3d& position, 
                           const Math::Color3f& color,
                           double power,
                           int photons):
color(color),
position(position),
power(power),
photons(photons)
{
    
}

PhotonSource::~PhotonSource()
{
    
}

// Lambertian lighting
Math::Color3f
PhotonSource::computeIntensity(const HitInfo &hit, const Scene& scene) const
{
    
    return Math::Color3f(color.x*power,
                       color.y*power,
                       color.z*power);
}

Math::Color3f
PhotonSource::computeSurfaceIntensity(const HitInfo &hit, const Scene& scene) const
{
    
    return Math::Color3f(color.x*power,
                           color.y*power,
                           color.z*power);
}


Math::Vec3d
PhotonSource::warp(const Math::Vec2d &v, const Math::Vec3d &origin) const
{
    return Math::Vec3d(0,0,0);
}

double
PhotonSource::getPdf(const Math::Vec3d &p, const Math::Vec3d &n) const
{
    return 1.0;
}

double
PhotonSource::getArea() const
{
    return 1.0;
}

bool
PhotonSource::areaLight() const
{
    return false;
}