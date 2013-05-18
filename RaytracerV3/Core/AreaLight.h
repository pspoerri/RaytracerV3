//
//  AreaLight.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__AreaLight__
#define __RaytracerV3__AreaLight__

#include "Light.h"
#include "Shape.h"
class AreaLight: public Light
{
public:
    AreaLight(const Math::Vec3d& position,
              const Math::Color4f& color,
              const double power);
    
    
    virtual bool areaLight()
    {
        return true;
    }
};
#endif /* defined(__RaytracerV3__AreaLight__) */
