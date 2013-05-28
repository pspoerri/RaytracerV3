//
//  Window.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 4/23/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

// Parts copied from http://www.glfw.org/documentation.html
// and from the ImageSynthesis course at ETH Zürich taught by
// Wojciech Jarosz

#include "Window.h"
#include "Math/Core.h"
#include "RenderGL.h"
#include "PhotonMapper.h"

using namespace Main;
using namespace Math;

const double g_angleFact = 0.2f;
const double g_scaleFact = 0.0005f;

const char * renderModeNames[] =
{
	"RENDER_GL",
	"RENDER_RAYTRACE"
};


Window::Window(uint width, uint height):
    width(width),
    height(height),
    scene(),
    sceneLoader(scene),
    mouseX(0),
    mouseY(0)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        initialized = false;
        return;
    }
    
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwOpenWindow(width, height, 32, 32, 32, 24, 24, 0, GLFW_WINDOW))
//    if (!glfwOpenWindow(width, height, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
    {
        initialized = false;
        return;
    }
    
    initialized = true;
    render = true;
    renderMode = RENDER_GL;
    sceneLoader.loadScene();
    
}

int
Window::run()
{
    if (!initialized)
    {
        return -1;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Loop until the user closes the window */
    while (glfwGetWindowParam(GLFW_OPENED))
    {
        /* Render here */
        mainLoop();
        /* Swap front and back buffers and process events */

        if (render) {
            glFinish();
            glfwSwapBuffers();
            render = false;
        } else {
            glfwWaitEvents();
        }
    }
    
    return 0;
}

void
Window::mainLoop()
{
    updateScreenSize();
    handle_keyboardInteraction();
    handle_mouse();
    if (render) {
        switch (renderMode) {
            case RENDER_GL:
            {
                RenderGL renderer;
                renderer.render(scene);
                break;
            }
            case RENDER_RAYTRACE:
            {
                PhotonMapper renderer;
                renderer.render(scene);
                renderMode = RENDER_GL;
                break;
            }
            default:
                break;
                
        }
    }
}

void
Window::updateWindowInformation()
{
    GLFWvidmode return_struct;
    
    glfwGetDesktopMode( &return_struct );
    if (height != return_struct.Height && width != return_struct.Width)
    {
        height = return_struct.Height;
        width = return_struct.Width;
    }
}

void
Window::rotate(int dx, int dy)
{
    try
    {
        double xfact = -g_angleFact*dy;
        double yfact = -g_angleFact*dx;
        
        Mat44d c2w = scene.camera.cameraToWorld();
		
        Vec3d A = c2w.A();
        Vec3d B = c2w.B();
        Vec3d C = c2w.C();
		
        // construct a coordinate system from up and viewdir
        Vec3d vRight = A;
        
        // now rotate everything
        A.rotate(double(yfact*M_PI/180.0f), B);
        A.normalize();
        B.rotate(double(xfact*M_PI/180.0f), vRight);
        C = cross(A, B).normalize();
        B = cross(C, A).normalize();
        
        c2w = Mat44d(A, B, C, c2w.D());
        
        scene.camera.setCameraToWorld(c2w);
    }
    catch (const std::exception & e)
    {
		std::cout << "Error: " << e.what() << std::endl;
    }
}

void
Window::twist(int dx, int dy)
{
    try
    {
        double fact = sign(dx)*g_angleFact*sqrtf((double)(dx*dx + dy*dy));
        
        Mat44d c2w = scene.camera.cameraToWorld();
		
        Vec3d A = c2w.A();
        Vec3d B = c2w.B();
        
        // now rotate everything
        A.rotate(double(fact*M_PI/180.0f), c2w.C());
        A.normalize();
        B = cross(c2w.C(), A).normalize();
        
        c2w = Mat44d(A, B, c2w.C(), c2w.D());
        
        scene.camera.setCameraToWorld(c2w);
    }
    catch (const std::exception & e)
    {
		std::cout << "Error: " << e.what() << std::endl;
    }
}

void
Window::pan(int dx, int dy, int dz)
{
    try
    {
        Mat44d c2w = scene.camera.cameraToWorld();
        
        c2w.setD(c2w.D() - dx*g_scaleFact*c2w.A() + dy*g_scaleFact*c2w.B() - dz*g_scaleFact*c2w.C());
		
        scene.camera.setCameraToWorld(c2w);
        
    }
    catch (const std::exception & e)
    {
		std::cout << "Error: " << e.what() << std::endl;
    }
}


void
Window::handle_mouse()
{
    int x = mouseX;
    int y = mouseY;
    glfwGetMousePos(&mouseX, &mouseY);
    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_1))
    {
        rotate(mouseX-x, mouseY-y);
        render = true;
    }
    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_2))
    {
        pan(0,0,2*(mouseX-x+mouseY-y));
        render = true;
    }
    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_3))
    {
        pan(mouseX-x ,mouseY-y, 0);
        render = true;
    }
	
}

void
Window::updateScreenSize()
{
    int height, width;
    glfwGetWindowSize(&width, &height);
    scene.camera.setResolution(width, height);
}

void
Window::handle_keyboardInteraction()
{
    if (glfwGetKey(GLFW_KEY_UP)) {
        pan(0,0,100);
        render = true;
    }
    if (glfwGetKey(GLFW_KEY_DOWN)) {
        pan(0,0,-100);
        render = true;
    }
    if (glfwGetKey(GLFW_KEY_LEFT)) {
        pan(100,0,0);
        render = true;
    }
    if (glfwGetKey(GLFW_KEY_RIGHT)) {
        pan(-100,0,0);
        render = true;
    }
    if (glfwGetKey('g') || glfwGetKey('G')) {
        renderMode = RENDER_GL;
        render =true;
    }
    if (glfwGetKey('t') || glfwGetKey('T')) {
        if (renderMode != RENDER_RAYTRACE)
            render = true;
        renderMode = RENDER_RAYTRACE;
    }
    if (glfwGetKey('r') || glfwGetKey('R')) {
        render = true;
    }
}
