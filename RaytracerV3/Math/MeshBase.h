/*! \file Mesh.h
    \author Wojciech Jarosz
*/
#ifndef MATH_MESH_H
#define MATH_MESH_H

#include <Math/LimitsT.h>
#include <Math/Vec2.h>
#include <Math/Vec3.h>
#include <Math/Box.h>
#include <vector>
#include "stdint.h"

namespace Math
{

struct MeshBase
{
public:
    MeshBase() :
        vertices(0),
        normals(0),
        vertexColors(0),
        texCoords(0),
        materials(0),
        vertexIndices(0),
        materialIndices(0),
        numTris(0),
        numVertices(0),
        numMaterials(0),
        bbox()
    {
        // empty
    }
    
    virtual ~MeshBase()
    {
        // empty
    }
    
    void computeNormals();
    void flipNormals();
    void reverseOrientation();
    void calculateBBox();

    typedef Vec3<uint32_t> TupleI3;

    Vec3d* vertices;
    Vec3d* normals;
    Color3d* vertexColors;
    Vec2d* texCoords;
    std::string* materials;

    TupleI3* vertexIndices;
    uint32_t* materialIndices;

    uint32_t numTris;
    uint32_t numVertices;
    uint32_t numMaterials;
    
    Box3d bbox;
};

} // namespace Math

#endif // MATH_MESH_H
