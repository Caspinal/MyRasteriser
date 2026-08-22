
#include "/opt/homebrew/include/raylib.h"
#include "RaylibBackend.h"
#include <stdlib.h>
#include "CDrawingContext.h"

void raylibWindow(int width, int height, const char* title)
{
   
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
        drawRasterLine();
        drawRasterPoint(400, 300, 100); // Draw a circle at the center of the window

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