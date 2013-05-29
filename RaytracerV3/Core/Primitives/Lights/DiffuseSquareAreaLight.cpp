//
//  DiffuseSquareAreaLight.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/27/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "DiffuseSquareAreaLight.h"

#include <assert.h>
#include "Math/Mat44.h"
#include "Scene.h"
#include "Mesh.h"
#include "EmptyShader.h"
#include "Warp.h"
DiffuseSquareAreaLight::DiffuseSquareAreaLight(Math::MeshBase * mesh,
                                               const Math::Vec3d& lowerPos,
                                               const Math::Vec3d& dx,
                                               const Math::Vec3d& dy,
                                               double height,
                                               double width,
                                               const Math::Vec3d& normal,
                                               const Math::Color3f& color,
                                               double power,
                                               int photons):
    PhotonSource(lowerPos,color, power, photons),
    Mesh(new EmptyShader(), mesh),
    lowerPos(lowerPos),
    dx(dx.normalized()*width),
    dy(dy.normalized()*height),
    height(height),
    width(width),
    normal(normal.normalized())
{
}

DiffuseSquareAreaLight::~DiffuseSquareAreaLight()
{
    
}

void
DiffuseSquareAreaLight::emitPhotons(std::vector<EmittedPhoton> &photonEmitter, Scene &scene)
{
    std::vector<Math::Vec2d> samples;
    scene.generateStratifiedJitteredSamples(samples, photons);
    std::vector<Math::Vec2d> lightSamples;
    scene.generateStratifiedJitteredSamples(lightSamples, photons);
    const double emittedPhotons = (double) samples.size();
    
    photonEmitter.reserve(photonEmitter.size()+photons);
    float total_color = color.x+color.y+color.z;
    
    Math::Vec3f emittedPower = power/(emittedPhotons*total_color)*color;
    
    //    Math::Mat44d tr;
    //    tr.makeIdentity();
    //    tr.rotateTo(Math::Vec3d(0,0,1), d);
    //
    //    return location+radius*(tr*ret);
    
    Math::Mat44d tr;
    tr.makeIdentity();
    tr.rotateTo(Math::Vec3d(0,0,1), normal);
    //
    for (size_t i = 0; i < samples.size(); i++)
    {
        Math::Vec2d uv = samples[i];
        Math::Vec2d lightUV = lightSamples[i];
        Math::Vec3d pos = lowerPos + uv.x*dx + uv.y*dy + 1e-3*normal;
        //        std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
        Math::Vec3d d;
        Math::Warp::uniformHemisphere(&d, lightUV.x, lightUV.y);
        
        //        Math::Vec3d dir = (tr*d).normalize();
        //        dir.z = -d.z;
        Math::Vec3d dir = d;
        dir.z = -dir.z;
        //        std::cout << d.x << " " << d.y << " " << d.z << std::endl;
        //        std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
        
        photonEmitter.push_back({pos, emittedPower, dir, false});
    }
}