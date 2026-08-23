//
//  COBJMesh.h
//  GLUTDISPLAYCAPITAN
//
//  Created by Connor  on 08/01/2026.
//  Copyright © 2026 Connor. All rights reserved.
//

#ifndef COBJMesh_h
#define COBJMesh_h

#include <stdio.h>
#include "CArray.h"
#include "CLMath.h"

typedef struct COBJMesh COBJMesh;

struct COBJMesh
{
    CArray vertices;
    CArray faceIndicies;
    // CArray faceNormals;
    //CArray faceTextureCoordinates;
    
    int indexPerFace;
    int vertexCount;
    int indexCount;
};

void COBJMeshInt(COBJMesh* mesh);
int readOBJ(COBJMesh* mesh, const char *filename);
void COBJMeshDraw(COBJMesh* mesh, f4x4 model);

#endif /* COBJMesh_h */
