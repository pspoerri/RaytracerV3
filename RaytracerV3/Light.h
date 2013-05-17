//
//  Light.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Light__
#define __RaytracerV3__Light__

#include "Math/Color.h"
#include "Math/Core.h"
#include "HitInfo.h"
#include "Scene.h"

enum LightSamplingMode {
    DIRECT,
    UNIFORM_SURFACE_AREA_SAMPLING,
    UNIFORM_SUBTENDED_SOLID_ANGLE_SAMPLING,
};

class Light
{
public:
    Light(const Math::Vec3d& position,
          const Math::Color4f& color,
          const double power);
    const Math::Vec3d position;
    const Math::Color4f color;
    const double power;
    
    virtual Math::Color3f computeIntensity(const HitInfo &hit, const Scene &scene) const;
    virtual Math::Color3f computeSurfaceIntensity(const HitInfo &hit, const Scene &scene) const;
    
    
    virtual Math::Vec3d warp(const Math::Vec2d &v, const Math::Vec3d &origin) const;
    virtual double      getPdf(const Math::Vec3d &p,  const Math::Vec3d &origin) const;
    virtual double      getArea() const;
    
    virtual bool areaLight() const;
};

#endif /* defined(__RaytracerV3__Light__) */
