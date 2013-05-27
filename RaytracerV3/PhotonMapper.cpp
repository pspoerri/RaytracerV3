//
//  PhotonMapper.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "PhotonMapper.h"
#include <OpenGL/OpenGL.h>
#include "Platform/Progress.h"
#include "PhotonSource.h"
#include "PhotonMap.h"
#include "Shape.h"

PhotonMapper::PhotonMapper():
    m_fbo(FrameBuffer(GL_TEXTURE_2D, 512, 512, -1, GL_RGBA32F_ARB, 1, 1, 0, "PhotonMapper FBO"))
{
    m_fbo.checkFramebufferStatus(1);
}

PhotonMapper::~PhotonMapper()
{
    
}


void
PhotonMapper::setRes(int x, int y)
{
	m_rgbaBuffer.resizeErase(x, y);
	m_fbo.resizeExistingFBO(x, y);
	
	// clear the buffers
	m_rgbaBuffer = Math::Vec4f(0.0f);
	
	// Upload a blank texture to the FBO
	glBindTexture(GL_TEXTURE_2D, m_fbo.colorTextureID(0));
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_fbo.width(), m_fbo.height(), GL_RGBA, GL_FLOAT, &m_rgbaBuffer(0,0));
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
PhotonMapper::render(Scene &scene)
{
    int xRes = scene.camera.xRes();
    int yRes = scene.camera.yRes();
    setRes(xRes, yRes);
    
	//clear m_rgbaBuffer
    m_rgbaBuffer.reset(Math::Color4f(1.0,1,1,1.0));
	//setup progress reporting using Platform::Progress
    
    Platform::Progress progress = Platform::Progress("Raytracing Image", xRes*yRes);
	//for each pixel generate a camera ray
    
    std::cout << "Emitting Photons..." << std::endl;
    std::vector<EmittedPhoton> emittedPhotons;
    for (PhotonSource *source: scene.photonSources)
    {
        source->emitPhotons(emittedPhotons, scene);
    }
    
    PhotonMap photonMap(1024*1024*1024);
    PhotonMap specularPhotonMap(1024*1024*1024);
    std::cout << "Scattering Photons..." << std::endl;
    for (size_t i=0; i<emittedPhotons.size(); i++)
    {
        scene.photonScattering(emittedPhotons[i], photonMap, specularPhotonMap);
    }
    photonMap.balance();
    specularPhotonMap.balance();
    
    for (int i=0; i < xRes; i++) {
        for (int j=0; j<yRes; j++) {
            Ray r = Ray();
            scene.camera.generateRay(r, i, j);
            Math::Vec3f col = recursiveRender(r, photonMap, specularPhotonMap, scene);
            m_rgbaBuffer(i, j) = Math::Vec4f(col.x, col.y, col.z, 1.0);
        }
        progress.step(yRes);
    }
	
	//Copy the final rendering to the texture
    glBindTexture(GL_TEXTURE_2D, m_fbo.colorTextureID(0));
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_fbo.width(), m_fbo.height(), GL_RGBA, GL_FLOAT, &m_rgbaBuffer(0,0));
    glBindTexture(GL_TEXTURE_2D, 0);    //Render to Screen
	m_fbo.blitFramebuffer(FBO_COLOR0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    m_fbo.displayAlphaAsFullScreenTexture(FBO_COLOR0);

}

Math::Vec3f
PhotonMapper::recursiveRender(Ray &r,
                              PhotonMap &photonMap,
                              PhotonMap &specularPhotonMap,
                              const Scene &scene) const
{
    Shape *s_hit = scene.intersect(r);
    if (s_hit != NULL) {
        s_hit->fillHitInfo(r);
        Math::Vec3f  col = s_hit->surfaceShader->shade(this, r.hit, photonMap, specularPhotonMap, scene);
        if (s_hit->areaLight()) {
            // TODO
            col = Math::Vec3f(1.0,1.0, 1.0);
        }
        return col;
    }
    return Math::Vec3f(0,0,0);
}