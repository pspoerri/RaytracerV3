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
class HitInfo;

//#include "Scene.h"
typedef struct VolumetricPhoton
{
    Math::Vec3d position;
    Math::Vec3d power;
    double      radius;
} VolumetricPhoton;
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
    PhotonSource(const Math::Vec3d& position, const Math::Color3f& color, double power, int photons);
    ~PhotonSource();
    
    const Math::Color3f color;
    const Math::Vec3d position;
    const double power;
    const int photons;
    
    virtual void emitPhotons(std::vector<EmittedPhoton>& photons, Scene& scene) = 0;
    
    virtual Math::Color3f computeIntensity(const HitInfo &hit, const Scene &scene) const;
    virtual Math::Color3f computeSurfaceIntensity(const HitInfo &hit, const Scene &scene) const;
    
    
    virtual Math::Vec3d warp(const Math::Vec2d &v, const Math::Vec3d &origin) const;
    virtual double      getPdf(const Math::Vec3d &p,  const Math::Vec3d &origin) const;
    virtual double      getArea() const;
    
    virtual bool areaLight() const;
    
};
#endif /* defined(__RaytracerV3__PhotonSource__) */
