//
//  SceneLoader.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__SceneLoader__
#define __RaytracerV3__SceneLoader__

#include "Scene.h"
class SceneLoader
{
    Scene &scene;
public:
    SceneLoader(Scene &scene);
    void reset();

    void loadScene();
    void loadSpheres();
    void loadCornellBox4();

};
#endif /* defined(__RaytracerV3__SceneLoader__) */
