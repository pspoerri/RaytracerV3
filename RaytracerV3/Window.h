//
//  Window.h
//  RaytracerV3
//
//  Created by Pascal Spörri on 4/23/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

#ifndef __RaytracerV3__Window__
#define __RaytracerV3__Window__
#include "platform_includes.h"
namespace Main {
    
    class Window
    {
        uint height;
        uint width;
        bool initialized;
    public:
        Window(uint width=1024, uint height=768);
        void mainLoop();
        int run();
    };

};
#endif /* defined(__RaytracerV3__Window__) */
