
#include "CLMath.h"
#include <stdbool.h>
#include "CPixelColour.h"

typedef enum  {
    CDrawingContextBlendMode_NONE,
    CDrawingContextBlendMode_ALPHA,
    CDrawingContextBlendMode_ADDITIVE,
    CDrawingContextBlendMode_MULTIPLY
} CDrawingContextBlendMode;

typedef struct {
    int x;
    int y;
} PixelPoint;

typedef struct 
{
    f4 pos;
    f3 normal;
    f2 texCoord;
    
    CPixelColour col;
} Vertex;


char* tmpBuffer;
float* tmpDepthBuffer;

typedef struct {
    int width;
    int height;
    void* colourRenderTarget;
    void* depthRenderTarget;
    void* stencilRenderTarget;

   // PixelColour fillColour; 
   // PixelColour strokeColour;
    

    CDrawingContextBlendMode blendMode;
    
} CDrawingContext;

inline CDrawingContext getCurrentThreadContext();

void drawRasterLine();
void drawRasterPoint(int xc, int yc, int r);

void drawRasterLineBresham(f4 a, f4 b);
void DrawQuad(Vertex* v, f4x4 viewport);