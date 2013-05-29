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
    const double surface_reflectance;
public:
    LambertShader(const Math::Color3f & kd = Math::Color3f(0.8f), double surface_reflectance=1.0);
    ~LambertShader();
    
    virtual Math::Color3f shade(const HitInfo & hit, const Scene &scene) const;
    
    virtual Math::Color3f shade(const Renderer *renderer,
                                const HitInfo & hit,
                                PhotonMap &photonMap,
                                PhotonMap &specularPhotonMap,
                                const Scene &scene,
                                bool gather) const;
    
    virtual void processPhoton(const HitInfo & hit,
                               EmittedPhoton photon,
                               PhotonMap &photonMap,
                               PhotonMap &specularPhotonMap,
                               const Scene &scene) const;
};
#endif /* defined(__RaytracerV3__LambertShader__) */
