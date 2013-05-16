//
//  SurfaceShader.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__SurfaceShader__
#define __RaytracerV3__SurfaceShader__

class HitInfo;
class Scene;
#include "Math/Color.h"
#include <iostream>
class SurfaceShader
{
public:
    SurfaceShader();
    ~SurfaceShader();
    
    virtual Math::Color3f shade(const HitInfo & hit,
                                const Scene &scene) const;
    
};
#endif /* defined(__RaytracerV3__SurfaceShader__) */
