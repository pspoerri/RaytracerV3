//
//  PointLight.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__PointLight__
#define __RaytracerV3__PointLight__

#include "Light.h"

class PointLight: public Light
{
public:
    PointLight(const Math::Vec3d& position,
               const Math::Color4f& color,
               const double power);
    
    virtual Math::Color3f computeIntensity(const HitInfo &hit, const Scene &scene) const;

};

#endif /* defined(__RaytracerV3__PointLight__) */
