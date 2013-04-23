//
//  main.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 4/23/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//
#include "platform_includes.h"
#include "Window.h"
#include <iostream>

int main(int argc, const char * argv[])
{
    using namespace Main;
    Window w(1024, 768);
    return w.run();
}

