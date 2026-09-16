//
//  COBJMesh.c
//  GLUTDISPLAYCAPITAN
//
//  Created by Connor  on 08/01/2026.
//  Copyright © 2026 Connor. All rights reserved.
//

#include "COBJMesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "CDrawingContext.h"


void COBJMeshInt(COBJMesh* mesh)
{
    CArrayInit(&mesh->vertices, sizeof(f3), 1);
    CArrayInit(&mesh->faceNormals, sizeof(f3), 1);
    CArrayInit(&mesh->faceTextureCoordinates, sizeof(f2), 1);

    CArrayInit(&mesh->faceIndicies, sizeof(int), 1);
    CArrayInit(&mesh->faceNormalIndicies, sizeof(int), 1);
      CArrayInit(&mesh->faceTextureCoordinatesIndicies, sizeof(int), 1);

    mesh->indexPerFace = 4;
    mesh->indexCount = 0;
    mesh->vertexCount = 0;
    
}

void COBJMeshAddVertex(COBJMesh* mesh ,f3 vertex)
{
    int index = mesh->vertexCount;
    int count = mesh->vertices.currentItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->vertices, count+1);
    }
    
    f3* verticies = ((f3*)mesh->vertices.data);
    verticies[index] = vertex;
    
    mesh->vertexCount++;
    mesh->vertices.currentItemCount++;
}

void COBJMeshAddNormal(COBJMesh* mesh ,f3 normal)
{
    int index = mesh->faceNormals.currentItemCount;
    int count = mesh->faceNormals.maxItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->faceNormals, count+1);
    }
    
    f3* faceNormals = ((f3*)mesh->faceNormals.data);
    faceNormals[index] = normal;

    mesh->faceNormals.currentItemCount++;
}

void COBJMeshAddTexCoord(COBJMesh* mesh ,f2 texCoord)
{
    int index = mesh->faceTextureCoordinates.currentItemCount;
    int count = mesh->faceTextureCoordinates.maxItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->faceTextureCoordinates, count+1);
    }
    
    f2* texCoords = ((f3*)mesh->faceTextureCoordinates.data);
    texCoords[index] = texCoord;
    
    mesh->faceTextureCoordinates.currentItemCount++;
}



void COBJMeshAddIndex(COBJMesh* mesh ,int faceIndex)
{
    int index = mesh->indexCount;
    int count = mesh->faceIndicies.currentItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->faceIndicies, count+1);
    }
    
    int* indexes = ((int*)mesh->faceIndicies.data);
    indexes[index] = faceIndex;
    
    mesh->indexCount++;
    mesh->faceIndicies.currentItemCount++;
}

void COBJMeshAddTexIndex(COBJMesh* mesh ,int texIndex)
{
    int index = mesh->faceTextureCoordinatesIndicies.currentItemCount;
    int count = mesh->faceTextureCoordinatesIndicies.maxItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->faceTextureCoordinatesIndicies, count+1);
    }
    
    int* indexes = ((int*)mesh->faceTextureCoordinatesIndicies.data);
    indexes[index] = texIndex;
    
    mesh->faceTextureCoordinatesIndicies.currentItemCount++;
}

void COBJMeshAddNormalIndex(COBJMesh* mesh ,int texIndex)
{
    int index = mesh->faceNormalIndicies.currentItemCount;
    int count = mesh->faceNormalIndicies.maxItemCount;
    
    if( (index+1) > count) {
        CArrayResize(&mesh->faceNormalIndicies, count+1);
    }
    
    int* indexes = ((int*)mesh->faceNormalIndicies.data);
    indexes[index] = texIndex;
    
    mesh->faceNormalIndicies.currentItemCount++;
}

int readOBJ(COBJMesh* mesh, const char *filename) {
    
    FILE *file = fopen(filename, "r");
    
    float ll = 0;
    
    if( file)
    {
        const size_t buffSize = 10;
        size_t start = 0;
        
        char chars[buffSize];
        while (fgets(&chars[0], buffSize, file) != NULL) {
            char* newLine = strchr(&chars[0], '\n');
            if(newLine)
            {
                
                size_t end = ftell(file);
                size_t length = end - start;
                
                char fullNewLine[length+1];
                
                fseek(file, -(length), SEEK_CUR);
                fgets(&fullNewLine[0], (int)length+1, file);
                
                start = ftell(file);
                
                float x; float y; float z;
                
                if(sscanf (&fullNewLine[0],"v %f %f %f",&x, &y, &z) == 3)
                {
                    // printf("Vertex X:%f Y:%f Z:%f \n",x,y,z);
                    COBJMeshAddVertex(mesh, (f3){x,y,z});
                    
                    if(x > ll)
                    {
                        ll = x;
                    }
                }

                 
                if(sscanf (&fullNewLine[0],"vn %f %f %f",&x, &y, &z) == 3)
                {
                    // printf("Vertex X:%f Y:%f Z:%f \n",x,y,z);
                    COBJMeshAddNormal(mesh, (f3){x,y,z});
                }

                if(sscanf (&fullNewLine[0],"vt %f %f",&x, &y) == 2)
                {
                    // printf("Vertex X:%f Y:%f Z:%f \n",x,y,z);
                    COBJMeshAddTexCoord(mesh, (f2){x,y});
                }
                
                int a0,a1,a2 ,b0,b1,b2, c0,c1,c2, d0,d1,d2;
                if(sscanf (&fullNewLine[0],"f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i",&a0,&a1,&a2 ,&b0,&b1,&b2, &c0,&c1,&c2, &d0,&d1,&d2) == 12)
                {
                    //printf("Face %i %i %i %i \n",a0,b0,c0,d0);
                    COBJMeshAddIndex(mesh,a0);
                     COBJMeshAddTexIndex(mesh,a1);
                    COBJMeshAddNormalIndex(mesh,a2);
                   
                    COBJMeshAddIndex(mesh,b0);
                     COBJMeshAddTexIndex(mesh,b1);
                    COBJMeshAddNormalIndex(mesh,b2);

                    COBJMeshAddIndex(mesh,c0);
                     COBJMeshAddTexIndex(mesh,c1);
                    COBJMeshAddNormalIndex(mesh,c2);
                   
                    COBJMeshAddIndex(mesh,d0);
                     COBJMeshAddTexIndex(mesh,d1);
                    COBJMeshAddNormalIndex(mesh,d2);
                    
                    mesh->indexPerFace = 4;
                }else if(sscanf (&fullNewLine[0],"f %i/%i/%i %i/%i/%i %i/%i/%i ",&a0,&a1,&a2 ,&b0,&b1,&b2, &c0,&c1,&c2) == 9)
                {
                    // printf("Face %i %i %i \n",a0,b0,c0);
                    COBJMeshAddIndex(mesh,a0);
                    COBJMeshAddIndex(mesh,b0);
                    COBJMeshAddIndex(mesh,c0);
                    
                    mesh->indexPerFace = 3;
                } else if(sscanf (&fullNewLine[0],"f %i %i %i ",&a0,&b0,&c0) == 3)
                {
                    // printf("Face %i %i %i \n",a0,b0,c0);
                    COBJMeshAddIndex(mesh,a0);
                    COBJMeshAddIndex(mesh,b0);
                    COBJMeshAddIndex(mesh,c0);
                    
                    mesh->indexPerFace = 3;
                }
            }
        };
        fclose(file);
    }
    
    
    //    f3* verticies = ((f3*)mesh->vertices.data);
    //
    //
    //    for(int i= 0;  i < mesh->vertexCount; i++)
    //    {
    //        f3 v = verticies[i];
    //        printf("f3 X:%f Y:%f Z:%f \n",v.x,v.y,v.z);
    //    }
    //
    //    printf("faces ");
    //    int* fi = ((int*)mesh->faceIndicies.data);
    //    for(int i= 0;  i < mesh->indexCount; i++)
    //    {
    //        int findex = fi[i];
    //        printf("%i ",findex);
    //    }
    //    printf("\n");
    
    
    return 0;
}

