//
//  Mesh.cpp
//  ImageSynthesisFramework
//
//  Created by wjarosz on 3/13/12.
//  Copyright (c) 2012. All rights reserved.
//

#include "Mesh.h"
#include <iostream>
#include "Math/MeshBase.h"
#include "Math/MathGL.h"
#include "Math/Core.h"
#include "Math/LineAlgo.h"

using namespace Math;
using std::vector;

namespace
{
	
    class Proc
    {
    public:
        Proc(const MeshBase * mesh, int maxDepth, int maxObjects) :
		maxDepth(maxDepth),
		maxObjects(maxObjects)
        {
            if (!mesh)
                return;
            
            // Compute bounding boxes of all triangles
            m_bboxes.reserve(mesh->numTris);
            for (unsigned i = 0; i < mesh->numTris; ++i)
            {
                Box3d tempBox;
                tempBox.enclose(mesh->vertices[mesh->vertexIndices[i].x]);
                tempBox.enclose(mesh->vertices[mesh->vertexIndices[i].y]);
                tempBox.enclose(mesh->vertices[mesh->vertexIndices[i].z]);
                m_bboxes.push_back(tempBox);
            }
        }
        
        inline unsigned nObjs() const {return m_bboxes.size();}
        inline const Box3d & bbox(unsigned i) {return m_bboxes[i];}
        
        int maxDepth;
        int maxObjects;
        
    private:
        vector<Box3d> m_bboxes;
    };
	
	
    bool
    intersectTriangle(Ray * r, MeshBase * mesh, unsigned int index)
    {
        if (Math::intersect(r->o, r->d,
                            mesh->vertices[mesh->vertexIndices[index].x],
                            mesh->vertices[mesh->vertexIndices[index].y],
                            mesh->vertices[mesh->vertexIndices[index].z],
                            r->tMin, r->tMax,
                            &r->hit.t, &r->hit.uv, &r->hit.Ng))
        {
            r->hit.N = r->hit.Ng.normalize();
            return true;
        }
        
        return false;
    }
	
} // namespace




Mesh::Mesh(SurfaceShader * ss,
		   Math::MeshBase * mesh, int maxDepth, int maxObjects) :
Shape(ss),
m_mesh(mesh),
m_maxDepth(maxDepth),
m_maxObjects(maxObjects)
{
	Proc proc(m_mesh, m_maxDepth, m_maxObjects);
	
	BBH::BuildStats stats;
	m_bbh.buildTree(proc, stats);
	stats.printStats();
}

void
Mesh::renderGL() const
{
	if (!m_mesh)
		return;
    
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < m_mesh->numTris; ++i)
	{
		glVertex(m_mesh->vertices[m_mesh->vertexIndices[i].x]);
		glVertex(m_mesh->vertices[m_mesh->vertexIndices[i].y]);
		glVertex(m_mesh->vertices[m_mesh->vertexIndices[i].z]);
	}
	glEnd();
}

bool
Mesh::intersect(Ray * r) const
{
#define MAX_TODO 64
    const BBH::Node * todo[MAX_TODO];
    int todoPos = 0;
	
    int hitIndex = -1;
    const BBH::Node *node = &m_bbh.nodes[0];
    while (node)
    {
        if (node->isLeaf())
        {
            // Check for intersections inside leaf node
            unsigned nObjects = node->nObjects();
            if (nObjects == 1)
            {
                const int index = node->oneIndex;
                if (intersectTriangle(r, m_mesh, index))
                {
					r->hit.shape = this;
                    r->tMax = r->hit.t;
                    hitIndex = index;
                }
            }
            else if (nObjects > 1)
            {
                const unsigned * indices = node->indices;
                for (unsigned i = 0; i < nObjects; ++i)
                {
                    const unsigned index = indices[i];
                    if (intersectTriangle(r, m_mesh, index))
                    {
						r->hit.shape = this;
                        r->tMax = r->hit.t;
                        hitIndex = index;
                    }
                }
            }
        }
        else
        {
            if (Math::intersects(r->o, r->d, node->bbox, r->tMin, r->tMax))
            {
                // Enqueue secondChild in todo list
                todo[todoPos] = &m_bbh.nodes[node->right];
                ++todoPos;
				
                // Advance to next child node
                ++node;
                continue;
            }
        }
		
        // Grab next node to process from todo list
        if (todoPos > 0)
        {
            --todoPos;
            node = todo[todoPos];
        }
        else
            break;
    }
	
    return (hitIndex != -1 && r->hit.shape);
}


void
Mesh::fillHitInfo(Ray * r) const
{
	r->hit.surfaceShader = surfaceShader;
    r->hit.P = r->o + r->hit.t*r->d;
    r->hit.I = r->d;
    r->hit.O = r->o;
}