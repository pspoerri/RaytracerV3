//
//  Sphere.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Sphere__
#define __RaytracerV3__Sphere__

#include "Math/Vec3.h"
#include "Shape.h"
class Sphere : public Shape
{
public:
    
	Sphere(SurfaceShader * surfaceShader = 0,
		   const Math::Vec3d & loc = Math::Vec3d(0.0f), double rad = 1.0f);
    const Math::Vec3d location;
	const double radius;
	void renderGL(bool wireframe=false) const;
	
    bool intersect(Ray & ray) const;
    void fillHitInfo(Ray &ray) const;
	
};
#endif /* defined(__RaytracerV3__Sphere__) */
