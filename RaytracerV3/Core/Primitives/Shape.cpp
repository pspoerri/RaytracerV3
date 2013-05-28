//
//  Shape.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/16/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "Shape.h"

Shape::Shape(SurfaceShader* surfaceShader):
    surfaceShader(surfaceShader)
{
    // Do nothing
}

Shape::~Shape()
{
    // Do nothing
}


bool
Shape::intersects(Ray &r) const
{
    return intersect(r);
}

void
Shape::fillHitInfo(Ray &r) const
{
    
}

void
Shape::renderGL(bool wireframe) const
{
    
}

bool
Shape::areaLight() const 
{
    return false;
}