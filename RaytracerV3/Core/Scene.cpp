//
//  Scene.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "Scene.h"
#include "Shape.h"
#include "PhotonMap.h"

Scene::Scene():
    rand_gen(new Math::RandMT(time(NULL))),
photonMap(NULL),
specularPhotonMap(NULL),
    _monteCarloSamples(32)
{
//    maxPhotonMapSearchDist = 0.1;
    maxPhotonMapSearchDist = 10.0;
    numPhotonMapPhotons = 100;
    
    sigma_s = 0.1;
    sigma_t = 0.0001;
    rayMarchScatter = 0.1;
}

Scene::~Scene()
{
    delete rand_gen;
    delete photonMap;
    delete specularPhotonMap;
}

void
Scene::generateStratifiedJitteredSamples(std::vector<Math::Vec2d> &samples,
                                         int N) const
{
    int n = floor(sqrtf(N));
    if (N != n*n) {
        n++;
        N = n*n;
#ifdef DEBUG
        std::cerr << "Scene::generateStratifiedJitteredSamples increasing sample size"<<std::endl;
#endif
    }
    samples.clear();
    samples.reserve(n*n);
    double factor = 1.0/double(n);
    double dx = factor;
    for (int i=0; i< n; i++)
    {
        double fi = double(i)*factor;
        for (int j=0; j<n; j++) {
            double fj = double(j)*factor;
            double x = rand_gen->nextd(fi, fi+dx);
            double y = rand_gen->nextd(fj, fj+dx);
            samples.push_back(Math::Vec2d(x,y));
        }
    }
}

void
Scene::generateRandomSamples(std::vector<Math::Vec2d> &samples,
                             int N) const
{
    samples.clear();
    samples.reserve(N);
    for (int i=0; i<N; i++)
    {
        double x = rand_gen->nextd(0.0,1.0);
        double y = rand_gen->nextd(0.0,1.0);
        samples.push_back(Math::Vec2d(x,y));
    }
}

void
Scene::generateUniformSamples(std::vector<Math::Vec2d> &samples,
                                    int N) const 
{
    int n = floor(sqrtf(N));
    if (N != n*n) {
        n++;
        N = n*n;
    }
    samples.clear();
    samples.reserve(n*n);
    double factor = 1.0/double(n);
    double dx = factor/2.0;
    for (int i=0; i< n; i++)
    {
        double x = double(i)*factor+dx;
        for (int j=0; j<n; j++) {
            double y = double(j)*factor+dx;
            samples.push_back(Math::Vec2d(x,y));
        }
    }
}

int
Scene::getMonteCarloSamples() const
{
    return _monteCarloSamples;
}

Shape*
Scene::intersect(Ray &r) const {
    
    double t = r.tMax;
    Shape *s_hit = NULL;
    for (Shape *s: shapes) {
        if (s->intersect(r)) {
            double ht = r.hit.t;
            //            r.tMax = ht;
            //            if (ht >= r.tMin && ht < r.tMax) {
            if (ht < t) {
                s_hit = s;
                t = ht;
            }
            //            }
        }
    }
    r.hit.t = t;
    return s_hit;
}

void
Scene::emit_scatterPhotons()
{
    std::cout << "Emitting Photons..." << std::endl;
    std::vector<EmittedPhoton> emittedPhotons;
    for (PhotonSource *source: photonSources)
    {
        source->emitPhotons(emittedPhotons, *this);
    }
    
    photonMap = new PhotonMap(1024*1024*1024);
    specularPhotonMap = new PhotonMap(1024*1024*1024);
    std::cout << "Scattering Photons..." << std::endl;
    for (size_t i=0; i<emittedPhotons.size(); i++)
    {
        photonScattering(emittedPhotons[i],
                         *photonMap,
                         *specularPhotonMap);
    }
    photonMap->balance();
    specularPhotonMap->balance();
}

void
Scene::photonScattering(EmittedPhoton photon,
                        PhotonMap &photonMap,
                        PhotonMap &specularPhotonMap) const
{
    Ray r;
    r.o = photon.position+0.001*photon.dir;
    r.d = photon.dir;
    
    Shape* hitShape = intersect(r);
    if (hitShape != NULL)
    {
        hitShape->fillHitInfo(r);
        if (hitShape->surfaceShader == NULL)
        {
            return;
        }
        r.hit.surfaceShader->processPhoton(r.hit,
                                           photon,
                                           photonMap,
                                           specularPhotonMap,
                                           *this);
    }
}

void
Scene::reset()
{
    delete photonMap;
    delete specularPhotonMap;
    fog.clear();
    shapes.clear();
    photonSources.clear();
}