
#include "/opt/homebrew/include/raylib.h"
#include "RaylibBackend.h"
#include <stdlib.h>
#include "CDrawingContext.h"
#include "COBJMesh.h"



f4 f3ToF4(f3 a){
    f4 result = {};
    result.x = a.x;
    result.y = a.y;
    result.z = a.z;
    result.w = 1.0f;
    
    return result;
}

void drawMeshAsLines(COBJMesh* mesh, f4x4 mvp)
{
    f3* verticies = ((f3*)mesh->vertices.data);
    int* fi = ((int*)mesh->faceIndicies.data);
    f4x4 viewport = f4x4Viewport(0, 0, 1280, 800, 0.0f, 1.0f);

    for(int i= 0;  i < mesh->indexCount; i+=mesh->indexPerFace)
    {
        if(mesh->indexPerFace == 4)
        {
            int fi0 = fi[(i)]-1;
            int fi1 = fi[(i+1)]-1;
            int fi2 = fi[(i+2)]-1;
            int fi3 = fi[(i+3)]-1;
            
            f3 v0 = verticies[fi0];
            f3 v1 = verticies[fi1];
            f3 v2 = verticies[fi2];
            f3 v3 = verticies[fi3];

            f4 v0c = f4x4MulF4(mvp, f3ToF4(v0));
            f4 v1c = f4x4MulF4(mvp, f3ToF4(v1));
            f4 v2c = f4x4MulF4(mvp, f3ToF4(v2));
            f4 v3c = f4x4MulF4(mvp, f3ToF4(v3));

            // Perform perspective divide AND viewport mapping
            f4 v0m = f4ClipToScreen(v0c, viewport);
            f4 v1m = f4ClipToScreen(v1c, viewport);
            f4 v2m = f4ClipToScreen(v2c, viewport);
            f4 v3m = f4ClipToScreen(v3c, viewport);

            drawRasterLineBresham(v1m, v3m);
            drawRasterLineBresham(v3m, v2m);
            drawRasterLineBresham(v2m, v1m);

            drawRasterLineBresham(v0m, v1m);
            drawRasterLineBresham(v1m, v3m);
            drawRasterLineBresham(v3m, v0m);
        }
    }
}

void raylibWindow(int width, int height, const char* title)
{
    float tr = 0.0;
        

   // 1. Define transforms
    f4x4 scale = f3x3Tof4x4(f3x3Scale((f3){0.04f, 0.04f, 0.04f})); 
    f4x4 trans = f4x4Trans((f3){0.0f, 0.0f, 0.0f});
    
    // Corrected Model Matrix: Translation * Scale (depending on your library's order)
    f4x4 model = f4x4MulF4x4(scale, trans); 

    // Camera view matrix
    f4x4 view = f4x4Trans((f3){0.0f, 0.0f, -5.0f});

    // Projection matrix
    float aspect = (float)width / (float)height;
    f4x4 proj = f4x4Persp(degToRad(60.0f), aspect, 0.1f, 50.0f);

    // Corrected MVP: Proj * View * Model
    f4x4 mvp = f4x4MulF4x4(proj, f4x4MulF4x4(view, model));
         mvp = f4x4MulF4x4(f4x4MulF4x4(model, view), proj);
       

    COBJMesh mesh;
    COBJMeshInt(&mesh);
    readOBJ(&mesh, "/Users/connoraspinall/Developer/My Rasteriser/Old/GLUTDISPLAYCAPITAN/cube.obj");

   InitWindow(width, height, title);
    SetTargetFPS(60);

    // 1. Allocate a CPU-side pixel buffer (RGB, 3 bytes per pixel)
     unsigned char *pixels = (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char));

    // 2. Load an empty Image structure on the CPU pointing to our buffer
    Image cpuImage = {
        .data = pixels,
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };

    // 3. Load the texture onto the GPU once. 
    // This allocates the VRAM buffer we will reuse every frame.
    Texture2D gpuTexture = LoadTextureFromImage(cpuImage);

    int frameCounter = 0;

    while (!WindowShouldClose()) {
        frameCounter++;

        // 4. Generate/Modify your image on the CPU
        // For demonstration, let's create a moving gradient/noise pattern
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (y * width*3) + (x*3);
                
                int v = x ^ y % 255;  
                // Pure CPU pixel manipulation
                pixels[index + 0] = 0;
                pixels[index + 1] = 0;
                pixels[index + 2] = 0;//128; // B

                
                
            }
        }

        tmpBuffer = (char*)pixels; // Set the global tmpBuffer to point to our pixel data
        //drawRasterLine();
        //drawRasterPoint(400, 300, 100); // Draw a circle at the center of the window
       // drawRasterTriangle((PixelPoint){640, 700}, (PixelPoint){100, 100}, (PixelPoint){1180, 100}); // Draw a triangle

        drawMeshAsLines(&mesh, mvp);

        // 5. Upload the fresh CPU pixels to the existing GPU texture memory
        UpdateTexture(gpuTexture, pixels);

        // 6. Render
        BeginDrawing();
            ClearBackground(BLACK);

            // Draw our dynamically updated texture
            DrawTexture(gpuTexture, 0, 0, WHITE);

            DrawFPS(10, 10);
        EndDrawing();
    }

    // Clean up
    UnloadTexture(gpuTexture);
    free(pixels); 
    CloseWindow();
    
}