//
//  IsotropicPointLight.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__IsotropicPointLight__
#define __RaytracerV3__IsotropicPointLight__

#include "PhotonSource.h"
class IsotropicPointLight: public PhotonSource
{
public:
    IsotropicPointLight(const Math::Vec3d& position,
                        const Math::Color3f& color,
                        double power,
                        int photons);
    ~IsotropicPointLight();
    //    virtual Math::Color3f computeIntensity(const HitInfo &hit, const Scene &scene) const;
        virtual void emitPhotons(std::vector<EmittedPhoton>& photonEmitter, Scene& scene);
virtual Math::Color3f computeIntensity(const HitInfo &hit, const Scene &scene) const;
};
#endif /* defined(__RaytracerV3__IsotropicPointLight__) */
