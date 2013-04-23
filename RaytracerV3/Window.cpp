//
//  Window.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 4/23/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//

// Parts copied from http://www.glfw.org/documentation.html

#include "Window.h"

using namespace Main;

Window::Window(uint width, uint height):
    width(width),
    height(height)
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
        glfwSwapBuffers();
    }
    
    return 0;
}

void
Window::mainLoop()
{
    
}