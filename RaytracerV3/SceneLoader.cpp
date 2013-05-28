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
#include "Math/MeshBase.h"
#include "Mesh.h"
#include "Math/Obj.h"
#include "DiffuseSquareAreaLight.h"
#include "SpecularDielectricShader.h"
#include "SpecularMirrorShader.h"
#include <GL/glfw.h>


using namespace Math;
SceneLoader::SceneLoader(Scene &scene):
    scene(scene)
{
    
}

void
SceneLoader::loadScene()
{
    
    loadCornellBox();
//    loadCave();
}

bool
SceneLoader::handleSceneLoading()
{
    if (glfwGetKey('1')) {
        loadCornellBox();
        return true;
    }
    if (glfwGetKey('2'))
    {
        loadCave();
        return true;
    }
    if (glfwGetKey('9'))
    {
        loadSpheres();
        return true;
    }
    return false;
}

void
SceneLoader::loadSpheres()
{
    reset();
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
                            1000, 1000000);
    //    scene.lights.push_back(pointLight);
    scene.photonSources.push_back(pointLight);
}

void
SceneLoader::loadCave()
{
    reset();
    MeshBase *cave = Math::readObjMesh("data/cave/cave.obj");
    Color3f white(1.0, 1.0, 1.0);
    LambertShader *white_shader = new LambertShader(white,0.5);
    scene.shapes.push_back(new Mesh(white_shader, cave));

    Vec3d entrance(0,-17,15);
    Vec3d cameraPos(0.6, -15.9,-6.9);
    Vec3d lightColor(1.0, 1.0, 1.0);
    Vec3d dir = (entrance-cameraPos).normalize();
//    Vec3d dir = Vec3d(-0.0677413, 0.85384, 0.516109).normalize();
    Vec3d up = Vec3d(0,0,1).normalize();
//    Vec3d dir = Vec3d(-0.21, 0.67,-0.015).normalize();
//    Vec3d up = Vec3d(0,0,1).normalize();
    
    IsotropicPointLight *light = new IsotropicPointLight(
                                                         entrance,
                                                         lightColor,
                                                         50000.0,
                                                         10*1024*1024);
    scene.photonSources.push_back(light);
    
    scene.camera.updateCameraPos(cameraPos, dir, up);

}

void
SceneLoader::loadCornellBox()
{
    reset();
    MeshBase *mtop    = Math::readObjMesh("data/cornell_box/top.obj");
    MeshBase *mbottom = Math::readObjMesh("data/cornell_box/bottom.obj");
    MeshBase *mleft   = Math::readObjMesh("data/cornell_box/left.obj");
    MeshBase *mright  = Math::readObjMesh("data/cornell_box/right.obj");
    MeshBase *mlower  = Math::readObjMesh("data/cornell_box/lower.obj");
    MeshBase *mlight  = Math::readObjMesh("data/cornell_box/light.obj");
    
    Color3f white(1.0, 1.0, 1.0);
    Color3f red(1.0, 0.0, 0.0);
    Color3f green(0.0, 1.0, 0.0);
    LambertShader *white_shader = new LambertShader(white,0.5);
    LambertShader *green_shader = new LambertShader(green, 0.5);
    LambertShader *red_shader = new LambertShader(red, 0.5);
    
    scene.shapes.push_back(new Mesh(white_shader, mtop));
    scene.shapes.push_back(new Mesh(white_shader, mbottom));
    scene.shapes.push_back(new Mesh(white_shader, mlower));
    scene.shapes.push_back(new Mesh(red_shader, mleft));
    scene.shapes.push_back(new Mesh(green_shader, mright));
    
    Vec3d lowerPos(-0.25, -0.25, 1);
    Vec3d normal(0,0,-1);
    Vec3d dx(1.0, 0, 0);
    Vec3d dy(0, 1.0, 0);
    Vec3d lightColor(1.0, 1.0, 1.0);
    double width = 0.5;
    double height = 0.5;
    
    IsotropicPointLight *light = new IsotropicPointLight(
                                                         Vec3d(0,0,1.001),
                                                       lightColor,
                                                       70.0,
                                                       10*1024*1024);
    scene.photonSources.push_back(light);
    scene.maxPhotonMapSearchDist = 0.1;
    scene.numPhotonMapPhotons = 500;

//    DiffuseSquareAreaLight *areaLight = new DiffuseSquareAreaLight(
//                                                                   mlight,
//                                                                   lowerPos,
//                                                                   dx,
//                                                                   dy,
//                                                                   height,
//                                                                   width,
//                                                                   normal,
//                                                                   lightColor,
//                                                                   10.0,
//                                                                   1024*1024);
//    scene.shapes.push_back(areaLight);
//    scene.photonSources.push_back(areaLight);
    
    double sphere_radius = 0.3;
    double pos = 1.0-1.8*sphere_radius;
    
//    SpecularDielectricShader *refraction = new SpecularDielectricShader(2.42);
//    Sphere *mirrored = new Sphere(refraction, Vec3d(pos, -pos, -1.0+sphere_radius), sphere_radius);
//    Sphere *glass = new Sphere(refraction, Vec3d(-pos, pos, -1.0+sphere_radius), sphere_radius);
    SpecularMirrorShader *mirror = new SpecularMirrorShader(0.5);
    SpecularDielectricShader *refraction = new SpecularDielectricShader(1.333);
    Sphere *mirrored = new Sphere(mirror, Vec3d(pos, -pos, -1.0+sphere_radius), sphere_radius);
    Sphere *glass = new Sphere(refraction, Vec3d(-pos, pos, -1.0+sphere_radius), sphere_radius);
    scene.shapes.push_back(mirrored);
    scene.shapes.push_back(glass);
    ////
    
    
    scene.camera.updateCameraPos(Vec3d(0,4.5,0), Vec3d(0,1,0), Vec3d(0,0,1));
}


void
SceneLoader::reset()
{
    scene.reset();
}