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
#include "Util/Array2D.h"

class PhotonMapper: Renderer
{
protected:
    void setRes(int x, int y);
    FrameBuffer m_fbo;
    Util::Array2D<Math::Color4f> m_rgbaBuffer;

public:
    PhotonMapper();
    ~PhotonMapper();
    
    virtual void render(Scene &scene);
    
    virtual Math::Vec3f recursiveRender(Ray &r,
                                        PhotonMap& photonMap,
                                        PhotonMap& specularPhotonMap,
                                        const Scene& scene,
                                        bool gather) const;
    virtual Math::Vec3f rayMarch(Ray &r,
                                 double tmin,
                                 double tmax,
                                 PhotonMap& photonMap,
                                 PhotonMap& specularPhotonMap,
                                 const Scene& scene,
                                 const Shape* nearestShape,
//                                 const Math::Box<Math::Vec3d>& box,
                                 bool gather) const;
};
#endif /* defined(__RaytracerV3__PhotonMapper__) */
