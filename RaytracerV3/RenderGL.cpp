//
//  RenderGL.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "RenderGL.h"
#include "Shape.h"

RenderGL::RenderGL():
    m_fbo(FrameBuffer(GL_TEXTURE_2D, 512, 512, -1, GL_RGBA32F_ARB, 1, 1, 0, "OpenGL FBO"))
{
    m_fbo.checkFramebufferStatus(1);
}

RenderGL::~RenderGL()
{
    // Do nothing
}

void
RenderGL::render(Scene &scene)
{
    render(scene, false);
}
void
RenderGL::render(Scene &scene, bool wireframe)
{
    m_fbo.resizeExistingFBO(scene.camera.xRes(), scene.camera.yRes());
    m_fbo.bindBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene.camera.renderGL();
    
    for (const Shape *s: scene.shapes)
    {
        s->renderGL(wireframe);
    }
    m_fbo.unbindBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_fbo.displayAlphaAsFullScreenTexture(FBO_COLOR0);
}

