//
//  IsotropicPointLight.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "IsotropicPointLight.h"

#include "Math/Vec2.h"
#include "Warp.h"
#include "Scene.h"
IsotropicPointLight::IsotropicPointLight(const Math::Vec3d& position,
                                         const Math::Color3f& color,
                                         double power,
                                         int photons):
PhotonSource(position,color, power, photons)
{
    
}

IsotropicPointLight::~IsotropicPointLight()
{
    
}

void
IsotropicPointLight::emitPhotons(std::vector<EmittedPhoton>& photonEmitter, Scene& scene)
{
    std::vector<Math::Vec2d> samples;
    scene.generateStratifiedJitteredSamples(samples, photons);
    const double sampleSize = samples.size();
    photonEmitter.reserve(photonEmitter.size()+photons);

    float total_color = color.x+color.y+color.z;
    Math::Vec3f emittedPower = power/(sampleSize*total_color)*color;
    for (Math::Vec2d &sample: samples)
    {
        Math::Vec3d dir;
        Math::Warp::uniformSphere(&dir, sample.x, sample.y);
        photonEmitter.push_back({position, emittedPower, dir, false});
    }
}

Math::Color3f
IsotropicPointLight::computeIntensity(const HitInfo &hit, const Scene &scene) const
{
    Math::Vec3d d = position-hit.P;
    double d2 = d.length2();
    double f = power/(4.0*M_PI*d2);
    return Math::Color3f(color.x*f,
                         color.y*f,
                          color.z*f);
}