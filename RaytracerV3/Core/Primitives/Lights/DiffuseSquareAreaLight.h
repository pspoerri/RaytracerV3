//
//  DiffuseSquareAreaLight.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/27/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__DiffuseSquareAreaLight__
#define __RaytracerV3__DiffuseSquareAreaLight__

#include "PhotonSource.h"
#include "Mesh.h"
#include "Math/Vec3.h"
#include "Math/Color.h"

class DiffuseSquareAreaLight: virtual public PhotonSource, virtual public Mesh
{
public:
    DiffuseSquareAreaLight(Math::MeshBase * mesh,
                           const Math::Vec3d& lowerPos,
                           const Math::Vec3d& dx,
                           const Math::Vec3d& dy,
                           double height,
                           double width,
                           const Math::Vec3d& normal,
                           const Math::Color3f& color,
                           double power,
                           int photons);
    ~DiffuseSquareAreaLight();
    
    const Math::Vec3d lowerPos;
    const Math::Vec3d dx;
    const Math::Vec3d dy;
    const double height;
    const double width;
    const Math::Vec3d normal;
    
    virtual bool areaLight()
    {
        return true;
    }
    
    virtual void emitPhotons(std::vector<EmittedPhoton>& photonEmitter, Scene& scene);
    
    
};
#endif /* defined(__RaytracerV3__DiffuseSquareAreaLight__) */
