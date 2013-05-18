//
//  SurfaceShader.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__SurfaceShader__
#define __RaytracerV3__SurfaceShader__

class HitInfo;
class Scene;
class PhotonMap;
class Renderer;
#include "Math/Color.h"
#include <iostream>
#include "PhotonSource.h"

class SurfaceShader
{
public:
    SurfaceShader();
    ~SurfaceShader();
    
    virtual Math::Color3f shade(const HitInfo & hit,
                                const Scene &scene) const;
    
    virtual Math::Color3f shade(const Renderer *render,
                                const HitInfo & hit,
                                PhotonMap &photonMap,
                                PhotonMap &specularPhotonMap,
                                const Scene &scene) const;
    
    virtual void processPhoton(const HitInfo & hit,
                               EmittedPhoton photon,
                               PhotonMap &photonMap,
                               PhotonMap &specularPhotonMap,
                               const Scene &scene) const;
    
};
#endif /* defined(__RaytracerV3__SurfaceShader__) */
