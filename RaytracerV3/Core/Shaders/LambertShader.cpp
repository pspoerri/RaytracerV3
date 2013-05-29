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
#include "PhotonMap.h"
#include "Warp.h"
#include "Renderer.h"
using namespace Math;
using namespace std;
Color3f
LambertShader::shade(const HitInfo & hit, const Scene &scene) const
{
    Color3f ret = Color3f(0,0,0);
    
//    Math::Mat44d tr;
//    tr.makeIdentity();
//    tr.rotateTo(Math::Vec3d(0,0,1), hit.N);
//    
//    std::vector<Vec2d> samples;
//    scene.generateStratifiedJitteredSamples(samples, scene.getMonteCarloSamples());
//    int scatter = 0;
//    for (const Vec2d sample: samples)
//    {
//        
//        Ray ray;
//        ray.o = hit.P;
//        ray.tMin = 1e-3;
//        
//        Vec3d d;
//        Warp::cosineHemisphere(&d, sample.x, sample.y);
//        ray.d = tr*d;
//        
//        Shape *s_hit = scene.intersect(ray);
//        if (s_hit != NULL) {
//            s_hit->fillHitInfo(ray);
//            ret += s_hit->surfaceShader->shade(ray.hit, *(scene.photonMap), *(scene.specularPhotonMap), scene);
//        }
//            //                    shapeColor += m_kd;
//    }
//    ret = ret/double(scene.getMonteCarloSamples());
//
//     //    ret.x = 1.0;
//    ret.x = m_kd.x*ret.x;
//    ret.y = m_kd.y*ret.y;
//    ret.z = m_kd.z*ret.z;
    return ret/M_PI;
}


Math::Color3f
LambertShader::shade(const Renderer *renderer,
                     const HitInfo & hit,
                     PhotonMap &photonMap,
                     PhotonMap &specularPhotonMap,
                     const Scene &scene,
                     bool gather) const
{
    Math::Color3f col(0.0,0.0,0.0);

    if (gather)
    {
        Math::Mat44d tr;
        tr.makeIdentity();
        tr.rotateTo(Math::Vec3d(0,0,1), hit.N);

        std::vector<Vec2d> samples;
        scene.generateStratifiedJitteredSamples(samples, scene.getMonteCarloSamples());
        double nsamples = double(samples.size());
        for (const Vec2d sample: samples)
        {
            Ray ray;
            ray.o = hit.P;
            ray.tMin = 1e-3;

            Vec3d d;
            Warp::cosineHemisphere(&d, sample.x, sample.y);
            ray.d = (tr*d).normalize();
            col += (ray.d).dot(hit.N)*renderer->recursiveRender(ray, photonMap, specularPhotonMap, scene, false)/nsamples;
                //                    shapeColor += m_kd;
        }
        
        for (PhotonSource *l : scene.photonSources) {
            if (l->areaLight()) {
                std::cout << "LambertShader::shade: arealight unsupported" << std::endl;
                continue;
            }
            const Vec3d &hN = hit.N;
            const Vec3d &hO = hit.P;
            Vec3d d = (l->position-hO);
            double dist = d.length();
            
            Ray ray;
            ray.o = hit.P;
            ray.tMin = 1e-3;
            
            ray.tMax = dist-1e-5;
            ray.d = d.normalize();
            if (!scene.intersect(ray)) {
                double f = (ray.d).dot(hN);
                col += l->computeIntensity(hit, scene)*f/M_PI;
            }
        }
    }
    float maxDist = scene.maxPhotonMapSearchDist;
    float nPhotons = scene.numPhotonMapPhotons;
    float pos[3];
    float normal[3];
    
    pos[0] = hit.P.x;
    pos[1] = hit.P.y;
    pos[2] = hit.P.z;
    normal[0] = hit.N.x;
    normal[1] = hit.N.y;
    normal[2] = hit.N.z;
    
    if (gather)
    {
        float irrSpec[3];
        specularPhotonMap.irradiance_estimate(irrSpec, pos, normal, maxDist, nPhotons);
        col += Math::Color3f(irrSpec[0], irrSpec[1], irrSpec[2]);
    }
    else
    {
        float irrStdc[3];
        photonMap.irradiance_estimate(irrStdc, pos, normal, maxDist, nPhotons);
        col += Math::Color3f(irrStdc[0], irrStdc[1], irrStdc[2]);
    }
//    col *= m_kd;
    return col*m_kd;
}


void
LambertShader::processPhoton(const HitInfo & hit,
                             EmittedPhoton photon,
                             PhotonMap &photonMap,
                             PhotonMap &specularPhotonMap,
                             const Scene &scene) const
{
    float power[3];
    power[0] = photon.power.x;
    power[1] = photon.power.y;
    power[2] = photon.power.z;
    
    float pos[3];
    pos[0] = hit.P.x;
    pos[1] = hit.P.y;
    pos[2] = hit.P.z;
    
    float dir[3];
    dir[0] = hit.I.x;
    dir[1] = hit.I.y;
    dir[2] = hit.I.z;
    if (photon.specularBounces)
    {
        specularPhotonMap.store(power, pos, dir);
    }
    photonMap.store(power, pos, dir);

    double r = scene.rand_gen->nextd();
    if (r > surface_reflectance)
    {
//        photon.dir = Math::reflect(hit.N, hit.I);
        double x = scene.rand_gen->nextd();
        double y = scene.rand_gen->nextd();
        Vec3d d;
        Warp::cosineHemisphere(&d, x, y);
        Math::Mat44d tr;
        tr.makeIdentity();
        tr.rotateTo(Math::Vec3d(0,0,1), hit.N);
        photon.dir = tr*d;
        photon.position = hit.P+0.001*hit.N;
        photon.indirect = true;
        photon.specularBounces = false;
        scene.photonScattering(photon, photonMap, specularPhotonMap);
    }
    

    
}

LambertShader::LambertShader(const Color3f & kd, double surface_reflectance) :
    m_kd(kd),
    surface_reflectance(surface_reflectance)
{
    
}

LambertShader::~LambertShader()
{
	
}