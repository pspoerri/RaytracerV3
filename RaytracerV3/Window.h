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
#include "Scene.h"
#include "SceneLoader.h"
namespace Main {

    enum RenderMode {
        RENDER_GL,
        RENDER_RAYTRACE
    };
    
    class Window
    {
        uint height;
        uint width;
        bool initialized;
        bool render;
        Scene scene;
        SceneLoader sceneLoader;
        int mouseX;
        int mouseY;
        
        RenderMode renderMode;
    public:
        Window(uint width=1024, uint height=768);
        void mainLoop();
        void updateWindowInformation();
        void getKeyboardInput(double dt);
        int run();
        
        void display();
        
        void updateScreenSize();
        
        void rotate(int dx, int dy);
        void twist(int dx, int dy);
        void pan(int dx, int dy, int dz);
        void handle_mouse();
        void handle_keyboardInteraction();
    };

};
#endif /* defined(__RaytracerV3__Window__) */
