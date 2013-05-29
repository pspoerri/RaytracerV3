//
//  Octree.cpp
//  ShapeModelling
//
//  Created by Pascal Spörri on 3/17/13.
//
//

#include "Octree.h"

Octree::Octree(int maxDepth,
               const Vec3d& bbox_min,
               const Vec3d& bbox_max):
    maxDepth(maxDepth),
    diagonal((bbox_max-bbox_min).length()),
    _bbox_min(bbox_min),
    _bbox_max(bbox_max),
    root(new OctreeNode(NULL, bbox_min, bbox_max, 0, maxDepth))
{
}

Octree::~Octree()
{
    std::cerr << "Octree::Deleting Octree" << std::endl;
    delete root;
}

// Warning: We are degenerating the tree here. This function should
// be used with care... 
void
Octree::add(const VolumetricPhoton& photon)
{
    const Vec3d& p = photon.position;
    if (p.x > _bbox_max.x || p.x < _bbox_min.x
        || p.y > _bbox_max.y || p.y < _bbox_min.y
        || p.z > _bbox_max.z || p.z < _bbox_min.z) {
        std::cerr << "Warning: Point out of bounds, won't insert it here..." << std::endl;
        return;
    }
    root->add(photon);
}

//void
//Octree::nearestVertices(std::vector<std::pair<IndexType, Vector3> > &vertices, const Vector3 &p, double radius) const {
//    if (root == NULL) {
//        std::cerr << "Octree::nearestVertices: Octree not initialized" << std::endl;
//    }
//    root->nearestVertices(vertices, p, radius);
//}
//
//void
//Octree::nearestVerticesIDX(std::vector<IndexType> &vertices, const Vector3 &p, double radius) const
//{
//    if (root == NULL) {
//        std::cerr << "Octree::nearestVertices: Octree not initialized" << std::endl;
//    }
//    root->nearestVerticesIDX(vertices, p, radius);
////    std::vector<OctreeNode *> queue;
////    queue.push_back(root);
////    while (!queue.empty()) {
////        OctreeNode *cur = queue.back();
////        queue.pop_back();
////        
////        for (OctreeNode *o: cur->childNodes())
////        {
////            if (o == NULL) {
////                continue;
////            }
////            if (o->inside(p, radius)) {
////                if (!(o->empty())) {
////                    for (const std::pair<IndexType, Vector3>& s: o->getObjects())
////                    {
////                        Vector3 &v = s.second;
////                        if ((p-v).squaredNorm() < r2) {
////                            vertices.push_back(s.first);
////                        }
////                    }
////                    
////                }
////                
////            }
////        }
////    }
//}

//double
//Octree::findMinEps(IndexType idx, const Vector3&p, double eps) const
//{
//    std::vector<std::pair<IndexType, Vector3> > vertices;
//    nearestVertices(vertices, p, eps);
//    for (std::pair<IndexType, Vector3> &s: vertices) {
//        if (s.first == idx) {
//            continue;
//        }
//        Vector3 &v = s.second;
//        
//        double dist = (v-p).norm();
//        
//        eps = std::min<double>(eps, dist/2.0);
//    }
//    return eps;
//}
