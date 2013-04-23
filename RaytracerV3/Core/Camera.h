/*! \file Camera.h
 \brief Contains the Camera class
 \author Wojciech Jarosz
*/
#ifndef IS_CAMERA_H
#define IS_CAMERA_H

class Ray;

#include "Vec2.h"
#include "Vec3.h"
#include "Mat44.h"
#include "Ray.h"

/*!
	This class represents a camera. The camera handles mapping
	camera space to world space (and visa-versa).
*/
class Camera
{
private:
	Math::Vec2i m_resolution;
    Math::Mat44d m_worldToCamera, m_cameraToWorld,
				 m_perspective,
                 m_worldToNDC, m_NDCToWindow,
                 m_ScreenToWorld, m_worldToScreen;
    double m_fovy;
    double m_aspect;
    double m_height, m_width;

    void update();
    Math::Vec4f cameraOrigin;
public:
	Camera(unsigned resX = 640, unsigned resY = 480);
	
    void renderGL() const;
    void generateRay(Ray& r, double x, double y) const;
	
	unsigned xRes() const {return m_resolution.x;}
	unsigned yRes() const {return m_resolution.y;}
	
	void setResolution(unsigned resX, unsigned resY);
	
	double FOVY() const {return m_fovy;}
	void setFOVY(double fovy);
	
    const Math::Vec4f& getCameraOrigin() const {return cameraOrigin; }
	const Math::Mat44d& worldToCamera() const {return m_worldToCamera;}
	const Math::Mat44d& cameraToWorld() const {return m_cameraToWorld;}
	const Math::Mat44d& worldToNDC() const {return m_worldToNDC;}
	const Math::Mat44d& NDCToWindow() const {return m_NDCToWindow;}
    const Math::Mat44d& worldToScreen() const {return m_worldToScreen;}
	
    void updateCameraPos(const Math::Vec3d &eye, const Math::Vec3d &center, const Math::Vec3d &up);
	void setWorldToCamera(const Math::Mat44d & w2c);
	void setCameraToWorld(const Math::Mat44d & c2w);
    
};

#endif
