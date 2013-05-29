//
//  SpecularMirrorShader.cpp
//  ImageSynthesisFramework
//
//  Created by Pascal Spörri on 4/18/13.
//
//


#include "SpecularMirrorShader.h"
#include "Scene.h"
#include "Renderer.h"


SpecularMirrorShader::SpecularMirrorShader(double reflectivity):
    reflectivity(reflectivity)
{
    
}

Math::Color3f
SpecularMirrorShader::shade(const HitInfo &hit, const Scene &scene) const
{
    return Math::Color3f(0,0,0);
}

Math::Color3f
SpecularMirrorShader::shade(const Renderer *renderer,
                            const HitInfo &hit,
                            PhotonMap &photonMap,
                            PhotonMap &specularPhotonMap,
                            const Scene &scene,
                            bool gather) const
{
    Ray r;
    r.d = Math::reflect(hit.N, hit.I);
    r.o = hit.P+0.001*hit.N;
//    renderer->recursiv
    return renderer->recursiveRender(r, photonMap, specularPhotonMap, scene, gather);
}

void
SpecularMirrorShader::processPhoton(const HitInfo &hit,
                                    EmittedPhoton photon,
                                    PhotonMap &photonMap,
                                    PhotonMap &specularPhotonMap,
                                    const Scene &scene) const
{
    double b = scene.rand_gen->nextd(0.0, 1.0);
    if (b < reflectivity)
    {
        return;
    }
    photon.dir = Math::reflect(hit.N, hit.I);
    photon.position = hit.P+0.001*hit.N;
    if (!photon.indirect)
        photon.specularBounces = true;
    scene.photonScattering(photon, photonMap, specularPhotonMap);
    
}