//
//  RenderGL.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__RenderGL__
#define __RaytracerV3__RenderGL__

#include <iostream>
#include "Renderer.h"
#include "OGL/FBO.h"
class RenderGL: public Renderer
{
protected:
    void setRes(int x, int y);
    FrameBuffer m_fbo;
public:
    RenderGL();
    ~RenderGL();
    
    virtual void render(Scene &scene);
};



#endif /* defined(__RaytracerV3__RenderGL__) */
