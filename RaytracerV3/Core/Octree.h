//
//  Octree.h
//  ShapeModelling
//
//  Created by Pascal Spörri on 3/17/13.
//
//

#ifndef __ShapeModelling__Octree__
#define __ShapeModelling__Octree__

#ifndef OCTREEMAXDEPTH
#define OCTREEMAXDEPTH 10
#endif

#include "Math/Vec3.h"
#include "OctreeNode.h"
#include "PhotonSource.h"
#include <vector>
using namespace Math;
class Octree
{
public:
    Octree(int maxDepth,
           const Vec3d& bbox_min,
           const Vec3d& bbox_max);
    
    ~Octree();
    void init(const Vec3d& bbox_min, const Vec3d& bbox_max );
    
    const int maxDepth;
    
    void add(const VolumetricPhoton &photon);
    
private:
    const double diagonal;
    const Vec3d _bbox_min;
    const Vec3d _bbox_max;

    OctreeNode *root;
    

public:
    const Vec3d& getBBoxMin() const
    {
        return _bbox_min;
    }
    const Vec3d& getBBoxMax() const
    {
        return _bbox_max;
    }
    double getDiagonal() const
    {
        return diagonal;
    }

//    double findMinEps(IndexType idx, const Vector3& p, double starteps) const;
};

#endif /* defined(__ShapeModelling__Octree__) */
