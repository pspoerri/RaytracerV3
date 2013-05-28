//
//  SpecularDielectricShader.cpp
//  ImageSynthesisFramework
//
//  Created by Pascal Spörri on 4/18/13.
//
//

#include "SpecularDielectricShader.h"

#include "SpecularMirrorShader.h"
#include "Scene.h"
#include "Renderer.h"
#include "PhotonMap.h"
#include "Shape.h"
SpecularDielectricShader::SpecularDielectricShader(double refractiveIndex):
    refractiveIndex(refractiveIndex)
{
    
}

Math::Color3f
SpecularDielectricShader::shade(const HitInfo &hit, const Scene &scene) const
{
    return Math::Color3f(0,0,0);
}

Math::Color3f
SpecularDielectricShader::shade(const Renderer *renderer,
                            const HitInfo &hit,
                            PhotonMap &photonMap,
                            PhotonMap &specularPhotonMap,
                            const Scene &scene) const
{

    double reflectivity = Math::reflectance(hit.N, hit.I, 1.0, refractiveIndex);
    double refractivity = 1.0-reflectivity;
//    if (refractiveIndex >= 1.0)
//    {
//        reflectivity = 0.0;
//        refractivity = 1.0;
//    }
    
    Ray refracted;
    Math::Vec3d refr = Math::refract(-hit.I, hit.N, 1.0/refractiveIndex);
    Ray ri;
    ri.o = hit.P - 0.001*hit.N;
    ri.d = refr.normalized();
    hit.shape->intersect(ri);
    hit.shape->fillHitInfo(ri);
    refracted.d = Math::refract(-refr, -ri.hit.N, refractiveIndex).normalized();
    refracted.o = ri.hit.P-ri.hit.N*0.001;

    Ray reflected;
    reflected.d = Math::reflect(hit.N, hit.I);
    reflected.o = hit.P+0.001*hit.N;

    return
        (1.0-reflectivity)
            *renderer->recursiveRender(refracted, photonMap, specularPhotonMap, scene)
        +reflectivity
        *renderer->recursiveRender(reflected, photonMap, specularPhotonMap, scene)
;
}

void
SpecularDielectricShader::processPhoton(const HitInfo &hit,
                                    EmittedPhoton photon,
                                    PhotonMap &photonMap,
                                    PhotonMap &specularPhotonMap,
                                    const Scene &scene) const
{
    double b = scene.rand_gen->nextd(0.0, 1.0);
    if (!photon.indirect)
        photon.specularBounces = true;
    double reflectivity = Math::reflectance(hit.N, hit.I, 1.0, refractiveIndex);
//    if (refractiveIndex >= 1.0)
//    {
//        reflectivity = 0.0;
//    }
    if (b > reflectivity)
    {
        // do refraction
        Math::Vec3d refr = Math::refract(-hit.I, hit.N, 1.0/refractiveIndex);
        Ray r;
        r.o = hit.P - 0.001*hit.N;
        r.d = refr;
        hit.shape->intersect(r);
        hit.shape->fillHitInfo(r);
        photon.dir = Math::refract(-refr, -r.hit.N, refractiveIndex);
        photon.position = r.hit.P+r.hit.N*0.001;
        scene.photonScattering(photon, photonMap, specularPhotonMap);
    }
    else
    {
        // process reflectivty
        photon.dir = Math::reflect(hit.N, hit.I);
        photon.position = hit.P+0.001*hit.N;
    }

    scene.photonScattering(photon, photonMap, specularPhotonMap);
    
}