
#include "CLMath.h"

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


char* tmpBuffer;

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
void drawRasterTriangle(PixelPoint a, PixelPoint b, PixelPoint c);
void drawRasterLineBresham(f4 a, f4 b);

