//
//  LambertShader.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/17/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "LambertShader.h"

#include <vector>
#include "Light.h"
#include "Shape.h"
#include <assert.h>


using namespace Math;
using namespace std;
Color3f
LambertShader::shade(const HitInfo & hit, const Scene &scene) const
{
    Color3f ret = Color3f(0,0,0);
    
    
    std::vector<Vec2d> samples;
    
    
    for (const Light *l : scene.lights) {
        const Vec3d &hN = hit.N;
        const Vec3d &hO = hit.P;
        
        
        
        if (l->areaLight()) {
            
            scene.generateStratifiedJitteredSamples(samples, scene.getMonteCarloSamples());
            Math::Color3f shapeColor(0.0f);
            
            int counter = 0;
            
            for (const Vec2f &v: samples) {
                counter++;
                
                Ray ray;
                ray.o = hit.P;
                ray.tMin = 1e-3;
                
                Vec3d lp = l->warp(v, hit.P);
                Vec3d d = (lp-hit.P);
                double dist = d.length();
                d = d.normalize();
                
                ray.tMax = dist + 1e-3;
                ray.d = d;
                Shape *s_int = scene.intersect(ray);
                if (s_int && ray.hit.t > dist-1e-1 && s_int->areaLight()) {
                    double f = (d.dot(hN));
                    if (f < 0.0) {
                        continue;
                    }
                    ray.hit.t = dist;
                    
                    shapeColor += l->computeIntensity(ray.hit, scene)*f/(dist*dist);
                    //                    shapeColor += m_kd;
                }
            }
            
            shapeColor = shapeColor/double(counter);
            ret += shapeColor;
            
        } else {
            Vec3d d = (l->position-hO);
            double dist = d.length();
            d = d.normalize();
            
            Ray ray;
            ray.o = hit.P;
            ray.tMin = 1e-3;
            
            ray.tMax = dist-1e-5;
            ray.d = d;
            if (!scene.intersect(ray)) {
                double f = d.dot(hN);
                ret += l->computeIntensity(hit, scene)*f;
            }
        }
        
    }
    //    ret.x = 1.0;
    ret.x = m_kd.x*ret.x;
    ret.y = m_kd.y*ret.y;
    ret.z = m_kd.z*ret.z;
    return ret/M_PI;
}


//Math::Color3f
//LambertShader::shade(const Renderer *render,
//                     const HitInfo & hit,
//                     PhotonMap &photonMap,
//                     PhotonMap &specularPhotonMap,
//                     const Scene &scene) const
//{
//    float maxDist = scene.maxPhotonMapSearchDist;
//    float nPhotons = scene.numPhotonMapPhotons;
//    float irrStdc[3];
//    float irrSpec[3];
//    float pos[3];
//    float normal[3];
//    
//    pos[0] = hit.P.x;
//    pos[1] = hit.P.y;
//    pos[2] = hit.P.z;
//    normal[0] = hit.N.x;
//    normal[1] = hit.N.y;
//    normal[2] = hit.N.z;
//    
//    photonMap.irradiance_estimate(irrStdc, pos, normal, maxDist, nPhotons);
//    specularPhotonMap.irradiance_estimate(irrSpec, pos, normal, maxDist, nPhotons);
//    
//    Math::Color3f col(irrStdc[0], irrStdc[1], irrStdc[2]);
//    col.x += irrSpec[0];
//    col.y += irrSpec[1];
//    col.z += irrSpec[2];
//    col *= m_kd;
//    return col;
//}
//
//
//void
//LambertShader::processPhoton(const HitInfo & hit,
//                             EmittedPhoton photon,
//                             PhotonMap &photonMap,
//                             PhotonMap &specularPhotonMap,
//                             const Scene &scene) const
//{
//    float power[3];
//    power[0] = photon.power.x;
//    power[1] = photon.power.y;
//    power[2] = photon.power.z;
//    
//    float pos[3];
//    pos[0] = hit.P.x;
//    pos[1] = hit.P.y;
//    pos[2] = hit.P.z;
//    
//    float dir[3];
//    dir[0] = hit.I.x;
//    dir[1] = hit.I.y;
//    dir[2] = hit.I.z;
//    if (photon.specularBounces)
//    {
//        specularPhotonMap.store(power, pos, dir);
//    }
//    photonMap.store(power, pos, dir);
//    
//}

LambertShader::LambertShader(const Color3f & kd) :
m_kd(kd)
{
    
}

LambertShader::~LambertShader()
{
	
}