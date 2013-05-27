//
//  SceneLoader.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//


#include "SceneLoader.h"
#include "Sphere.h"
#include "LambertShader.h"
#include "PointLight.h"
#include "IsotropicPointLight.h"

using namespace Math;
SceneLoader::SceneLoader(Scene &scene):
    scene(scene)
{
    
}

void
SceneLoader::loadScene()
{
    Math::Color3f color(0.5f);
    SurfaceShader *gray = new LambertShader(color);
//    new AmbientOcclusionShader(JITTERED, COSINE_HEMISPHERE, color);
//    scene.setSkylightColor(color);
    
    
    
    double bigsphere_radius = 1000000.0f;
    Vec3d bigsphere_center(0,0, -bigsphere_radius);
    double smallsphere_radius = 10.0f;
    Vec3d smallsphere_center(0, 0, smallsphere_radius);
    
    scene.shapes.push_back(new Sphere(gray, bigsphere_center, bigsphere_radius));
    scene.shapes.push_back(new Sphere(gray, smallsphere_center, smallsphere_radius));
    
    scene.camera.updateCameraPos(smallsphere_center-Vec3d(-smallsphere_radius, smallsphere_radius*10.0, -1.0*smallsphere_radius), smallsphere_center, Vec3d(0,0,1));
    
    IsotropicPointLight *pointLight =
        new IsotropicPointLight(
            smallsphere_center-Vec3d(-smallsphere_radius, smallsphere_radius*10.0, -1.0*smallsphere_radius),
            Math::Color3f(1,1,1),
            1000000, 10000000);
//    scene.lights.push_back(pointLight);
    scene.photonSources.push_back(pointLight);
}