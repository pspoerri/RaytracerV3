//
//  AreaLight.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "AreaLight.h"

AreaLight::AreaLight(const Math::Vec3d& position,
                     const Math::Color4f& color,
                     const double power):
Light(position, color, power)
{
    
}