//
//  PhotonSource.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__PhotonSource__
#define __RaytracerV3__PhotonSource__

#include "Math/Vec3.h"
#include "Math/Color.h"
#include <vector>

class Scene;
//#include "Scene.h"

typedef struct EmittedPhoton
{
    Math::Vec3d position;
    Math::Vec3f power;
    Math::Vec3d dir;
    bool        specularBounces;
    bool        indirect;
} EmittedPhoton;

class PhotonSource
{
public:
    PhotonSource(const Math::Color3f& color, double power, int photons);
    ~PhotonSource();
    
    const Math::Color3f color;
    const double power;
    const int photons;
    
    virtual void emitPhotons(std::vector<EmittedPhoton>& photons, Scene& scene) = 0;
    
    
};
#endif /* defined(__RaytracerV3__PhotonSource__) */
