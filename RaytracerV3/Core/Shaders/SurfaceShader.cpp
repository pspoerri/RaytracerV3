//
//  SurfaceShader.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "SurfaceShader.h"
using namespace Math;
SurfaceShader::SurfaceShader()
{
    
}

SurfaceShader::~SurfaceShader()
{
    
}

Math::Color3f SurfaceShader::shade(const HitInfo & hit,
                                   const Scene &scene) const
{
    std::cout << "Warning: Executing SurfaceShader::shade()" << std::endl;
    return Color3f(0,0,0);
}


Math::Color3f
SurfaceShader::shade(const Renderer *render,
                     const HitInfo & hit,
                     PhotonMap &photonMap,
                     PhotonMap &specularPhotonMap,
                     const Scene &scene,
                     bool gather) const
{
    std::cout << "Warning: Executing SurfaceShader::shade()" << std::endl;
    return Color3f(0,0,0);
}

void
SurfaceShader::processPhoton(const HitInfo & hit,
                             EmittedPhoton photon,
                             PhotonMap &photonMap,
                             PhotonMap &specularPhotonMap,
                             const Scene &scene) const
{
    return;
}