//
//  SpecularDielectricShader.h
//  ImageSynthesisFramework
//
//  Created by Pascal Spörri on 4/18/13.
//
//

#ifndef __ImageSynthesisFramework__SpecularDielectricShader__
#define __ImageSynthesisFramework__SpecularDielectricShader__

#include "SurfaceShader.h"
#include "PhotonSource.h"

class Renderer;

class SpecularDielectricShader: public SurfaceShader
{
public:

    SpecularDielectricShader(double refractiveIndex);
    const double refractiveIndex;
    
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

#endif /* defined(__ImageSynthesisFramework__SpecularDielectricShader__) */
