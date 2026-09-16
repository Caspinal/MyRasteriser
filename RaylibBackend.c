
#include "/opt/homebrew/include/raylib.h"

#include </opt/homebrew/include/icns.h>


#include "RaylibBackend.h"
#include <stdlib.h>
#include "CDrawingContext.h"
#include "COBJMesh.h"
#include "CPixelColour.h"








void drawMesh(COBJMesh* mesh, f4x4 mvp, f4x4 viewport)
{
     f3* verticies = ((f3*)mesh->vertices.data);
    int* fi = ((int*)mesh->faceIndicies.data);

    f3* normals = ((f3*)mesh->faceNormals.data);
    int* ni = ((int*)mesh->faceNormalIndicies.data);

    f2* texCoords = ((f2*)mesh->faceTextureCoordinates.data);
    int* ti = ((int*)mesh->faceTextureCoordinatesIndicies.data);

    CPixelColour colours[8] = {
        (CPixelColour){0.0,1.0,1.0,1.0},
        (CPixelColour){0.0,0.0,1.0,1.0},
        (CPixelColour){1.0,1.0,1.0,1.0},
        (CPixelColour){1.0,0.0,1.0,1.0},

        (CPixelColour){0.0,1.0,0.0,1.0},
        (CPixelColour){0.0,0.0,0.0,1.0},
        (CPixelColour){1.0,1.0,0.0,1.0},
        (CPixelColour){1.0,0.0,0.0,1.0},
    };

    Vertex VertexList[4];
   

    for(int i= 0;  i < mesh->indexCount; i+=mesh->indexPerFace)
    {
        if(mesh->indexPerFace == 4)
        {
            int fi0 = fi[(i)]-1;
            int fi1 = fi[(i+1)]-1;
            int fi2 = fi[(i+2)]-1;
            int fi3 = fi[(i+3)]-1;

            int ni0 = ni[(i)]-1;
            int ni1 = ni[(i+1)]-1;
            int ni2 = ni[(i+2)]-1;
            int ni3 = ni[(i+3)]-1;

            int ti0 = ti[(i)]-1;
            int ti1 = ti[(i+1)]-1;
            int ti2 = ti[(i+2)]-1;
            int ti3 = ti[(i+3)]-1;
            
            f3 v0 = verticies[fi0];
            f3 v1 = verticies[fi1];
            f3 v2 = verticies[fi2];
            f3 v3 = verticies[fi3];

            f4 v0c = f4x4MulF4(mvp, f3ToF4(v0));
            f4 v1c = f4x4MulF4(mvp, f3ToF4(v1));
            f4 v2c = f4x4MulF4(mvp, f3ToF4(v2));
            f4 v3c = f4x4MulF4(mvp, f3ToF4(v3));

            VertexList[0].pos = v0c;
            VertexList[1].pos = v1c;
            VertexList[2].pos = v2c;
            VertexList[3].pos = v3c;

            f3 n0 = normals[ni0];
            f3 n1 = normals[ni1];
            f3 n2 = normals[ni2];
            f3 n3 = normals[ni3];

            VertexList[0].normal = n0;
            VertexList[1].normal = n1;
            VertexList[2].normal = n2;
            VertexList[3].normal = n3;

            f2 t0 = texCoords[ti0];
            f2 t1 = texCoords[ti1];
            f2 t2 = texCoords[ti2];
            f2 t3 = texCoords[ti3];

            VertexList[0].texCoord = t0;
            VertexList[1].texCoord = t1;
            VertexList[2].texCoord = t2;
            VertexList[3].texCoord = t3;

            VertexList[0].col = colours[fi0];
            VertexList[1].col = colours[fi1];
            VertexList[2].col = colours[fi2];
            VertexList[3].col = colours[fi3];

            DrawQuad(&VertexList[0],viewport);
        }
    }
}


  icns_family_t *icnsFamily = NULL;
  icns_image_t iconImage;

int loadICNS() {
   
    FILE *file = fopen("/Users/connoraspinall/Downloads/tiger/icns/ApplicationsFolderIcon.icns", "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Read the ICNS family data from the file
    int result = icns_read_family_from_file(file, &icnsFamily);
    fclose(file);

    if (result != ICNS_STATUS_OK) {
        fprintf(stderr, "Error reading ICNS file (code %d)\n", result);
        return 1;
    }



    icns_sint32_t count = 0;
    icns_count_elements_in_family(icnsFamily, &count);

        printf("ICNS file loaded successfully. Element count: %d\n", count);
    // Loop through individual icon sub-elements inside the container
    for (int i = 0; i < count; i++) {
        icns_element_t *element = &icnsFamily->elements[i];
    
        // Print the 4-byte OSType header (e.g., 'ic07', 'ic08', 'ic10', 'PNG ')
        char typeStr[16] = {0};
        icns_type_str(element->elementType, typeStr);

        printf("  [Element %d] Type: %s, Data Size: %u bytes\n", 
               i, typeStr, element->elementSize);
    }

    icns_type_t targetType = ICNS_256x256_32BIT_ARGB_DATA; // 'ic08'
    

    // 3. Let libicns handle RLE / PNG decoding into icns_image_t
    int result2 = icns_get_image32_with_mask_from_family(icnsFamily, ICNS_128X128_32BIT_DATA, &iconImage);

    if (result2 == ICNS_STATUS_OK) {
        printf("Successfully decoded image via libicns:\n");
        printf("  Dimensions: %dx%d\n", iconImage.imageWidth, iconImage.imageHeight);
        printf("  Channels:   %d\n", iconImage.imageChannels);
        printf("  Data Size:  %d bytes\n", iconImage.imageDataSize);

        // iconImage.imageData now contains raw decoded pixel buffer (ARGB / RGBA)

        // Clean up the decoded image structure memory
       // icns_free_image(&iconImage);
    } else {
        printf("Could not decode icon type requested (code: %d). Type may not exist in this file.\n", result);
    }
}


float camZ = -5.0f;

void updateKeys() {

int key = GetKeyPressed();

// Keep reading until the internal queue is empty (returns 0)
    while (key > 0) {
        // Process the key press here
        printf("%c \n",(char)key);
        
        // Get the next key in the queue
        key = GetKeyPressed(); 
    }

}

void raylibWindow(int width, int height, const char* title)
{
    float tr = 0.0;
        

  // loadICNS();
    
       

    COBJMesh mesh;
    COBJMeshInt(&mesh);
    readOBJ(&mesh, "/Users/connoraspinall/Developer/My Rasteriser/Old/GLUTDISPLAYCAPITAN/cube.obj");

   InitWindow(width, height, title);
    SetTargetFPS(60);

    // 1. Allocate a CPU-side pixel buffer (RGB, 3 bytes per pixel)
     unsigned char* pixels = (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char));
     tmpDepthBuffer = (float *)malloc(width * height * sizeof(float));

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

        updateKeys();

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

                tmpDepthBuffer[y*width+x] = 1.0f; // Set the global tmpDepthBuffer to point to our depth data
                
            }
        }

        tmpBuffer = (char*)pixels; // Set the global tmpBuffer to point to our pixel data
        //drawRasterLine(); 
        drawRasterPoint(0, 0, 10); // Draw a circle at the center of the window
       // drawRasterTriangle((PixelPoint){640, 700}, (PixelPoint){100, 100}, (PixelPoint){1180, 100}); // Draw a triangle


       // 1. Define transforms
    f4x4 scale = f3x3Tof4x4(f3x3Scale((f3){1.0f, 1.0f, 1.0f})); 
    f4x4 trans = f4x4Trans((f3){0.0f, 0.0f, 0.0f});
   f4x4 rot = f3x3Tof4x4(f3x3Rot((f3){0.0f, 1.0f, 0.0f}, degToRad(tr)));
       
 // f4x4 model = f4x4MulF4x4(f4x4MulF4x4(scale, rot), trans);
    f4x4 model = f4x4MulF4x4(trans, f4x4MulF4x4(rot, scale));
  //f4x4 model = f4x4MulF4x4(scale, trans);

    // Camera view matrix
    float scrollSpeed = 4.0f;


    // Inside your main loop:
    camZ -= (GetMouseWheelMove() * scrollSpeed);
    camZ = fmaxf(camZ, -50.0f); // Limit how far back the camera can go
    camZ = fminf(camZ, -1.0f);  // Limit how close the camera can get
    f4x4 view = f4x4Trans((f3){0.0f, 0.0f, camZ}); // Move the camera back along the Z-axis

    // Projection matrix
    float aspect = (float)width / (float)height;
    f4x4 proj = f4x4Persp(degToRad(60.0f), aspect, 0.1f, 50.0f);
   // f4x4 ortho = f4x4Ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 50.0f);

    // Corrected MVP: Proj * View * Model
      f4x4 mvp = f4x4MulF4x4(proj, f4x4MulF4x4(view, model)); // think my thing is backwards 
       //f4x4  mvp = f4x4MulF4x4(f4x4MulF4x4(view, model), proj);

         f4x4 viewport = f4x4Viewport(0, 0, 1280, 800, 0.0f, 1.0f);


        drawMesh(&mesh, mvp, viewport);

        tr+=1.0f;

        // for (int y = 0; y < iconImage.imageHeight; y++) {
        //     for (int x = 0; x < iconImage.imageWidth; x++) {
        //         int index = (y * width*3) + (x*3);
                
        //        // int v = x ^ y % 255;  
        //         // Pure CPU pixel manipulation
        //         pixels[index + 0] = iconImage.imageData[(y * iconImage.imageWidth + x) * 4 + 0]; // R
        //         pixels[index + 1] = iconImage.imageData[(y * iconImage.imageWidth + x) * 4 + 1]; // G
        //         pixels[index + 2] = iconImage.imageData[(y * iconImage.imageWidth + x) * 4 + 2]; // B

                
                
        //     }
        // }

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