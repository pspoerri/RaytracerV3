//
//  LambertShader.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/17/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__LambertShader__
#define __RaytracerV3__LambertShader__

#include "SurfaceShader.h"
#include "Scene.h"
//#include "Shader.h"
class Renderer;
class LambertShader : public SurfaceShader
{
protected:
    Math::Color3f m_kd;
    
public:
    LambertShader(const Math::Color3f & kd = Math::Color3f(0.8f));
    ~LambertShader();
    
    virtual Math::Color3f shade(const HitInfo & hit, const Scene &scene) const;
    
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
#endif /* defined(__RaytracerV3__LambertShader__) */
