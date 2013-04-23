//
//  main.cpp
//  RaytracerV3
//
//  Created by Pascal Spörri on 4/23/13.
//  Copyright (c) 2013 Pascal Spörri. All rights reserved.
//
#include "platform_includes.h"

#include <iostream>

int main(int argc, const char * argv[])
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwOpenWindow(640, 480, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        return -1;
    
    /* Loop until the user closes the window */
    while (glfwGetWindowParam(GLFW_OPENED))
    {
        /* Render here */
        
        /* Swap front and back buffers and process events */
        glfwSwapBuffers();
    }
    
    // blubb
    
    return 0;
}

