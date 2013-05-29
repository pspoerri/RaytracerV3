//
//  SpecularMirrorShader.h
//  ImageSynthesisFramework
//
//  Created by Pascal Spörri on 4/18/13.
//
//

#ifndef __ImageSynthesisFramework__SpecularMirrorShader__
#define __ImageSynthesisFramework__SpecularMirrorShader__

#include "SurfaceShader.h"
#include "PhotonMap.h"
#include "PhotonSource.h" 
class Renderer;
class SpecularMirrorShader: public SurfaceShader
{
public:
    SpecularMirrorShader(double reflectivity);
    const double reflectivity;
    virtual Math::Color3f shade(const HitInfo & hit, const Scene &scene) const;
    
    virtual Math::Color3f shade(const Renderer *render,
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

#endif /* defined(__ImageSynthesisFramework__SpecularMirrorShader__) */
