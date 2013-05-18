#include "Camera.h"
#include "MathGL.h"

using namespace Math;

Camera::Camera(unsigned x, unsigned y) :
	m_resolution(x, y),
	m_fovy(30),
	m_aspect(x/double(y)),
	m_height(2.0f*tanf(radians(0.5f*m_fovy))),
	m_width(m_height*m_aspect)
{
   updateCameraPos(Vec3d(0.0, 2.0f, 3.0f), Vec3d(0,0.5,0.0f), Vec3d(0.0f, 1.0f, 0.0f));
//	m_cameraToWorld = m_worldToCamera.inverse();
//    m_perspective.perspective(m_fovy, m_aspect, 0.1f, 1000.0f);
//	m_worldToNDC = m_perspective * m_worldToCamera;
//    m_NDCToWindow.viewport(m_resolution.x, m_resolution.y);
//    m_ScreenToWorld = m_NDCToWindow.inverse()*m_worldToNDC.inverse();
//    m_worldToScreen = m_NDCToWindow*m_worldToNDC;
//    update();
}


void
Camera::updateCameraPos(const Math::Vec3d &eye, const Math::Vec3d &center, const Math::Vec3d &up)
{
    m_worldToCamera.lookAt(eye, center, up);
	m_cameraToWorld = m_worldToCamera.inverse();
    m_perspective.perspective(m_fovy, m_aspect, 0.1f, 1000.0f);
	m_worldToNDC = m_perspective * m_worldToCamera;
    m_NDCToWindow.viewport(m_resolution.x, m_resolution.y);
    m_ScreenToWorld = m_NDCToWindow.inverse()*m_worldToNDC.inverse();
    m_worldToScreen = m_NDCToWindow*m_worldToNDC;
    update();
}

void
Camera::generateRay(Ray &r, double x, double y) const
{
    //TODO: Implement Camera Ray Generation Code

	//the preallocated Ray r should have a world space origin and direction
	//and as well as a region of interest (using r->tMin and r->tMax)
	//given the image space coordinates x and y.
    Math::Vec4f pixel_pos = m_ScreenToWorld*Math::Vec4f(x, y, 0.0, 1.0);
    pixel_pos /= pixel_pos.w;
    Math::Vec4f pixel_pos_max = m_ScreenToWorld*Math::Vec4f(x, y, 1.0, 1.0);
    pixel_pos_max /= pixel_pos_max.w;

    Math::Vec4f direction = pixel_pos - cameraOrigin;

    r.tMax = (pixel_pos_max-cameraOrigin).length();
    r.tMin = (pixel_pos-cameraOrigin).length();

    r.o.x = cameraOrigin.x;
    r.o.y = cameraOrigin.y;
    r.o.z = cameraOrigin.z;

    r.d.x = direction.x;
    r.d.y = direction.y;
    r.d.z = direction.z;
    r.d = r.d.normalized();
}


void
Camera::setResolution(unsigned x, unsigned y)
{
    if (m_resolution.x == x && m_resolution.y == y){
        return;
    }
	m_resolution.set(x, y);
	m_aspect = x / double(y);
	m_width = m_height*m_aspect;
	m_perspective.perspective(m_fovy, m_aspect, 0.1f, 1000.0f);
	m_worldToNDC = m_perspective * m_worldToCamera;
    m_NDCToWindow.viewport(m_resolution.x, m_resolution.y);
    m_ScreenToWorld = m_NDCToWindow.inverse()*m_worldToNDC.inverse();
    m_worldToScreen = m_NDCToWindow*m_worldToNDC;

    update();
}

void
Camera::setFOVY(double fov)
{
	m_fovy = fov;
	m_height = 2.0f*tanf(radians(m_fovy)),
	m_width = m_height*m_aspect;
    m_perspective.perspective(m_fovy, m_aspect, 0.1f, 1000.0f);
	m_worldToNDC = m_perspective * m_worldToCamera;
    update();
}

void
Camera::setWorldToCamera(const Mat44d & w2c)
{
	m_worldToCamera = w2c;
	m_cameraToWorld = m_worldToCamera.inverse();
	
	m_worldToNDC = m_perspective * m_worldToCamera;

    update();
}

void
Camera::setCameraToWorld(const Mat44d & c2w)
{
	m_cameraToWorld = c2w;
	m_worldToCamera = m_cameraToWorld.inverse();

	m_worldToNDC = m_perspective * m_worldToCamera;

    update();
}

void
Camera::renderGL() const
{
    // Set perspective projection
    glMatrixMode(GL_PROJECTION);
	glLoadMatrix(m_perspective);
    
    // Place the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrix(m_worldToCamera);
}


void
Camera::update() {
    m_ScreenToWorld = m_worldToNDC.inverse()*m_NDCToWindow.inverse();
    m_worldToScreen = m_NDCToWindow*m_worldToNDC;
    cameraOrigin = m_cameraToWorld*Math::Vec3d(0.0, 0.0, 0.0);
}

