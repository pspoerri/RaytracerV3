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
PhotonSource(color, power, photons),
position(position)
{
    
}

IsotropicPointLight::~IsotropicPointLight()
{
    
}

void
IsotropicPointLight::emitPhotons(std::vector<EmittedPhoton>& photonEmitter, Scene& scene)
{
    std::vector<Math::Vec2d> samples;
    scene.generateRandomSamples(samples, photons);
    photonEmitter.reserve(photonEmitter.size()+photons);
#warning Please check formula
    float total_color = color.x+color.y+color.z;
    Math::Vec3f emittedPower = power/(double(photons)*total_color)*color;
    for (Math::Vec2d &sample: samples)
    {
        Math::Vec3d dir;
        Math::Warp::uniformSphere(&dir, sample.x, sample.y);
        photonEmitter.push_back({position, emittedPower, dir, false});
    }
}