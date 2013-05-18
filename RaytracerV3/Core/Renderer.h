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
#include "PhotonMap.h"

class Renderer
{
public:
    virtual ~Renderer();
    virtual void render(Scene &scene) = 0;
    
    virtual Math::Vec3f recursiveRender(Ray &r,
                                        PhotonMap& photonMap,
                                        PhotonMap& specularPhotonMap,
                                        const Scene& scene) const
    {
        
        return Math::Vec3f(0,0,0);
    }
};

#endif /* defined(__RaytracerV3__Renderer__) */
