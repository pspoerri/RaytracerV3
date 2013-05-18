//
//  Scene.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Scene__
#define __RaytracerV3__Scene__

#include <vector>
#include <iostream>
#include "Camera.h"
#include "Math/Rand.h"
#include "PhotonSource.h"

class Light;
class Shape;
class PhotonSource;
class PhotonMap;
using namespace std;
class Scene
{
public:
    Scene();
    ~Scene();
    Math::RandMT *rand_gen;

    vector<Shape *> shapes;
    vector<Light *> lights;
    vector<PhotonSource *> photonSources;
    Camera camera;
    
    float maxPhotonMapSearchDist;
    float numPhotonMapPhotons;
    
    void generateStratifiedJitteredSamples(std::vector<Math::Vec2d> &samples,
                                           int N) const;
    void generateRandomSamples(std::vector<Math::Vec2d> &samples,
                               int N) const;
    void generateUniformSamples(std::vector<Math::Vec2d> &samples,
                                int N) const;
    
    int getMonteCarloSamples() const;
    
    Shape* intersect(Ray &r) const;
    
    void photonScattering(EmittedPhoton photon,
                          PhotonMap &photonMap,
                          PhotonMap &specularPhotonMap) const;

private:
    int _monteCarloSamples;
};

#endif /* defined(__RaytracerV3__Scene__) */
