/*! \file Mesh.cpp
    \author Wojciech Jarosz
*/
#if HAVE_CONFIG_H
#  include <config.h>
#endif // HAVE_CONFIG_H

#include "MeshBase.h"
#include "Obj.h"
#include <string.h>
#include <stdlib.h>
#include "stdint.h"
#include <stdexcept>

#ifdef _WIN32
#define isnan _isnan
#define isinf(f) (!_finite((f)))
#endif

namespace Math
{	

using namespace std;


void
MeshBase::computeNormals()
{
    int* faceCounts = new int[numVertices];
    memset(faceCounts, 0, sizeof(int) * numVertices);
    for (size_t i = 0; i < numTris; i++)
    {
        // count number of times vertices are used
        faceCounts[vertexIndices[i].x]++;
        faceCounts[vertexIndices[i].y]++;
        faceCounts[vertexIndices[i].z]++;
    }

    // allocate space for vertex face lists
    int** vertexFaces = new int*[numVertices];
    memset(vertexFaces, 0, sizeof(int*) * numVertices);
    for (size_t i = 0; i < numVertices; i++)
    {
        vertexFaces[i] = new int[faceCounts[i]+1];
        vertexFaces[i][0] = faceCounts[i];
    }

    // fill vertex face lists
    for (size_t i = 0; i < numTris; i++)
    {
        vertexFaces[vertexIndices[i].x][faceCounts[vertexIndices[i].x]--] = i;
        vertexFaces[vertexIndices[i].y][faceCounts[vertexIndices[i].y]--] = i;
        vertexFaces[vertexIndices[i].z][faceCounts[vertexIndices[i].z]--] = i;
    }

    delete [] faceCounts;

    Vec3d* faceNormals = new Vec3d[numTris];
    for (size_t i = 0; i < numTris; i++)
    {
        // compute face normal
        Vec3d e1 = vertices[vertexIndices[i].y] -
                  vertices[vertexIndices[i].x];
        Vec3d e2 = vertices[vertexIndices[i].z] -
                  vertices[vertexIndices[i].x];
        faceNormals[i] = cross(e1,e2);
        if (faceNormals[i].length() == 0)
        {
			std::cerr << "bad normal" << std::endl;
        }
    }

    // we assume normals array has been pre-allocated to hold
    // one normal per vertex
    for (size_t i = 0; i < numVertices; i++)
    {
        // compute average normal
        Vec3d n(0.0f);
        for (int j = 1; j <= vertexFaces[i][0]; j++)
            n += faceNormals[vertexFaces[i][j]];

        n.normalize();
        normals[i] = n;

        if (isnan(n[0]) || isnan(n[1]) || isnan(n[2]))
            normals[i] = Vec3d(1.0f, 0.0f, 0.0f);
        else
            normals[i] = n;
    }
    
    delete [] faceNormals;
    
    // cleamup
    for (size_t i = 0; i < numVertices; i++)
    {
        if (vertexFaces[i])
            delete [] vertexFaces[i];
    }
    
    delete [] vertexFaces;
}


void
MeshBase::flipNormals()
{
	if (!normals)
		return;

    for (size_t i = 0; i < numVertices; ++i)
        normals[i] = -normals[i];
}


void
MeshBase::reverseOrientation()
{
    flipNormals();
    
    for (size_t i = 0; i < numTris; ++i)
        std::swap(vertexIndices[i].x, vertexIndices[i].z);
}


void
MeshBase::calculateBBox()
{
    // calculate min and max corner
	bbox.makeEmpty();
    for (size_t i = 0; i < numVertices; ++i)
		bbox.enclose(vertices[i]);
}

} // namespace Mesh
