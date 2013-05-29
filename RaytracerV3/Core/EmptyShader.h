//
//  EmptyShader.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/27/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__EmptyShader__
#define __RaytracerV3__EmptyShader__

#include "SurfaceShader.h"

class EmptyShader: public SurfaceShader
{
public:
    EmptyShader();
    ~EmptyShader();
    
    virtual Math::Color3f shade(const HitInfo & hit, const Scene &scene) const;
    
    virtual Math::Color3f shade(const Renderer *render,
                                const HitInfo & hit,
                                PhotonMap &photonMap,
                                PhotonMap &specularPhotonMap,
                                const Scene &scene,
                                bool gather) const;
    
    virtual void processPhoton(EmittedPhoton photon,
                               PhotonMap &photonMap,
                               PhotonMap &specularPhotonMap,
                               const Scene &scene) const;
};

#endif /* defined(__RaytracerV3__EmptyShader__) */
