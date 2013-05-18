//
//  Scene.h
//  Image Synthesis Basecode
//
//  Created by Wojciech Jarosz on 10/29/11.
//  Copyright 2011 Student. All rights reserved.
//

#ifndef RENDER_APP_MESH_H
#define RENDER_APP_MESH_H

#include "Shape.h"

#include "Math/Vec3.h"
#include "Math/MeshBase.h"
#include "Math/BBH.h"

class Mesh : public Shape
{
private:
	Math::MeshBase * m_mesh;
	Math::BBH m_bbh;
    int m_maxDepth;
    int m_maxObjects;
	SurfaceShader * m_shader;
	
public:
	
	Mesh(SurfaceShader * surfaceShader,
		 Math::MeshBase * mesh,
		 int maxDepth = 64, int maxObjects = 1);
	
	void renderGL() const;
	
    bool intersect(Ray * r) const;
    
    bool intersect(Ray &r) const
    {
        return intersect(&r);
    }
    
    void fillHitInfo(Ray * r) const;
    void fillHitInfo(Ray & r) const
    {
        fillHitInfo(&r);
    }
};

#endif // RENDER_APP_MESH_H