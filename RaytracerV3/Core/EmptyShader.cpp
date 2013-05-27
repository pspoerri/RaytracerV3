//
//  EmptyShader.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/27/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "EmptyShader.h"
EmptyShader::EmptyShader()
{
    
}

EmptyShader::~EmptyShader()
{
    
}

Math::Color3f
EmptyShader::shade(const HitInfo & hit, const Scene &scene) const
{
    return Math::Color3f(0,0,0);
}

Math::Color3f
EmptyShader::shade(const HitInfo & hit,
                   PhotonMap &photonMap,
                   PhotonMap &specularPhotonMap,
                   const Scene &scene) const
{
    return Math::Color3f(0,0,0);
}

void
EmptyShader::processPhoton(EmittedPhoton photon,
                           PhotonMap &photonMap,
                           PhotonMap &specularPhotonMap,
                           const Scene &scene) const
{
    return;
}