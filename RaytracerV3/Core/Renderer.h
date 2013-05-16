//
//  Renderer.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Renderer__
#define __RaytracerV3__Renderer__

#include "Scene.h"
#include <iostream>

class Renderer
{
public:
    virtual ~Renderer();
    virtual void render(Scene &scene) = 0;
};

#endif /* defined(__RaytracerV3__Renderer__) */
