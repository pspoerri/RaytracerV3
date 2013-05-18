//
//  PhotonSource.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 5/18/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#include "PhotonSource.h"

PhotonSource::PhotonSource(const Math::Color3f& color,
                           double power,
                           int photons):
color(color),
power(power),
photons(photons)
{
    
}

PhotonSource::~PhotonSource()
{
    
}