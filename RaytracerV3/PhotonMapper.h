//
//  PhotonMapper.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__PhotonMapper__
#define __RaytracerV3__PhotonMapper__

#include "Renderer.h"
#include "OGL/FBO.h"

class PhotonMapper: Renderer
{
protected:
    void setRes(int x, int y);
    FrameBuffer m_fbo;
public:
    PhotonMapper();
    ~PhotonMapper();
    
    virtual void render(Scene &scene);
};
#endif /* defined(__RaytracerV3__PhotonMapper__) */
