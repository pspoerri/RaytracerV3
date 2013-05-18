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
    _monteCarloSamples(64)
{
    maxPhotonMapSearchDist = 0.1;
    numPhotonMapPhotons = 64;
}

Scene::~Scene()
{
    delete rand_gen;
}

void
Scene::generateStratifiedJitteredSamples(std::vector<Math::Vec2d> &samples,
                                         int N) const
{
    int n = floor(sqrtf(N));
    if (N != n*n) {
        n++;
        N = n*n;
    }
    samples.clear();
    samples.reserve(n*n);
    double factor = 1.0/double(n+1);
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