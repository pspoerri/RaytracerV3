//
//  OctreeNode.cpp
//  ShapeModelling
//
//  Created by Pascal Spörri on 3/17/13.
//
//

#include "OctreeNode.h"

OctreeNode::OctreeNode(OctreeNode *root, const Vec3d &vmin, const Vec3d &vmax, int depth, int maxdepth):
root(root),
vmin(vmin),
vmax(vmax),
vmid(vmin*0.5+vmax*0.5),
diag2((vmax-vmin).length()),
diag(sqrt(diag2)),
maxdepth(maxdepth),
depth(depth)
{
    _children.resize(8, 0);
}

OctreeNode::~OctreeNode() {
    for (OctreeNode *n: _children) {
        delete n;
    }
}

const std::vector<VolumetricPhoton>&
OctreeNode::objects() const
{
    return _objects;
}

inline std::pair<Vec3d, Vec3d> OctreeNode::computeChildBound(int i) {
    //    double dmax = std::numeric_limits<double>::max();
    //    double dmin = std::numeric_limits<double>::min();
    Vec3d lower;
    Vec3d upper;
    
    lower.x = (i & 4) ? vmid.x : vmin.x;
    upper.x = (i & 4) ? vmax.x : vmid.x;
    
    lower.y = (i & 2) ? vmid.y : vmin.y;
    upper.y = (i & 2) ? vmax.y : vmid.y;
    
    lower.z = (i & 1) ? vmid.z : vmin.z;
    upper.z = (i & 1) ? vmax.z : vmid.z;
    
    return std::pair<Vec3d, Vec3d>(lower, upper);
}

inline int OctreeNode::insidechildNode(const Vec3d &p) const {
    return (p.x > vmid.x ? 4 : 0)
    + (p.y > vmid.y ? 2 : 0)
    + (p.z > vmid.z ? 1 : 0);
}


void
OctreeNode::add(const VolumetricPhoton& photon)
{
    // IndexType loc, const Vector3 &vertice, double radius
    const Vec3d& vertice = photon.position;
    double radius = photon.radius;
    /*:: Possibly add data item to current octree node ::*/
    if (depth >= maxdepth || diag2 < radius ) {
        //    if (depth == maxdepth - 1) {
        _objects.push_back(photon);
        return;
    }
    
    /*:: Otherwise add data item to octree children ::*/
    
    // Determine which children overlap
    
    Vec3d verticeMin(vertice.x-radius, vertice.y-radius, vertice.z-radius);
    Vec3d verticeMax(vertice.x+radius, vertice.y+radius, vertice.z+radius);
    const bool x[2] = {verticeMin.x <= vmid.x,
                 verticeMax.x >  vmid.x};
    const bool y[2] = {verticeMin.y <= vmid.y,
                 verticeMax.y >  vmid.y};
    const bool z[2] = {verticeMin.z <= vmid.z,
                 verticeMax.z >  vmid.z};
    bool over[8];
    over[0] = x[0] & y[0] & z[0];
    over[1] = x[0] & y[0] & z[1];
    over[2] = x[0] & y[1] & z[0];
    over[3] = x[0] & y[1] & z[1];
    over[4] = x[1] & y[0] & z[0];
    over[5] = x[1] & y[0] & z[1];
    over[6] = x[1] & y[1] & z[0];
    over[7] = x[1] & y[1] & z[1];
    
    for (int child = 0; child < 8; ++child) {
        if (!over[child])
            continue;
        // Allocate children if needed and continue traversal
        if (!children(child)) {
            std::pair<Vec3d, Vec3d> bounds = computeChildBound(child);
//            double childlength = (bounds.first - bounds.second).squaredNorm();
            _children[child] = new OctreeNode(this, bounds.first, bounds.second, depth+1, maxdepth);
        }
//        if (_children[child]->inside, <#double radius#>
        _children[child]->add(photon);
    }
}

bool
OctreeNode::inside(const Vec3d &p, double radius) const
{
//    double dist = (p-vmid).norm();
//    if (diag/2.0 < dist-radius || diag/2.0 < radius) {
//        return true;
//    }
    double x = p.x;
    double y = p.y;
    double z = p.z;
    if (vmin.x - radius < x && vmin.y - radius < y && vmin.z - radius < z &&
        vmax.x + radius > x && vmax.y + radius > y && vmax.z + radius > z) {
        return true;
    }
    return false;
}

void
OctreeNode::nearestVertices(std::vector<VolumetricPhoton> &vertices, const Vec3d &p, double radius)
{
    for (const VolumetricPhoton& s: _objects)
    {
        const Vec3d &v = s.position;
        double r2 = radius+s.radius;
        r2 *= r2;

        double dist = (p-v).length2();
        if (dist < r2) {
            vertices.push_back(s);
        }
    }
    for (OctreeNode* o: _children) {
        if (o == NULL) {
            continue;
        }
        if (o->inside(p, radius)) {
            o->nearestVertices(vertices, p, radius);
        }
    }
}

const std::vector<OctreeNode* >&
OctreeNode::childNodes() const
{
    return _children;
}

