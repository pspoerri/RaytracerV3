//
//  OctreeNode.h
//  ShapeModelling
//
//  Created by Pascal Spörri on 3/17/13.
//
//

#ifndef __ShapeModelling__OctreeNode__
#define __ShapeModelling__OctreeNode__

// Code copied and adapted from my computer graphics class exercise :)

class OctreeNode;
#include "Octree.h"
#include <iostream>
#include <vector>
#include <utility>
#include "types.h"
#include "PhotonSource.h"

using namespace Math;
class OctreeNode
{
public: 
    OctreeNode(OctreeNode* root, const Vec3d& vmin, const Vec3d& vmax, int depth, int maxdepth=OCTREEMAXDEPTH);
    ~OctreeNode();
    const OctreeNode* root;
    const Vec3d vmin;
    const Vec3d vmax;
    const Vec3d vmid;
    const double diag2;
    const double diag;
    const int depth;
    const int maxdepth;
    
    const std::vector<VolumetricPhoton>& objects() const;
    void add(const VolumetricPhoton& photon);
        
    void nearestVertices(std::vector<VolumetricPhoton >& photons, const Vec3d& p, double radius);

private:

    std::vector<VolumetricPhoton> _objects;
    std::vector<OctreeNode* > _children;
    
public:

    const OctreeNode* children(int i) const {
        return _children[i];
    }
    
    std::pair<Vec3d, Vec3d> computeChildBound(int i);
    bool inside(const Vec3d& p, double radius) const;
    int insidechildNode(const Vec3d& p) const;

    const std::vector<OctreeNode* >& childNodes() const;
    const std::vector<VolumetricPhoton >& getObjects() const;

    bool empty() const {
        return (_objects.size() == 0);
    }
    
//    bool intersectRay(const Ray& ray) const;

};

#endif /* defined(__ShapeModelling__OctreeNode__) */
