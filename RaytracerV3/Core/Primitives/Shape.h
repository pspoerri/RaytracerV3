//
//  Shape.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Shape__
#define __RaytracerV3__Shape__

#include "SurfaceShader.h"
#include "Ray.h"
class Shape
{
public:
    SurfaceShader* surfaceShader;
    
    Shape(SurfaceShader* surfaceShader = 0);
    virtual ~Shape();

    virtual bool intersect(Ray& r) const = 0;
    virtual bool intersects(Ray& r) const;
    virtual void fillHitInfo(Ray& r) const;

    virtual void renderGL() const = 0;

    virtual bool areaLight() const;
};
#endif /* defined(__RaytracerV3__Shape__) */
