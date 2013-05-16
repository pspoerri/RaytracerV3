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
#include "Shape.h"
#include "Light.h"

using namespace std;
class Scene
{
public:
    Scene();
    
    vector<Shape *> shapes;
    vector<Light *> lights;
    Camera camera;
};

#endif /* defined(__RaytracerV3__Scene__) */
